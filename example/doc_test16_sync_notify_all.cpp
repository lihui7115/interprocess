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
  named_condition named_cnd{open_or_create, "cnd"};
  named_cnd.notify_all();
  std::cout << "notify all" << std::endl;
}
