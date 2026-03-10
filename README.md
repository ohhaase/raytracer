# Relativistic Ray Tracer

Relativistic Ray Tracer project for rendering black holes in real time. Originally was developed in Visual Studio without version control (I was young and naive). Now ported to a proper repository using CMake for building. Ported mainly as a means of practicing CMake and C++ projects outside of VS. Will possibly update in the future with more features for fun.

To build, we first need to get CMake initialized. Run

```
cmake -G "Unix Makefiles" -B build -DCMAKE_CXX_COMPILER='g++'
```

This makes a build directory, forces cmake to make a Unix Makefile, and sets the compiler to GNU++. 

Note: Maybe should relax the GNU++ specification in the future.

Then, to generate the executable, use

```
cmake --build build
```

This generates an executable in ./build/.

To run the executable, use

```
./build/<executablename> <sim parameters>
```

This will generate the resulting data relative to the main directory.
