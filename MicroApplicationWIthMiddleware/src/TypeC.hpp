#ifndef TYPE_C_HPP
#define TYPE_C_HPP
#include <AbstractFilter.hpp>
#include <iostream>
#include <string>

class TypeC {
public:
  TypeC() : m3(0.0), m4("A") {}

  double m3;
  std::string m4;

  template <typename T> void copy(const T &sender) {
    this->m3 = sender.m3;
    this->m4 = sender.m4;
  }

  template <typename T> void publishTo(T &inputPort) const {
    // currently deep copy is not supported
    inputPort.copy(*this);
  }

  void filter() {

    //std::cout << __func__ << ", " << __FILE__ << ". Address of typeC: " << this << std::endl;

    // limit the range between [7, 15]
    if (this->m3 < 7)
    {
      this->m3 = 7U;
    }
    else if(this->m3 > 15)
    {
      this->m3 = 15;
    }
    
    // do not modify m4.
  }

  void customFilter(AbstractFilter &filter) { filter.filter(*this); }

  void move(TypeC &&other) {
    m3 = std::move(other.m3);
    m4 = std::move(other.m4);
  }
  virtual ~TypeC() = default;
};

#endif
