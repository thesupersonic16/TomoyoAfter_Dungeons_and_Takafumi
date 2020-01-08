#include "EnemyData.h"

int enemyIndex = 0;
Enemy* Enemies = nullptr;

void ResetEnemyData()
{
    enemyIndex = 0;
    memset(Enemies, 0, 20 * sizeof(Enemy));
}

void AddEnemy(EnemyTypes type, int level, int experience, int health, int attkR, int attkL, int def, int intel, int dex, int speed, int mov, int x, int y, Rotation rot)
{
    Enemies[enemyIndex].active = true;
    Enemies[enemyIndex].type = type;
    Enemies[enemyIndex].level = level;
    Enemies[enemyIndex].experience = experience;
    Enemies[enemyIndex].maxHealth = health;
    Enemies[enemyIndex].health = health;
    Enemies[enemyIndex].x = x;
    Enemies[enemyIndex].y = y;
    Enemies[enemyIndex].rotation = rot;
    Enemies[enemyIndex].baseStats.attackR = attkR;
    Enemies[enemyIndex].baseStats.attackL = attkL;
    Enemies[enemyIndex].baseStats.defense = def;
    Enemies[enemyIndex].baseStats.intellect = intel;
    Enemies[enemyIndex].baseStats.dexterity = dex;
    Enemies[enemyIndex].baseStats.speed = speed;
    Enemies[enemyIndex].baseStats.moves = mov;
    Enemies[enemyIndex].battleStats.attackR = attkR;
    Enemies[enemyIndex].battleStats.attackL = attkL;
    Enemies[enemyIndex].battleStats.defense = def;
    Enemies[enemyIndex].battleStats.intellect = intel;
    Enemies[enemyIndex].battleStats.dexterity = dex;
    Enemies[enemyIndex].battleStats.speed = speed;
    Enemies[enemyIndex].battleStats.moves = mov;
    ++enemyIndex;
}

void AddEnemyDataByFloor(int floor)
{
    switch (floor)
    {
    case 1:
        AddEnemy(EnemyType_GreenBeastman, 1, 1, 12, 14, 0, 8, 0, 8, 22, 3, 10, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 1, 1, 12, 14, 0, 8, 0, 8, 22, 3, 11, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 1, 1, 12, 14, 0, 8, 0, 8, 22, 3, 10, 12, Rot_West);
        break;
    case 2:
        AddEnemy(EnemyType_GreenBeastman, 1, 1, 12, 14, 0, 8, 0, 8, 22, 3, 11, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 1, 1, 12, 14, 0, 8, 0, 8, 22, 3, 10, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 1, 1, 12, 14, 0, 8, 0, 8, 22, 3, 12, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 2, 1, 16, 19, 0, 11, 0, 10, 22, 3, 14, 6, Rot_West);
        break;
    case 3:
        AddEnemy(EnemyType_GreenBeastman, 1, 2, 12, 14, 0, 8, 0, 8, 22, 3, 10, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 1, 2, 12, 14, 0, 8, 0, 8, 22, 3, 9, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 2, 2, 16, 19, 0, 11, 0, 10, 22, 3, 14, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 2, 2, 16, 19, 0, 11, 0, 10, 22, 3, 13, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 2, 2, 16, 19, 0, 11, 0, 10, 22, 3, 14, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 3, 3, 20, 24, 0, 14, 0, 12, 22, 3, 16, 17, Rot_West);
        break;
    case 4:
        AddEnemy(EnemyType_GreenBeastman, 1, 2, 12, 14, 0, 8, 0, 8, 22, 3, 5, 1, Rot_South);
        AddEnemy(EnemyType_GreenBeastman, 2, 2, 16, 19, 0, 11, 0, 10, 22, 3, 11, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 2, 2, 16, 19, 0, 11, 0, 10, 22, 3, 10, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 3, 2, 20, 24, 0, 14, 0, 12, 22, 3, 16, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 3, 2, 20, 24, 0, 14, 0, 12, 22, 3, 17, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 3, 2, 20, 24, 0, 14, 0, 12, 22, 3, 16, 11, Rot_West);
        break;
    case 5:
        AddEnemy(EnemyType_GreenBeastman, 2, 2, 16, 19, 0, 11, 0, 10, 22, 3, 10, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 2, 2, 16, 19, 0, 11, 0, 10, 22, 3, 11, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 3, 2, 20, 24, 0, 14, 0, 12, 22, 3, 13, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 3, 2, 20, 24, 0, 14, 0, 12, 22, 3, 14, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 3, 2, 20, 24, 0, 14, 0, 12, 22, 3, 12, 14, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 4, 2, 24, 29, 0, 17, 0, 14, 22, 3, 17, 6, Rot_West);
        AddEnemy(EnemyType_Golem, 4, 8, 36, 29, 0, 17, 0, 14, 15, 3, 17, 8, Rot_West);
        break;
    case 6:
        AddEnemy(EnemyType_GreenBeastman, 4, 4, 24, 29, 0, 17, 0, 14, 22, 3, 12, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 4, 4, 24, 29, 0, 17, 0, 14, 22, 3, 10, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 4, 4, 24, 29, 0, 17, 0, 14, 22, 3, 14, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 4, 4, 24, 29, 0, 17, 0, 14, 22, 3, 11, 13, Rot_West);
        break;
    case 7:
        AddEnemy(EnemyType_GreenBeastman, 4, 5, 24, 29, 0, 17, 0, 14, 22, 3, 10, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 4, 5, 24, 29, 0, 17, 0, 14, 22, 3, 10, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 5, 5, 28, 34, 0, 20, 0, 16, 22, 3, 12, 3, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 5, 5, 28, 34, 0, 20, 0, 16, 22, 3, 13, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 5, 5, 28, 34, 0, 20, 0, 16, 22, 3, 13, 14, Rot_West);
        break;
    case 8:
        AddEnemy(EnemyType_GreenBeastman, 4, 7, 24, 29, 0, 17, 0, 14, 22, 3, 9, 4, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 4, 7, 24, 29, 0, 17, 0, 14, 22, 3, 10, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 5, 7, 28, 34, 0, 20, 0, 16, 22, 3, 12, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 5, 7, 28, 34, 0, 20, 0, 16, 22, 3, 10, 14, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 5, 7, 28, 34, 0, 20, 0, 16, 22, 3, 12, 16, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 6, 7, 32, 39, 0, 23, 0, 18, 22, 3, 18, 7, Rot_West);
        break;
    case 9:
        AddEnemy(EnemyType_GreenBeastman, 4, 8, 24, 29, 0, 17, 0, 14, 22, 3, 9, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 5, 8, 28, 34, 0, 20, 0, 16, 22, 3, 11, 14, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 5, 8, 28, 34, 0, 20, 0, 16, 22, 3, 9, 16, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 6, 8, 32, 39, 0, 23, 0, 18, 22, 3, 12, 3, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 6, 8, 32, 39, 0, 23, 0, 18, 22, 3, 14, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 6, 8, 32, 39, 0, 23, 0, 18, 22, 3, 16, 8, Rot_West);
        break;
    case 10:
        AddEnemy(EnemyType_GreenBeastman, 5, 10, 28, 34, 0, 20, 0, 16, 22, 3, 10, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 5, 10, 28, 34, 0, 20, 0, 16, 22, 3, 9, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 6, 10, 32, 39, 0, 23, 0, 18, 22, 3, 6, 0, Rot_South);
        AddEnemy(EnemyType_GreenBeastman, 6, 10, 32, 39, 0, 23, 0, 18, 22, 3, 9, 2, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 6, 10, 32, 39, 0, 23, 0, 18, 22, 3, 11, 4, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 7, 10, 36, 44, 0, 26, 0, 20, 22, 3, 16, 12, Rot_West);
        AddEnemy(EnemyType_Golem, 7, 40, 108, 44, 0, 26, 0, 20, 15, 3, 18, 8, Rot_West);
        break;
    case 11:
        AddEnemy(EnemyType_GreenBeastman, 8, 16, 40, 49, 0, 29, 0, 24, 22, 3, 10, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 8, 16, 40, 49, 0, 29, 0, 24, 22, 3, 9, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 8, 16, 40, 49, 0, 29, 0, 24, 22, 3, 12, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 8, 16, 40, 49, 0, 29, 0, 24, 22, 3, 11, 13, Rot_West);
        break;
    case 12:
        AddEnemy(EnemyType_GreenBeastman, 8, 18, 44, 49, 0, 29, 0, 24, 22, 3, 11, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 8, 18, 44, 49, 0, 29, 0, 24, 22, 3, 10, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 8, 18, 44, 49, 0, 29, 0, 24, 22, 3, 11, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 9, 18, 48, 54, 0, 32, 0, 26, 22, 3, 16, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 9, 18, 48, 54, 0, 32, 0, 26, 22, 3, 16, 10, Rot_West);
        break;
    case 13:
        AddEnemy(EnemyType_GreenBeastman, 8, 20, 44, 49, 0, 29, 0, 24, 22, 3, 9, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 9, 20, 48, 54, 0, 32, 0, 26, 22, 3, 11, 8, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 9, 20, 48, 70, 0, 28, 0, 26, 22, 3, 12, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 9, 20, 48, 54, 0, 32, 0, 26, 22, 3, 11, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 10, 20, 52, 59, 0, 35, 0, 28, 22, 3, 15, 4, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 10, 20, 52, 59, 0, 35, 0, 28, 22, 3, 15, 6, Rot_West);
        break;
    case 14:
        AddEnemy(EnemyType_GreenBeastman, 9, 22, 48, 54, 0, 32, 0, 26, 22, 3, 10, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 9, 22, 48, 54, 0, 32, 0, 26, 22, 3, 11, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 9, 22, 48, 54, 0, 32, 0, 26, 22, 3, 10, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 10, 22, 52, 59, 0, 35, 0, 28, 22, 3, 13, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 10, 22, 52, 59, 0, 35, 0, 28, 22, 3, 14, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 10, 22, 52, 59, 0, 35, 0, 28, 22, 3, 14, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 10, 22, 52, 59, 0, 35, 0, 28, 22, 3, 13, 14, Rot_West);
        break;
    case 15:
        AddEnemy(EnemyType_GreenBeastman, 9, 26, 48, 54, 0, 32, 0, 26, 22, 3, 9, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 9, 26, 48, 54, 0, 32, 0, 26, 22, 3, 9, 15, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 9, 26, 48, 54, 0, 32, 0, 26, 22, 3, 8, 17, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 10, 26, 52, 59, 0, 35, 0, 28, 22, 3, 14, 2, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 10, 26, 52, 59, 0, 35, 0, 28, 22, 3, 15, 4, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 10, 26, 52, 59, 0, 35, 0, 28, 22, 3, 14, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 11, 26, 56, 64, 0, 38, 0, 30, 22, 3, 18, 16, Rot_West);
        AddEnemy(EnemyType_Golem, 11, 104, 168, 64, 0, 38, 0, 30, 15, 3, 17, 17, Rot_West);
        break;
    case 16:
        AddEnemy(EnemyType_GreenBeastman, 11, 36, 64, 69, 0, 38, 0, 30, 22, 3, 11, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 11, 36, 64, 69, 0, 38, 0, 30, 22, 3, 12, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 11, 36, 64, 69, 0, 38, 0, 30, 22, 3, 13, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 11, 36, 64, 69, 0, 38, 0, 30, 22, 3, 12, 12, Rot_West);
        break;
    case 17:
        AddEnemy(EnemyType_GreenBeastman, 11, 41, 64, 69, 0, 38, 0, 30, 22, 3, 9, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 11, 41, 64, 69, 0, 38, 0, 30, 22, 3, 10, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 12, 41, 69, 74, 0, 41, 0, 32, 22, 3, 14, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 12, 41, 69, 74, 0, 41, 0, 32, 22, 3, 13, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 12, 41, 69, 74, 0, 41, 0, 32, 22, 3, 14, 8, Rot_West);
        break;
    case 18:
        AddEnemy(EnemyType_BlueBeastman, 12, 46, 69, 74, 0, 41, 0, 32, 26, 5, 16, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 11, 46, 64, 69, 0, 38, 0, 30, 22, 3, 11, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 11, 46, 64, 69, 0, 38, 0, 30, 22, 3, 10, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 12, 46, 69, 74, 0, 41, 0, 32, 22, 3, 14, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 12, 46, 69, 74, 0, 41, 0, 32, 22, 3, 12, 16, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 13, 46, 74, 79, 0, 44, 0, 34, 22, 3, 18, 8, Rot_West);
        break;
    case 19:
        AddEnemy(EnemyType_GreenBeastman, 11, 51, 64, 69, 0, 38, 0, 30, 22, 3, 9, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 12, 51, 69, 74, 0, 41, 0, 32, 22, 3, 12, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 12, 51, 69, 74, 0, 41, 0, 32, 22, 3, 12, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 12, 51, 69, 74, 0, 41, 0, 32, 22, 3, 11, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 13, 51, 74, 79, 0, 44, 0, 34, 22, 3, 16, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 13, 51, 74, 79, 0, 44, 0, 34, 22, 3, 17, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 13, 51, 74, 79, 0, 44, 0, 34, 22, 3, 16, 14, Rot_West);
        break;
    case 20:
        AddEnemy(EnemyType_GreenBeastman, 12, 58, 69, 74, 0, 41, 0, 32, 22, 3, 10, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 12, 58, 69, 74, 0, 41, 0, 32, 22, 3, 10, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 13, 58, 74, 79, 0, 44, 0, 34, 22, 3, 2, 18, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 13, 58, 74, 79, 0, 44, 0, 34, 22, 3, 5, 18, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 13, 58, 74, 79, 0, 44, 0, 34, 22, 3, 7, 17, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 14, 58, 79, 84, 0, 47, 0, 36, 22, 3, 16, 3, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 14, 58, 79, 84, 0, 47, 0, 36, 22, 3, 17, 5, Rot_West);
        AddEnemy(EnemyType_Golem, 14, 232, 257, 84, 8, 47, 0, 36, 15, 3, 17, 8, Rot_West);
        break;
    case 21:
        AddEnemy(EnemyType_GreenBeastman, 15, 81, 84, 90, 0, 51, 0, 40, 22, 3, 11, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 15, 81, 84, 90, 0, 51, 0, 40, 22, 3, 10, 14, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 15, 81, 84, 90, 0, 51, 0, 40, 22, 3, 13, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 15, 81, 84, 90, 0, 51, 0, 40, 22, 3, 14, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 15, 81, 84, 90, 0, 51, 0, 40, 22, 3, 15, 13, Rot_West);
        break;
    case 22:
        AddEnemy(EnemyType_GreenBeastman, 15, 86, 84, 90, 0, 51, 0, 40, 22, 3, 10, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 15, 86, 84, 90, 0, 51, 0, 40, 22, 3, 11, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 15, 86, 84, 90, 0, 51, 0, 40, 22, 3, 12, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 15, 86, 84, 90, 0, 51, 0, 40, 22, 3, 13, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 16, 86, 89, 96, 0, 55, 0, 42, 22, 3, 16, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 16, 86, 89, 96, 0, 55, 0, 42, 22, 3, 17, 7, Rot_West);
        break;
    case 23:
        AddEnemy(EnemyType_BlueBeastman, 15, 91, 84, 90, 0, 51, 0, 40, 26, 5, 10, 5, Rot_West);
        AddEnemy(EnemyType_BlueBeastman, 15, 91, 84, 90, 0, 51, 0, 40, 26, 5, 10, 15, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 16, 91, 89, 120, 0, 49, 0, 42, 22, 3, 11, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 17, 91, 94, 102, 0, 59, 0, 44, 22, 3, 14, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 16, 91, 89, 96, 0, 55, 0, 42, 22, 3, 14, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 16, 91, 89, 96, 0, 55, 0, 42, 22, 3, 14, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 17, 91, 94, 102, 0, 59, 0, 44, 22, 3, 14, 14, Rot_West);
        break;
    case 24:
        AddEnemy(EnemyType_GreenBeastman, 15, 96, 84, 90, 0, 51, 0, 40, 22, 3, 11, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 15, 96, 84, 90, 0, 51, 0, 40, 22, 3, 12, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 16, 96, 89, 96, 0, 55, 0, 42, 22, 3, 5, 18, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 16, 96, 89, 96, 0, 55, 0, 42, 22, 3, 7, 17, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 17, 96, 94, 102, 0, 59, 0, 44, 22, 3, 17, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 17, 96, 94, 102, 0, 59, 0, 44, 22, 3, 18, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 17, 96, 94, 102, 0, 59, 0, 44, 22, 3, 17, 13, Rot_West);
        break;
    case 25:
        AddEnemy(EnemyType_GreenBeastman, 16, 105, 89, 96, 0, 55, 0, 42, 22, 3, 9, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 16, 105, 89, 96, 0, 55, 0, 42, 22, 3, 11, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 16, 105, 89, 96, 0, 55, 0, 42, 22, 3, 11, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 16, 105, 89, 96, 0, 55, 0, 42, 22, 3, 9, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 17, 105, 94, 102, 0, 59, 0, 44, 22, 3, 14, 4, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 17, 105, 94, 102, 0, 59, 0, 44, 22, 3, 15, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 17, 105, 94, 102, 0, 59, 0, 44, 22, 3, 15, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 17, 105, 94, 102, 0, 59, 0, 44, 22, 3, 14, 15, Rot_West);
        AddEnemy(EnemyType_Golem, 18, 420, 400, 108, 0, 63, 0, 46, 15, 3, 18, 9, Rot_West);
        break;
    case 26:
        AddEnemy(EnemyType_GreenBeastman, 18, 130, 109, 108, 0, 63, 0, 46, 22, 3, 11, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 18, 130, 109, 108, 0, 63, 0, 46, 22, 3, 11, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 18, 130, 109, 108, 0, 63, 0, 46, 22, 3, 13, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 18, 130, 109, 108, 0, 63, 0, 46, 22, 3, 13, 12, Rot_West);
        break;
    case 27:
        AddEnemy(EnemyType_GreenBeastman, 18, 140, 109, 108, 0, 63, 0, 46, 22, 3, 8, 4, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 18, 140, 109, 108, 0, 63, 0, 46, 22, 3, 10, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 18, 140, 109, 108, 0, 63, 0, 46, 22, 3, 11, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 19, 140, 114, 114, 0, 67, 0, 48, 22, 3, 14, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 19, 140, 114, 114, 0, 67, 0, 48, 22, 3, 13, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 19, 140, 114, 114, 0, 67, 0, 48, 22, 3, 12, 14, Rot_West);
        break;
    case 28:
        AddEnemy(EnemyType_BlueBeastman, 19, 150, 114, 114, 0, 67, 0, 48, 26, 5, 11, 12, Rot_West);
        AddEnemy(EnemyType_BlueBeastman, 19, 150, 114, 114, 0, 67, 0, 48, 26, 5, 12, 15, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 20, 150, 119, 120, 0, 71, 0, 50, 22, 3, 10, 7, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 20, 150, 119, 144, 0, 63, 0, 50, 22, 3, 14, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 20, 150, 119, 120, 0, 71, 0, 50, 22, 3, 17, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 20, 150, 119, 120, 0, 71, 0, 50, 22, 3, 17, 14, Rot_West);
        break;
    case 29:
        AddEnemy(EnemyType_GreenBeastman, 18, 160, 109, 108, 0, 63, 0, 46, 22, 3, 10, 3, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 18, 160, 109, 108, 0, 63, 0, 46, 22, 3, 11, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 18, 160, 109, 108, 0, 63, 0, 46, 22, 3, 12, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 19, 160, 114, 114, 0, 67, 0, 48, 22, 3, 12, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 19, 160, 114, 114, 0, 67, 0, 48, 22, 3, 10, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 19, 160, 114, 114, 0, 67, 0, 48, 22, 3, 10, 15, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 20, 160, 119, 120, 0, 71, 0, 50, 22, 3, 16, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 20, 160, 119, 120, 0, 71, 0, 50, 22, 3, 17, 9, Rot_West);
        break;
    case 30:
        AddEnemy(EnemyType_GreenBeastman, 18, 180, 109, 108, 0, 63, 0, 46, 22, 3, 10, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 18, 180, 109, 108, 0, 63, 0, 46, 22, 3, 11, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 19, 180, 114, 114, 0, 67, 0, 48, 22, 3, 9, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 19, 180, 114, 114, 0, 67, 0, 48, 22, 3, 9, 16, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 19, 180, 114, 114, 0, 67, 0, 48, 22, 3, 7, 18, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 20, 180, 119, 120, 0, 71, 0, 50, 22, 3, 17, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 20, 180, 119, 120, 0, 71, 0, 50, 22, 3, 18, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 20, 180, 119, 120, 0, 71, 0, 50, 22, 3, 17, 14, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 21, 180, 124, 126, 0, 75, 0, 52, 22, 3, 17, 2, Rot_West);
        AddEnemy(EnemyType_Golem, 21, 720, 600, 126, 0, 75, 0, 52, 15, 3, 18, 4, Rot_West);
        break;
    case 31:
        AddEnemy(EnemyType_GreenBeastman, 22, 230, 132, 133, 0, 80, 0, 56, 22, 3, 13, 2, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 22, 230, 132, 133, 0, 80, 0, 56, 22, 3, 11, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 22, 230, 132, 133, 0, 80, 0, 56, 22, 3, 10, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 22, 230, 132, 133, 0, 80, 0, 56, 22, 3, 14, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 22, 230, 132, 133, 0, 80, 0, 56, 22, 3, 13, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 22, 230, 132, 133, 0, 80, 0, 56, 22, 3, 12, 13, Rot_West);
        break;
    case 32:
        AddEnemy(EnemyType_GreenBeastman, 22, 240, 132, 133, 0, 80, 0, 56, 22, 3, 10, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 22, 240, 132, 133, 0, 80, 0, 56, 22, 3, 11, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 22, 240, 132, 133, 0, 80, 0, 56, 22, 3, 14, 7, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 23, 240, 138, 168, 0, 76, 0, 58, 22, 3, 14, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 23, 240, 138, 140, 0, 85, 0, 58, 22, 3, 12, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 23, 240, 138, 140, 0, 85, 0, 58, 22, 3, 13, 14, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 23, 240, 138, 140, 0, 85, 0, 58, 22, 3, 11, 17, Rot_West);
        break;
    case 33:
        AddEnemy(EnemyType_GreenBeastman, 22, 250, 132, 133, 0, 80, 0, 56, 22, 3, 4, 0, Rot_South);
        AddEnemy(EnemyType_GreenBeastman, 22, 250, 132, 133, 0, 80, 0, 56, 22, 3, 6, 2, Rot_South);
        AddEnemy(EnemyType_GreenBeastman, 22, 250, 132, 133, 0, 80, 0, 56, 22, 3, 11, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 22, 250, 132, 133, 0, 80, 0, 56, 22, 3, 10, 10, Rot_West);
        AddEnemy(EnemyType_BlueBeastman, 23, 250, 138, 140, 0, 85, 0, 58, 26, 5, 1, 19, Rot_North);
        AddEnemy(EnemyType_BlueBeastman, 23, 250, 138, 140, 0, 85, 0, 58, 26, 5, 4, 19, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 23, 250, 138, 140, 0, 85, 0, 58, 22, 3, 6, 17, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 23, 250, 138, 140, 0, 85, 0, 58, 22, 3, 9, 17, Rot_West);
        break;
    case 34:
        AddEnemy(EnemyType_GreenBeastman, 22, 260, 132, 133, 0, 80, 0, 56, 22, 3, 5, 2, Rot_South);
        AddEnemy(EnemyType_GreenBeastman, 23, 260, 138, 140, 0, 85, 0, 58, 22, 3, 2, 17, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 23, 260, 138, 140, 0, 85, 0, 58, 22, 3, 4, 17, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 24, 260, 144, 147, 0, 90, 0, 60, 22, 3, 9, 4, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 22, 260, 132, 165, 0, 72, 0, 56, 22, 3, 10, 6, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 22, 260, 132, 165, 0, 72, 0, 56, 22, 3, 10, 9, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 22, 260, 132, 165, 0, 72, 0, 56, 22, 3, 10, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 24, 260, 144, 147, 0, 90, 0, 60, 22, 3, 9, 15, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 24, 260, 144, 176, 0, 80, 0, 60, 22, 3, 13, 9, Rot_West);
        break;
    case 35:
        AddEnemy(EnemyType_BlueBeastman, 23, 280, 138, 140, 0, 85, 0, 58, 26, 5, 15, 2, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 22, 280, 132, 133, 0, 80, 0, 56, 22, 3, 5, 2, Rot_South);
        AddEnemy(EnemyType_GreenBeastman, 22, 280, 132, 133, 0, 80, 0, 56, 22, 3, 9, 5, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 23, 280, 138, 168, 0, 78, 0, 58, 22, 3, 12, 3, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 23, 280, 138, 168, 0, 78, 0, 58, 22, 3, 5, 18, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 23, 280, 138, 140, 0, 85, 0, 58, 22, 3, 7, 17, Rot_North);
        AddEnemy(EnemyType_RedBeastman, 24, 280, 144, 176, 0, 80, 0, 60, 22, 3, 13, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 24, 280, 144, 147, 0, 90, 0, 60, 22, 3, 14, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 24, 280, 144, 147, 0, 90, 0, 60, 22, 3, 12, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 280, 150, 154, 0, 95, 0, 62, 22, 3, 14, 17, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 280, 150, 154, 0, 95, 0, 62, 22, 3, 16, 16, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 280, 150, 154, 0, 95, 0, 62, 22, 3, 16, 18, Rot_West);
        AddEnemy(EnemyType_Golem, 25, 1120, 650, 154, 0, 95, 0, 62, 15, 3, 18, 17, Rot_West);
        break;
    case 36:
        AddEnemy(EnemyType_GreenBeastman, 25, 330, 150, 154, 0, 95, 0, 62, 22, 3, 9, 5, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 25, 330, 150, 184, 0, 85, 0, 62, 22, 3, 11, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 330, 150, 154, 0, 95, 0, 62, 22, 3, 9, 14, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 330, 150, 154, 0, 95, 0, 62, 22, 3, 13, 4, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 330, 150, 154, 0, 95, 0, 62, 22, 3, 15, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 330, 150, 154, 0, 95, 0, 62, 22, 3, 14, 12, Rot_West);
        break;
    case 37:
        AddEnemy(EnemyType_BlueBeastman, 25, 350, 150, 154, 0, 95, 0, 62, 26, 5, 10, 17, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 350, 150, 154, 0, 95, 0, 62, 22, 3, 9, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 350, 150, 154, 0, 95, 0, 62, 22, 3, 10, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 350, 150, 154, 0, 95, 0, 62, 22, 3, 11, 13, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 25, 350, 150, 184, 0, 85, 0, 62, 22, 3, 14, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 26, 350, 156, 161, 0, 100, 0, 64, 22, 3, 15, 3, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 26, 350, 156, 161, 0, 100, 0, 64, 22, 3, 17, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 26, 350, 156, 161, 0, 100, 0, 64, 22, 3, 17, 10, Rot_West);
        break;
    case 38:
        AddEnemy(EnemyType_BlueBeastman, 25, 370, 150, 154, 0, 95, 0, 62, 26, 5, 1, 1, Rot_South);
        AddEnemy(EnemyType_BlueBeastman, 26, 370, 156, 161, 0, 100, 0, 64, 26, 5, 13, 17, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 370, 150, 154, 0, 95, 0, 62, 22, 3, 10, 3, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 370, 150, 154, 0, 95, 0, 62, 22, 3, 11, 7, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 25, 370, 150, 184, 0, 85, 0, 62, 22, 3, 11, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 370, 150, 154, 0, 95, 0, 62, 22, 3, 10, 13, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 26, 370, 156, 194, 0, 90, 0, 64, 22, 3, 15, 4, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 26, 370, 156, 161, 0, 100, 0, 64, 22, 3, 16, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 27, 370, 162, 168, 0, 105, 0, 66, 22, 3, 18, 2, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 27, 370, 162, 168, 0, 105, 0, 66, 22, 3, 18, 15, Rot_West);
        break;
    case 39:
        AddEnemy(EnemyType_GreenBeastman, 26, 390, 156, 161, 0, 100, 0, 64, 22, 3, 0, 6, Rot_East);
        AddEnemy(EnemyType_GreenBeastman, 26, 390, 156, 161, 0, 100, 0, 64, 22, 3, 0, 11, Rot_East);
        AddEnemy(EnemyType_GreenBeastman, 26, 390, 156, 161, 0, 100, 0, 64, 22, 3, 0, 15, Rot_East);
        AddEnemy(EnemyType_RedBeastman, 26, 390, 156, 194, 0, 90, 0, 64, 22, 3, 4, 1, Rot_South);
        AddEnemy(EnemyType_GreenBeastman, 25, 390, 150, 154, 0, 95, 0, 62, 22, 3, 5, 1, Rot_South);
        AddEnemy(EnemyType_RedBeastman, 26, 390, 156, 194, 0, 90, 0, 64, 22, 3, 4, 18, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 25, 390, 150, 154, 0, 95, 0, 62, 22, 3, 3, 18, Rot_North);
        AddEnemy(EnemyType_RedBeastman, 27, 390, 162, 202, 0, 95, 0, 66, 22, 3, 9, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 27, 390, 162, 168, 0, 105, 0, 66, 22, 3, 9, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 26, 390, 156, 161, 0, 100, 0, 64, 22, 3, 11, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 26, 390, 156, 161, 0, 100, 0, 64, 22, 3, 11, 13, Rot_West);
        break;
    case 40:
        AddEnemy(EnemyType_BlueBeastman, 26, 420, 156, 161, 0, 100, 0, 64, 26, 5, 9, 17, Rot_West);
        AddEnemy(EnemyType_BlueBeastman, 26, 420, 156, 161, 0, 100, 0, 64, 26, 5, 13, 16, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 420, 150, 154, 0, 95, 0, 62, 22, 3, 4, 2, Rot_South);
        AddEnemy(EnemyType_RedBeastman, 26, 420, 156, 194, 0, 90, 0, 64, 22, 3, 10, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 26, 420, 156, 161, 0, 100, 0, 64, 22, 3, 9, 5, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 27, 420, 162, 202, 0, 95, 0, 66, 22, 3, 14, 4, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 27, 420, 162, 202, 0, 95, 0, 66, 22, 3, 14, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 27, 420, 162, 168, 0, 105, 0, 66, 22, 3, 12, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 27, 420, 162, 168, 0, 105, 0, 66, 22, 3, 12, 14, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 25, 420, 150, 164, 0, 95, 0, 62, 22, 3, 5, 17, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 28, 420, 168, 175, 0, 110, 0, 68, 22, 3, 16, 2, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 28, 420, 168, 175, 0, 110, 0, 68, 22, 3, 17, 4, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 28, 420, 168, 175, 0, 110, 0, 68, 22, 3, 18, 11, Rot_West);
        AddEnemy(EnemyType_Golem, 28, 1680, 650, 175, 0, 110, 0, 68, 15, 3, 18, 2, Rot_West);
        break;
    case 41:
        AddEnemy(EnemyType_GreenBeastman, 29, 510, 206, 183, 0, 116, 0, 72, 22, 3, 9, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 29, 510, 206, 183, 0, 116, 0, 72, 22, 3, 14, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 29, 510, 206, 183, 0, 116, 0, 72, 22, 3, 12, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 29, 510, 206, 183, 0, 116, 0, 72, 22, 3, 11, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 29, 510, 206, 183, 0, 116, 0, 72, 22, 3, 10, 14, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 30, 510, 214, 191, 0, 122, 0, 74, 22, 3, 16, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 30, 510, 214, 191, 0, 122, 0, 74, 22, 3, 14, 13, Rot_West);
        break;
    case 42:
        AddEnemy(EnemyType_BlueBeastman, 29, 530, 206, 183, 0, 116, 0, 72, 26, 5, 15, 15, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 29, 530, 206, 183, 0, 116, 0, 72, 22, 3, 10, 5, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 29, 530, 206, 219, 0, 104, 0, 72, 22, 3, 12, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 29, 530, 206, 183, 0, 116, 0, 72, 22, 3, 12, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 29, 530, 206, 183, 0, 116, 0, 72, 22, 3, 10, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 30, 530, 214, 191, 0, 122, 0, 74, 22, 3, 17, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 30, 530, 214, 191, 0, 122, 0, 74, 22, 3, 17, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 30, 530, 214, 191, 0, 122, 0, 74, 22, 3, 16, 13, Rot_West);
        break;
    case 43:
        AddEnemy(EnemyType_GreenBeastman, 29, 550, 206, 183, 0, 116, 0, 72, 22, 3, 10, 7, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 29, 550, 206, 183, 0, 116, 0, 72, 22, 3, 11, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 29, 550, 206, 183, 0, 116, 0, 72, 22, 3, 10, 11, Rot_West);
        AddEnemy(EnemyType_BlueBeastman, 30, 550, 214, 191, 0, 122, 0, 74, 26, 5, 12, 14, Rot_West);
        AddEnemy(EnemyType_BlueBeastman, 30, 550, 214, 191, 0, 122, 0, 74, 26, 5, 13, 16, Rot_West);
        AddEnemy(EnemyType_BlueBeastman, 30, 550, 214, 191, 0, 122, 0, 74, 26, 5, 12, 18, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 31, 550, 222, 238, 0, 115, 0, 76, 22, 3, 15, 4, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 31, 550, 222, 238, 0, 115, 0, 76, 22, 3, 16, 6, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 31, 550, 222, 238, 0, 115, 0, 76, 22, 3, 15, 8, Rot_West);
        break;
    case 44:
        AddEnemy(EnemyType_GreenBeastman, 29, 570, 206, 183, 0, 116, 0, 72, 22, 3, 8, 2, Rot_South);
        AddEnemy(EnemyType_GreenBeastman, 29, 570, 206, 183, 0, 116, 0, 72, 22, 3, 9, 3, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 29, 570, 206, 220, 0, 104, 0, 72, 22, 3, 11, 5, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 29, 570, 206, 220, 0, 104, 0, 72, 22, 3, 12, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 30, 570, 214, 191, 0, 122, 0, 74, 22, 3, 10, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 30, 570, 214, 191, 0, 122, 0, 74, 22, 3, 9, 12, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 30, 570, 214, 191, 0, 122, 0, 74, 22, 3, 12, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 30, 570, 214, 191, 0, 122, 0, 74, 22, 3, 3, 18, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 30, 570, 214, 191, 0, 122, 0, 74, 22, 3, 5, 18, Rot_North);
        AddEnemy(EnemyType_RedBeastman, 31, 570, 222, 238, 0, 115, 0, 76, 22, 3, 16, 15, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 31, 570, 222, 199, 0, 128, 0, 76, 22, 3, 16, 18, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 31, 570, 222, 199, 0, 128, 0, 76, 22, 3, 18, 14, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 31, 570, 222, 238, 0, 115, 0, 76, 22, 3, 18, 17, Rot_West);
        break;
    case 45:
        AddEnemy(EnemyType_BlueBeastman, 30, 590, 214, 191, 0, 122, 0, 74, 26, 5, 14, 5, Rot_West);
        AddEnemy(EnemyType_BlueBeastman, 30, 590, 214, 191, 0, 122, 0, 74, 26, 5, 14, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 29, 590, 206, 183, 0, 116, 0, 72, 22, 3, 10, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 29, 590, 206, 183, 0, 116, 0, 72, 22, 3, 9, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 29, 590, 206, 183, 0, 116, 0, 72, 22, 3, 10, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 29, 590, 206, 183, 0, 116, 0, 72, 22, 3, 9, 12, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 30, 590, 214, 230, 0, 110, 0, 74, 22, 3, 5, 1, Rot_South);
        AddEnemy(EnemyType_GreenBeastman, 30, 590, 214, 191, 0, 122, 0, 74, 22, 3, 7, 2, Rot_South);
        AddEnemy(EnemyType_RedBeastman, 30, 590, 214, 230, 0, 110, 0, 74, 22, 3, 3, 18, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 30, 590, 214, 191, 0, 122, 0, 74, 22, 3, 5, 18, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 31, 590, 222, 199, 0, 128, 0, 76, 22, 3, 15, 1, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 31, 590, 222, 238, 0, 115, 0, 76, 22, 3, 16, 2, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 590, 230, 207, 0, 134, 0, 78, 22, 3, 16, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 590, 230, 207, 0, 134, 0, 78, 22, 3, 16, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 590, 230, 207, 0, 134, 0, 78, 22, 3, 13, 15, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 590, 230, 207, 0, 134, 0, 78, 22, 3, 12, 16, Rot_West);
        AddEnemy(EnemyType_Golem, 32, 2360, 700, 207, 0, 134, 0, 78, 15, 3, 18, 6, Rot_West);
        AddEnemy(EnemyType_Golem, 32, 2360, 700, 207, 0, 134, 0, 78, 15, 3, 18, 12, Rot_West);
        break;
    case 46:
        AddEnemy(EnemyType_GreenBeastman, 32, 680, 260, 207, 0, 134, 0, 78, 22, 3, 10, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 680, 260, 207, 0, 134, 0, 78, 22, 3, 11, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 680, 260, 207, 0, 134, 0, 78, 22, 3, 11, 10, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 680, 260, 207, 0, 134, 0, 78, 22, 3, 10, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 680, 260, 207, 0, 134, 0, 78, 22, 3, 14, 4, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 32, 680, 260, 248, 0, 120, 0, 78, 22, 3, 15, 7, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 32, 680, 260, 248, 0, 120, 0, 78, 22, 3, 15, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 680, 260, 207, 0, 134, 0, 78, 22, 3, 14, 15, Rot_West);
        AddEnemy(EnemyType_Golem, 32, 2720, 700, 207, 0, 134, 0, 78, 15, 3, 18, 9, Rot_West);
        break;
    case 47:
        AddEnemy(EnemyType_BlueBeastman, 32, 710, 260, 207, 0, 134, 0, 78, 26, 5, 14, 5, Rot_West);
        AddEnemy(EnemyType_BlueBeastman, 32, 710, 260, 207, 0, 134, 0, 78, 26, 5, 14, 14, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 710, 260, 207, 0, 134, 0, 78, 22, 3, 8, 3, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 710, 260, 207, 0, 134, 0, 78, 22, 3, 10, 5, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 710, 260, 207, 0, 134, 0, 78, 22, 3, 10, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 710, 260, 207, 0, 134, 0, 78, 22, 3, 9, 15, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 33, 710, 268, 215, 0, 140, 0, 80, 22, 3, 17, 7, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 33, 710, 268, 258, 0, 128, 0, 80, 22, 3, 15, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 33, 710, 268, 215, 0, 140, 0, 80, 22, 3, 15, 11, Rot_West);
        AddEnemy(EnemyType_Golem, 33, 2840, 724, 215, 0, 140, 0, 80, 15, 3, 18, 9, Rot_West);
        break;
    case 48:
        AddEnemy(EnemyType_GreenBeastman, 32, 740, 260, 207, 0, 134, 0, 78, 22, 3, 9, 4, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 740, 260, 207, 0, 134, 0, 78, 22, 3, 11, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 740, 260, 207, 0, 134, 0, 78, 22, 3, 11, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 740, 260, 207, 0, 134, 0, 78, 22, 3, 9, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 33, 740, 268, 215, 0, 140, 0, 80, 22, 3, 14, 7, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 33, 740, 268, 258, 0, 126, 0, 80, 22, 3, 15, 4, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 33, 740, 268, 258, 0, 126, 0, 80, 22, 3, 14, 9, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 33, 740, 268, 258, 0, 126, 0, 80, 22, 3, 13, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 33, 740, 268, 215, 0, 140, 0, 80, 22, 3, 12, 15, Rot_West);
        AddEnemy(EnemyType_Golem, 33, 2960, 724, 215, 0, 140, 0, 80, 15, 3, 17, 6, Rot_West);
        AddEnemy(EnemyType_Golem, 33, 2960, 724, 215, 0, 140, 0, 80, 15, 3, 17, 13, Rot_West);
        break;
    case 49:
        AddEnemy(EnemyType_BlueBeastman, 32, 770, 260, 207, 0, 134, 0, 78, 26, 5, 14, 1, Rot_West);
        AddEnemy(EnemyType_BlueBeastman, 32, 770, 260, 207, 0, 134, 0, 78, 26, 5, 14, 18, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 770, 260, 207, 0, 134, 0, 78, 22, 3, 10, 6, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 770, 260, 207, 0, 134, 0, 78, 22, 3, 9, 8, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 770, 260, 207, 0, 134, 0, 78, 22, 3, 9, 11, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 770, 260, 207, 0, 134, 0, 78, 22, 3, 10, 13, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 32, 770, 260, 207, 0, 134, 0, 78, 22, 3, 7, 3, Rot_South);
        AddEnemy(EnemyType_GreenBeastman, 32, 770, 260, 207, 0, 134, 0, 78, 22, 3, 7, 16, Rot_North);
        AddEnemy(EnemyType_GreenBeastman, 33, 770, 268, 215, 0, 140, 0, 80, 22, 3, 15, 4, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 33, 770, 268, 258, 0, 126, 0, 80, 22, 3, 13, 8, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 33, 770, 268, 258, 0, 126, 0, 80, 22, 3, 13, 11, Rot_West);
        AddEnemy(EnemyType_RedBeastman, 33, 770, 268, 258, 0, 126, 0, 80, 22, 3, 15, 9, Rot_West);
        AddEnemy(EnemyType_GreenBeastman, 33, 770, 268, 215, 0, 140, 0, 80, 22, 3, 15, 15, Rot_West);
        AddEnemy(EnemyType_Golem, 34, 3080, 748, 223, 0, 146, 0, 82, 15, 3, 11, 4, Rot_West);
        AddEnemy(EnemyType_Golem, 34, 3080, 748, 223, 0, 146, 0, 82, 15, 3, 11, 15, Rot_West);
        AddEnemy(EnemyType_Golem, 34, 3080, 748, 223, 0, 146, 0, 82, 15, 3, 17, 7, Rot_West);
        AddEnemy(EnemyType_Golem, 34, 3080, 748, 223, 0, 146, 0, 82, 15, 3, 17, 12, Rot_West);
        break;
    default:
        break;
    }
}