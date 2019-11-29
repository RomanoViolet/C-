#include "Filter.hpp"
#include "NotMyApp.hpp"
#include "TypeB.hpp"
template <> void Filter<NotMyApp>::filter(TypeB &b) {
  b.m3 = b.m3 / 1.24;
  b.m4 = b.m4 + ".. uh oh Not My App";
}