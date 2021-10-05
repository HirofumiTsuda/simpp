#include "allof.hpp"

#include <memory>

#include "core.hpp"
#include "event.hpp"

namespace simpp{
  
  AllOf::AllOf(const std::shared_ptr<Environment>& env,
		       std::shared_ptr<Event>& left,
		       std::shared_ptr<Event>& right)
  : Condition(env, left, right) {}

  bool AllOf::evaluate(){
    return (count == events.size());
  }
  
} //simpp
