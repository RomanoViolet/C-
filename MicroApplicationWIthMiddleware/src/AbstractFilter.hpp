#ifndef ABSTRACTFILTER_HPP_
#define ABSTRACTFILTER_HPP_
class TypeA;
class TypeB;
class TypeC;
class TypeD;
class TypeE;
class AbstractFilter {
public:
  AbstractFilter() = default;
  virtual void filter(TypeA &a) = 0;
  virtual void filter(TypeB &b) = 0;
  virtual void filter(TypeC &c) = 0;
  virtual void filter(TypeD &d) = 0;
  virtual void filter(TypeE &e) = 0;
  virtual ~AbstractFilter() = default;
};
#endif // !ABSTRACTFILTER_HPP_
