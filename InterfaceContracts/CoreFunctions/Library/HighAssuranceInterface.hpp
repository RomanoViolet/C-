#ifndef HIGH_ASSURANCE_INTERFACE_HPP_
#define HIGH_ASSURANCE_INTERFACE_HPP_

#include <Type_InputInterface.hpp>
#include <vector>

class HighAssuranceInputInterface
{
public:
  HighAssuranceInputInterface( ) = default;
  virtual ~HighAssuranceInputInterface( ) = default;
  virtual void preprocessInputs( ) = 0;

private:
};

#endif
