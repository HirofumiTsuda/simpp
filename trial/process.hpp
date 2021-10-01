#ifndef SIM_PROCESS_HPP
#define SIM_PROCESS_HPP

#include <memory>
#include <functional>
#include <boost/coroutine2/coroutine.hpp>

#include "event.hpp"

namespace simpp{
  
  using coro_t = boost::coroutines2::coroutine<std::shared_ptr<Event> >;
  class Environment;
  
  class Process : public Event{
  public:
    Process(const std::shared_ptr<Environment>& , const std::function<void(coro_t::push_type&)>);
    void execute();
    void resume(std::shared_ptr<Event> &);
    std::unique_ptr<coro_t::pull_type> generator;    
  private:
    std::shared_ptr<Event> target; 
  };
}

#endif
