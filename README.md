# Dungeon Game: Text Quest

## Team Members
1. Yu Wei - Student ID 
2. Ma Xiaoyu - Student ID
3. Yu Renhan - Student ID 
4. Cai Yuxuan - Student ID 
5. Wang Leshen - Student ID

自己填ID

## Division of Work
- [Student name] : Main flow and integration
- [Student name] : Map and random events
- [Student name] : Battle and enemies
- [Student name] : Player, inventory and items
- [Student name] : Save/load system and documentation

这只是初步的分工

## Game Description
This project is a text-based dungeon-crawling RPG where players explore a multi-floor dungeon, encounter random events, battle enemies and bosses, collect items, purchase gear from shops, and aim to defeat the final dragon boss.

## Features Implemented
- Feature 1 : Three difficulty levels: Easy / Normal / Hard
- Feature 2 : Multi-floor dungeon progression 
- Feature 3 : Turned-based combat system with attack, item use and flee mechanics
- Feature 4 : Random room events (enemy, treasure, shop
- Feature 5 : Player level-up system with increasing stats

需进一步讨论

## Course Requirement Mapping

Explain how your project satisfies each requirement.

1. Generation of random events
- Random room types
- Random enemy spawns based on the dungeon difficulty
- Used in : map.cpp, event.cpp, enemy.cpp
2. Data structures for storing data
- Player struct : name,HP , attack, defense
- Enemy struct : name, HP, attack, defense, reward
- vector<string> for inventory storage
- Used in : player.cpp, enemy.h
3. Dynamic memory management
- Dynamic inventory using std::vector
- Automatic memory management by standard library
- No memory leaks, compatible with academy server
- Used in: player.cpp, inventory system
4. File input/output
- Save game to save.txt
- Load game from save.txt
- Used in : save.cpp, save.h
5. Program codes in multiple files
- Separate .h and .cpp files for each module
- Clear separation of game functions
- Files : main, game, layer, enemy, battle, map, event, save
6. Multiple difficulty levels
- Players select Easy/Normal/Hard difficulty level at start
- Difficulty affects player stats and enemy strength
- Used in: player.cpp, enemy.cpp

## File Structure

```text
main.cpp      - main menu and game flow
game.cpp/h    - integration helpers
player.cpp/h  - player module
enemy.cpp/h   - enemy module
battle.cpp/h  - battle module
map.cpp/h     - map and room module
event.cpp/h   - event module
item.cpp/h    - item module
save.cpp/h    - history record module
Makefile      - build instructions
README.md     - project description
```

## Compilation

```bash
make
```

## Execution

```bash
./dungeon_game
```

## Non-standard Libraries

If you do not use any, write:

```text
None
```

If you do use any, list them here and explain what they are for.

## Notes

- Add function comments where needed.
- Make sure the final version can compile on the academy server.
- Prepare a short demonstration video before submission.

## Problems to be discussed
- Game content and structure (一些设定：dungeon game 难度，有没有last boss，通关条件，



