#ifndef HIGH_ASSURANCE_INTERFACE_HPP_
#define HIGH_ASSURANCE_INTERFACE_HPP_

#include <Type_InputInterface.hpp>
#include <vector>

namespace RomanoViolet
{
  class HighAssuranceInterface
  {
  public:
    template < typename T >
    void addInputInterface( T &interface )
    {
      this->_allInputInterfaces.emplace_back(
          static_cast< AbstractInputInterface * >( &interface ) );
    }

  private:
    std::vector< AbstractInputInterface * > _allInputInterfaces;
  };
}  // namespace RomanoViolet

#endif
