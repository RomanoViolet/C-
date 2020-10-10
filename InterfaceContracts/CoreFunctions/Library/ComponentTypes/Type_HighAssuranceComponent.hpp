#ifndef TYPE_HIGH_ASSURANCE_COMPONENT
#define TYPE_HIGH_ASSURANCE_COMPONENT

class TypeHighAssuranceComponent
{
public:
  TypeHighAssuranceComponent( ) = default;
  virtual void doPreconditionCheck( ) = 0;
  virtual void doPostConditionCheck( ) = 0;
  virtual void initialize( ) = 0;
  virtual void compute( ) = 0;
  virtual ~TypeHighAssuranceComponent( ) = default;
};

enum class SILLevels { QM = 0U, A = 1U, B = 2U, C = 3U, D = 4U };

template < SILLevels SILLevel >
class SIL
{
public:
  int a;
};

#endif  // TYPE_HIGH_ASSURANCE_COMPONENT
