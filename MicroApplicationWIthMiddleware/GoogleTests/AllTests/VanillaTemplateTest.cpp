#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <TemplatedClass.hpp>
#include <TypeA.hpp>
TEST(TemplatedType, TestForDoubleType) {
  // Plain test of templated class
  TemplatedType<double> d;
  EXPECT_EQ(d.doSomething(), typeid(double).name());
}

TEST(TemplatedType, TestForStringType) {
  // Plain test of templated class
  TemplatedType<std::string> d;
  EXPECT_EQ(d.doSomething(), typeid(std::string).name());
}

TEST(TemplatedType, TestForTypeAType) {
  // Plain test of templated class
  TemplatedType<TypeA> a;
  a.doSomething();
  EXPECT_EQ(a.doSomething(), typeid(TypeA).name());
}