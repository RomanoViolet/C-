#include <Library/InterfaceTypes/InterfaceA.hpp>
namespace RomanoViolet
{
  void InterfaceA::doPreconditionCheck( )
  {
    // The members making up this interface are known.
    if ( this->velocity.getValue( ) > 0.6F && this->minWithIntegerBounds.getValue( ) < 0.4F ) {
      // go back to safe defaults.
      this->velocity = 0.5F;
      this->minWithIntegerBounds = 0.3F;
    }
  }
}  // namespace RomanoViolet
