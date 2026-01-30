# Raylearner

A real-time 2D physics simulation built with [Raylib](https://www.raylib.com/) demonstrating fixed timestep integration, elastic collisions with energy loss, and interactive controls.

## Features

- **Real-time Physics Simulation**: Accurate gravity simulation with proper unit conversions
- **Fixed Timestep Integration**: Uses the accumulator pattern for deterministic physics regardless of frame rate
- **Elastic Collisions**: Ball bounces off walls with configurable coefficient of restitution (energy loss)
- **Interactive Controls**: Modify ball size and reset simulation in real-time
- **Debug Visualization**: Live display of velocity, acceleration, and FPS
- **Modern C23**: Clean, professional code using modern C features like `constexpr`

## Physics Details

### Fixed Timestep with Accumulator Pattern

The simulation uses a fixed timestep (1/12000 seconds) for physics updates, independent of the rendering frame rate. This ensures:
- Deterministic physics behavior across different hardware
- Numerical stability in integration
- Reproducible simulations

The accumulator pattern (popularized by Glenn Fiedler's [Fix Your Timestep](https://gafferongames.com/post/fix_your_timestep/)) works by:
1. Accumulating elapsed frame time
2. Running physics updates in fixed increments
3. Preventing "spiral of death" by capping maximum frame time

### Integration Method

The simulation uses **semi-implicit Euler integration** (also called symplectic Euler):
```c
velocity += acceleration * dt
position += velocity * dt
```

This method is more stable than explicit Euler for physics simulations, particularly for oscillating systems.

### Coefficient of Restitution

Collisions with walls include energy loss via the coefficient of restitution (default: 0.92):
- `1.0` = perfectly elastic (no energy loss)
- `0.0` = perfectly inelastic (ball doesn't bounce)
- `0.92` = ball retains 92% of velocity after each collision

### Coordinate System

- **Origin**: Top-left corner (0, 0)
- **X-axis**: Increases to the right
- **Y-axis**: Increases downward
- **Units**: Pixels (with conversion utilities for meters)

### Unit Conversions

The simulation converts between physical units (meters) and screen coordinates (pixels):
- **Conversion factor**: 3779.5275591 pixels per meter
- **Based on**: 96 DPI standard (1 inch = 96 pixels, 1 meter ≈ 39.37 inches)
- **Gravity**: 9.8 m/s² converted to pixels/s²

## Prerequisites

- **Raylib**: Version 4.0 or higher
  - macOS: `brew install raylib`
  - Ubuntu/Debian: `sudo apt install libraylib-dev`
  - Windows: See [Raylib installation guide](https://github.com/raysan5/raylib#build-and-installation)
- **CMake**: Version 3.15 or higher
- **C Compiler**: Supporting C23 standard
  - Clang 15+ (recommended)
  - GCC 13+
  - MSVC 2022+

## Building

### macOS / Linux

```bash
# Clone or download the repository
cd raylearner

# Configure with CMake
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build

# Run
./build/raylib_app
```

### Debug Build

For development with debug symbols and no optimization:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### macOS Frameworks

On macOS, the build automatically links required frameworks:
- CoreVideo
- IOKit
- Cocoa
- GLUT
- OpenGL

## Usage

### Running the Simulation

```bash
./build/raylib_app
```

### Controls

| Key | Action |
|-----|--------|
| **A** | Increase ball size (double) |
| **S** | Decrease ball size (halve) |
| **SPACE** | Reset ball to initial state |
| **ESC** | Exit application |

### On-Screen Information

The simulation displays:
- Title: "Raylearner Physics Simulation"
- FPS counter
- Current velocity (pixels/second)
- Current acceleration (pixels/second²)
- Control hints

## Project Structure

```
raylearner/
├── src/
│   └── main.c              # Main simulation code
├── build/                  # Build artifacts (generated)
├── .github/
│   └── workflows/
│       └── ci.yml          # GitHub Actions CI configuration
├── CMakeLists.txt          # CMake build configuration
├── .clang-format           # Code formatting rules (LLVM style)
├── .gitignore              # Git ignore patterns
├── LICENSE                 # Unlicense (public domain)
└── README.md               # This file
```

### Code Organization

`src/main.c` is organized into clear sections:

1. **Constants**: Window dimensions, physics parameters, conversion factors
2. **Types**: Data structures (Ball)
3. **Function Declarations**: Forward declarations with documentation
4. **Main**: Initialization, game loop, and rendering
5. **Function Implementations**: Physics and utility functions

## Code Style

The project follows TigerBeetle-inspired code style:
- **Naming**: `snake_case` for functions and variables
- **Formatting**: LLVM style with 4-space indentation
- **Documentation**: Comprehensive comments explaining the "why"
- **Organization**: Clear section separators and logical grouping
- **Modern C**: Uses C23 features like `constexpr` for compile-time constants

Format code with:
```bash
clang-format -i src/main.c
```

## Technical Details

### Compilation Flags

- **All Builds**: `-Wall -Wextra -Wpedantic` (strict warnings)
- **Debug**: `-g -O0` (debug symbols, no optimization)
- **Release**: `-O3 -DNDEBUG` (maximum optimization, disable assertions)

### Performance

- **Target FPS**: 120 (configurable via `SetTargetFPS`)
- **Physics Rate**: 12,000 steps per second (SIM_DT = 1/12000)
- **Typical Physics Steps**: ~10-100 steps per frame depending on FPS

### Assertions

Debug builds include runtime assertions to validate:
- Ball position stays within screen bounds after collision handling
- Physics calculations maintain numerical stability

## Contributing

Contributions are welcome! This is a learning project demonstrating physics simulation concepts.

### Ideas for Enhancement

- Multiple balls with ball-to-ball collision detection
- User-adjustable gravity (G-key for increase, H-key for decrease)
- Mouse interaction: click and drag to throw the ball
- Trail rendering to visualize motion path
- Different ball materials with varying restitution coefficients
- Adjustable simulation speed (time scaling)
- Record and playback simulation states

### Submitting Changes

1. Fork the repository
2. Create a feature branch: `git checkout -b feature-name`
3. Format code: `clang-format -i src/*.c`
4. Test locally: `cmake --build build && ./build/raylib_app`
5. Commit with descriptive message
6. Submit a pull request

## License

This project is released into the **public domain** under the [Unlicense](LICENSE).

You are free to:
- Use this code for any purpose (personal, educational, commercial)
- Modify and distribute without restriction
- Include in your own projects without attribution (though attribution is appreciated!)

See the [LICENSE](LICENSE) file for the full legal text.

## Acknowledgments

- **Raylib**: Excellent library for game and graphics programming - [raylib.com](https://www.raylib.com/)
- **Glenn Fiedler**: "Fix Your Timestep" article explaining the accumulator pattern - [gafferongames.com](https://gafferongames.com/post/fix_your_timestep/)
- **TigerBeetle**: Inspiration for clean, professional C code style - [tigerbeetle.com](https://tigerbeetle.com/)

## References

- [Raylib Documentation](https://www.raylib.com/cheatsheet/cheatsheet.html)
- [Fix Your Timestep - Glenn Fiedler](https://gafferongames.com/post/fix_your_timestep/)
- [Game Physics - Erin Catto (Box2D)](https://box2d.org/publications/)
- [Real-Time Collision Detection - Christer Ericson](https://realtimecollisiondetection.net/)

---

**Note**: This is a learning project demonstrating physics simulation concepts. For production physics engines, consider using established libraries like [Chipmunk2D](https://chipmunk-physics.net/) or [Box2D](https://box2d.org/).
