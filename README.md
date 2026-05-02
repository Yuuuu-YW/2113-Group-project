# Dungeon of Shadows

A text-based Dungeons & Dragons-inspired RPG written in C++11.

---

## Team Members & Contributions

| Member   | GitHub Username | Contribution                                                                                              |
|----------|-----------------|-----------------------------------------------------------------------------------------------------------|
| Cai Yuxuan  | 3036483208   | `Entity.h/cpp` base class; `Player.h/cpp` full implementation; save/load serialisation logic             |
| Yu Renhan   | 3036481511   | `Monster.h/cpp` (Skeleton/Goblin/Mini-Boss/Boss types); `Dungeon.h/cpp` floor/room manager; random event system (trap / treasure / rest); mini-boss spawn logic |
| Wang Leshen | 3036481949   | `Combat.h/cpp` turn-based battle system; critical-hit mechanic; difficulty-scaled flee & special rates; no-flee enforcement for mini-boss and boss encounters   |
| Ma Xiaoyu   | 3036481664   | `main.cpp` game loop, shop, between-floor menu, opening narrative; `Art.h/cpp` ASCII art & combat HUD    |
| Yu Wei      | 3036483351   | `Utils.h/cpp` RNG & terminal helpers; `SaveLoad.h/cpp`; `Makefile`; `README.md`; code review & docs      |

> Each member contributes ≥ 10 % of added lines as measured by GitHub's Contributors Graph.

---

## Application Description

**Dungeon of Shadows** is a turn-based console RPG set in a monster-infested underground labyrinth.

The surface world is being terrorised by creatures emerging from a deep dungeon passage.
As a recruited adventurer you must descend through 3 floors (3 rooms each), battle monsters,
and ultimately slay the **Shadow Lord** lurking at the bottom.

---

## Features

- **Three playable classes** — each determines *your own* HP / ATK / DEF (independent of difficulty):
  - `Saber`    — High ATK (20), Low DEF (4),  HP 100
  - `Archer`   — Balanced ATK (15), DEF (6),  HP 120
  - `Shielder` — Low ATK (10), High DEF (12), HP 160
- **Three independent difficulty levels** — affect *enemy* stats only:
  - `Easy`   — Enemy HP/ATK × 0.7 | Special rate 8 %  | Flee rate 70 %
  - `Normal` — Enemy HP/ATK × 1.0 | Special rate 15 % | Flee rate 50 %
  - `Hard`   — Enemy HP/ATK × 1.4 | Special rate 30 % | Flee rate 30 %
- **3 Floors × 3 Rooms** — 9 normal/mini-boss rooms plus a final Boss floor:
  - Floor 1 (rooms 1–2): Skeleton enemies; room 3: **Skeleton Warden** (mini-boss, no flee)
  - Floor 2 (rooms 1–2): Goblin enemies;   room 3: **Goblin Chief**    (mini-boss, no flee)
  - Floor 3 (rooms 1–2): Mixed Skeleton/Goblin (×1.2 stat bonus); room 3: **Shadow Knight** (mini-boss, no flee)
  - Boss Floor: **Shadow Lord** (no flee)
- **Mini-boss system** — the last room on every floor spawns a stronger guardian; flee is disabled for all mini-boss and final boss encounters
- **ASCII art combat HUD** — side-by-side HP bars update every turn; each enemy type has its own sprite
- **Dungeon mini-map** — horizontal floor progress shown at the start of every room (`[X]`=cleared, `[?]`=current, `[ ]`=ahead, `[B]`=boss)
- **Random events** between rooms: spike traps, treasure chests, campfire rest spots (each with ASCII art)
- **Turn-based combat** with Attack / Use Item / Flee options; **Flee is disabled** against mini-bosses and the final boss
- **Critical hits** (15 % chance, ×2 damage) and **monster special attacks** (difficulty-scaled trigger rate)
- **Levelling system** — gain XP and gold from battles; +15 MaxHP, +3 ATK, +1 DEF per level-up
- **In-dungeon shop** — spend gold on Small Potion (30 HP) or Large Potion (60 HP) between floors
- **Starting gold** — player begins with 20 gold for early potion purchases
- **Save / Load** — full game state written to `save.dat` using plain-text file I/O
- **Multiple enemy types**: Skeleton → Goblin → Mixed (floor 3) → Mini-Bosses (Skeleton Warden / Goblin Chief / Shadow Knight) → Shadow Lord (final boss)

---

## Code Requirements Checklist

| Requirement                         | Where implemented                                         |
|-------------------------------------|-----------------------------------------------------------|
| Random event generation             | `Dungeon::rollEvent()` — `Utils::randDouble()` / `randInt()` |
| Data structures for storing data    | `std::vector<Item>` inventory in `Player`; stat arrays in `Player.cpp` / `Monster.cpp` |
| Dynamic memory management           | `new Monster(...)` / `delete mob` in `main.cpp`; `new Player` for load path |
| File input/output                   | `SaveLoad::saveGame()` / `loadGame()` — `<fstream>`       |
| Program code in multiple files      | 9 `.cpp` source files + 8 `.h` headers                    |
| Multiple difficulty levels          | `Difficulty` enum (EASY / NORMAL / HARD) — independent of class choice |

---

## File Structure

```
dungeon_game2/
├── include/
│   ├── Entity.h       # Base class for all combat entities
│   ├── Player.h       # Player character: class, difficulty, level, inventory
│   ├── Monster.h      # Enemy types and special abilities
│   ├── Combat.h       # Turn-based battle system
│   ├── Dungeon.h      # Floor/room management and random events
│   ├── SaveLoad.h     # File I/O save/load interface
│   ├── Utils.h        # RNG, terminal helpers, input validation
│   └── Art.h          # ASCII art: monster sprites, event art, combat HUD, mini-map
├── src/
│   ├── Entity.cpp
│   ├── Player.cpp
│   ├── Monster.cpp
│   ├── Combat.cpp
│   ├── Dungeon.cpp
│   ├── SaveLoad.cpp
│   ├── Utils.cpp
│   ├── Art.cpp        # All ASCII art implementations
│   └── main.cpp       # Entry point and top-level game flow
├── Makefile
└── README.md
```

---

## Non-Standard Libraries

**None.** The project uses only the C++11 standard library:

`<iostream>`, `<string>`, `<vector>`, `<fstream>`, `<sstream>`,
`<cstdlib>`, `<ctime>`, `<cmath>`, `<limits>`, `<algorithm>`

No third-party libraries are required. No additional installation is needed.
The program compiles and runs on any system with a C++11-compliant `g++` (GCC ≥ 4.8),
including the CS department's academy server.

---

## Compilation & Execution Instructions

### Requirements
- `g++` with C++11 support (GCC ≥ 4.8 or Clang ≥ 3.3)
- `make`

### Build with Make

```bash
cd dungeon_game2
make
```

This produces the executable `dungeon_game` in the project root.

### Run

```bash
./dungeon_game
```

### Clean

```bash
make clean
```

### Manual compilation (without Make)

```bash
g++ -std=c++11 -pedantic-errors -Wall -Wextra -Iinclude \
    src/Entity.cpp src/Player.cpp src/Monster.cpp \
    src/Combat.cpp src/Dungeon.cpp src/SaveLoad.cpp \
    src/Utils.cpp src/Art.cpp src/main.cpp \
    -o dungeon_game
```

---

## Gameplay Quick Reference

| Input | Action                                              |
|-------|-----------------------------------------------------|
| `1`   | New Game / Attack (combat) / Continue (room/floor)  |
| `2`   | Load Game / Use Item (combat) / Visit Shop          |
| `3`   | Quit / Flee (combat, **disabled vs mini-boss & boss**) / Save Game |
| `4`   | View player status (between floors)                 |

- **Save file**: `save.dat` is created in the working directory.
- **To load**: choose option `2` from the main menu.

---

## Story Background

> "Adventurers, have you noticed? The nights are growing darker.
> The land is in chaos — eerie miasma blankets the villages,
> people vanish without a trace, danger lurks everywhere.
> No one has seen their full form. Sounds drift up from the shadows
> below through that deep passage in the ruins… leading to the
> DUNGEON BELOW!
> Your mission: grip your weapon, descend through 3 floors of 3 rooms each,
> and kill everything inside. Survive and safeguard the surface world."
