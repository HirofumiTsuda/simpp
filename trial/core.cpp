#include "core.hpp"

#include <iostream>
#include <functional>
#include <memory>

#include <boost/coroutine2/coroutine.hpp>

#include "event.hpp"
#include "timeout.hpp"
#include "queue_event.hpp"
#include "process.hpp"

namespace simpp{

  using coro_t = boost::coroutines2::coroutine<std::shared_ptr<Event> >;    

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
    for(auto f : callbacks){
      f(event);
    }
  }

  void Environment::run(double until){
    while(pq.size() > 0 && until >= get_time()){
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



