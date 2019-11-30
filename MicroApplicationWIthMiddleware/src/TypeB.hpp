#ifndef TYPE_B_HPP
#define TYPE_B_HPP
#include <AbstractFilter.hpp>
#include <iostream>
#include <string>

class TypeB {
public:
  TypeB() : m3(0.0), m4("Hello, World") {}

  double m3;
  std::string m4;

  void doSomething() { std::cout << "doSomething from TypeB." << std::endl; }

  template <typename T> void copy(const T &sender) {
    this->m3 = sender.m3;
    this->m4 = sender.m4;
  }

  template <typename T> void publishTo(T &inputPort) const {
    // currently deep copy is not supported
    inputPort.copy(*this);
  }

  void filter() {

    //std::cout << __func__ << ", " << __FILE__ << ". Address of typeB: " << this << std::endl;
    
    // double m3
    this->m3 = this->m3 * 2;

    // compress the header
    if (this->m4.compare("Header") == 0) {
      this->m4 = "CompressedHeader";
    }
  }

  void customFilter(AbstractFilter &filter) { filter.filter(*this); }

  void move(TypeB &&other) {
    m3 = std::move(other.m3);
    m4 = std::move(other.m4);
  }
  virtual ~TypeB() = default;
};

#endif