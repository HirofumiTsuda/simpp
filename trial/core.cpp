#include "core.hpp"

#include <iostream>
#include <functional>
#include <memory>

#include <boost/coroutine2/coroutine.hpp>

#include "event.hpp"

namespace simpp{

  using coro_t = boost::coroutines2::coroutine<std::shared_ptr<Event> >;    

  QueueEvent::QueueEvent(const double time, const int id, const int priority, const std::shared_ptr<Event> event) 
  : time(time), id(id), priority(priority), event(event) {
    std::cout << "queue : " << this->event->is_ok() << std::endl;
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
  

  std::shared_ptr<Environment> Environment::create(double initial_time){
    std::shared_ptr<Environment> env = std::make_shared<Environment>();
    env->now = initial_time;
    return std::move(env);
  }
  void Environment::step(){
    QueueEvent item = pq.top();
    pq.pop();
    auto event = item.get_event();
    this->now = item.get_time();
    auto callbacks = std::move(event->callbacks);
    event->callbacks.clear();
    event->set_done();
    std::cout << "size:" << callbacks.size() << std::endl;   
    for(auto f : callbacks){
      f(event);
    }
  }

  void Environment::run(double until){
    while(pq.size() > 0){
      std::cout << "step : " << get_time() << std::endl;
      step();
    }
  }
  
  double Environment::get_time(){ 
    return this->now; 
  }

  std::shared_ptr<Event> Environment::event(){
    return std::make_shared<Event>(shared_from_this());
  }

  std::shared_ptr<Timeout> Environment::timeout(double delay){
    std::shared_ptr<Timeout> time_event = std::make_shared<Timeout>(shared_from_this(), delay);
    time_event->cast_into_queue();
    return time_event;
  }

  std::shared_ptr<Process> Environment::process(const std::function<void(coro_t::push_type&)> f){
    return std::make_shared<Process>(shared_from_this(), f);
  }

  void Environment::schedule(std::shared_ptr<Event> event, int priority, double delay){    
    pq.emplace(now + delay, id++, priority, event);
  }

} //simpp



