#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <cassert>
#include <boost/coroutine2/coroutine.hpp>

#include "core.hpp"
#include "event.hpp"
#include "timeout.hpp"
#include "process.hpp"
#include "operator.hpp"
#include "operator.hpp"

#include "gtest/gtest.h"

using namespace simpp;
using coro_t = boost::coroutines2::coroutine<std::shared_ptr<simpp::Event>>;
typedef std::shared_ptr<simpp::Environment> Env;
typedef std::shared_ptr<simpp::Event> Eve;

namespace{


void generator(Env& env, std::vector<double>* v, coro_t::push_type& sink, double tau1, double tau2, bool all){
  while(true){
    auto e1 = env->timeout(tau1);
    auto e2 = env->timeout(tau2);
    if(all){
      sink(Ops::all(e1, e2));
    }else{
      sink(Ops::any(e1, e2));
    }
    v->push_back(env->get_time());
  }
}



std::vector<double> run(double tau1, double tau2, bool all){
  std::shared_ptr<simpp::Environment> env = simpp::Environment::create();
  std::vector<double> v;
  std::function<void(coro_t::push_type&)> f = std::bind(generator, env, &v, std::placeholders::_1, tau1, tau2, all);
  env->process(f);
  env->run(1000);
  return v;
}

TEST(FUNCTION_TEST, AND_TEST){
  double tau1 = 10;
  double tau2 = 20;
  double t = tau2;
  std::vector<double> v = run(tau1, tau2, true);
  for(double num : v){
    ASSERT_EQ(num, t);
    t += tau2;
  }
}

TEST(FUNCTION_TEST, OR_TEST){
  double tau1 = 10;
  double tau2 = 20;
  double t = tau1;
  std::vector<double> v = run(tau1, tau2, false);
  for(double num : v){
    ASSERT_EQ(num, t);
    t += tau1;
  }  
} 
} // namespace

