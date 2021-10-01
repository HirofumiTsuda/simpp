#ifndef SIM_QUEUEEVENT_HPP
#define SIM_QUEUEEVENT_HPP

#include <memory>

namespace simpp{

  class Event;
  
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
}


#endif
