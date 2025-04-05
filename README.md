# KTL

Kernel Template Library is open-source library providing CRT environment, STL-style containers and RAII tools for Windows Kernel programming.

* [Features](#features)
  * [C Runtime environment](#build-requirements)
  * [C++ Standard Library implementation](#C++-standard-library-implementation)
  * [CMake](#cmake)
* [Installation & Usage](#installation-&-Usage)
  * [CMakeLists.txt to build with a pre-built KTL](#cmakelists.txt-to-build-with-a-pre-built-ktl)
  * [Build requirements](#build-requirements)
* [Examples](#samples)
* [Roadmap for the near future](#roadmap-for-the-near-future)

## Credits

* Forked from [DymOK92's](https://github.com/DymOK93) [KTL](https://github.com/DymOK93/KTL)
* [avakar](https://github.com/avakar) for his [vcrtl](https://github.com/avakar/vcrtl) project which enables exceptions
* Extension from [wdk_template](https://github.com/build-cpp/wdk_template) to expand on the concept to have a C/C++ runtime

## Features

* C Runtime environment
    * **Exception handling mechanism** (now for x64 only)
    * Buffer security checks
    * C++ Standard compatible termination if execution is run out of control 
    * Construction and destruction of the non-trivial static objects
    * Memory allocation using new and delete
    * Filesystem Mini-Filter support routines


* C++ Standard Library implementation
    * `<atomic>` (now for x86 and x64 only)
    * Optimized, C++ Standard compatible `<algorithm>` library
    * `<allocator>` with standard allocators for different pool types
    * Boost-based implementation of the `compressed_pair`
    * Exceptions objects hierarchy (`std::exception` analog optimized for use in the kernel)
    * Iterators
    * MSVC-intrinsic-based coroutines
    * Mutexes, events and condition variables based on kernel synchronization primitives with RAII wrappers
    * Smart pointers (`unique_ptr`, `shared_ptr` and `weak_ptr`, `intrusive_ptr`)
    * `<type_traits>`
    * `<thread>` for managing driver-dedicated threads
    * `<tuple>`
    * `<optional>` with constexpr support
    * `unordered_node_map`, `unordered_node_set`, `unordered_flat_map` and `unordered_flat_set` using [robin-hood-hashing](https://github.com/martinus/robin-hood-hashing)
    * `<vector>`
    * Lock-free queue, `node_allocator` and some auxiliary algorithms 
    * [fmt](https://github.com/fmtlib/fmt/) as a string formatting library 
    * Tested with C++20


* CMake
    * Building of kernel drivers
    * Generating a test-signing certificate
    * Driver signing 

_Complete documentation in progress_.

## Installation & Usage
You can use KTL directly as driver CMake project subdirectory or link with pre-built KTL binaries applying `find_package()`.

It includes **2 static libraries**: 
* `ktl-runtime.lib` (CRT)
* `ktl.lib` (C++ tools)

### Basic cmake.toml for a driver
```toml
[cmake]
version = "3.10"
cmkr-include = "cmake/cmkr.cmake"

[variables]
CMAKE_MODULE_PATH = "${CMAKE_CURRENT_SOURCE_DIR}/cmake"

[project]
name = "KTL-Example"
languages = ["CXX"]
include-before = ["cmake/msvc-configurations.cmake"]

[fetch-content]
ktl = { git = "https://github.com/oopsmishap/ktl" }

[find-package.WDK]

[template.ktl-driver]
type = "executable"
add-function = "wdk_add_driver"
compile-features = ["cxx_std_20"]
link-libraries = ["ktl::ktl"]

[target.ktl-example]
type = "ktl-driver"
sources = ["src/**.cpp"]
include-directories = ["include"]
```

### Build requirements:
* [WDK10](https://learn.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk)
* Visual Studio 2019 (not tested on older versions)
* [cmkr](https://cmkr.build/)
* CMake 3.10 and higher

## Examples
* [KTL-Example](https://github.com/oopsmishap/KTL-Example) - A barebones driver utilizing KTL
* [CoroDriverSample](https://github.com/DymOK93/CoroDriverSample) - a simple driver demonstrating the use of C++20 coroutines in kernel mode 

## Roadmap for the near future 
* Linked lists and Red-Black-Tree containers
* Intrusive containers
* Coroutine-compatible async primitives
* **Exception handling on the x86 platforms**
