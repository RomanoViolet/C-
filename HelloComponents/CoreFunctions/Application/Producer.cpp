#include "Producer.hpp"

void Producer::doPreconditionCheck( )
{
  // do something clever
  this->_error = ErrorCode::NO_ERROR;
}

void Producer::doPostConditionCheck( )
{
  // nothing till now.
}

void Producer::initialize( )
{
}
void Producer::compute( )
{
  this->a_out.setValue( 37U );
}
