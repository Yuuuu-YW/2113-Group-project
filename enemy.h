#pragma once

#include "player.h"
#include "enemy.h"

// 触发房间事件（战斗/宝箱/治疗）
void triggerEvent(int currentLevel, int difficulty, Player& player, bool& gameOver);

// 是否能进下一关
bool canMoveToNextLevel(int currentLevel);

原来的代码的一些问题：不要出现enemy！
