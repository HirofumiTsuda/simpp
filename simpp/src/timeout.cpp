#include "timeout.hpp"

#include <cassert>

#include "core.hpp"
#include "event.hpp"

namespace simpp{
  Timeout::Timeout(const std::shared_ptr<Environment>& env, const double delay)
      : Event(env), delay(delay) {
    assert(delay >= 0);
  }  
  void Timeout::cast_into_queue(){
    ok = true;
    env->schedule(shared_from_this(), 1, delay);
  }
}
