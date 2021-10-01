#include "queue_event.hpp"

#include <memory>

#include "event.hpp"

namespace simpp{
  
  QueueEvent::QueueEvent(const double time, const int id, const int priority, const std::shared_ptr<Event> event) 
  : time(time), id(id), priority(priority), event(event) {
  }
  
  bool QueueEvent::operator<(const QueueEvent &other) const {
    if(time != other.time)
      return (time < other.time);
    if(priority != other.priority)
      return (priority < other.priority);
    if(id != other.id)
      return (id < other.id);
    return true;
  }
  
  bool QueueEvent::operator>(const QueueEvent &other) const {
    if(time != other.time)
      return (time > other.time);
    if(priority != other.priority)
      return (priority > other.priority);
    if(id != other.id)
      return (id > other.id);
    return true;
  }  
}
