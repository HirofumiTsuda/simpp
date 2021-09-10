#include <iostream>
#include <memory>

#include "core.hpp"
#include "event.hpp"

int main(void){
  std::shared_ptr<simpp::Environment> env = simpp::Environment::create(3.0);
  env->timeout(2.0);
  env->timeout(10.0);
  env->timeout(27.0);
}
