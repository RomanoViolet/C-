#ifndef TYPE_HIGH_ASSURNACE_INTERFACE
#define TYPE_HIGH_ASSURNACE_INTERFACE

namespace RomanoViolet
{
  class TypeHighAssuranceInterface
  {
  public:
    TypeHighAssuranceInterface( ) = default;
    virtual void doPreconditionCheck( ) = 0;
    void setValue( const T &value );
    virtual ~TypeHighAssuranceInterface( ) = default;
  };
}  // namespace RomanoViolet

#endif  // TYPE_HIGH_ASSURNACE_INTERFACE
