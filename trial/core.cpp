#include "core.hpp"

#include <iostream>
#include <memory>

#include "event.hpp"

namespace simpp{

  QueueEvent::QueueEvent(const double time, const int id, const int priority, const std::shared_ptr<Event> event) 
  : time(time), id(id), priority(priority), event(event) {}
  
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
  

  std::shared_ptr<Environment> Environment::create(double initial_time){
    std::shared_ptr<Environment> env = std::make_shared<Environment>();
    env->now = initial_time;
    return std::move(env);
  }
  
  double Environment::get_time(){ 
    return this->now; 
  }


  std::shared_ptr<Event> Environment::event(){
    return std::make_shared<Event>(shared_from_this());;
  }

  std::shared_ptr<Timeout> Environment::timeout(double delay){
    std::shared_ptr<Timeout> time_event = std::make_shared<Timeout>(shared_from_this(), delay);
    time_event->cast_into_queue();
    return time_event;
  }

  void Environment::schedule(std::shared_ptr<Event> event, int priority, double delay){ 
    pq.emplace(QueueEvent(now + delay, 0, priority, event));
  }

} //simpp

