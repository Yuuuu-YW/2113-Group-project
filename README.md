# Dungeon of Shadows

> *"The darkness beneath the earth stirs. Something ancient has awakened — and it hungers."*

A text-based, turn-based RPG written in C++11. No GUI, no third-party libraries — just pure terminal adventure.

---

## Team Members & Contributions

| Member      | UID        | Contribution                                                                                                                             |
|-------------|------------|------------------------------------------------------------------------------------------------------------------------------------------|
| Cai Yuxuan  | 3036483208 | `Entity.h/cpp` base class; `Player.h/cpp` full implementation; save/load serialisation logic                                            |
| Yu Renhan   | 3036481511 | `Monster.h/cpp` (Skeleton / Goblin / Mini-Boss / Boss types); `Dungeon.h/cpp` floor & room manager; random event system; mini-boss spawn |
| Wang Leshen | 3036481949 | `Combat.h/cpp` turn-based battle system; critical-hit mechanic; difficulty-scaled flee & special rates; no-flee enforcement; `README.md` |
| Ma Xiaoyu   | 3036481664 | `main.cpp` game loop, shop, between-floor menu, opening narrative; `Art.h/cpp` ASCII art & combat HUD                                   |
| Yu Wei      | 3036483351 | `Utils.h/cpp` RNG & terminal helpers; `SaveLoad.h/cpp`; `Makefile`; code review & docs                                                  |

> Each member contributes ≥ 10 % of added lines as measured by GitHub's Contributors Graph.

---

## Story Background

### The World Above

The kingdom of Aelindra was once prosperous — golden harvests, bustling market towns, and decades of hard-won peace. But three months ago, everything changed.

It began with the animals. Livestock vanished overnight. Hunting dogs refused to enter the forest. Then the villagers near the old ruins started disappearing — first one or two, then entire families. Those who returned were hollow-eyed, muttering about *shadows that breathe* and *a voice from below the earth*.

The ruins stand at the edge of the Greywood Forest, half-swallowed by vines and forgotten by history. Scholars once believed the structure was merely an ancient watchtower. They were wrong. Beneath it lies a **dungeon of immeasurable depth**, carved by hands no living person can name — and something down there has woken up.

### The Call to Arms

The Royal Council, desperate and out of options, has issued an open summons: any warrior, rogue, or archer brave enough to descend into the dungeon and silence whatever lurks within will be rewarded beyond measure. Dozens answered. None came back.

You are the latest to answer the call.

### The Dungeon

Three floors of twisting stone corridors, each more dangerous than the last. The upper levels are patrolled by **Skeletons** — animated remains of those who came before you. Deeper down, savage **Goblins** have made the tunnels their home, rigging traps and hoarding stolen gold. On the third floor, both factions clash, and their survivors are larger, angrier, and battle-hardened.

Guarding the passage between each floor is a **Mini-Boss** — a champion of its kind that will not let you pass without a fight to the death. At the very bottom, in a chamber of pure darkness, waits the **Shadow Lord**: the ancient entity that has been pulling every string from the beginning.

Kill it, and the dungeon dies with it. Fail, and join the shadows forever.

---

## Dungeon Map Overview

```
SURFACE
   |
   v
[Floor 1] Room 1 ── Room 2 ── [SKELETON WARDEN]  <- mini-boss, no flee
   |
   v
[Floor 2] Room 1 ── Room 2 ── [GOBLIN CHIEF]     <- mini-boss, no flee
   |
   v
[Floor 3] Room 1 ── Room 2 ── [SHADOW KNIGHT]    <- mini-boss, no flee
   |
   v
[Boss Chamber]     [SHADOW LORD]                  <- final boss, no flee
```

---

## Characters & Classes

At the start of the game, choose your **class**. Your class determines your base stats only — it does **not** affect enemy difficulty.

| Class     | HP  | ATK | DEF | Playstyle                                              |
|-----------|-----|-----|-----|--------------------------------------------------------|
| `Saber`   | 100 |  20 |   4 | Glass cannon. Kill fast or die fast.                   |
| `Archer`  | 120 |  15 |   6 | Balanced. Forgiving for first-time players.            |
| `Shielder`| 160 |  10 |  12 | Tank. Outlasts enemies through sheer endurance.        |

### Levelling Up

Every enemy killed grants **XP** and **gold**. Upon levelling up:
- Max HP **+15**
- ATK **+3**
- DEF **+1**

There is no level cap. In long runs, a high-level Shielder becomes nearly unkillable.

---

## Enemies

### Normal Enemies

| Enemy    | Floor  | Behaviour                                                      |
|----------|--------|----------------------------------------------------------------|
| Skeleton | 1      | Basic attacker. Low HP, low ATK. Occasional **Bone Rattle** (stuns briefly). |
| Goblin   | 2      | Faster and sneakier. May use **Sneak Strike** for bonus damage.|
| Mixed    | 3      | Both types appear, with stats boosted ×1.2 from floor scaling. |

### Mini-Bosses *(flee disabled)*

Each mini-boss is the guardian of its floor. You cannot run — defeat it or die trying.

| Mini-Boss         | Floor | HP  | ATK | Special Attack          |
|-------------------|-------|-----|-----|-------------------------|
| Skeleton Warden   |   1   |  90 |  11 | **Bone Slam** (+8 dmg)  |
| Goblin Chief      |   2   | 110 |  14 | **War Cry** (+12 dmg)   |
| Shadow Knight     |   3   | 130 |  17 | **Dark Slash** (+16 dmg)|

> Stats shown are base values (Normal difficulty). Easy = ×0.7, Hard = ×1.4.

### Final Boss *(flee disabled)*

**The Shadow Lord** — ancient, patient, and utterly merciless. It has watched every adventurer who ever entered this dungeon. It knows your every move before you make it. Defeat it to end the curse and free Aelindra.

---

## Difficulty Levels

Difficulty affects **enemy stats only**. Your own HP/ATK/DEF never change based on difficulty.

| Difficulty | Enemy HP/ATK | Special Attack Rate | Flee Success Rate |
|------------|:------------:|:-------------------:|:-----------------:|
| Easy       |    × 0.7     |         8 %         |        70 %       |
| Normal     |    × 1.0     |        15 %         |        50 %       |
| Hard       |    × 1.4     |        30 %         |        30 %       |

**Recommended for first playthrough:** Normal with Archer.

---

## Gameplay Guide

### 1. Starting the Game

```
1) New Game
2) Load Game
3) Quit
```

Select **New Game** to begin. You will be prompted to:
1. Enter your character name
2. Choose a class (Saber / Archer / Shielder)
3. Choose a difficulty (Easy / Normal / Hard)

You start with **20 gold** — enough to buy one Small Potion before the first mini-boss.

---

### 2. Exploring the Dungeon

Each floor has **3 rooms**. The mini-map at the top of the screen tracks your progress:

```
Floor 1:  [X] [?] [ ] [B]
           ^   ^         ^
        cleared |      boss floor
            current room
```

- `[X]` — Cleared room
- `[?]` — Current room
- `[ ]` — Unexplored room
- `[B]` — Boss chamber (after floor 3)

**Between rooms**, a random event may occur:

| Event          | Effect                                    |
|----------------|-------------------------------------------|
| Spike Trap     | Lose a small amount of HP                 |
| Treasure Chest | Gain gold (amount varies)                 |
| Campfire       | Restore HP (partial heal)                 |
| Nothing        | Proceed quietly                           |

---

### 3. Combat System

Combat is **turn-based**. Each turn you choose one of the following actions:

```
1) Attack
2) Use Item
3) Flee       <-- disabled against mini-bosses and the final boss
```

#### Attack
Your base damage is your ATK minus the enemy's DEF (minimum 1). There is a **15 % chance** of landing a **Critical Hit**, which deals **×2 damage**.

#### Use Item
Consume a potion from your inventory:
- **Small Potion** — restores 30 HP
- **Large Potion** — restores 60 HP

#### Flee
Attempt to escape the battle. Success rate depends on difficulty level. **Cannot be used against mini-bosses or the final boss.**

#### Monster Special Attacks
Each enemy type has a signature special move triggered at a difficulty-scaled rate. Special attacks deal significantly more damage than normal attacks — be prepared.

#### Combat HUD
During battle, a side-by-side ASCII display shows:
- Your HP bar and stats
- The enemy's HP bar and sprite
- A running combat log of actions taken

---

### 4. Between Floors — the Shop

After clearing all 3 rooms on a floor, you reach a **rest area** with a shop before descending to the next floor. Here you can:

| Option         | Cost | Effect              |
|----------------|------|---------------------|
| Small Potion   |  10g | +30 HP when used    |
| Large Potion   |  25g | +60 HP when used    |
| Save Game      |  —   | Write progress to `save.dat` |
| View Status    |  —   | Check HP / ATK / DEF / Level |
| Continue       |  —   | Descend to next floor|

> **Tip:** Always buy at least one Large Potion before facing a mini-boss. You cannot flee, so healing items are your only safety net.

---

### 5. Saving and Loading

- **Save**: available from the between-floor menu (option shown as *Save Game*).
- **Load**: select option `2` from the main menu on startup.
- Save data is stored in `save.dat` in the working directory.
- Only one save slot exists. Saving overwrites the previous file.

---

## Strategy Tips

- **Saber** players should prioritise eliminating mini-bosses before losing too much HP — your low DEF makes prolonged fights dangerous.
- **Shielder** players can afford to skip the shop early; save gold for Large Potions on floors 2–3.
- On **Hard** difficulty, special attack rates triple compared to Easy — consider stocking two Large Potions before each mini-boss.
- Random events can swing a run significantly. A well-timed Campfire before the Goblin Chief can be the difference between life and death.
- Level up as much as possible on floor 1 — the stat bonuses compound through the rest of the dungeon.

---

## Features Summary

- **Three playable classes** with distinct stat profiles
- **Three difficulty levels** that scale enemy power independently of class
- **Mini-boss system** — each floor ends with a mandatory, no-flee guardian encounter
- **Final boss** — Shadow Lord with unique sprite and no-flee enforcement
- **ASCII art combat HUD** — HP bars and enemy sprites rendered every turn
- **Dungeon mini-map** — visual room progress on every floor
- **Random events** — traps, treasure, and campfires between rooms
- **Critical hits** (15 % chance, ×2 damage) and **monster special attacks**
- **Levelling system** — XP and stat growth from every kill
- **In-dungeon shop** between floors
- **Save / Load** — full game state persistence via plain-text file I/O
- **No third-party libraries** — pure C++11 standard library only

---

## Code Requirements Checklist

| Requirement                      | Where implemented                                                                 |
|----------------------------------|-----------------------------------------------------------------------------------|
| Random event generation          | `Dungeon::rollEvent()` — `Utils::randDouble()` / `randInt()`                      |
| Data structures for storing data | `std::vector<Item>` inventory in `Player`; stat arrays in `Player.cpp` / `Monster.cpp` |
| Dynamic memory management        | `new Monster(...)` / `delete mob` in `main.cpp`; `new Player` for load path       |
| File input/output                | `SaveLoad::saveGame()` / `loadGame()` — `<fstream>`                               |
| Program code in multiple files   | 9 `.cpp` source files + 8 `.h` headers                                            |
| Multiple difficulty levels       | `Difficulty` enum (EASY / NORMAL / HARD) — independent of class choice            |

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

| Input | Action                                                          |
|-------|-----------------------------------------------------------------|
| `1`   | New Game / Attack (combat) / Continue (room or floor)           |
| `2`   | Load Game / Use Item (combat) / Visit Shop                      |
| `3`   | Quit / Flee (combat — **disabled vs mini-boss & final boss**) / Save Game |
| `4`   | View player status (between floors)                             |

- **Save file**: `save.dat` is created in the working directory.
- **To load**: choose option `2` from the main menu.
