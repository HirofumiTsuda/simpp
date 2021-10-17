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

#include "gtest/gtest.h"

using namespace simpp;
using coro_t = boost::coroutines2::coroutine<std::shared_ptr<simpp::Event>>;
typedef std::shared_ptr<simpp::Environment> Env;
typedef std::shared_ptr<simpp::Event> Eve;

namespace{

void generator(Env& env, double duration, std::vector<double>* v, coro_t::push_type& sink){
  while(true){
    std::shared_ptr<simpp::Timeout> e = env->timeout(duration);
    sink(e);
    v->push_back(env->get_time());
  }
}



std::vector<double> run(int duration){
  std::shared_ptr<simpp::Environment> env = simpp::Environment::create();
  std::vector<double> v;
  std::function<void(coro_t::push_type&)> f = std::bind(generator, env, duration, &v, std::placeholders::_1);
  env->process(f);
  env->run(1000);
  return v;
}

TEST(FUNCTION_TEST, NORMAL_TIMEOUT){
  double d = 10;
  double t = d;
  std::vector<double> v = run(d);
  for(double num : v){
    ASSERT_EQ(num, t);
    t += d;
  }
}

TEST(FUNCTION_TEST, ABNORMAL_TIMEOUT){
  double d = -1;
  ASSERT_DEATH({
      run(d);
    }, "");
} 
} // namespace

