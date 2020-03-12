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
  managed_shared_memory managed_shm{open_or_create, "Boost", 1024};
  
  // Managed shared memory uses member functions such as construct(),
  // which expects a type as a template parameter

  int *i = managed_shm.find_or_construct<int>("Integer")(99);

  named_mutex named_mtx{open_or_create, "mtx"};
  named_condition named_cnd{open_or_create, "cnd"};
  
  {
    // must use lock before notify, because wait pred will ignore the notification if without lock
    scoped_lock<named_mutex> lock{named_mtx};
    lock.unlock();
  }
  named_cnd.notify_one();
  std::cout << "notify one" << std::endl;
  
//  std::this_thread::sleep_for(15s);
  
  *i = 100;
  {
    scoped_lock<named_mutex> lock{named_mtx};
    lock.unlock();
  }
  named_cnd.notify_one();
  std::cout << "notify two" << std::endl;
}
