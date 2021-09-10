#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <boost/coroutine2/coroutine.hpp>

using coro_t = boost::coroutines2::coroutine<int>;
class Holder{
private:
  int x;
  std::unique_ptr<coro_t::pull_type> source;  
public:
  Holder(std::function<void(coro_t::push_type&)> f){
    source = std::make_unique<coro_t::pull_type>(coro_t::pull_type(f));
  }
  virtual ~Holder() {};
  int yield(){
    int num = source->get();
    (*source)();
    return num;
  }
};

void generator(int x, boost::coroutines2::coroutine<int>::push_type& sink){
  while(true){
    std::cout << "gen :" << x << std::endl;
    sink(x);
    x+=1;
    std::cout << "gen :" << x << std::endl;
    sink(x);
    x++;
    std::cout << "gen :" << x << std::endl;
    sink(x);
    x++;
    std::cout << "gen :" << x << std::endl;
    sink(x);
    x++;
  }
}

int main(void){
  auto f = std::bind(generator, 10, std::placeholders::_1);
  Holder h(f);
  for(int i=0;i<10;i++){
    int num = h.yield();
    std::cout << "main : " << num << std::endl;
  }
}
