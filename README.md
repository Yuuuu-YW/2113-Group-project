# Dungeon Game: Text Quest

## Team Members

Please replace the placeholders below with your actual names and student IDs.

1. Member 1 - Main flow and integration
2. Member 2 - Map and random events
3. Member 3 - Battle and enemies
4. Member 4 - Player, inventory, and items
5. Member 5 - Save/load system and documentation

## Project Description

This project is a text-based dungeon adventure game written in C++ for the
ENGG1340 / COMP2113 course project.

The player explores a dungeon through the terminal, encounters random events,
fights enemies, collects items, and aims to survive until the end of the run.
The project is designed as a modular console game so that different teammates
can work on separate files without frequently changing the same code.

## Current Progress

The current version is a project skeleton with:

- a main menu
- difficulty selection
- input validation
- placeholder game flow
- placeholder module integration for player, map, events, battle, items, and save/load
- a `Makefile` for compilation

This version is intended to provide a stable starting point for team
development. More gameplay logic will be implemented in later commits.

## Planned Features

- Multiple difficulty levels: Easy, Normal, Hard
- Random dungeon events
- Turn-based battles
- Enemy system
- Player stats and health system
- Item and inventory system
- Save and load system
- Boss encounter or final stage

## Coding Requirements Mapping

This project is planned to satisfy the course requirements in the following way:

1. Generation of random events
   Random room events will be generated in the event module.
2. Data structures for storing data
   Structs and collections will be used for players, enemies, rooms, and items.
3. Dynamic memory management
   Dynamic memory will be used when handling game objects and expandable data.
4. File input/output
   The save/load module will read and write game progress to files.
5. Program codes in multiple files
   The program is already split into multiple `.cpp` and `.h` files.
6. Multiple difficulty levels
   The player can choose different difficulty levels from the main menu.

## File Structure

```text
main.cpp      - main menu and program entry
game.cpp/h    - integration layer for game flow
player.cpp/h  - player data and status
enemy.cpp/h   - enemy data
battle.cpp/h  - battle logic
map.cpp/h     - dungeon room and map logic
event.cpp/h   - random event logic
item.cpp/h    - items and inventory-related helpers
save.cpp/h    - save and load logic
Makefile      - build instructions
```

## How To Compile

Use the following command in the project directory:

```bash
make
```

This will generate the executable:

```bash
./dungeon_game
```

## How To Run

After compiling, run:

```bash
./dungeon_game
```

## Non-standard Libraries

Currently, the project only uses standard C++ libraries and does not require
additional installation.

## Collaboration Plan

To reduce merge conflicts, each teammate should mainly work on different files:

- Member 1: `main.cpp` and integration with `game.cpp`
- Member 2: `map.cpp`, `map.h`, `event.cpp`, `event.h`
- Member 3: `battle.cpp`, `battle.h`, `enemy.cpp`, `enemy.h`
- Member 4: `player.cpp`, `player.h`, `item.cpp`, `item.h`
- Member 5: `save.cpp`, `save.h`, `README.md`

Suggested workflow:

1. Pull the latest code before starting work.
2. Create or switch to your own feature branch.
3. Only modify the files you are responsible for unless the team agrees.
4. Commit with meaningful messages.
5. Merge back into `main` only after testing.

## Notes

- All functions should include comments describing what they do, their inputs,
  and their outputs.
- The final version should be able to compile on the academy server.
- The team should also prepare a short demonstration video for submission.
