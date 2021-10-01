#ifndef SIM_EVENT_HPP
#define SIM_EVENT_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <boost/coroutine2/coroutine.hpp>

#include "core.hpp"

namespace simpp{
  using coro_t = boost::coroutines2::coroutine<std::shared_ptr<Event> >;
  
  class Event : public std::enable_shared_from_this<Event> {
  public:
    // Constructor
<<<<<<< HEAD
    Event(const std::shared_ptr<Environment>& _env);
    virtual ~Event();
=======
    Event(const std::shared_ptr<Environment>& _env) : env(_env) {
      ok = false;
      done = false;
      triggered = false;
    }
    virtual ~Event() {}
>>>>>>> 5e9db70bed74cf77fb7d2a8f187e9bde135e286e
    // Methods
    void succeed();
    std::shared_ptr<Event> get_ptr();
    bool is_ok();
<<<<<<< HEAD
    bool is_pending();
=======
>>>>>>> 5e9db70bed74cf77fb7d2a8f187e9bde135e286e
    bool is_triggered();
    bool is_done();
    void set_done();
    std::vector<std::function<void(std::shared_ptr<Event> &)>> callbacks;  
  protected:
<<<<<<< HEAD
    bool ok=false;
    bool triggered=false;
    bool done=false;
=======
    bool ok;
    bool triggered;
    bool done;
>>>>>>> 5e9db70bed74cf77fb7d2a8f187e9bde135e286e
    std::shared_ptr<Environment> env;
  }; 
}

#endif
