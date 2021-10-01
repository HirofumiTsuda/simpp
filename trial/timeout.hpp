#ifndef SIM_TIMEOUT_HPP
#define SIM_TIMEOUT_HPP

#include <memory>

#include "event.hpp"

namespace simpp{
  class Environment;
  
  class Timeout : public Event{
  public:
    Timeout(const std::shared_ptr<Environment>& , const double );
    void cast_into_queue();
  private:
    double delay;
  };
}
#endif
