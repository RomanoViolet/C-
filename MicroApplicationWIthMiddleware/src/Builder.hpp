#ifndef BUILDER_HPP
#define BUILDER_HPP

#include "AbstractFilter.hpp"
#include "CustomMemoryManagement.hpp"
#include <memory>
#include <sstream>
#include <stdint.h>
#include <utility>
#include <vector>

class InterfaceCommonOperationsAcrossAllTypes {
public:
  virtual ~InterfaceCommonOperationsAcrossAllTypes() = default;
  virtual void filter(){};

  // https://stackoverflow.com/a/21731447 Remove the name of the parameter from
  // the argument list in order to avoid -Werror=unused-parameter
  virtual void customFilter(AbstractFilter &){};
};

template <typename T>
class CommonOperationsAcrossAllTypes
    : public InterfaceCommonOperationsAcrossAllTypes {
public:
  explicit CommonOperationsAcrossAllTypes(T &t) : t(t) {}
  virtual void filter();
  void customFilter(AbstractFilter &filter);
  T &t;
};

class InterfaceBuilder;

/**
 * @class AbstractInterfaceBuilder
 * @brief The abstract class exists only so that it becomes possible to create a
 * vector of different types
 */
class AbstractInterfaceBuilder {};

/**
 * @class AggregateInterfaces
 * @brief Provides a single wrapper to aggregate all input and output types to
 * the customer.
 */
struct AggregateInterfaces {
  AggregateInterfaces()
      : allInputInterfaces(
            std::vector<InterfaceCommonOperationsAcrossAllTypes *>()),
        allOutputInterfaces(
            std::vector<InterfaceCommonOperationsAcrossAllTypes *>()),
        customMemoryManager(nullptr){};

  /// \todo  and here lies the problem
  static InterfaceBuilder create();
  void get();
  void printThis();
  size_t getSize();
  void filter();
  void customInputFilter(AbstractFilter &filter);

  std::vector<InterfaceCommonOperationsAcrossAllTypes *> allInputInterfaces;
  std::vector<InterfaceCommonOperationsAcrossAllTypes *> allOutputInterfaces;
  CustomMemoryManagement *customMemoryManager;

  // gcc -Weffc++ coerces into writing a copy constructor and an assignment
  // operator whenever a pointer- type data member is involved. since this class
  // does not do typical resource management (i.e., there is no memory
  // allocation or deallocation performed) the constructor and assigment are
  // provided with an empty body.
  AggregateInterfaces &operator=(AggregateInterfaces other);
  AggregateInterfaces(const AggregateInterfaces &other);
  void swap(AggregateInterfaces &first, AggregateInterfaces &second);
};

class InterfaceBuilder : public AggregateInterfaces {
public:
  explicit InterfaceBuilder() : customPlacementNew(CustomMemoryManagement()) {}

  /**
   * @brief This method allows the customer to pass multiple types in a fluent
   * interface style
   *
   * @tparam T
   * @tparam otherInputTypes
   * @return InterfaceBuilder&
   */
  template <typename T, typename... otherInputTypes>
  InterfaceBuilder &withInputTypes(T t, otherInputTypes... types);

  template <typename T, typename... otherOutputTypes>
  InterfaceBuilder &withOutputTypes(T t, otherOutputTypes... types);
  CustomMemoryManagement customPlacementNew;

  InterfaceBuilder &withMemoryManager(CustomMemoryManagement &allocatedMemory);

  ~InterfaceBuilder() {
    //std::cout << "Destructor for InterfaceBuilder Called. " << std::endl;
  }

private:
  /**
   * @brief Utility method for unpacking all provided types.
   *
   * @tparam T
   */
  template <typename T, typename... otherInputTypes>
  void unpackAllInputPorts(T &t, otherInputTypes &... others);

  template <typename T> void unpackAllInputPorts(T &t);

  template <typename T, typename... otherOutputTypes>
  void unpackAllOutputPorts(T &t, otherOutputTypes &... others);

  template <typename T> void unpackAllOutputPorts(T &t);
};

#include "Builder.inl"
#endif