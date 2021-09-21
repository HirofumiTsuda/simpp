#include <iostream>
#include <functional>
#include <memory>
#include <boost/coroutine2/coroutine.hpp>
#include "core.hpp"
#include "event.hpp"

using namespace simpp;
using coro_t = boost::coroutines2::coroutine<std::shared_ptr<simpp::Event>>;
typedef std::shared_ptr<simpp::Environment> Env;

void generator(Env& env, boost::coroutines2::coroutine<std::shared_ptr<simpp::Event> >::push_type& sink){
  sink(env->timeout(0));
  while(true){
    std::shared_ptr<simpp::Timeout> e = env->timeout(3);
    std::cout << "[pre] time:" << env->get_time() << "id :"<< e << std::endl;
    sink(e);
    std::cout << "[post] time:" << env->get_time() << std::endl;    
  }
}

int main(void){
  std::shared_ptr<simpp::Environment> env = simpp::Environment::create();
  std::function<void(coro_t::push_type&)> f = std::bind(generator, env, std::placeholders::_1);
  auto pro = env->process(f);
  pro->execute();
  env->run(100);
}
