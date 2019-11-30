#ifndef FILTER_HPP_
#define FILTER_HPP_
#include "AbstractFilter.hpp"
class TypeA;
class TypeB;
class TypeC;
class TypeD;
class TypeE;

template <typename T> class Filter : public AbstractFilter {
public:
  Filter() = default;
  void filter(TypeA &a);
  void filter(TypeB &b);
  void filter(TypeC &c);
  void filter(TypeD &d);
  void filter(TypeE &e);
  ~Filter() = default;
};
#endif // !ABSTRACTFILTER_HPP_
