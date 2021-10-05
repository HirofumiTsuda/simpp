#include "condition.hpp"

#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <functional>
#include <stdexcept>
#include <cassert>

#include "core.hpp"
#include "event.hpp"


namespace simpp{
  Condition::Condition(const std::shared_ptr<Environment>& env,
		       std::shared_ptr<Event>& left,
		       std::shared_ptr<Event>& right)
    : Event(env) {
    assert((left != nullptr) && (right != nullptr));
    events.push_back(left);
    events.push_back(right);
  }

  void Condition::set_callbacks(){
    for(auto event : events){
      if(env != event->get_env())
	throw std::runtime_error( \
	    "It is not allowed to mix events from different environments");
    }

    std::function<void(std::shared_ptr<Event>&)> check_callback = \
      [this](std::shared_ptr<Event>& event){ check(event);};
    for(auto event : events){      
      if(event->is_done()){
	check(event);
      }else{
	event->add_callback(check_callback, shared_from_this(),true);
      }
    }
    if(is_done())
      throw std::runtime_error("Condition has been already triggered!");
    add_callback([this](std::shared_ptr<Event>& eve){
		   build_value(eve);
		 }, shared_from_this(),false);
  }

  
  void Condition::remove_check_callback(const std::shared_ptr<Event> parent){
    std::cout << "remove check callback : " << parent << std::endl;
    for(auto event : events){
      for(auto iter = event->callbacks.begin();iter != event->callbacks.end();){
	if(iter->parent == parent && iter->check){
	  iter = event->callbacks.erase(iter);
	}else{
	  iter++;
	}
      }
      event->remove_check_callback(shared_from_this());
    }
  }

  bool Condition::evaluate(){
    throw std::runtime_error("Evaluate is not implemented in Condition class");
  }

  void Condition::check(std::shared_ptr<Event>& event){
    if(is_done())
      return;
    count++;
    if(!event->is_ok())
      throw std::runtime_error("Check is executed although the event has not been triggered.");
    if(evaluate())
      succeed();
  }

  void Condition::build_value(std::shared_ptr<Event>& event){
    remove_check_callback(shared_from_this());
    /*
      values are going to be aggregated...
     */
  }
  
} // simpp
