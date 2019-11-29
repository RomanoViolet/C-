#ifndef TEMPLATED_CLASS_HPP_
#define TEMPLATED_CLASS_HPP_

#include <string>

template <typename T> class TemplatedType {
public:
  TemplatedType() = default;

  std::string doSomething();
};

#include "TemplatedClass.inl"
#endif