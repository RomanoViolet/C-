#ifndef TYPE_A_HPP
#define TYPE_A_HPP

#include <AbstractFilter.hpp>
#include <iostream>
#include <utility>
class TypeA {
public:
  TypeA() : m1(0.0), m2(0U) {}

  double m1;
  int m2;

  void move(TypeA &&other) {
    m1 = std::move(other.m1);
    m2 = std::move(other.m2);
  }

  template <typename T> void copy(const T &sender) {
    this->m1 = sender.m1;
    this->m2 = sender.m2;
  }

  template <typename T> void publishTo(T &inputPort) const {
    // currently deep copy is not supported
    inputPort.copy(*this);
  }

  void filter() {
    //std::cout << __func__ << ", " << __FILE__ << ". Address of typeA: " << this
    //          << std::endl;
    
    // ceil m1 to [-10, +10]
    this->m1 = this->m1 < 10.0 ? this->m1 : 10;

    // limit between [0, 1]
    this->m2 = this->m2 < 0 ? 0 : this->m2;
  }

  void customFilter(AbstractFilter &filter) { filter.filter(*this); }

  virtual ~TypeA() = default;
};

#endif