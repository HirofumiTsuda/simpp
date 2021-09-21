#ifndef SIM_CORE_HPP
#define SIM_CORE_HPP

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

  using coro_t = boost::coroutines2::coroutine<std::shared_ptr<Event> >;  
  
  class QueueEvent{
    /*
      A class for events in a priority queue.
      The operators < is overridden for comparison. 
    */
  public:
    QueueEvent(const double, const int, const int, const std::shared_ptr<Event>);
    bool operator<(const QueueEvent &) const;
    bool operator>(const QueueEvent &) const;
    std::shared_ptr<Event> get_event(){ return event; };
    double get_time(){ return time; };    
  private:
    double time;
    int id;
    int priority;
    std::shared_ptr<Event> event;
  };
  
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
