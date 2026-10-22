# RayCaster

A small Wolfenstein 3D-style raycasting demo written in C with SDL2. The renderer builds a pseudo-3D scene from a 2D grid map using DDA wall casting, textured wall slices, and floor casting.

## Features

- Real-time raycasting renderer with a 70° field of view.
- DDA-based wall intersection and perspective-correct wall height.
- Textured walls and floor rendered from PNG assets.
- First-person movement and rotation.
- Collision checks against the map grid.
- 24×24 demonstration map with multiple wall materials.
- SDL2 streaming texture used as the software-rendered frame buffer.

## Controls

| Key | Action |
| --- | --- |
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| Close window | Exit the application |

## Screenshot

![RayCaster demo](screenshots/raycast-demo.png)

## Project structure

```text
.
├── src/
│   ├── main.c       # Game loop, map, ray casting, movement
│   ├── app.*        # SDL window, renderer, and frame buffer setup
│   ├── draw.*       # Scene, wall, texture, and minimap drawing helpers
│   ├── input.*      # Keyboard state handling
│   ├── timer.*      # Frame timing helpers
│   ├── defs.*       # Screen, map, and rendering constants
│   └── player.h     # Player state
├── pics/            # 64×64 PNG wall and floor textures
├── libs/SDL_image/  # Vendored SDL_image source
├── CMakeLists.txt
└── README.md
```

## Requirements

- CMake 3.19 or newer
- A C11-compatible compiler
- SDL2 development libraries
- SDL_image support; the SDL_image source is included in `libs/SDL_image`

On macOS with Homebrew, install SDL2 before configuring the project:

```bash
brew install sdl2
```

## Build

Configure and build from the repository root:

```bash
cmake -S . -B build
cmake --build build
```

The current CMake target produces an executable named `sg_test`.

## Run

The program loads textures through paths relative to the executable's working directory. Run it from the build directory so `../pics` resolves to the repository's texture folder:

```bash
cd build
./sg_test
```

On Windows, run the corresponding executable from the build directory, for example:

```powershell
cd build
.\sg_test.exe
```

## Rendering pipeline

For each screen column, the renderer:

1. Builds a ray from the player's direction and camera-plane offset.
2. Walks through the map grid with DDA until it hits a wall cell.
3. Corrects the wall distance to reduce fisheye distortion.
4. Projects the wall into a vertical screen slice.
5. Samples the matching texture column and darkens side-facing walls.
6. Casts floor samples for the lower and upper parts of the scene.

The final pixel buffer is uploaded to an SDL texture and presented every frame.

## Notes

- The demo currently uses a hard-coded map and player start position in `src/main.c`.
- The visible scene uses `redbrick.png`, `bluestone.png`, `colorstone.png`, and `wood.png`; the remaining images are available for extending the map.
- The repository contains local working-tree changes outside this README; they were preserved while documenting the project.

