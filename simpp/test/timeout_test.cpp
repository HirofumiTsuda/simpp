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


void generator(Env& env, double time, std::vector<double>* v, coro_t::push_type& sink){
  while(true){
    std::shared_ptr<simpp::Timeout> e = env->timeout(DURATION);
    sink(e);
    v->push_back(env->get_time());
  }
}

testing::
int main(void){
  std::shared_ptr<simpp::Environment> env = simpp::Environment::create();
  std::vector<double> v;
  std::function<void(coro_t::push_type&)> f = std::bind(generator, env, &v, std::placeholders::_1);
  env->process(f);
  env->run(1000);
  for(double d : v)
    std::cout << d << std::endl;
}
