#include "Filter.hpp"
#include "NotMyApp.hpp"
#include "TypeC.hpp"
template <> void Filter<NotMyApp>::filter(TypeC &c) {
  c.m3 = c.m3 + 1.34;
  c.m4 = "oh oh " + c.m4;
}