#include "Filter.hpp"
#include "NotMyApp.hpp"
#include "TypeE.hpp"
template <> void Filter<NotMyApp>::filter(TypeE &e) {
  e.m1 = 9.99 * e.m1;
  e.m2 = -1000 + e.m2;
}