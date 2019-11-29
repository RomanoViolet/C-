# PIMPL with Placement New
## Uses `std::unique_ptr`

## Details
The approach uses a unique pointer to manage a PIMPL class allocated on a pre-allocated piece of memory (static memory allocation, on the stack).

## Verification
GCC flag `-Wplacement-new=` can be used to verify whether the class did (or did not) fill into pre-allocated memory.
Example, in case of static allocation of 10 bytes (file: `FastPIMPLExample`, expression `char allocatedMemory[10];`) but with 
the `impl` class containing a much larger member (file: `FastPIMPLExample.cpp`, expression `int internalStorage[100]`) the following error is reported:

```
FastPIMPLExample.cpp:29:98: warning: placement new constructing an object of type ‘MyClassWithFastPimpl::impl’ and size ‘416’ in a region of type ‘char [10]’ and size ‘10’ [-Wplacement-new=]
 MyClassWithFastPimpl::MyClassWithFastPimpl() : pimpl{new (MyClassWithFastPimpl::allocatedMemory) impl}

```