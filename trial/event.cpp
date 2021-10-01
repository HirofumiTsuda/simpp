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

  Event::Event(const std::shared_ptr<Environment>& _env) : env(_env) {
    ok=false;
    triggered=false;
    done=false;
  }
  Event::~Event() {}  

  std::shared_ptr<Event> Event::get_ptr(){
    return shared_from_this();
  }

  bool Event::is_ok(){
    return ok;
  }

  bool Event::is_triggered(){
    return triggered;
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
    if(triggered){
      throw std::runtime_error("Event is already triggered!");
    }
    ok = true;
    triggered = true;
    env->schedule(shared_from_this());
  }
  
}
