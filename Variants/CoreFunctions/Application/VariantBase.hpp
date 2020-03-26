#ifndef VARIANT_BASE_HPP_
#define VARIANT_BASE_HPP_

#include <Application/BaseComponent.hpp>

namespace RomanoViolet
{
  template < BaseComponent::SuportedVariants selectedVariant >
  class Variant : BaseComponent
  {
  public:
    Variant( ) : BaseComponent( )
    {
    }
  };
}  // namespace RomanoViolet

#endif  // !VARIANT_BASE_HPP_
