# CUB3D

Cub3D is a project from the 42 Paris Common Core. It's a first-person 3D game written in C using the MiniLibX library, inspired by the legendary *Wolfenstein 3D*. The goal is to build a raycasting engine from scratch: turning a 2D grid map into a 3D view, with textured walls, a game loop and real-time input handling.

## Table of Contents

1. [Description](#description)
2. [Demo](#demo)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Controls](#controls)
6. [Map format](#map-format)
7. [How it works](#how-it-works)
8. [Project structure](#project-structure)
9. [Challenges](#challenges)
10. [Roadmap](#roadmap)
11. [Credits](#credits)
12. [License](#license)

## Description

You explore a cozy, slightly eerie maze through the eyes of a cat: soft pink-violet fog, warm light, and paws swiping at the screen. Doors slide open (and closed) with a click, and the map slowly reveals itself as you explore.

As a 42 project, it follows the school's strict coding rules (the Norm): functions of 25 lines max, 5 functions per file, no `for` loops, restricted standard library usage, and a focus on clean, maintainable code.

### Features

**Mandatory part**
- Raycasting engine (DDA algorithm) with a fish-eye–free perspective
- Different wall textures for each direction (North, South, East, West)
- Custom floor and ceiling colors
- Smooth movement and rotation
- Full `.cub` file parsing and validation, with explicit error messages

**Bonus and extras**
- Wall collisions with a player hitbox
- Mouse look
- Animated sliding doors that can be opened **and closed**, with collisions on the door panels when the door is half open
- Round minimap with:
  - **fog of war**: only the cells you have actually seen are shown
  - live **field of view** cone, stopped by walls
  - door states (closed / moving / open)
  - optional **rotating mode** (the player always faces up) with a north indicator
  - mouse wheel zoom
- Full-screen map (with the same fog of war), zoomable
- Animated paw attack on click
- **Ambiance**: distance fog that fades into a pink-violet color, warm light tint, directional wall shading, and a vignette
- Frame-rate–independent movement (delta time)
- Debug HUD: FPS, frame time, position, view angle, wall distance, door state

## Demo

<!-- Add your GIFs in a demo/ folder -->
<p align="center">
  <img src="demo/demo_explore.gif" width="45%" alt="Exploring the maze">
  <img src="demo/demo_doors.gif" width="45%" alt="Opening and closing doors">
</p>
<p align="center">
  <img src="demo/demo_minimap.gif" width="45%" alt="Minimap with fog of war">
  <img src="demo/demo_big_map.gif" width="45%" alt="Full-screen map">
</p>

## Installation

The game needs the MiniLibX library. The Makefile automatically clones it when you run `make`, but this may vary depending on your OS. Feel free to change the repo link in the Makefile to match the MiniLibX version that suits your system.

On Ubuntu, you will also need the X11 development packages:

```
sudo apt install xorg libxext-dev libbsd-dev
```

### Supported OS

- **Ubuntu**: Tested and working
- **macOS**: Untested (MiniLibX for macOS has a different API)
- **Fedora**: Not compatible (due to MiniLibX function incompatibilities)

## Usage

1. Build the project:

```
make
```

2. Run the game with a map:

```
./cub3d map/map.cub
```

Other Makefile rules: `make clean` (object files), `make fclean` (objects, binary and MiniLibX), `make re`.

## Controls

| Key | Action |
|-----|--------|
| W / Z | Move forward |
| S | Move backward |
| A / Q | Strafe left |
| D | Strafe right |
| Mouse | Look around |
| Left click | Paw attack / open or close the door in front of you |
| Mouse wheel | Zoom the minimap (or the full-screen map when it is open) |
| M | Open / close the full-screen map |
| R | Toggle the rotating minimap |
| TAB | Show / hide the debug HUD |
| ESC | Quit |

Both QWERTY (WASD) and AZERTY (ZQSD) layouts are supported.

## Map format

Maps are text files with the `.cub` extension. The file starts with the scene elements, in any order, followed by the map, which must come last.

```
NO ./texture/purpletile.xpm
SO ./texture/lightwood.xpm
WE ./texture/purplebrick.xpm
EA ./texture/lightstone.xpm

F 87,33,98
C 104,63,199

1111111111111
1000000000001
1011100D11101
10000000000N1
1111111111111
```

### Elements

| Identifier | Meaning |
|------------|---------|
| `NO` / `SO` / `WE` / `EA` | Path to the `.xpm` texture for each wall direction |
| `F` | Floor color, as `R,G,B` (0–255) |
| `C` | Ceiling color, as `R,G,B` (0–255) |

### Map characters

| Character | Meaning |
|-----------|---------|
| `1` | Wall |
| `0` | Empty floor |
| `N` / `S` / `E` / `W` | Player start, facing North / South / East / West (exactly one) |
| `D` | Door |
| ` ` (space) | Outside of the map |

A valid map must be closed (surrounded by walls) and contain exactly one player. Any invalid file (wrong extension, missing or duplicated element, bad color, missing texture, open map...) is rejected with an `Error` message.

## How it works

### Raycasting

For each of the 1024 screen columns, a ray is cast from the player through the camera plane. The **DDA** (Digital Differential Analysis) algorithm walks the grid cell by cell until the ray hits a wall. The *perpendicular* distance to the wall (not the Euclidean one, which would cause a fish-eye effect) gives the height of the wall slice to draw, and the exact hit point gives which column of the texture to use.

### Doors

A closed door stops the ray like a wall. While a door is moving or open, it is treated as a **transparent layer**: the ray remembers the door, keeps going to the real wall behind it, then the door is drawn on top, skipping its transparent pixels. You can see the room behind a door while it slides open.

Each door is a small state machine (`closed → opening → open → closing`), and its cell value in the map (`4`, `5`, `6`) drives both rendering and collisions. When a door is open, only the middle gap is walkable: the panels still block the player.

### Minimap and fog of war

Every cell crossed by a ray during the frame is marked as *seen*. The minimap and the full-screen map only draw seen cells.

The field of view cone is exact: each map pixel is projected into camera space (like a sprite) and compared to a **z-buffer** that holds the wall distance of every screen column.

The minimap is drawn straight into the 3D frame, because MiniLibX images have no transparency and a separate image could not be round.

### Ambiance

All the lighting goes through a single function, ready for future light sources:
- **fog**: `f = 1 - exp(-distance × density)`, fading into a pink-violet color instead of black
- **directional shading**: North/South faces get less light than East/West, which gives volume to corners
- **floor and ceiling**: each screen row matches a fixed distance on the floor, so the fog is precomputed per row and costs nothing per frame
- **vignette**: precomputed factors that darken the edges of the screen

Every setting (fog color and density, light color, vignette strength...) is a `#define` in `cub.h`.

### Movement

Movement is based on the elapsed time between frames, so the player moves at the same speed (`MOVE_SPEED` cells per second) whatever the frame rate. Collisions use a square hitbox around the player, tested axis by axis so that the player slides along walls instead of getting stuck.

## Project structure

```
cub3D/
├── cub.h                  # structures, constants and prototypes
├── Makefile
├── map/                   # .cub map files
├── texture/               # .xpm textures (walls, doors, paws)
├── libft/                 # my own C library
└── srcs/
    ├── main.c
    ├── game_event.c       # game loop and keyboard events
    ├── parse/             # .cub file parsing and validation
    ├── exec/
    │   ├── raycasting*.c  # DDA and wall distance
    │   ├── draw*.c        # textures and floor / ceiling
    │   ├── ambiance.c     # light, fog and vignette
    │   ├── doors.c        # door state machine and animation
    │   ├── door_collision.c
    │   ├── move*.c        # movement, collisions, mouse rotation
    │   ├── map_render.c   # shared minimap / big map rendering
    │   ├── mini_map.c
    │   ├── big_map.c
    │   ├── hud*.c         # debug HUD
    │   └── sprites.c      # paw animation and mouse clicks
    └── utils/             # init, free, map conversion
```

## Challenges

The main difficulties were:
- understanding the raycasting math (camera plane, DDA, perpendicular distance) and mapping textures correctly on each wall face
- parsing and validating the `.cub` file robustly, including checking that the map is closed
- rendering see-through animated doors without hiding the walls behind them
- keeping everything smooth on the CPU (no GPU with MiniLibX) while staying within the Norm
- tracking down edge cases, like a segfault when the player got too close to a wall and the wall height overflowed an `int`

## Roadmap

Ideas for the future:
- Light sources (lamps, torches) with a light map and colored lights
- Floor and ceiling textures (floor casting)
- Sprites: collectible objects and enemies
- Sound

## Credits

Made by [andjenna](https://github.com/Nadekko) and ede-cola as part of the 42 Paris curriculum.

<!-- Fill in the source of each asset, as in so_long -->
| Asset | Source | Author |
|-------|--------|--------|
| Wall textures | TODO | TODO |
| Doors | TODO | TODO |
| Paws | TODO | TODO |

Raycasting resources that helped a lot: [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html).

## License

The source code of this project is released under the [MIT License](LICENSE).
