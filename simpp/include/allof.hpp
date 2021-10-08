#ifndef SIMPP_ALLOF_HPP
#define SIMPP_ALLOF_HPP


#include "condition.hpp"

namespace simpp{
  
  class AllOf : public Condition {
  public:
    AllOf(const std::shared_ptr<Environment>&, std::shared_ptr<Event>& , std::shared_ptr<Event>& );
  private:
    bool evaluate() override;
  };
} //simpp

#endif
 
