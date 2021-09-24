#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <boost/coroutine2/coroutine.hpp>
#include "core.hpp"
#include "event.hpp"

using namespace simpp;
using coro_t = boost::coroutines2::coroutine<std::shared_ptr<simpp::Event>>;
typedef std::shared_ptr<simpp::Environment> Env;

void generator(Env& env, boost::coroutines2::coroutine<std::shared_ptr<simpp::Event> >::push_type& sink){
  while(true){
    std::shared_ptr<simpp::Timeout> e = env->timeout(1);
    sink(e);
  }
}

int main(void){
  std::shared_ptr<simpp::Environment> env = simpp::Environment::create();
  std::function<void(coro_t::push_type&)> f = std::bind(generator, env, std::placeholders::_1);
  auto pro = env->process(f);
  pro->execute();
  env->run(10000000);
}
