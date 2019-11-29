#include "Filter.hpp"
#include "MyApp.hpp"
#include "TypeA.hpp"

template <> void Filter<MyApp>::filter(TypeA &a) {
  // manipulate the object. This time, set constant values
  a.m1 = a.m1 + 0.5;
  a.m2 *= 1;
}