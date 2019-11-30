#include "GenerateDataStream.hpp"

// TODO Find a way to remove inlines
void GenerateDataStream::initialize() {

  customPlacementNew.bindMemory(allocatedMemory);

  //std::ostringstream oss;
  //oss << &(allocatedMemory);
  //std::cout << "this: " << this
  //          << ". Address of allocated mempool at constructor: " << oss.str()
  //          << std::endl;

  this->allOutputInterface =
      AggregateInterfaces::create()
          .withMemoryManager(customPlacementNew)
          .withOutputTypes<TypeA &, TypeB &, TypeC &>(
              outputStream_1, outputStream_2, outputStream_3);
}

void* GenerateDataStream::getAllocatedMemoryAddress() const
{
  //std::cout << "Returning Allocated Memory Address: " << &(allocatedMemory) << std::endl;
  return static_cast<void*>(const_cast<uint8_t*>(allocatedMemory));
}

MemoryBounds GenerateDataStream::getAddressOfAggregateInterface() const
{
  MemoryBounds bounds;
  bounds.start = static_cast<void*>(this->allOutputInterface.allOutputInterfaces[0]);
  void* p = this->allOutputInterface.allOutputInterfaces[2];
  char* pp = static_cast<char*>(p);
  bounds.end = pp + sizeof(this->allOutputInterface.allOutputInterfaces[2]);
  //std::cout << "Returning address of allocatedOutputInterface: " << bounds.start << " - " << bounds.end << std::endl;
  return (bounds);
}

void GenerateDataStream::compute() {
  // consecutive integers.
  outputStream_1.m1 = seedOutputStream_1++;
  // limit the output between [-5, +20].
  seedOutputStream_1 = (seedOutputStream_1 > 20) ? -5 : seedOutputStream_1;

  // 1, -1, 1, -1, 1, -1, ...
  outputStream_1.m2 = (outputStream_1.m2 == -1) ? 1 : -1;

  // even positive integers.
  outputStream_2.m3 = seedOutputStream_2;
  // simulates a string data stream: Header-Body Header-Body sent in parts
  outputStream_2.m4 = (outputStream_2.m4 == "Header") ? "Body" : "Header";
  seedOutputStream_2 = seedOutputStream_2 + 2U;

  // odd positive integers
  outputStream_3.m3 = seedOutputStream_3;
  outputStream_3.m4 = this->seedLetter;
  if (this->seedLetter <= 'Z' )
  {
    this->seedLetter = static_cast<char>(static_cast<int>(this->seedLetter) + 1);
  }
  else
  {
    this->seedLetter = 'A';
  }
  
  seedOutputStream_3 = seedOutputStream_3 + 2U;
  // limit the output between [0., 51]
  seedOutputStream_3 = (seedOutputStream_3 > 51) ? 1U : seedOutputStream_3;
}

void GenerateDataStream::filter() { this->allOutputInterface.filter(); }
