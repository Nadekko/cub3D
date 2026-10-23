# CUB3D

Cub3D is a project from the 42 Paris Common Core: a first-person 3D game written in C with the MiniLibX, inspired by *Wolfenstein 3D*. The goal is to build a raycasting engine from scratch, turning a 2D grid map into a textured 3D view with real-time input handling.

You explore a cozy, slightly eerie maze through the eyes of a cat: soft pink-violet fog, warm light, and paws swiping at the screen. Doors slide open (and closed), and the map slowly reveals itself as you explore.

<p align="center">
  <img src="demo/demo_explore.gif" width="45%" alt="Exploring the maze">
  <img src="demo/demo_doors.gif" width="45%" alt="Opening and closing doors">
</p>
<p align="center">
  <img src="demo/demo_minimap.gif" width="45%" alt="Minimap with fog of war">
  <img src="demo/demo_big_map.gif" width="45%" alt="Full-screen map">
</p>

## Features

**Mandatory part**
- Raycasting engine (DDA) without fish-eye distortion
- A different wall texture for each direction, custom floor and ceiling colors
- Full `.cub` file parsing and validation, with explicit error messages

**Bonus and extras**
- Wall collisions and mouse look
- Animated sliding doors that can be opened **and closed**
- Round minimap with fog of war, field of view cone, optional rotating mode and zoom
- Full-screen zoomable map
- Animated paw attack on click
- Ambiance: distance fog, warm light tint, directional wall shading and vignette
- Frame-rate–independent movement and a debug HUD (FPS, position, door state...)

## Installation

The Makefile automatically clones the MiniLibX when you run `make`. Depending on your OS, you may need to change the repo link in the Makefile.

On Ubuntu, you will also need the X11 development packages:

```
sudo apt install xorg libxext-dev libbsd-dev
```

Tested on Ubuntu. Untested on macOS, and not compatible with Fedora (MiniLibX incompatibilities).

## Usage

```
make
./cub3d map/map.cub
```

## Controls

| Key | Action |
|-----|--------|
| W / Z, S | Move forward / backward |
| A / Q, D | Strafe left / right |
| Mouse | Look around |
| Left click | Paw animation / open or close a door |
| Scroll | Zoom the minimap or the full-screen map |
| M | Open / close the full-screen map |
| R | Toggle the rotating minimap |
| TAB | Show / hide the debug HUD |
| ESC | Quit |

Both QWERTY and AZERTY layouts are supported.

## Map format

A `.cub` file starts with the wall textures (`NO`, `SO`, `WE`, `EA`) and the floor and ceiling colors (`F`, `C`, as `R,G,B`), in any order, followed by the map.

```
NO ./texture/purpletile.xpm
SO ./texture/lightwood.xpm
WE ./texture/purplebrick.xpm
EA ./texture/lightstone.xpm

F 87,33,98
C 104,63,199

1111111111111
1000000000001
1111111D11111
10000000000N1
1111111111111
```

| Character | Meaning |
|-----------|---------|
| `1` / `0` | Wall / empty floor |
| `N` / `S` / `E` / `W` | Player start and direction (exactly one) |
| `D` | Door |

The map must be closed by walls. Any invalid file is rejected with an `Error` message.

## How it works

For each screen column, a ray is cast from the player and walks the grid cell by cell with the **DDA** algorithm until it hits a wall. The perpendicular distance to the wall gives the height of the slice to draw, and the exact hit point gives the texture column.

Moving or open doors are treated as a **transparent layer**: the ray keeps going to the wall behind, then the door is drawn on top, so you can see the room behind it while it slides open. Every cell crossed by a ray is marked as *seen*, which drives the fog of war on the maps.

## Challenges

- Understanding the raycasting math and mapping textures correctly on each wall face
- Rendering see-through animated doors without hiding the walls behind them
- Keeping everything smooth on the CPU while staying within the Norm

## Known issues

Valgrind reports no leaks in the project's code (`definitely lost: 0`), but it does show a few X11 messages:
- **still reachable** blocks: hiding the cursor with `mlx_mouse_hide` makes libX11 load its locale and resource caches, which it never frees, even after the display is closed
- **`writev` points to uninitialised byte(s)**: a known libxcb false positive, triggered by `mlx_loop`

## Roadmap

- Light sources, floor and ceiling textures
- Sprites (objects, enemies) and sound

## Credits

Made by [Nadekko](https://github.com/Nadekko) and [JahLioness](https://github.com/JahLioness) as part of the 42 Paris curriculum.

**Assets** (some were modified for this project):
- **Wall textures**: from *Wolfenstein 3D*, © id Software, and the [Dungeon/Temple tileset](https://apple-dog.itch.io/dungeont) by [AppleDog](https://apple-dog.itch.io/)
- **Doors**: [Miscellaneous Pixel Assets](https://caniaeast.itch.io/miscellaneous-pixel-assets) by [CaniaEast](https://caniaeast.itch.io/)
- **Paws**: partially redrawn from the [Paw Kitten](https://tenor.com/view/paw-kitten-highfive-wave-cat-gif-5182489) GIF on Tenor (original author unknown)

Raycasting resource that helped a lot: [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html).

## License

The source code of this project is released under the [MIT License](LICENSE).

This license does not cover third-party content:

- The game assets belong to their respective authors and remain subject to their original terms (see [Credits](#credits)).
- MiniLibX is provided by 42 and distributed under its own license; see its repository for details.
