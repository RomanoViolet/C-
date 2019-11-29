#ifndef CUSTOMMEMORY_MANAGEMENT_HPP_
#define CUSTOMMEMORY_MANAGEMENT_HPP_
#include <array>
#include <iostream>
#include <stdint.h>
class CustomMemoryManagement {
public:
  explicit CustomMemoryManagement(uint8_t *allocatedExternalMemory)
      : startPosition(0), allocatedMemoryPool(allocatedExternalMemory) {}
  CustomMemoryManagement() : startPosition(0), allocatedMemoryPool(nullptr) {}

  // copy constructor.
  CustomMemoryManagement(const CustomMemoryManagement &other);

  // assignment operator
  // CustomMemoryManagement& operator=(const CustomMemoryManagement& other);
  /**
   * @brief Traditionally, an assignment operator requires a const reference to
   * the RHS "other" as an argument, which is then used to create a copy, in the
   * copy step of the copy-and-swap idiom. If a deep copy is not necessary, then
   * it is possible to rely on the compiler to create a copy for us instead.
   *        Specifically, changing the argument type from const reference to a
   * type, the argument which takes in an object causes the compiler to create a
   * copy on the stack which is then passed onto the assignment operator's
   * definition.
   * @see https://www.youtube.com/watch?v=7LxepUEcXA4
   */
  CustomMemoryManagement &operator=(CustomMemoryManagement copy);

  template <typename T> T *placementNew(T &initialValue);

  void bindMemory(uint8_t *allocatedExternalMemory) {
    allocatedMemoryPool = allocatedExternalMemory;
  }

  ~CustomMemoryManagement() {
    std::cout << " Destructor for CustomMemoryManagement called. " << std::endl;
  }

private:
  long unsigned int startPosition;
  uint8_t *allocatedMemoryPool;

  // swap method required for copy-and-swap, which is used to implement the
  // assignement operator
  void swap(CustomMemoryManagement &first, CustomMemoryManagement &second);
};

#include "CustomMemoryManagement.inl"
#endif // !CUSTOMMEMORY_MANAGEMENT_HPP_
