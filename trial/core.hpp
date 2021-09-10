#ifndef SIM_CORE_HPP
#define SIM_CORE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <memory>

namespace simpp{

  class Event;
  class Timeout;
  
  
  class QueueEvent{
    /*
      A class for events in a priority queue.
      The operators < is overridden for comparison. 
    */
  public:
    QueueEvent(const double, const int, const int, const std::shared_ptr<Event>);
    bool operator<(const QueueEvent &) const;
    bool operator>(const QueueEvent &) const;
    std::shared_ptr<Event> get_event();
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
  private:
    double now = 0;
    std::priority_queue<QueueEvent, std::vector<QueueEvent>, std::greater<QueueEvent>> pq;
  };
  
}
#endif // simpp
