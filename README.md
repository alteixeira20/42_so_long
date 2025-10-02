<p align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C badge">
  <img src="https://img.shields.io/badge/MiniLibX-5C6BC0?style=for-the-badge&logo=opengl&logoColor=white" alt="MiniLibX badge">
  <img src="https://img.shields.io/badge/Make-427819?style=for-the-badge&logo=cmake&logoColor=white" alt="Make badge">
  <img src="https://img.shields.io/badge/Shell-4EAA25?style=for-the-badge&logo=gnu-bash&logoColor=white" alt="Shell badge">
  <img src="https://img.shields.io/badge/Valgrind-773344?style=for-the-badge&logo=gnu&logoColor=white" alt="Valgrind badge">
  <img src="https://img.shields.io/badge/GDB-800000?style=for-the-badge&logo=gnu&logoColor=white" alt="GDB badge">
</p>
<h1 align="center">so_long</h1>
<p align="center">MiniLibX-powered 2D exploration gane with animated sprite work, full map validation, with a built-in Tester.</p>
<p align="center">
  <img src="docs/images/running_game.gif" alt="Gameplay showcase" width="85%">
</p>

## Table of Contents
1. [At a Glance](#at-a-glance)
2. [About](#about)
3. [Subject Compliance](#subject-compliance)
4. [Custom Tester](#custom-tester)
5. [Repository Layout](#repository-layout)
6. [Build & Integration](#build--integration)
7. [Usage Guidelines](#usage-guidelines)
8. [Feature Deep Dive](#feature-deep-dive)
9. [Input & Animation](#input--animation)
10. [Rendering & HUD](#rendering--hud)
11. [Internal Architecture](#internal-architecture)
12. [Tester Workflow](#tester-workflow)
13. [Results & Reporting](#results--reporting)

## At a Glance
> **Highlights:** Mandatory compliance, bonus animations, and repeatable validation in a single codebase.
- Mandatory source lives in `src/`, matching the subject's structure; bonus content lives in `srcb/` and keeps API parity for easy swapping.
- Map safety hinges on rectangular checks, perimeter walls, required components, and a flood-fill reachability pass before the game even opens.
- Assets are all local (`assets/`), so the build stays portable across 42 evaluation hosts and personal setups.
- The Makefile wraps compilation, guided map selection, and automated tests so setup-to-play is a two-command workflow.

```sh
# Compile the animated build and launch a sample map
make bonus && ./so_long assets/maps/valid/demo.ber
```

## About
- The game parses `.ber` layouts, validates them, spins up MiniLibX, and reacts to keyboard inputs through the routines in `src/game/game_init.c` and `src/game/game_input.c`.
- Directional animation, mining loops, and enemy patrol failures come from the bonus pipeline (`srcb/game/game_animations_bonus.c`, `srcb/game/game_input_bonus.c`).
- Collectibles, exits, and enemies are all configured from tile metadata, so map changes flow straight into gameplay without code edits.
- Libft (including `ft_printf`, `get_next_line`, and utility helpers) ships inside the repository, removing external dependencies for evaluators or teammates.

## Subject Compliance
> Every rule in the subject is explicitly validated before the game starts, ensuring predictable and safe gameplay.

### Verification Highlights

<details>
<summary><strong>Map validation</strong></summary>

- Must be **rectangular** (`src/map/map_validation.c`).
- Must be **fully enclosed by walls** (`src/map/map_validation.c`).
- Accepts only the allowed characters:
  - `0` → empty space
  - `1` → wall
  - `C` → collectible
  - `E` → exit
  - `P` → player
  (implemented in `srcb/map/map_validation_utils_bonus.c:48`)

</details>

<details>
<summary><strong>Required components</strong></summary>

- Exactly **one player** and **one exit**.
- At least **one collectible**.
- Verified with `check_components_errors()`
  (`srcb/map/map_validation_utils_bonus.c:21`).

</details>

<details>
<summary><strong>Pathfinding</strong></summary>

- `is_map_solvable()` duplicates the map and performs a **flood-fill** check.
- Confirms that **all collectibles and exits are reachable** before gameplay begins (`srcb/map/map_pathfinding_bonus.c:49`).

</details>

<details>
<summary><strong>Gameplay rules</strong></summary>

- Movement with **WASD**.
- Player cannot pass through walls.
- Move count is displayed after each step (terminal in mandatory, HUD overlay in bonus).
- Win the game by exiting the door after mining all the collectibles.
- Quit the game by using `ESC` or window close (`srcb/game/game_input_utils_bonus.c:36`).

</details>

<details>
<summary><strong>Error handling</strong></summary>

- Any misconfiguration (duplicate exits, invalid chars, broken walls, unreachable areas)
  → exits cleanly with `Error\n` followed by an explicit descriptive message.

</details>

<details>
<summary><strong>Bonus extensions</strong></summary>

- **Sprite animation**, **HUD-based move counter**, and **enemy patrols** build on top of the mandatory rules,  
  keeping validation intact and consistent.  

</details>


## Custom Tester
<p align="center">
  <img src="docs/images/running_tests.gif" alt="Automated tester run" width="85%">
</p>

- `make tester` chains two guards: `test_invalid` sweeps every map under `assets/maps/invalid`, and `test_textures` iterates through each `.xpm` texture.
- Invalid maps verify both the formatted error header and the specific descriptive line while Valgrind watches for leaks (`Makefile:204`).
- Texture checks temporarily revoke file permissions to confirm the engine surfaces the offending asset in its error output before restoring everything (`Makefile:240`).

## Repository Layout
<details open>
<summary><strong>Directory Cheat Sheet</strong></summary>

```
inc/          - Shared headers (`so_long.h`, `so_long_bonus.h`) describing structs, keycodes, and prototypes.
src/          - Mandatory gameplay: static sprites, HUD-free movement, and core validation.
srcb/         - Bonus gameplay: animated sprites, mining cycles, HUD overlay, and enemy collisions.
assets/       - Tiles, player sprites, mining sequences, and curated maps (valid + invalid suites).
docs/         - Subject PDF and capture assets (WEBM sources + README GIFs).
mlx/          - MiniLibx Library already compiled to ease use
libft/        - Custom 42 Library with helper functions (printf, gnl, libft/ft_*)
```

> Tip: `rg --files srcb/game` is a quick way to trace each bonus-specific helper from animation to input handling.

</details>

## Build & Integration
> **Self-contained tooling:** clone, build, test- no extra environment work.

```sh
make            # mandatory build (clones libft if absent)
make bonus      # animated build with mining + enemy logic
make start      # interactive map chooser with optional launch
make tester     # runs invalid-map sweep + texture permissions suite
make fclean     # removes binaries, objects, and the libft clone
```

- `make` pulls in libft (if missing), builds MiniLibX, and links the mandatory binary.
- `make bonus` compiles the bonus objects and still outputs `so_long`, so launching maps never changes between builds.
- `make start` offers an ncurses-like prompt that copies a map to the working directory, optionally runs it, and cleans up the copy afterwards (`Makefile:64`).
- `make tester` orchestrates both test targets sequentially, with exit codes bubbling up so CI can flag failures instantly.

## Usage Guidelines
> **Playbook:** load a map, explore, and exit without leaving artifacts behind.
- Launch the mandatory build with `./so_long <map.ber>` or compile the bonus branch first for animated sprites.
- Movement is WASD-driven; ESC and the window close button call `close_game()` for a graceful teardown (`srcb/game/game_input_utils_bonus.c:36`).
- Expect rectangular, fully walled maps with one player, one exit, collectibles, and optional enemies; anything else is rejected with a formatted error.
- Collectibles trigger a mining animation and decrement counters before updating the HUD (`srcb/game/game_input_utils_bonus.c:53`).
- Enemy contact prints a game-over message and closes the window immediately, keeping the loss state tight (`srcb/game/game_input_bonus.c:31`).

## Feature Deep Dive
<details open>
<summary><strong>Gameplay Systems</strong></summary>

| Element | What Happens | Key Implementation |
| --- | --- | --- |
| Map parsing | Streams `.ber` files into memory with `get_next_line`, keeping allocation defensive. | `srcb/map/map_parser_bonus.c:52` (`read_map`) |
| Component accounting | Counts players, exits, and collectibles before the flood-fill step. | `srcb/map/map_validation_utils_bonus.c:21` (`check_components_errors`) |
| Pathfinding | Duplicates the map and flood-fills reachable space, ensuring loot and exits are accessible. | `srcb/map/map_pathfinding_bonus.c:49` (`is_map_solvable`) |
| Static rendering | Repaints every tile each frame and layers sprites on top of the floor. | `srcb/game/game_render_bonus.c:17` (`draw_tile`) |
| Movement animation | Interpolates frames between tiles with direction-aware sprites. | `srcb/game/game_animations_bonus.c:37` (`play_move_anim`) |
| Mining animation | Plays frame sequences in place before the collectible disappears. | `srcb/game/game_animations_bonus.c:69` (`play_mining_anim`) |
| HUD overlay | Writes the live move counter directly to the window. | `srcb/game/game_render_bonus.c:35` (`draw_move_counter`) |

</details>

## Input & Animation
<details>
<summary><strong>Controls & Motion</strong></summary>

- Input funnels through `handle_input()` with a compact key map, branching into `set_direction()` and `move_player()` (`srcb/game/game_input_utils_bonus.c:23`).
- Direction indices (0 up, 1 down, 2 left, 3 right) drive both animation arrays and enemy collision handling, so sprites and logic stay in sync (`inc/so_long_bonus.h:67`).
- `play_move_anim()` interpolates sprite placement in pixel space, redrawing origin and destination tiles each step to avoid ghosting.
- Mining uses a slightly longer delay per frame (`delay = 130`) to make the sequence readable without freezing the main loop (`srcb/game/game_assets_bonus.c:44`).

</details>

## Rendering & HUD
<details>
<summary><strong>Presentation Layer</strong></summary>

- Tiles always render the floor first, then layer the appropriate sprite so movement feels grounded (`srcb/game/game_render_bonus.c:17`).
- The move counter is drawn via `mlx_string_put()` in the upper-left corner, updating after each successful move (`srcb/game/game_render_bonus.c:35`).
- Window size scales from the map dimensions and the fixed `TILE_SIZE` constant (64 px), keeping the viewport pixel-perfect for any valid map.

</details>

## Internal Architecture
<details>
<summary><strong>Data Flow</strong></summary>

> Ownership and teardown paths are explicit to avoid leaking MiniLibX resources.
- `t_game` carries the live map, player state, counters, and a `t_graphics` instance that wraps MLX pointers and texture banks (`inc/so_long_bonus.h:36`).
- Animation metadata (`t_anim` and `t_anim_ctx`) isolates timing, frame pointers, and interpolation math so movement logic stays declarative (`inc/so_long_bonus.h:12`).
- Texture loading relies on `load_anim()` + `load_image()`, producing detailed error messages when a sprite fails to load (`srcb/game/game_assets_bonus.c:8`).
- Cleanup frees static textures, animation arrays, and the duplicated map before destroying the MLX window and display (`srcb/game/game_init_bonus.c:23`).

</details>

## Tester Workflow
> **Automation flow:** compile once, sweep invalid maps, lock down textures, and surface leaks immediately.
- `test_invalid` iterates through every `.ber` stored under `assets/maps/invalid`, capturing the first two output lines to ensure the standard "Error" header and explanation are intact (`Makefile:190`).
- Valgrind runs in the background for each invalid map, forcing an error exit code on leaks so memory hygiene is verified alongside messaging.
- `test_textures` chmods each `.xpm` to `000`, runs the game with a known-good map, confirms the error mentions the missing file, and restores original permissions (`Makefile:240`).
- `make tester` returns non-zero if any suite fails, so the target doubles as a CI check or a quick local regression test.

## Results & Reporting
> **Signal over noise:** The tester and logs are designed to show only the important results (errors, verdicts, tallies) and hide unnecessary clutter for efficient debugging.
- Console logs show per-case verdicts and aggregate tallies, making it obvious where to focus next.
- Valgrind trace dumps appear only when something goes wrong, keeping successful runs concise.
- During manual sessions, the on-screen move counter mirrors the terminal `printf` output so navigation errors are easy to trace.
