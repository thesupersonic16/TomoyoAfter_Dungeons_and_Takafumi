#pragma once
#include "Common.h"

enum EnemyTypes
{
    EnemyType_None = -1,
    EnemyType_RedBeastman,
    EnemyType_GreenBeastman,
    EnemyType_BlueBeastman,
    EnemyType_Golem = 5
};

typedef struct
{
    bool active;
    // The type of Enemy, like what kind of Beastman
    EnemyTypes type;
    int level;
    // Experience you will earn when defeated
    int experience;
    int unknown04;
    int maxHealth;
    int unknown06;
    Stats baseStats;
    int health;
    // Has some relation to unknown6, Maybe this is used for battling?
    int unknown18;
    Stats battleStats;
    int unknown29;
    int unknown30;
    int x;
    int y;
    Rotation rotation;
    int turnPosition;
    int unknown35;
    int unknown36;
    int unknown37;
    int unknown38;
} Enemy;
extern Enemy* Enemies;

void ResetEnemyData();
void AddEnemy(EnemyTypes type, int level, int experience, int health, int attkR, int attkL, int def, int intel, int dex, int speed, int mov, int x, int y, Rotation rot);
void AddEnemyDataByFloor(int floor);
