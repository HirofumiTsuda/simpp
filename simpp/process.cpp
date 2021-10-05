#include "process.hpp"

#include <memory>
#include <functional>
#include <boost/coroutine2/coroutine.hpp>

#include "event.hpp"
#include "core.hpp"

namespace simpp{

  using coro_t = boost::coroutines2::coroutine<std::shared_ptr<Event> >;  

  Process::Process(const std::shared_ptr<Environment>& env, const std::function<void(coro_t::push_type&)> f)
    : Event(env){
      generator = std::make_unique<coro_t::pull_type>(coro_t::pull_type(f));  
    }
   

  void Process::execute(){
    std::shared_ptr<Event> event = generator->get();
    event->add_callback(
	[this](std::shared_ptr<Event> &eve){
	   this->resume(eve);
	}, shared_from_this(),false);
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
	this->ok = true;
        env->schedule(shared_from_this());
        break;
      }     
      if(res != nullptr && !res->is_done()){
	  res->add_callback([this](std::shared_ptr<Event> &eve){
			      this->resume(eve);
			    }, shared_from_this(),false);
	  break;
      }
    }
  }
}
