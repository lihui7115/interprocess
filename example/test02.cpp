#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <thread>

using namespace boost::interprocess;

int main()
{
  shared_memory_object shdmem{open_or_create, "Boost", read_write};
  shdmem.truncate(1024);
  mapped_region region{shdmem, read_write};
  memset(region.get_address(), 0x12, region.get_size());
  std::cout << std::hex << region.get_address() << '\n';    // 0x7f7d092a2000
  std::cout << std::dec << region.get_size() << '\n';
  
  std::cout << (int)*(char*)region.get_address() << '\n';
  
  // 同一个shared_memory_object通过mapped_region
  // 映射出来的地址值是不一样的，但是内容还是同一份
  mapped_region region2{shdmem, read_only};        
  
  std::cout << (int)*(char*)region2.get_address() << '\n';   // 0x7f7d092a1000
  std::cout << std::hex << region2.get_address() << '\n';
  std::cout << std::dec << region2.get_size() << '\n';
  
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(20s);
}
