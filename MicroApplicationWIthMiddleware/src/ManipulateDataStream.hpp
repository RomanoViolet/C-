#ifndef MANIPULATEDATASTREAM_HPP_
#define MANIPULATEDATASTREAM_HPP_

#include <iostream>
#include "CustomMemoryManagement.hpp"
#include <Builder.hpp>
#include <TypeA.hpp>
#include <TypeB.hpp>
#include <TypeC.hpp>
#include <TypeD.hpp>
#include <TypeE.hpp>
#include <MemoryBounds.hpp>


class ManipulateDataStream {
public:
  ManipulateDataStream()
      : inputStream_1(TypeA()), inputStream_2(TypeB()), inputStream_3(TypeC()),
        outputStream_1(TypeD()), outputStream_2(TypeE()),
        customPlacementNew(CustomMemoryManagement(nullptr)),
        allInterfaces(AggregateInterfaces())
         {}

  // memory exposed to customers
  // inputStream_x allows the customer to write data
  TypeA inputStream_1;
  TypeB inputStream_2;
  TypeC inputStream_3;

  // outputStream_x allows the customer to read data generated by this class
  TypeD outputStream_1;
  TypeE outputStream_2;

  void initialize();
  void writeDataStream();
  void compute();
  void filter();
  void myCustomFilter();
  void* getAllocatedMemoryAddress() const;
  MemoryBounds getAddressOfAggregateInterface() const;

private:
  alignas(64) uint8_t allocatedMemory[1000];
  CustomMemoryManagement customPlacementNew;
  AggregateInterfaces allInterfaces;

  template <typename T> struct RangeBoundary {
  private:
    T max{};
    T min{};
  };

  template <typename T> class CustomFilter : private T {
  public:
    CustomFilter() {}

  private:
    RangeBoundary<double> RangeBoundaries_m1;
    RangeBoundary<int> RangeBoundaries_m2;
  };

  // https://stackoverflow.com/a/24628295
  // Group TypeB and TypeC into one so that these can use a single
  // fully-specialized template This is because TypeB and TypeC share the same
  // internal
  template <typename T> struct Group : std::integral_constant<int, 0> {};

}; // class ManipulateDataStream

// parital specialization of CustomFilter for TypeB
// Dammit. C++ does not allow template specialization within the scope of the
// class the template is first declared in.
template <> class ManipulateDataStream::CustomFilter<TypeB> : private TypeB {
public:
  CustomFilter()
      : RangeBoundaries_m3(RangeBoundary<double>()),
        RangeBoundaries_m4(RangeBoundary<std::string>()) {}

private:
  RangeBoundary<double> RangeBoundaries_m3;
  RangeBoundary<std::string> RangeBoundaries_m4;
};
#endif
