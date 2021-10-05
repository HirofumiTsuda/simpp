#ifndef SIMPP_EVENT_HPP
#define SIMPP_EVENT_HPP

#include <memory>
#include <vector>
#include <functional>

#include "core.hpp"
#include "callback.hpp"

namespace simpp{

  
  class Event : public std::enable_shared_from_this<Event> {
  public:
    // Constructor
    Event(const std::shared_ptr<Environment>& );
    virtual ~Event();
    // variables
    std::vector<Callback> callbacks;    
    // Methods
    void succeed();
    std::shared_ptr<Event> get_ptr();
    std::shared_ptr<Environment> get_env();
    bool is_ok() const;
    bool is_triggered() const;
    bool is_done() const;
    void set_done();
    void add_callback(std::function<void(std::shared_ptr<Event> &)>, std::shared_ptr<Event>, bool);
    virtual void remove_check_callback(std::shared_ptr<Event>);
  protected:
    bool ok=false;
    bool triggered=false;
    bool done=false;
    int check_locator = -1;
    std::shared_ptr<Environment> env;
  }; 
}

#endif
