
#define BOOST_INTERPROCESS_FILESYSTEM_BASED_POSIX_SHARED_MEMORY

//#define BOOST_INTERPROCESS_SHARED_DIR_FUNC
//namespace boost::interprocess::ipcdetail{
//void get_shared_dir(std::string &shared_dir) {
//  shared_dir = "/tmp";
//}
//}

#define BOOST_INTERPROCESS_SHARED_DIR_PATH "/dev/shm"

#include <boost/interprocess/shared_memory_object.hpp>
#include <iostream>
#include <thread>

using namespace boost::interprocess;

int main()
{
  try {
    /*
       The operation of shm_open() is analogous to that of open(2).  name specifies the shared memory object to be created or opened.  For portable use, a  shared  memory  object
       should  be  identified by a name of the form /somename; that is, a null-terminated string of up to NAME_MAX (i.e., 255) characters consisting of an initial slash, followed
       by one or more characters, none of which are slashes.
     * */
  shared_memory_object shdmem{open_or_create, "Boost1", read_write, permissions(0600)};
  shdmem.truncate(1024*2);
  std::cout << shdmem.get_name() << '\n';
  offset_t size;
  if (shdmem.get_size(size))
    std::cout << size << '\n';
  
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(5s);
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
