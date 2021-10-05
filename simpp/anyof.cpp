#include "anyof.hpp"

#include <memory>

#include "core.hpp"
#include "event.hpp"

namespace simpp{
  
  AnyOf::AnyOf(const std::shared_ptr<Environment>& env,
		       std::shared_ptr<Event>& left,
		       std::shared_ptr<Event>& right)
  : Condition(env, left, right) {}

  bool AnyOf::evaluate(){
    return ((count > 0) || events.size() == 0);
  }
  
} //simpp
