# cub3D

## Description

cub3D is a walking simulator utilizing ray-casting techniques similar to Wolfenstein 3D. Developed as part of the Hive Helsinki curriculum with a bit of our own flare.

## Collaborators

- [Markus Laaksonen](https://github.com/mxafi)
- [Lionel](https://github.com/liocle)

## Technologies

Written in C, cub3D leverages MLX42, a compact graphics library similar to MiniLibX.

## Project Focus

- Proficient use of C
- Implementation of fundamental algorithms (e.g. DDA)
- Interaction with a minimal graphics library
- Emphasis on precision and rigor
- Collaboration within a team

## Features

- Map file parsing
- Map validation
- Raycast maze rendering
- Collision detection

## How to Use

```sh
git clone --recurse-submodules https://github.com/xafilabs/cub3D cub3D
cd cub3D
make
./cub3D maps/good/subject_map.cub
```

### Requirements

- GCC compiler

## Controls

| Key          | Action            |
| ------------ | ----------------- |
| W            | Move forward      |
| A            | Move left         |
| D            | Move right        |
| S            | Move backwards    |
| Left Arrow   | Turn Left         |
| Right Arrow  | Turn Right        |
| ESC          | Close window      |
