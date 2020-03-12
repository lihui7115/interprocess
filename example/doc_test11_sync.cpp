#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <iostream>
#include <thread>

using namespace boost::interprocess;

int main()
{
  managed_shared_memory managed_shm{open_or_create, "shm", 1024};
  int *i = managed_shm.find_or_construct<int>("Integer")();
  named_mutex named_mtx{open_or_create, "mtx"};
  named_mtx.lock();
//  using namespace std::chrono_literals;
//  std::this_thread::sleep_for(20s);
  ++(*i);
  std::cout << *i << '\n';
  named_mtx.unlock();
}
