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

  Event::Event(const std::shared_ptr<Environment>& _env) : env(_env) {}
  Event::~Event() {}  

  std::shared_ptr<Event> Event::get_ptr(){
    return shared_from_this();
  }

  std::shared_ptr<Environment> Event::get_env(){
    return env;
  }  

  bool Event::is_ok() const {
    return ok;
  }

  bool Event::is_triggered() const {
    return triggered;
  }

  bool Event::is_done() const {
    return done;
  }

  void Event::set_done(){
    if(done)
      throw std::runtime_error("Event is already done!");
    done = true;
  }

  void Event::succeed(){
    if(triggered){
      throw std::runtime_error("Event is already triggered!");
    }
    ok = true;
    triggered = true;
    env->schedule(shared_from_this());
  }

  void Event::add_callback(std::function<void(std::shared_ptr<Event> &)> f,
			   std::shared_ptr<Event> parent,
			   bool check){
    callbacks.emplace_back(f, parent, check);
  }

  void Event::remove_check_callback(std::shared_ptr<Event> parent){
    /*
      The detail of this method is defined in sub-classes.
      The role of this method is to remove "check" function from
      the callbacks.
    */
    return;
  }


}
