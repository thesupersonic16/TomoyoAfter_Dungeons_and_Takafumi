#pragma once
#include "Common.h"

enum CharacterSlots
{
    Char_Tomoya,
    Char_Tomoyo,
    Char_Kanako,
    Char_Tomo,
    Char_Fuko
};

enum Jobs
{
    Job_None = -1,
    Job_Swordsman,
    Job_Knight,
    Job_Lord,
    Job_Samurai,
    Job_Thief,
    Job_Ninja,
    Job_Assassin,
    Job_Magus,
    Job_Priest,
    Job_Wizard
};

enum SkillStatus : int
{
    SkillStatus_NotObtained,
    SkillStatus_Ready,
    SkillStatus_Used,
    SkillStatus_Unknown
};
#pragma pack(push, 4)

typedef struct
{
    bool alive;
    int unknown001;
    int level;
    Jobs job;
    int unlockedJobs[10]; // Jobs unlocked, (0 or 1)
    int jobLevel; // Level record for learning Job Skills (Resets on Job change)
    int experience; // Experience left to reach the next Level
    int unknown016;
    int unknown017;
    int unlockedPersonalSkills[10]; // PSkills unlocked, (0 or 1)
    int unlockedJobSkills[5]; // JSkills unlocked, (0 or 1)
    Stats unknown33;
    int unknown043;
    int unknown044;
    Stats offsetStat; // Seems to be used to compare equipment
    int maxHealth;
    int unknown056;
    Stats currentStat; // 57
    int currentHealth; // 67
    SkillStatus personalSkills[10];
    SkillStatus jobSkills[5];
    // This is a copy of currentStat, This can be modified to temporary change the stats
    Stats battleStat;
    int unknown093;
    int unknown094;
    int x;
    int y;
    Rotation rotation;
    int turnPosition;
    // Spawning Position and Rotation
    int spawnX;
    int spawnY;
    Rotation spawnRotation;
    
    int unknown102;
    int unknown103;
    int unknown104;
    int unknown105;
    int unknown106;
    int unknown107;
    int unknown108;
    int unknown109;
    int unknown110;
    int unknown111;
    int unknown112;
    int unknown113;
    int unknown114;
    int unknown115;
    int unknown116;
    int unknown117;
    int unknown118;
    int unknown119;
    int unknown120;
    int unknown121;
    int unknown122;
    int unknown123;
    int unknown124;
    int unknown125;
    int unknown126;
    int unknown127;
    int unknown128;
    int unknown129;
    int unknown130;
    int unknown131;
    int unknown132;
    int unknown133;
    int unknown134;
    int unknown135;
    int unknown136;
    int unknown137;
    int unknown138;
    int unknown139;
    int unknown140;
    int unknown141;
    int unknown142;
    int unknown143;
    int unknown144;
    int unknown145;
    int unknown146;
    int unknown147;
    int unknown148;
    int unknown149;
    int unknown150;
    int unknown151;
    int unknown152;
    int unknown153;
    int unknown154;
    int unknown155;
    int unknown156;
    int unknown157;
    int unknown158;
    int unknown159;
    int unknown160;
    int unknown161;
    int unknown162;
    int unknown163;
    int unknown164;
    int unknown165;
    int unknown166;
    int unknown167;
    int unknown168;
    int unknown169;
    int unknown170;
    int unknown171;
    int unknown172;
    int unknown173;
    int unknown174;
    int unknown175;
    int unknown176;
    int unknown177;
    int unknown178;
} Player;
#pragma pack(pop)
extern Player* Players;

void ClearPlayerData(int playerslot);
void ResetPlayerData(int playerslot);
Stats* AddStatToPlayer(Player* player, Stats* right);