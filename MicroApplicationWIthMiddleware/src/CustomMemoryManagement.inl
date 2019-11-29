#ifndef CUSTOMMEMORYMANAGEMENT_INL_
#define CUSTOMMEMORYMANAGEMENT_INL_
#include "CustomMemoryManagement.hpp"
#include <cstdlib>
#include <cxxabi.h>
#include <iostream>
#include <sstream>

inline void CustomMemoryManagement::swap(CustomMemoryManagement &first,
                                         CustomMemoryManagement &second)
{
  // will not throw an exception since memory for first and second is already
  // available and passed in.
  std::swap(first.allocatedMemoryPool, second.allocatedMemoryPool);
  std::swap(first.startPosition, second.startPosition);
}

// copy constructor
// -Weffc++ goads into initializing the members via list initialization.
inline CustomMemoryManagement::CustomMemoryManagement(
    const CustomMemoryManagement &other)
    : startPosition(0U), allocatedMemoryPool(nullptr)
{
  this->allocatedMemoryPool = other.allocatedMemoryPool;
  this->startPosition = other.startPosition;
}

// assignment operator
// inline CustomMemoryManagement& CustomMemoryManagement::operator=(const
// CustomMemoryManagement& other)
inline CustomMemoryManagement &CustomMemoryManagement::
operator=(CustomMemoryManagement copy)
{

  // swap the data from other into the temporary created above
  this->swap(copy, *this);
  return (*this);
}

template <typename T>
inline T *CustomMemoryManagement::placementNew(T &initialValue)
{
  T *allocatedAddress;
  //std::ostringstream oss;
  if (this->allocatedMemoryPool != nullptr)
  {
    //std::cout << "Allocating " << sizeof(T) << " bytes of memory at: ";
    
    //oss << static_cast<void *>(this->allocatedMemoryPool);
    //std::cout << oss.str();
    //std::cout << " at offset of " << std::to_string(this->startPosition);
    //std::string tname = typeid(T).name();
    //std::cout << " for type: " << tname << std::endl;
    //int status;
    //char *demangled_name =
    //    abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
    //if (status == 0)
    //{
    //  tname = demangled_name;
    //  std::free(demangled_name);
    //}

    allocatedAddress =
        new (this->allocatedMemoryPool + this->startPosition) T(initialValue);
    this->startPosition = this->startPosition + sizeof(initialValue);
  }
  else
  {
    std::cout << "Memory address is NULL" << std::endl;
    allocatedAddress = nullptr;
  }

  return (allocatedAddress);
}

#endif // !CUSTOMMEMORYMANAGEMENT_INL_
