#ifndef TYPE_D_HPP
#define TYPE_D_HPP
#include <AbstractFilter.hpp>
#include <iostream>
class TypeD {
public:
  TypeD() : m1(0.0), m2(0U) {}

  double m1;
  int m2;

  template <typename T> void copy(const T &sender) {
    this->m1 = sender.m1;
    this->m2 = sender.m2;
  }

  template <typename T> void publishTo(T &inputPort) const {
    // currently deep copy is not supported
    inputPort.copy(*this);
  }

  void filter() {
    this->m1 = this->m1 + 10;
    this->m2 = this->m2 - 10;
  }

  void customFilter(AbstractFilter &filter) { filter.filter(*this); }

  void move(TypeD &&other) {
    m1 = std::move(other.m1);
    m2 = std::move(other.m2);
  }
  virtual ~TypeD() = default;
};

#endif