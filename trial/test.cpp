#include <iostream>
#include <functional>
#include <memory>
#include <boost/coroutine2/coroutine.hpp>

#include "core.hpp"
#include "event.hpp"
#include "timeout.hpp"
#include "process.hpp"

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
    std::shared_ptr<simpp::Timeout> e = env->timeout(3);
    sink(e);
    std::cout << "[1] timeout is done " << env->get_time() << std::endl;
    if(!intervene->event->is_triggered()){
      std::cout << "[1] succeed : " << env->get_time() << std::endl;          
      intervene->event->succeed();
    }
  }
}

<<<<<<< HEAD
void generator2(Env& env, std::shared_ptr<Intervene> intervene, boost::coroutines2::coroutine<std::shared_ptr<simpp::Event> >::push_type& sink){
  while(true){
    std::shared_ptr<simpp::Timeout> e = env->timeout(17);
    sink(e);
    std::cout << "[2] waiting : " << env->get_time() << std::endl;
    sink(intervene->event);
    std::cout << "[2] release : " << env->get_time() << std::endl;
    if(intervene->event->is_triggered())
      intervene->event = env->event();
=======
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
>>>>>>> 5e9db70bed74cf77fb7d2a8f187e9bde135e286e
  }
}

int main(void){
  std::shared_ptr<simpp::Environment> env = simpp::Environment::create();
<<<<<<< HEAD
  std::shared_ptr<Intervene> intervene = std::make_shared<Intervene>(env);  
  std::function<void(coro_t::push_type&)> f = std::bind(generator1, env, intervene ,std::placeholders::_1);
  std::function<void(coro_t::push_type&)> g = std::bind(generator2, env, intervene ,std::placeholders::_1);  
  auto pro1 = env->process(f);
  pro1->execute();
  auto pro2 = env->process(g);
  pro2->execute();  
  env->run(1000);
=======
  std::shared_ptr<Intervene> intervene = std::make_shared<Intervene>(env);
  std::function<void(coro_t::push_type&)> f = std::bind(generator1, env, intervene, std::placeholders::_1);
  auto pro = env->process(f);
  pro->execute();
  std::function<void(coro_t::push_type&)> g = std::bind(generator2, env, intervene, std::placeholders::_1);
  auto pro2 = env->process(g);
  pro2->execute();  
  env->run(10000000);
>>>>>>> 5e9db70bed74cf77fb7d2a8f187e9bde135e286e
}
