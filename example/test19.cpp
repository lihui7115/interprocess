#include <boost/interprocess/sync/file_lock.hpp>
#include <iostream>
#include <thread>
#include <chrono>

using namespace boost::interprocess;
using namespace std::chrono_literals;

int main() {
  
  file_lock f("/tmp/test");
  bool ret = f.try_lock();   // 通常用法 try_lock再判断
  std::cout << ret << std::endl;
  while(1) {
    std::this_thread::sleep_for(1s);
  }
  std::cout << "exit" << std::endl;
  return 0;
}