#include "Filter.hpp"
#include "MyApp.hpp"
#include "TypeE.hpp"
template <> void Filter<MyApp>::filter(TypeE &e) {
  e.m1 = 15.999 * e.m1;
  e.m2 = -37 + e.m2;
}