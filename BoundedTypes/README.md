# Types with Upper and Lower Bounds

## Objective
Demonstrates the concept of _bounded types_ wherein a type's maximum and minimum values are provided at compile time.
Useful in applications where in a symbol's range must be restricted to a pre-computed (design) range.

## Tools, Etc.
| Tool | Version Tested |
| :---         |     :---:      |
| CMake | 3.10.2 |
| GCC   | 7.4.0-1 |
| Clang   | 8.0.0.3 |
| C++ Standard   | 11, 14, 17 |
## Quick Start 
1. Declare a type and bounds:
```c++
#include <Library/SafeTypes.hpp>
// Lower bound: 1/2 = 0.5F. Upper bound: 3/4 = 0.75F
using VelocityType = RomanoViolet::SafeType< Fraction( 1, 2 ), Fraction( 3, 4 ) >;
```
2. Do something with it:
```c++
  // Lower bound: 1/2 = 0.5F. Upper bound: 3/4 = 0.75F
  VelocityType v = 0.5F;

  VelocityType w = v.getValue( ) + 0.20F;
  // ...
```
3. Build 
```bash 
./buildProject.sh -s 11 -c LLVM -b debug
```
To get available switches, read `./buildProject.sh` or run it without any arguments.
```bash 
./buildProject.sh
```

## Safety in Bounded Types
A bounded type will always ceil or floor the stored value based on the provided upper and lower bounds.


## Structure
```bash
├── BuildScripts                 | build scripts
│   ├── CMake                    | CMake helper scripts
│   └── Docker                   | Shell scripts which invoke CMake
├── CoreFunctions                | This project
│   └── Library                  | Bounded types defined here.
├── Documentation                | Empty for now. 
├── GoogleTests                  | Test cases.
│   ├── NegativeTest             | Test for stuff that should happen.
│   └── PositiveTests            | Test for stuff that should not happen.
├── Requirements                 | Empty for now.
└── Tools                        | Useful for development using remote containers. 
    └── DockerBasedDevelopment
```
## Brief Approach
### General
Look into `CoreFunctions/Library/SafeTypes.hpp`, and thereon look into the header file based on the C++ standard of your choice.

Formally, `SafeType` is a template class which expects to be provided upper and lower bounds at compile time:
```c++
template <   int NumeratorForMinBound = 1,
             int DenominatorForMinBound = 1,
             int NumeratorForMaxBound = 1,
             int DenominatorForMaxBound = 1 >
  class SafeType
  {
      ...
  }
```
It is expected that both upper and lower bounds are to be specified as a rational number like so:
```
Numerator/Denominator 
```
where both `Numerator` and `Denominator` are integers.

### Sugar 
A convenience wrapper has been provided in `CoreFunctions/Library/CustomTypes.hpp` which allows the developer to wrap a safetype like so:
```c++
#include <Library/SafeTypes.hpp>
// Lower bound: 1/2 = 0.5F. Upper bound: 3/4 = 0.75F
using VelocityType = RomanoViolet::SafeType< Fraction( 1, 2 ), Fraction( 3, 4 ) >;
```

where `Fraction` is a convenience (macro) provided to improve readability:
```c++
#define Fraction( a, b ) a, b
```
Thereafter, a declared type e.g., `VelocityType` may be used in the application like so:
```c++
VelocityType v = 0.9; // Within upper and lower bounds.
// .. do some stuff with v.
```


### Special Case 
For special case of integer bounds, one can instantiate the class using only two integers.
```c++
// Lower bound = 1.F. Upper bound = 4.F
using CountingType = RomanoViolet::SafeType< 1, 4 >;
```
**Note:** Though the bounds are supplied as Rationals, or integers, the type stores a value as a float.

## Operators, etc.
A limited number of operators are provided, specifically for addition and subtraction.
Copy constructor as well as assignment operator is also provided.

## Tests 
Are available in `GoogleTests` folder.

## Design Description
Coming soon.

## Improvements
1. Currently, there is a lot of code copy between implementations for C++11, C++14, and C++17. This can be reduced.
2. C++11 implementation itself could be improved.
3. Design description needs to be written. 
4. A requirement to specify the _kernel type_ may be useful. At the moment, all objects instantiated from `SafeType` store a value as a `float`.
