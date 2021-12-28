# Language Native Enforcement Of Feature Requirements

This project demonstrates two methods for enforcing a feature requirement using `C++-20` language feature `concept`.
Another method to achieve the same objective without relying on `C++-20` language features is also demonstrated.

## Tools, Etc.
| Tool | Version Tested |
| :---         |     :---:      |
| CMake | 3.16.3 |
| GCC   | 10.3.0 |
| Clang   | 13.0.0 |
| C++ Standard   | 20 |

## Quick Start 
1. Build, including all available tests:
```bash 
./buildProject.sh -s 20 -c LLVM -b debug
```
To get available switches, read `./buildProject.sh` or run it without any arguments.
```bash 
./buildProject.sh
```
⚠️ The `-s` option must always be set to 20. The `-s` option tells the buildchain which C++ language standard to use for compiling. The demo included here requires C++20 standard.

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
Specified in _./CircularBuffer/NegativeCompilerTests_CPP17_, _./CircularBuffer/NegativeCompilerTests_CPP20Concepts_.

_NegativeCompilerTests_\<XXX\>_.cpp  are unit tests which are _expected_ to cause the compiler to abort the compilation process, "negative compiler tests". Such tests if naïvely included in the continuous integration job will break such automated jobs. Therefore, such negatve compiler tests here are wrapped in script, which is then integrated into the continuous integration pipeline. 
As a result, a build option as below:

```bash
./buildProject.sh -s 20 -c LLVM -b debug
```

will also run all unit tests, including "negative compiler tests":


```bash
      Start 12: CircularBuffer_runNegativeCompilerTests_CPP20Concepts
12/13 Test #12: CircularBuffer_runNegativeCompilerTests_CPP20Concepts ...   Passed    1.95 sec
      Start 13: CircularBuffer_runNegativeCompilerTests_CPP17
13/13 Test #13: CircularBuffer_runNegativeCompilerTests_CPP17 ...........   Passed    1.96 sec
```
