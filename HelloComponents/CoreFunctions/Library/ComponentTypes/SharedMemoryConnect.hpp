#ifndef SHARED_MEMORY_CONNECT_HPP_
#define SHARED_MEMORY_CONNECT_HPP_
#include <memory>

template < typename T >
class SharedMemoryConnect
{
public:
  SharedMemoryConnect( )
  {
    _memory = std::make_shared< T >( );
  };

  SharedMemoryConnect &to( T *to );
  SharedMemoryConnect &from( T *from );

  ~SharedMemoryConnect( )
  {
    _memory.reset( );
  }

protected:
private:
  std::shared_ptr< T > _memory;
};
#include "SharedMemoryConnect.inl"
#endif
