#ifndef SHARED_MEMORY_CONNECT_INL_
#define SHARED_MEMORY_CONNECT_INL_

template < typename T >
SharedMemoryConnect< T > &SharedMemoryConnect< T >::to( T *to )
{
  to = this->_memory;
  return *this;
}

template < typename T >
SharedMemoryConnect< T > &SharedMemoryConnect< T >::from( T *from )
{
  from = this->_memory;
  return *this;
}
#endif
