#include <boost/interprocess/managed_shared_memory.hpp>
#include <iostream>

using namespace boost::interprocess;

int main()
{
  shared_memory_object::remove("Boost");
  managed_shared_memory managed_shm{open_or_create, "Boost", 1024};
  int *i = managed_shm.find_or_construct<int>("Integer")(99);
  std::cout << *i << '\n';
  bool ret = managed_shm.destroy<int>("Integer");
  if(ret) {
    std::cout << "destroy Integer successfully" << '\n';
  }
  std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer");
  std::cout << p.first << '\n';
}
