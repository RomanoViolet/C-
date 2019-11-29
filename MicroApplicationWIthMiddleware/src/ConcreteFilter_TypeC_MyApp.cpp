#include "Filter.hpp"
#include "MyApp.hpp"
#include "TypeC.hpp"
template <> void Filter<MyApp>::filter(TypeC &c) {
  c.m3 = c.m3 + 13.34;
  c.m4 = "oh oh MyApp" + c.m4;
}