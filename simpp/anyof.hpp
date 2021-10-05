#ifndef SIMPP_ANYOF_HPP
#define SIMPP_ANYOF_HPP


#include "condition.hpp"

namespace simpp{
  
  class AnyOf : public Condition {
  public:
    AnyOf(const std::shared_ptr<Environment>&, std::shared_ptr<Event>& , std::shared_ptr<Event>& );
  private:
    bool evaluate() override;
  };
} //simpp

#endif
