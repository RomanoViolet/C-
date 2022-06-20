#include "Consumer.hpp"

void Consumer::initialize( )
{
}

void Consumer::compute( )
{
}

void Consumer::doPreconditionCheck( )
{
  // do something clever
  int16_t a;
  a = this->a_in.getValue();
  ( void )a;
}

void Consumer::doPostConditionCheck( )
{
  // nothing till now.
}
