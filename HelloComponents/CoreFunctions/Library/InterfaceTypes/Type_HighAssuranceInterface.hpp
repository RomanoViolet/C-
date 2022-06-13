#ifndef TYPE_HIGH_ASSURNACE_INTERFACE
#define TYPE_HIGH_ASSURNACE_INTERFACE


  class TypeHighAssuranceInterface
  {
  public:
    TypeHighAssuranceInterface( ) = default;
    virtual void doPreconditionCheck( ) = 0;
    virtual ~TypeHighAssuranceInterface( ) = default;
  };


#endif  // TYPE_HIGH_ASSURNACE_INTERFACE
