#include "Filter.hpp"
#include "NotMyApp.hpp"
#include "TypeD.hpp"
template <> void Filter<NotMyApp>::filter(TypeD &d) {
  d.m1 = 0.1 * d.m1;
  d.m2 = 45 + d.m2;
}