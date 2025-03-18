# OpenGL-Sandbox

## Overview

OpenGL-Sandbox is an interactive OpenGL playground designed for rendering 3D and 2D objects with various lighting effects and camera controls. This project serves as a learning and experimentation platform for graphics programming, demonstrating key OpenGL concepts. Each scene has separate behavior and presents different concepts.

## Features

- **3D and 2D Rendering**: Draws various geometric shapes and models with OpenGL.
- **Lighting System**: Supports ambient, diffuse, and specular lighting, including directional, point, and spotlights.
- **Camera Control**: Implements a movable camera for interactive navigation.
- **Scene Management**: Various predefined scenes demonstrating different concepts.
- **Shader Support**: Custom shader programs for graphical effects.
- **Texture Mapping**: Applies textures to objects.

## Project Structure

```
OpenGL-Sandbox/
├── src/
│   ├── camera/         # Camera handling functionality
│   ├── core/           # Application and window management
│   ├── graphics/       # Rendering, shaders, textures, lighting, geometry
│   │   ├── geometry/   # Meshes, models, polygons, spheres
│   │   ├── lightning/  # Lighting types and effects
│   ├── scenes/         # Scene implementations and management
├── res/                # Resources such as shaders, textures
├── CMakeLists.txt      # Build configuration
├── main.cpp            # Application entry point
└── README.md           # Project documentation
```

## Getting Started

### Prerequisites

The following dependencies are required to build and run the project:

- C++ Compiler
- OpenGL
- **GLFW**: A library for handling window creation, input, and OpenGL context management.
- **GLEW**: An OpenGL extension loader that simplifies accessing modern OpenGL features.
- **Assimp**: A library for importing and processing 3D model files.
- **Dear ImGui**: A GUI library for creating in-application user interfaces.
- **GLM**: A mathematics library optimized for OpenGL, used for transformations, vector operations, and linear algebra calculations.
- **stb\_image**: A lightweight library for loading image files for textures.
- **CMake**: A build system for project configuration and compilation.

**Note**: The project uses CMake's `FetchContent` to automatically download and set up these dependencies, so manual installation is not required unless you wish to configure them separately.

### Installation

#### Using Visual Studio (Windows)
1. Clone the repository:
   ```sh
   git clone https://github.com/ErezMatt/OpenGL-Sandbox.git
   cd OpenGL-Sandbox
   ```
2. Create a build directory and generate Visual Studio project files:
   ```sh
   mkdir build && cd build
   cmake .. -G "Visual Studio 16 2019"
   ```
3. Copy `res` folder to `build`
4. Open the generated `.sln` file in Visual Studio.
5. Set the project as the startup project and build it.
6. Run the application from Visual Studio.

## Usage

- Use **WASD** keys + **mouse** to control the camera.
- Press **ESC** to exit the camera mode.
- Select different scenes.
---
