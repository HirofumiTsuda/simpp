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

struct Intervene{
  std::shared_ptr<simpp::Event> eve;
  Env env;
  Intervene(Env &env) : env(env) { eve = env->event(); }
};


void generator1(Env& env, std::shared_ptr<Intervene>& intervene, boost::coroutines2::coroutine<std::shared_ptr<simpp::Event> >::push_type& sink){
  while(true){
    std::shared_ptr<simpp::Timeout> e = env->timeout(10);
    sink(e);
    //std::cout << "[1] waiting... :" << env->get_time() << std::endl;
    sink(intervene->eve);
    std::cout << "[1] execute :" << env->get_time() << std::endl;
    intervene->eve = env->event();
  }
}

void generator2(Env& env,  std::shared_ptr<Intervene>& intervene, boost::coroutines2::coroutine<std::shared_ptr<simpp::Event> >::push_type& sink){
  while(true){
    std::shared_ptr<simpp::Timeout> e = env->timeout(17);
    sink(e);
    std::cout << "[2] wake up! :" << env->get_time() << std::endl;   
    if(!intervene->eve->is_triggered()){
      intervene->eve->succeed();
    }
  }
}

int main(void){
  std::shared_ptr<simpp::Environment> env = simpp::Environment::create();
  std::shared_ptr<Intervene> intervene = std::make_shared<Intervene>(env);
  std::function<void(coro_t::push_type&)> f = std::bind(generator1, env, intervene, std::placeholders::_1);
  auto pro = env->process(f);
  pro->execute();
  std::function<void(coro_t::push_type&)> g = std::bind(generator2, env, intervene, std::placeholders::_1);
  auto pro2 = env->process(g);
  pro2->execute();  
  env->run(10000000);
}
