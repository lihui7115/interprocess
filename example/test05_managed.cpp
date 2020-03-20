#include <boost/interprocess/managed_shared_memory.hpp>
#include <iostream>

using namespace boost::interprocess;

struct Test {
  int num;
  char data[20];
};

int main()
{
  shared_memory_object::remove("Boost");
  managed_shared_memory managed_shm{open_or_create, "Boost", 1024};
  
  // Managed shared memory uses member functions such as construct(),
  // which expects a type as a template parameter

  int *i = managed_shm.construct<int>("Integer")(99);
  std::cout << *i << '\n';
  std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer");
  if (p.first) {
    std::cout << *p.first << '\n';
    std::cout << p.second << '\n';
  }
  
  {
    Test *i = managed_shm.construct<Test>("Test")();
    i->num = 10;

    std::pair<Test*, std::size_t> p = managed_shm.find<Test>("Test");
    if (p.first) {
      std::cout << p.first->num << '\n';
      std::cout << p.second << '\n';
    }
  }
}
