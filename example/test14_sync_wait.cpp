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
  named_mutex named_mtx{open_or_create, "mtx"};
  named_condition named_cnd{open_or_create, "cnd"};
  scoped_lock<named_mutex> lock{named_mtx};
  named_cnd.wait(lock);
  std::cout << "got a notification" << std::endl;
  
}
