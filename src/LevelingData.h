#pragma once
#include "Common.h"
#include "Character.h"

typedef struct
{
    int HP;
    int Attack;
    int Defence;
    int Intellect;
    int Dexterity;
    int CarryPower;
    int Bonus;
} BaseStatIncrease;

void FillJobStatsList();
void AddJobStat(Jobs job, int HP, int attack, int defence, int intellect, int dexterity, int carryPower, int bonus);
// Returns the Job Skill ID of the skill thats meant to be unlocked at that player level
// This function will return -1 if no skills are to be learnt
int CheckforJobSkillUnlock(Jobs job, int level);
extern BaseStatIncrease* JobStats;
extern int* LevelRequirements;