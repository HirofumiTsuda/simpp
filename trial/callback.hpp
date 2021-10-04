#ifndef SIMPP_CALLBACK_HPP
#define SIMPP_CALLBACK_HPP

#include <memory>
#include <functional>

namespace simpp{
  class Event;

  class Callback{
  public:
    Callback(std::function<void(std::shared_ptr<Event> &)> func,
	     std::shared_ptr<Event> parent,
	     bool check)
      : func(func), parent(parent), check(check) {}
    std::function<void(std::shared_ptr<Event> &)> func;
    std::shared_ptr<Event> parent;
    bool check;
  };
}

#endif
