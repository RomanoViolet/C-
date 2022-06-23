#include <Application/Consumer.hpp>
#include <Application/Producer.hpp>
#include <ComponentTypes/SharedMemoryConnect.hpp>
#include <iostream>
auto main( ) -> int
{
  Producer p;
  Consumer c;
  SharedMemoryConnect< int16_t > shm;
  shm.from( p.a_out.toPtr( ) ).to( c.a_in.toPtr( ) );
  p.compute( );
  std::cout << "Ran producer-consumer app" << std::endl;
  return 0;
}
