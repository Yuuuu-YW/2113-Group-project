# Dungeon Game: Text Quest

## Team Members
1. Yu Wei - Student ID 
2. Ma Xiaoyu - 3036481664
3. Yu Renhan - 3036481511
4. Cai Yuxuan - 3036483208 
5. Wang Leshen - 3036481949

## Division of Work
- Yu Wei : 
- Ma Xiaoyu : 
- Yu Renhan : 
- Cai Yuxuan : Battle system
  Turn-based battle logic, player/enemy interaction.
  Files: battle.cpp/h
- Wang Leshen :  

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

搬运AI

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
- 角色基本属性
  HP attack defense Level inventory（backpack）coin
- 游戏关卡setting
  游戏背景：地下城里盘踞着的魔物...
  难度分Easy/Normal/Hard，各个难度怎么设置难度的区分呢？是buff？还是怪的数值？
  通关条件：击败last boss
  房间设置：battle，treasure， shop， trap... 还能有些啥房间？
  是只有几关还是说要多搞几层？   P.S.说实话我觉得可以多搞几层，每一层都独特的怪e.g.骷髅、哥布林
  关于关卡的命名（如果有多层的话建议按照1-1，1-2，2-1，2-2这样命名，参考元气骑士）
  关卡之间的移动：大家觉得（1）按照一个确定的顺序到xx关 （2）玩家选择接下来进入的关卡类别 哪个比较好？
  （参考honkai：starrails）



