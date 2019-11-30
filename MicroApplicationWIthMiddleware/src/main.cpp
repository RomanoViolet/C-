#include "GenerateDataStream.hpp"
#include "ManipulateDataStream.hpp"
#include <iostream>

int main()
{
  std::cout << "Project: Vector of Different Types" << std::endl;

  GenerateDataStream generator;
  ManipulateDataStream manipulator;

  generator.initialize();
  manipulator.initialize();

  // run the application for 100 cycles.
  for (int i = 0; i < 100; ++i)
  {

    generator.compute();

    // call a class provided method for each class.
    // Each specific class' filter is automatically called even though the
    // "filter" method belongs to different types. use case: call the same
    // function for a given set of different types, typically required when
    // coupling an application with a middleware.
    // filtering is performed for all output interfaces of the generator.
    generator.filter();

    // Connect the sender to the receiver.
    // Requires shared memory. On a distributed memory, the receiver will be a
    // middleware or OS element.
    generator.outputStream_1.publishTo(manipulator.inputStream_1);
    generator.outputStream_2.publishTo(manipulator.inputStream_2);
    generator.outputStream_3.publishTo(manipulator.inputStream_3);

    /**
   * @brief The custom operation is not fully defined by the class itself (as
   * was the case of "filter" class). Instead, the each class provides a method
   * which accepts a user-provided filter to execute on the member. Also see the
   * "visitor" pattern. Such an approach is useful if the user needs to execute
   * a given operation (here, customInputFilter) on each type. The details of
   * the operation differ on the type itself.
   */
    manipulator.myCustomFilter();

    /**
   * @brief run the compute method of the class.
   */
    manipulator.compute();

    // execute a class method for each class.
    // In this case, a 'filter' method for each of the input members of the
    // manipulator class is executed.
    // filtering runs on all output interfaces of the manipulator class.
    // The choice of whether to run on all input or all output or both is made when implementing the filter() method in the manipulator.
    manipulator.filter();

    manipulator.writeDataStream();
    
  }
  return (0);
}