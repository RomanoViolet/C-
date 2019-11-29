#include "Filter.hpp"
#include "NotMyApp.hpp"
#include "TypeA.hpp"

template <> void Filter<NotMyApp>::filter(TypeA &a) {
  a.m1 = 13.5443;
  a.m2 = 12;
}