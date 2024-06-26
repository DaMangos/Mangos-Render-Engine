#include <iostream>

int main()
{
#ifdef NDEBUG
  std::cout << "hello main NDEBUG" << std::endl;
#else
  std::cout << "hello main" << std::endl;
#endif
}