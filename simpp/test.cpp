#include <iostream>
#include <functional>
#include <memory>
#include <boost/coroutine2/coroutine.hpp>

#include "core.hpp"
#include "event.hpp"
#include "timeout.hpp"
#include "process.hpp"
#include "operator.hpp"

using namespace simpp;
using coro_t = boost::coroutines2::coroutine<std::shared_ptr<simpp::Event>>;
typedef std::shared_ptr<simpp::Environment> Env;
typedef std::shared_ptr<simpp::Event> Eve;

struct Intervene{
  Env env;
  Eve event;
  Intervene(Env env) : env(env) {
    event = env->event();
  }
};

void generator1(Env& env, std::shared_ptr<Intervene> intervene, coro_t::push_type& sink){
  while(true){
    auto e17 = env->timeout(17);
    auto e10 = env->timeout(10);    
    auto e = simpp::Ops::any(e10, e17);
    std::cout << e10 << " " << e17 << " "<< e << std::endl;
    sink(e);
    std::cout << "[1] timeout is done " << env->get_time() << std::endl;
  }
}

int main(void){
  std::shared_ptr<simpp::Environment> env = simpp::Environment::create();
  std::shared_ptr<Intervene> intervene = std::make_shared<Intervene>(env);
  std::function<void(coro_t::push_type&)> f = std::bind(generator1, env, intervene, std::placeholders::_1);
  auto pro = env->process(f);
  pro->execute();
  env->run(100000);
}
