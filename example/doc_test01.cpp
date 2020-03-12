#include <boost/interprocess/shared_memory_object.hpp>
#include <iostream>
#include <thread>

using namespace boost::interprocess;

int main()
{
  shared_memory_object shdmem{open_or_create, "Boost", read_write};
  shdmem.truncate(1024*2);
  std::cout << shdmem.get_name() << '\n';
  offset_t size;
  if (shdmem.get_size(size))
    std::cout << size << '\n';
  
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(20s);
}
