# Ray Tracing in One Weekend with SDL

A C++ implementation of the ray tracer from "Ray Tracing in One Weekend" using SDL for graphics display.

## Features

- Real-time ray tracing rendering
- Diffuse materials (Lambertian shading)
- Sphere primitives
- Anti-aliasing
- Camera system with adjustable viewport
- SDL-based graphics output

## Building

This project uses CMake and requires SDL3. 

### Prerequisites
- CMake 3.16 or higher
- C++11 compatible compiler
- SDL3 (included as submodule)

### Build Instructions

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running

After building, run the executable from the build directory:

```bash
./raytracing
```

The program will render a scene with spheres and display it in an SDL window.

## Project Structure

- `renderer.cpp` - Main application and rendering loop
- `HeaderFiles/` - Contains all header files:
  - `camera.h` - Camera system
  - `color.h` - Color utilities and ray tracing logic
  - `Ray.h` - Ray class
  - `vec3.h` - 3D vector mathematics
  - `sphere.h` - Sphere primitive
  - `hittable.h` - Base class for hittable objects
  - `hittableList.h` - Container for multiple objects
  - `material.h` - Material definitions
  - `interval.h` - Interval mathematics
  - `utility.h` - Utility functions

## Based On

This implementation follows the "Ray Tracing in One Weekend" book by Peter Shirley, Trevor David Black, and Steve Hollasch.
