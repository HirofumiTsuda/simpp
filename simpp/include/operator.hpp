#ifndef SIMPP_OPERATOR_HPP
#define SIMPP_OPERATOR_HPP

#include <memory>

#include "event.hpp"
#include "allof.hpp"
#include "anyof.hpp"

namespace simpp{

  class Ops{
  public:
    static std::shared_ptr<AllOf> all(std::shared_ptr<Event> left, std::shared_ptr<Event> right){
      auto condition = std::make_shared<AllOf>(left->get_env(), left, right);
      condition->set_callbacks();
      return condition;
    }

    static std::shared_ptr<AnyOf> any(std::shared_ptr<Event> left, std::shared_ptr<Event> right){
      auto condition = std::make_shared<AnyOf>(left->get_env(), left, right);
      condition->set_callbacks();
      return condition;      
    }    
  };
}


#endif
