#ifndef SIMPP_CONDITION_HPP
#define SIMPP_CONDITION_HPP


#include <memory>
#include <vector>
#include <functional>

#include "event.hpp"

namespace simpp{

  class Environment;
  
  class Condition : public Event {
  public:
    Condition(const std::shared_ptr<Environment>&, std::shared_ptr<Event>& , std::shared_ptr<Event>& );
    void set_callbacks();
    void remove_check_callback(const std::shared_ptr<Event>) override;
  protected:
    virtual bool evaluate();
    void check(std::shared_ptr<Event>&);
    void build_value(std::shared_ptr<Event> &);
    std::vector<std::shared_ptr<Event>> events;
    int count = 0;
    
  };

}

#endif


