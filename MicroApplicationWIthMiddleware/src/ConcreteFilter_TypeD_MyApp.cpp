#include "Filter.hpp"
#include "MyApp.hpp"
#include "TypeD.hpp"
template <> void Filter<MyApp>::filter(TypeD &d) {
  d.m1 = 0.313 * d.m1;
  d.m2 = 79 + d.m2;
}