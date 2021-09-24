#include "event.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include <boost/coroutine2/coroutine.hpp>

#include "core.hpp"


namespace simpp{
  using coro_t = boost::coroutines2::coroutine<std::shared_ptr<Event> >;  
    std::shared_ptr<Event> get_ptr();
    bool is_ok();
    bool is_pending();

  std::shared_ptr<Event> Event::get_ptr(){
    return shared_from_this();
  }

  bool Event::is_ok(){
    return ok;
  }

  bool Event::is_pending(){
    return pending;
  }

  bool Event::is_done(){
    return done;
  }

  void Event::set_done(){
    if(done)
      throw std::runtime_error("Event is already done!");
    done = true;
  }

  void Event::succeed(){
    ok = true;
    env->schedule(shared_from_this());
  }

  void Timeout::cast_into_queue(){
    ok = true;
    env->schedule(shared_from_this(), 1, delay);
  }

  Process::Process(const std::shared_ptr<Environment>& env, const std::function<void(coro_t::push_type&)> f)
    : Event(env){
      generator = std::make_unique<coro_t::pull_type>(coro_t::pull_type(f));  
    }
   

  void Process::execute(){
    std::shared_ptr<Event> event = generator->get();
    event->callbacks.push_back([&](std::shared_ptr<Event> &eve){
				 resume(eve);
			       });
  }

  void Process::resume(std::shared_ptr<Event>& event){
    while(true){
      /*
      Check if the event is already triggered.
      If it is not yet, this is an error.
      Then, this process fails and the whole program should be shut down.
      */
      std::shared_ptr<Event> res;      
      if(*generator){
        // generator is valid
        if(event->is_ok()){
          (*generator)();	  
          res = generator->get();
        }else{
          throw std::runtime_error("Generator is invalid");
        }
      }else{
        /*
          This process has just finished. 
          Finally, this process is casted into the schedule-queue. 
        */
        env->schedule(shared_from_this());
        break;
      }     
      if(res != nullptr && !res->is_done()){
	      res->callbacks.push_back([this](std::shared_ptr<Event> &eve){
				     this->resume(eve);
				   });
	break;
      }
    }
  }
  
}
