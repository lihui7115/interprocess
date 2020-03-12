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
shared_memory_object::remove("Boost");
  managed_shared_memory managed_shm{open_or_create, "Boost", 1024};
  int *i = managed_shm.find_or_construct<int>("Integer")(99);

  
  named_mutex named_mtx{open_or_create, "mtx"};
  named_condition named_cnd{open_or_create, "cnd"};
  
  scoped_lock<named_mutex> lock{named_mtx};
  named_cnd.wait(lock, [i]() {
    bool ret = false;
    if (*i == 100) {
      std::cout << "checking pred, is 100, exit" << std::endl;
      ret =  true;
    } else {
      std::cout << "checking pred, not 100" << std::endl;
    }
    
    std::this_thread::sleep_for(20s);
    return ret;
  });

  std::cout << "got a notification" << std::endl;
  
}
