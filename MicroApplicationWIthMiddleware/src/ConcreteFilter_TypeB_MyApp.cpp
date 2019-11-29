#include "Filter.hpp"
#include "MyApp.hpp"
#include "TypeB.hpp"
template <> void Filter<MyApp>::filter(TypeB &b) {
  // manipulate the object.
  b.m3 = b.m3 / 0.124;
  b.m4 = b.m4 + ".. uh oh MyApp";
}