#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>
#include <thread>

using namespace boost::interprocess;
using namespace std::chrono_literals;

int main()
{
  managed_shared_memory managed_shm{open_or_create, "shm", 1024};
  int *i = managed_shm.find_or_construct<int>("Integer")(0);
  named_mutex named_mtx{open_or_create, "mtx"};
  named_condition named_cnd{open_or_create, "cnd"};
  scoped_lock<named_mutex> lock{named_mtx};
  while (*i < 100)
  {
    if (*i % 2 == 0)
    {
      ++(*i);
        
      std::this_thread::sleep_for(1s);
      named_cnd.notify_all();
      named_cnd.wait(lock);
    }
    else
    {
      std::cout << *i << std::endl;
      ++(*i);
      std::this_thread::sleep_for(1s);
      named_cnd.notify_all();
      named_cnd.wait(lock);
    }
  }
  named_cnd.notify_all();
  shared_memory_object::remove("shm");
  named_mutex::remove("mtx");
  named_condition::remove("cnd");
}
