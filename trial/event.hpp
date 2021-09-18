#ifndef SIM_EVENT_HPP
#define SIM_EVENT_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <boost/coroutine2/coroutine.hpp>

#include "core.hpp"

namespace simpp{
  using coro_t = boost::coroutines2::coroutine<std::shared_ptr<Event> >;
  
  class Event : public std::enable_shared_from_this<Event> {
  public:
    // Constructor
    Event(const std::shared_ptr<Environment>& _env) : env(_env) {}
    virtual ~Event() {}
    // Methods
    void succeed();
    std::shared_ptr<Event> get_ptr();
    bool is_ok();
    bool is_pending();
    bool is_done();
    void set_done();
    std::vector<std::function<void(std::shared_ptr<Event> &)>> callbacks;  
  protected:
    bool ok;
    bool defused; 
    bool pending;
    bool done;
    std::shared_ptr<Environment> env;
  }; 

  class Timeout : public Event{
  public:
    Timeout(const std::shared_ptr<Environment>& env, const double delay) : Event(env), delay(delay) {}
    void cast_into_queue();
  private:
    double delay;
  };

  class Process : public Event{
  public:
   Process(const std::shared_ptr<Environment>& , const std::function<void(coro_t::push_type&)> );
   void execute();
   void resume(std::shared_ptr<Event> &);
  private:
   std::unique_ptr<coro_t::pull_type> generator;
   std::shared_ptr<Event> target; 
  };

  class Initializer : public Event{
  public:
    Initializer(const std::shared_ptr<Environment>& env,std::shared_ptr<Process> && process)
      : Event(env), process(process) {}
    void execute();

  private:
    std::shared_ptr<Process> process; 
    std::shared_ptr<Event> event; 
  };
}

#endif
