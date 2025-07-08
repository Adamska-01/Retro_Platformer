# <img src="https://github.com/Adamska-01/DeadFrame2D/blob/master/Shared/Resources/Logos/Window_Icon.png?raw=true" alt="DeadFrame2D" title="DeadFrame2D" width="32"/> DeadFrame2D Template

This is a minimal template project using the [**DeadFrame2D**](https://github.com/Adamska-01/DeadFrame2D) engine as a submodule. It's intended as a clean starting point for new 2D game projects.


## 💡 Overview
The template sets up a basic `Application` class and initializes the engine in `main()`, using DeadFrame2D’s modular structure, asset mounting system, and scene architecture.

### 🗂 Folder Structure

- 📦 `Assets/`  
  All game-specific assets (textures, sounds, configs) go here.  
  This folder is automatically copied to the build output directory post-build.

- 💻 `src/`, `include/`  
  Your application’s source code.

- 🛠️ `Core/`  
  Contains DeadFrame2D engine included as a git submodule and third-party dependencies.


## 🚀 Getting Started

### 1. Generate project files
Run the batch script to generate project files and set up the environment:

| Platform |            Script           |
| -------- | --------------------------- |
| Windows  | `Scripts/Setup-Windows.bat` |
| Linux    | `Scripts/Setup-Linux.sh`    |

This will also update the submodules and add a git hook to retrigger the setup when a branch is checked out.

### 2. Build
Use your IDE (Visual Studio, CLion, etc.) or run make/ninja depending on the generated files.

## 🧩 Dependencies
- [DeadFrame2D](https://github.com/Adamska-01/DeadFrame2D) Engine (as a submodule)
  - [SDL2](https://github.com/libsdl-org/SDL) ([Image](https://github.com/libsdl-org/SDL_image), [Mixer](https://github.com/libsdl-org/SDL_mixer), [ttf](https://github.com/libsdl-org/SDL_ttf))
  - [Box2D](https://github.com/erincatto/box2d)
  - [TinyXML2](https://github.com/leethomason/tinyxml2)
  - [nlohmann](https://github.com/nlohmann/json)
