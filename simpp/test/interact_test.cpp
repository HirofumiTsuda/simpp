#include <iostream>
#include <functional>
#include <memory>
#include <boost/coroutine2/coroutine.hpp>

#include "core.hpp"
#include "event.hpp"
#include "timeout.hpp"
#include "process.hpp"
#include "operator.hpp"

#include "gtest/gtest.h"

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
    std::shared_ptr<simpp::Timeout> e = env->timeout(10);
    sink(e);
    if(!intervene->event->is_triggered()){
      intervene->event->succeed();
    }
  }
}


void generator2(Env& env, std::shared_ptr<Intervene> intervene,
		std::vector<double>* v, coro_t::push_type& sink){
  while(true){
    std::shared_ptr<simpp::Timeout> e = env->timeout(4);
    sink(e);
    sink(intervene->event);
    if(intervene->event->is_triggered())
      intervene->event = env->event();
    v->push_back(env->get_time());
    std::cout << env->get_time() << std::endl;
  }
}


void run(std::vector<double> *v){
  std::shared_ptr<simpp::Environment> env = simpp::Environment::create();
  std::shared_ptr<Intervene> intervene = std::make_shared<Intervene>(env);
  std::function<void(coro_t::push_type&)> f = std::bind(generator1, env, intervene, std::placeholders::_1);
  env->process(f);
  std::function<void(coro_t::push_type&)> g = std::bind(generator2, env, intervene, v, std::placeholders::_1);
  env->process(g);
  env->run(1000);
}


TEST(FUNCTION_TEST, INTERACTION_TEST){
  std::vector<double> v;
  run(&v);
  double t = 10;
  for(double tau : v){
    ASSERT_EQ(t, tau);
    t += 10;
  }
}
