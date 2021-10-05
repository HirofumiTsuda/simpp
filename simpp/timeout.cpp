#include "timeout.hpp"

#include "core.hpp"
#include "event.hpp"

namespace simpp{
  Timeout::Timeout(const std::shared_ptr<Environment>& env, const double delay)
      : Event(env), delay(delay) {}  
  void Timeout::cast_into_queue(){
    ok = true;
    env->schedule(shared_from_this(), 1, delay);
  }
}
