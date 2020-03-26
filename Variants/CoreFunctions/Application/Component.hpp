#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <Application/BaseComponent.hpp>
namespace RomanoViolet
{
  class Component : public TypeHighAssuranceComponent
  {
  public:
    enum class SupportedVariants : short {
      VariantWithAdditionlInterfaces = 0U,
      VariantWithIdenticalInterfaces = 1U
    };

    Component( ) = default;

    void initialize( );
    void doPreconditionCheck( );
    void compute( );
    void doPostConditionCheck( );

  private:
    ErrorCode _error;
  };
}  // namespace RomanoViolet

#endif  // COMPONENT_HPP_
