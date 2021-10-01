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
    Event(const std::shared_ptr<Environment>& _env);
    virtual ~Event();
    // Methods
    void succeed();
    std::shared_ptr<Event> get_ptr();
    bool is_ok();
    bool is_pending();
    bool is_triggered();
    bool is_done();
    void set_done();
    std::vector<std::function<void(std::shared_ptr<Event> &)>> callbacks;  
  protected:
    bool ok=false;
    bool triggered=false;
    bool done=false;
    std::shared_ptr<Environment> env;
  }; 
}

#endif
