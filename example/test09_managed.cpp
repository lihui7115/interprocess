#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>

using namespace boost::interprocess;

int main()
{
  shared_memory_object::remove("Boost");
  managed_shared_memory managed_shm{open_or_create, "Boost", 1024};
  typedef allocator<char,
    managed_shared_memory::segment_manager> CharAllocator;

// Boost.Interprocess provides implementations for many other containers from the standard library
// For example, boost::interprocess::vector and boost::interprocess::map are defined in boost/interprocess/containers/vector.hpp and boost/interprocess/containers/map.hpp, respectively.

// boost::container::basic_string or boost::interprocess::basic_string
  typedef boost::container::basic_string<char, std::char_traits<char>, CharAllocator> string;
  
  // memory name is "String"
  // assign "Hello!" with allocator SegmentManager
  string *s = managed_shm.find_or_construct<string>("String")("Hello!",
    managed_shm.get_segment_manager());
  s->insert(5, ", world");
  std::cout << *s << '\n';
}
