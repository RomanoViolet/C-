#include <cmath>
#include "ManipulateDataStream.hpp"
#include "Filter.hpp"
#include "MyApp.hpp"
#include "NotMyApp.hpp"
void ManipulateDataStream::initialize() {

  customPlacementNew.bindMemory(allocatedMemory);

  //std::ostringstream oss;
  //oss << &(allocatedMemory);
  //std::cout << "this: " << this
  //          << ". Address of allocated mempool at constructor: " << oss.str()
  //          << std::endl;

  this->allInterfaces =
      AggregateInterfaces::create()
          .withMemoryManager(customPlacementNew)
          .withInputTypes<TypeA &, TypeB &, TypeC &>(
              inputStream_1, inputStream_2, inputStream_3)
          .withOutputTypes<TypeD &, TypeE &>(outputStream_1, outputStream_2);
}

void ManipulateDataStream::myCustomFilter() {
  // Filter<MyApp> filter;
  Filter<NotMyApp> filter;
  // this->inputStream_1.customFilter(filter);
  // this->allInterfaces.customFilter(filter);
  this->allInterfaces.customInputFilter(filter);
}

void ManipulateDataStream::compute() {
  // some dummy calculations
  this->outputStream_1.m1 = std::pow(this->inputStream_1.m1, 0.5);
  this->outputStream_1.m2 = this->inputStream_1.m2 * 4 + this->inputStream_1.m1>12.0?111U:333U;

  this->outputStream_2.m1 = this->inputStream_2.m3;
  this->outputStream_2.m2 = (this->inputStream_2.m4.length() > 10 ? 0U : -100U )+
                            (this->inputStream_3.m4.length() > 5 ? 2U : 1U) +
                            (this->inputStream_3.m3 > 14.66 ? 30U : 50U);
}

void ManipulateDataStream::writeDataStream() {
  // at the moment, there is no receiver for manipulate, so we just print out
  // the values.
  std::cout << "outputStream_1.m1: " << this->outputStream_1.m1 << std::endl;
  std::cout << "outputStream_1.m2: " << this->outputStream_1.m2 << std::endl;

  std::cout << "outputStream_2.m1: " << this->outputStream_2.m1 << std::endl;
  std::cout << "outputStream_2.m2: " << this->outputStream_2.m2 << std::endl;
}

void ManipulateDataStream::filter() {
  for (auto thisOutputPort : this->allInterfaces.allOutputInterfaces) {
    thisOutputPort->filter();
  }
}


void* ManipulateDataStream::getAllocatedMemoryAddress() const
{
  //std::cout << "Returning Allocated Memory Address: " << &(allocatedMemory) << std::endl;
  return static_cast<void*>(const_cast<uint8_t*>(allocatedMemory));
}

MemoryBounds ManipulateDataStream::getAddressOfAggregateInterface() const
{
  MemoryBounds bounds;
  bounds.start = static_cast<void*>(this->allInterfaces.allInputInterfaces[0]);

  // get the address of the last output interface and add its own size to reach the end of the memory for this type's interfaces.
  // manipulator has two output interfaces.
  void* p = this->allInterfaces.allOutputInterfaces[1];
  char* pp = static_cast<char*>(p);

  bounds.end = pp + sizeof(this->allInterfaces.allInputInterfaces[2]) + sizeof(this->allInterfaces.allOutputInterfaces[1]);
  //std::cout << "Returning address of allocatedOutputInterface: " << bounds.start << " - " << bounds.end << std::endl;
  return (bounds);
}