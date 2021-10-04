#ifndef SIMPP_CORE_HPP
#define SIMPP_CORE_HPP

#include <iostream>
#include <functional>
#include <vector>
#include <queue>
#include <memory>

#include <boost/coroutine2/coroutine.hpp>

namespace simpp{

  class Event;
  class Process;
  class Timeout;
  class QueueEvent;

  using coro_t = boost::coroutines2::coroutine<std::shared_ptr<Event> >;
  
  class Environment : public std::enable_shared_from_this<Environment>{
    /*
      A class for managing your simulation. 
    */
  public:
    // methods
    static std::shared_ptr<Environment> create(double initial_time = 0.0);
    double get_time();
    void schedule(const std::shared_ptr<Event> , const int priority = 1, const double delay = 0); 
    std::shared_ptr<Event> event();
    std::shared_ptr<Timeout> timeout(double);
    std::shared_ptr<Process> process(const std::function<void(coro_t::push_type&)> );
    void step();
    void run(double until);
  private:
    double now = 0;
    std::priority_queue<QueueEvent, std::vector<QueueEvent>, std::greater<QueueEvent>> pq;
    int id=0;
  };
  
}
#endif // simpp
