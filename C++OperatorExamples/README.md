# Types As Operators

## Objective
Demonstrates the usage of types as operators, instead of using `static_cast` in order to convert between types.
Useful when a value assigned to an instance of a class must be assigned to a differing type.
Most common case is is assignment of a enumerated value to a different type:
```c++
  void f (int flag){}
  enum class MyEnumeration : uint8_t 
  { 
      OK = 0U, 
      ERROR = 1U, 
      APOCALYPSE = 2U 
  };
  MyEnumeration e{MyEnumeration::ERROR};
  
  f(e); // Error since there is no specified conversion from enum to int

  // Usual solution. static_cast is splattered all over client code.
  f(static_cast<int>(e));

  // Goal: Method to handle type conversions inside the class while keeping
  // user experience as if no type conversions are required.
  //
  // Not an error. MyEnumeration handles type conversions trasparently to the user.
  f(e); 
  
```
## Tools, Etc.
| Tool | Version Tested |
| :---         |     :---:      |
| CMake | 3.16.3 |
| GCC   | 9.3.0 |
| Clang   | 10.0.0.4 |
| C++ Standard   | 11, 14, 17 |
| Special Flags Used | `Werror=conversion` Purpose: Compiler reports an error if type conversion is implicit.

## Quick Start 
1. Build, including all available tests:
```bash 
./buildProject.sh -s 11 -c LLVM -b debug
```
To get available switches, read `./buildProject.sh` or run it without any arguments.
```bash 
./buildProject.sh
```

## Compiler Settings
All used compiler settings, including flags can be found in _./BuildScripts/SetBuildChainSpecifications.cmake_

## VSCode and Remote Containers
All required tools are available in a docker image that is described in the included Dockerfile.
The _Remote Containers_ plugin of VSCode is able to automatically build the required container and bring up the development environment.

## Pre-Requisities
1. [Visual Studio Code](https://code.visualstudio.com) 
2. Visual Studio Code plugin [Remote Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)
3. Docker with access to internet.

### Tested On
1. Ubuntu-20.04 (host), Ubuntu-20.04 (Container Base Image)
2. Machine with direct connection to internet. 

### Configurations for Machines Behind A Proxy
1. You may require an *authenticating proxy* such as [cntlm](http://cntlm.sourceforge.net)
2. You will need to configure Docker to work with your proxy 
3. You will need to configure ./devcontainer/devcontainer.json to work with proxy.

### How To Use 
1. Ensure pre-requisites are met,
2. Clone this repository, 
3. Open Visual Studio Code, Run the Remote-Containers: `Open Folder in Container...` command and select the folder where (the master branch of) this repository is cloned.
   1. See [this link](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) for more help.

## Unit Tests
Specified in _./GoogleTests/PositiveTests.cpp_.
An example of type conversion

## Brief Idea of The Approach
Use types as conversion operators like so (file: _./library/CastFromEnum.hpp_)
```c++
  operator double( )
  {
    return static_cast< double >( this->_value );
  }
```
As a result, the client code does not require any explicit `static_cast` 
(file: _./GoogleTests/PositiveTests/_, lines 62:70):
```c++
  CastFromEnum e3{ CastFromEnum::MyEnumeration::ERROR };
  // assign the value of the object, an enumeration. Conversion is handled inside the class itself
  double double_response = e3;
  EXPECT_DOUBLE_EQ( double_response, static_cast< double >( CastFromEnum::MyEnumeration::ERROR ) );

  CastFromEnum e4{ CastFromEnum::MyEnumeration::ERROR };
  // assign the value of the object, an enumeration. Conversion is handled inside the class itself
  bool bool_response = e3;
  EXPECT_FALSE( bool_response );
```
