#include <iostream>

template <typename T> std::string TemplatedType<T>::doSomething() {
  std::cout << "Type: " << typeid(T).name() << std::endl;
  return (typeid(T).name());
}