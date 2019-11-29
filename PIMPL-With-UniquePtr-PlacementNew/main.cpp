#include <iostream>

#include "FastPIMPLExample.hpp"

int main()
{
  std::cout << "Hello, World!" << std::endl;

  MyClassWithFastPimpl c;
  std::cout << "Object lives at: " << &c << " and is " << sizeof(c.pimpl) << std::endl;
  c.doPrintSomething();
  int returnValue = c.returnSomething();
  std::cout << "Return Value: " << returnValue << std::endl;
  return (0);
}
