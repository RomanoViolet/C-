#ifndef BUILDER_INL
#define BUILDER_INL

#include "Builder.hpp"
#include "CustomMemoryManagement.hpp"
#include <algorithm>
#include <iostream>
#include <utility>
template <typename T> void CommonOperationsAcrossAllTypes<T>::filter() {
  // T.filter();
  this->t.filter();
}

template <typename T>
void CommonOperationsAcrossAllTypes<T>::customFilter(AbstractFilter &filter) {
  // T.filter();
  this->t.customFilter(filter);
}

inline void AggregateInterfaces::printThis() {
  std::cout << "Used." << std::endl;
}

inline size_t AggregateInterfaces::getSize() {
  return (this->allInputInterfaces.size());
}

inline void AggregateInterfaces::swap(AggregateInterfaces &first,
                                      AggregateInterfaces &second) {
  // In the specific use-case demonstrated in this example, *this will always be
  // uninitialized and empty.

  if (second.allInputInterfaces.size() > 0) {

    for (InterfaceCommonOperationsAcrossAllTypes *thisInputInterface :
         second.allInputInterfaces) {
      first.allInputInterfaces.push_back(thisInputInterface);
    }
  }

  if (second.allOutputInterfaces.size() > 0) {
    // std::iter_swap(first.allOutputInterfaces.begin(),
    // second.allOutputInterfaces.begin());
    for (InterfaceCommonOperationsAcrossAllTypes *thisOutputInterface :
         second.allOutputInterfaces) {
      first.allOutputInterfaces.push_back(thisOutputInterface);
    }
  }

  std::swap(this->customMemoryManager, second.customMemoryManager);
}

inline AggregateInterfaces &AggregateInterfaces::
operator=(AggregateInterfaces other) {
  this->swap(*this, other);
  return (*this);
}

inline AggregateInterfaces::AggregateInterfaces(
    const AggregateInterfaces &other)
    : allInputInterfaces(
          std::vector<InterfaceCommonOperationsAcrossAllTypes *>()),
      allOutputInterfaces(
          std::vector<InterfaceCommonOperationsAcrossAllTypes *>()),
      customMemoryManager(nullptr) {
  this->allInputInterfaces = other.allInputInterfaces;
  this->allOutputInterfaces = other.allOutputInterfaces;
  this->customMemoryManager = other.customMemoryManager;
}

inline InterfaceBuilder AggregateInterfaces::create() {
  return (InterfaceBuilder{});
}

inline void AggregateInterfaces::get() {
  // read from an external memory and pull data into local variables
}

inline void AggregateInterfaces::filter() {
  // filters only output interfaces
  for (auto thisOutputType : this->allOutputInterfaces) {
    thisOutputType->filter();
  }
}

inline void AggregateInterfaces::customInputFilter(AbstractFilter &filter) {
  // filters only output interfaces
  for (auto thisInputType : this->allInputInterfaces) {
    thisInputType->customFilter(filter);
  }
}

inline InterfaceBuilder &
InterfaceBuilder::withMemoryManager(CustomMemoryManagement &allocatedMemory) {
  // shallow copy will work.
  this->customMemoryManager = &allocatedMemory;
  return (*this);
}
template <typename T, typename... otherInputTypes>
inline InterfaceBuilder &
InterfaceBuilder::withInputTypes(T t, otherInputTypes... others) {

  this->unpackAllInputPorts(t, others...);
  return (*this);
}

template <typename T, typename... otherOutputTypes>
inline InterfaceBuilder &
InterfaceBuilder::withOutputTypes(T t, otherOutputTypes... others) {

  this->unpackAllOutputPorts(t, others...);
  return (*this);
}

template <typename T> inline void InterfaceBuilder::unpackAllInputPorts(T &t) {

  // customPlacementNew.bindMemory(allocatedMemory);
  CommonOperationsAcrossAllTypes<T> v{CommonOperationsAcrossAllTypes<T>(t)};
  CommonOperationsAcrossAllTypes<T> *p =
      std::move(customMemoryManager->placementNew(v));
  allInputInterfaces.push_back(
      static_cast<InterfaceCommonOperationsAcrossAllTypes *>(p));
}

template <typename T, typename... otherInputTypes>
inline void InterfaceBuilder::unpackAllInputPorts(T &t,
                                                  otherInputTypes &... others) {
  unpackAllInputPorts(t);
  if (sizeof...(others) > 0) {
    unpackAllInputPorts(others...);
  }
}

template <typename T> inline void InterfaceBuilder::unpackAllOutputPorts(T &t) {

  CommonOperationsAcrossAllTypes<T> v{CommonOperationsAcrossAllTypes<T>(t)};
  CommonOperationsAcrossAllTypes<T> *p =
      std::move(customMemoryManager->placementNew(v));
  allOutputInterfaces.push_back(
      static_cast<InterfaceCommonOperationsAcrossAllTypes *>(p));
}

template <typename T, typename... otherOutputTypes>
inline void
InterfaceBuilder::unpackAllOutputPorts(T &t, otherOutputTypes &... others) {

  unpackAllOutputPorts(t);
  if (sizeof...(others) > 0) {
    unpackAllOutputPorts(others...);
  }
}

#endif