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

## Enemies & Bosses

> All stats listed are base values at **Normal** difficulty. Easy = ×0.7, Hard = ×1.4.

---

### Normal Enemies

#### Skeleton — Floor 1

| HP | ATK | Special Attack |
|----|-----|----------------|
| 30 |  6  | Bone Rattle    |

Long before the Shadow Lord stirred, the dungeon claimed its first victims: explorers, treasure hunters, and soldiers sent to investigate the ruins. They died in the dark, far from home, and were never recovered. The Shadow Lord found them useful.

Animated by shadow-energy seeping through the stone, these skeletons retain no memory of their former lives — only a hollow, mechanical drive to destroy anything warm and breathing. They do not feel pain. They do not tire. They advance in silence until either you or they stop moving.

Their special move, **Bone Rattle**, is a sudden convulsive shudder that sends bone fragments flying and throws off your footing, dealing moderate damage. If you look closely at a fallen skeleton, you may notice the rusted remnants of equipment — a belt buckle, a boot clasp — hinting that it was once an adventurer just like you.

---

#### Goblin — Floor 2

| HP | ATK | Special Attack |
|----|-----|----------------|
| 36 |  7  | Sneak Strike   |

Unlike the skeletons, Goblins came to the dungeon willingly. Driven out of the surface forests by expanding settlements, a tribe of goblins discovered the dungeon entrance decades ago and moved in. The Shadow Lord's influence warped them over generations — they grew more aggressive, more territorial, and far less inclined to retreat.

They have colonised Floor 2 entirely, turning stone corridors into a warren of sleeping nooks, crude forges, and trap-rigged passages. The gold they hoard is mostly stripped from adventurers who reached Floor 2 and got no further.

Their special move, **Sneak Strike**, is their signature trick: the goblin feigns a stumble, ducks inside your guard, and drives a hidden blade upward into an unprotected spot for heavy bonus damage. It is infuriatingly difficult to anticipate, even knowing it is coming.

---

#### Mixed Enemies — Floor 3

| HP (approx.) | ATK (approx.) | Stat Bonus   |
|-------------|--------------|--------------|
| ×1.2 scaled | ×1.2 scaled  | Both types   |

Floor 3 is where the dungeon's two factions collide. Neither skeletons nor goblins respect territorial lines, and the constant skirmishing has thinned both populations to only their strongest survivors. What remains are veterans — skeletons that have been shattered and reassembled multiple times, goblins with scars layered over older scars.

The Shadow Lord's influence is densest this deep. Both creature types are faster, hit harder, and absorb more punishment than anything above. All Floor 3 enemies carry a **×1.2 stat bonus** on top of difficulty scaling. Do not enter Floor 3 without at least one Large Potion in reserve.

---

### Mini-Bosses *(flee disabled)*

The last room of every floor is sealed by a Mini-Boss — a creature that has claimed dominance over its floor through power and the Shadow Lord's favour. These encounters cannot be escaped. The stairs will not appear until the guardian falls.

---

#### Skeleton Warden — Floor 1, Room 3

| HP | ATK | Special Attack       |
|----|-----|----------------------|
| 90 |  11 | Bone Slam (+8 dmg)   |

The Skeleton Warden was never an adventurer. It was the dungeon's original jailer — a towering figure who managed the cells and passages of this place when it was still inhabited by the living. Its iron-shod frame and sheer size set it apart from every other skeleton on Floor 1, and in death those qualities have been preserved and amplified by shadow-energy.

The Warden does not rattle or claw. It *slams*. Each blow carries the weight of centuries of patient waiting. Its special move, **Bone Slam**, drives both fists into the floor and sends a shockwave erupting beneath your feet, dealing its full ATK plus 8 bonus damage. On Hard difficulty this single strike can exceed 23 damage — enough to finish off a low-HP Saber player in two hits.

The Warden has stood at this post since the dungeon sealed itself. It has seen every adventurer who reached Room 3 of Floor 1. None of them made it past.

---

#### Goblin Chief — Floor 2, Room 3

| HP  | ATK | Special Attack      |
|-----|-----|---------------------|
| 110 |  14 | War Cry (+12 dmg)   |

The Goblin Chief is the self-declared king of the Goblin Warrens — a creature that clawed its way to dominance through years of brutal infighting, bearing the scars to prove it. It wears a dented crown hammered from stolen coins and carries a weapon that is technically a repurposed dungeon gate hinge, wielded with surprising expertise.

Where ordinary goblins are sneaky and opportunistic, the Chief is simply aggressive. It wants you dead, and it is not shy about it. Its special move, **War Cry**, is a bellowing roar that shakes the stone walls and sends the Chief charging forward in a frenzy, dealing its ATK plus 12 bonus damage. On Normal difficulty this can deal over 26 damage in a single turn.

The Chief's subjects are terrified of it. The Shadow Lord finds it useful precisely because it is already violent by nature — no corruption required.

---

#### Shadow Knight — Floor 3, Room 3

| HP  | ATK | Special Attack         |
|-----|-----|------------------------|
| 130 |  17 | Dark Slash (+16 dmg)   |

The Shadow Knight is something different from the skeletons and goblins above. It was once a knight — a decorated soldier sent by an earlier king to investigate the dungeon, long before the current crisis. He descended alone, by choice, convinced he could handle whatever was down there. He was wrong, but the Shadow Lord saw something worth keeping in him: discipline, skill, and an unbreakable will.

It did not reanimate him the way it reanimates skeletons. It *kept* him — intact, aware, and utterly hollowed out. The Shadow Knight remembers being human. It no longer cares. It serves the dark because there is nothing left of it that serves anything else.

Its special move, **Dark Slash**, channels shadow-energy through its blade in a sweeping arc that deals ATK plus 16 bonus damage. On Hard difficulty this single strike can exceed 39 damage. It is the most dangerous enemy in the dungeon outside the final boss, and it fights with the precision of a trained soldier rather than the savagery of a monster. Every movement is deliberate. Every opening it gives you is intentional.

---

### Final Boss — The Shadow Lord *(flee disabled)*

The entity at the bottom of the dungeon has no body in any conventional sense. What you encounter in the Hollow Throne is a manifestation — a shape the Shadow Lord has assembled to interact with something as limited as a physical being. It is ancient beyond any recorded history, patient beyond any human understanding, and it has been watching you since you set foot on the first staircase.

Every adventurer who descended before you fed it — their fear, their pain, their final desperate hope all converted into something the Shadow Lord could use. It is stronger now than it was when the first skeletons rose. It is stronger than it was when the first goblin heard its whisper and followed it underground. Every failed attempt to stop it has made it more powerful.

You are not the first to reach this chamber. You are the latest in a long line of people who believed they could end this.

The difference, perhaps, is that you have made it this far.

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
