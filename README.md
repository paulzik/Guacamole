# Guacamole Engine

A small **3D game engine** I created to experiment with the principles of Game Engines and how to implement interesting features in graphics.

Guacamole is written in modern C++ (C++20) with an Entity–Component–System core, an OpenGL renderer and a Dear ImGui-based editor.


https://github.com/user-attachments/assets/26680e1d-bddb-4519-9cfb-4078e62016bb

Currently is for Windows x64 only.

## Features

- **Entity–Component–System** — entities composed of components, updated by
  independent systems through a central `SystemManager`.
- **OpenGL 3.3 renderer** — Phong lighting with multiple point and directional
  lights, materials and shaders, textured meshes.
- **Skeletal animation** — skinned mesh rendering with an `Animator`, skeletons,
  and animation playback.
- **Physics** — rigid bodies and box/sphere colliders powered by
  [Bullet](https://github.com/bulletphysics/bullet3).
- **3D audio** — positional audio sources and a listener via OpenAL (MP3 decoding
  through minimp3).
- **Asset importing** — a pluggable importer registry backed by
  [Assimp](https://github.com/assimp/assimp) for models (`.fbx`, `.obj`),
  `stb_image` for textures (`.png`), shaders (`.vert`/`.frag`), and audio (`.mp3`).
- **In-engine editor** (Dear ImGui):
  - Scene graph / hierarchy view
  - Inspector with per-component editors (transform, camera, lights, renderers,
    colliders, animator)
  - Console window and menu bar
  - Object selection with transform and collider **gizmos**
- **Primitive factory** — built-in cube and sphere meshes.

## Tech stack

| Area        | Library |
|-------------|---------|
| Language    | C++20 |
| Windowing / input | [SDL3](https://libsdl.org) |
| Rendering   | OpenGL 3.3 core + [GLEW](https://glew.sourceforge.net) |
| Math        | [GLM](https://github.com/g-truc/glm) |
| Editor UI   | [Dear ImGui](https://github.com/ocornut/imgui) |
| Physics     | [Bullet](https://github.com/bulletphysics/bullet3) |
| Audio       | OpenAL + [minimp3](https://github.com/lieff/minimp3) |
| Model I/O   | [Assimp](https://github.com/assimp/assimp) |
| Images      | [stb_image](https://github.com/nothings/stb) |
| Build       | CMake |


## Building

The project targets **Windows x64** and is built with **Visual Studio** (MSVC) via
CMake. It works with any recent Visual Studio (2022 or newer) — you just point CMake
at the version you have installed (see below).

### Prerequisites

- Windows 10/11 (x64)
- [Visual Studio](https://visualstudio.microsoft.com/) 2022 or newer, with the
  *Desktop development with C++* workload
- [CMake](https://cmake.org/) 3.16 or newer (bundled with recent Visual Studio)
- [Git](https://git-scm.com/) with [Git LFS](https://git-lfs.com/)
  (some vendored `.lib` files are stored via LFS)

### Clone

`Assimp` and `Bullet` are Git submodules, so clone recursively and pull LFS files:

```bash
git clone --recursive https://github.com/paulzik/Guacamole.git
cd Guacamole
git lfs pull
```

If you already cloned without `--recursive`:

```bash
git submodule update --init --recursive
git lfs pull
```

### Configure & build

From the `CustomEngine` directory:

```bash
cmake -S . -B build -A x64
cmake --build build --config Debug
```

By default CMake generates for the newest Visual Studio it finds. If you have more
than one version installed, pin the generator to the one you'll open the solution in
so the project uses a toolset that IDE has:

```bash
# Visual Studio 2022
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
# Visual Studio 2026
cmake -S . -B build -G "Visual Studio 18 2026" -A x64
```

### Run

The executable expects to run with the `Assets/` folder reachable; CMake sets the
Visual Studio debugger working directory to the build output folder. From that
folder:

```bash
./build/Debug/CustomEngine.exe
```

You can also open the generated solution in Visual Studio — `build/CustomEngine.sln`,
or `build/CustomEngine.slnx` on Visual Studio 2026 and newer — set `CustomEngine` as
the startup project, and run with F5.

## Controls

The demo scene loads with a fly camera:

- **Hold right mouse button** to look around
- **W / A / S / D** — move forward / left / back / right
- **Q / E** — move down / up
- **Left Alt + right mouse** — orbit around the target
- Click objects in the viewport or scene graph to select them and edit them in the
  Inspector.
