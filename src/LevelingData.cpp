#include "Common.h"
#include "LevelingData.h"

BaseStatIncrease* JobStats = new BaseStatIncrease[10];
int* LevelRequirements = new int[100]
{
     0, 0, 30, 50, 80, 120, 180, 260, 360, 490,
     650, 840, 1070, 1340, 1650, 2010, 2420, 2880, 3400, 3980,
     4620, 5330, 6110, 6960, 7890, 8900, 9990, 11170, 12440, 13800,
     15260, 16820, 18480, 20290, 22250, 24360, 26620, 29080, 31740, 34600,
     37660, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000,
     40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000,
     40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000,
     40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000,
     40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000,
     40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000
};

void AddJobStat(Jobs job, int HP, int attack, int defence, int intellect, int dexterity, int carryPower, int bonus)
{
    JobStats[job].HP = HP;
    JobStats[job].Attack = attack;
    JobStats[job].Defence = defence;
    JobStats[job].Intellect = intellect;
    JobStats[job].Dexterity = dexterity;
    JobStats[job].CarryPower = carryPower;
    JobStats[job].Bonus = bonus;
}

void FillJobStatsList()
{
    memset(JobStats, 0, 10 * sizeof(BaseStatIncrease));
    AddJobStat(Job_Swordsman, 8, 3, 2, 1, 2, 2, 4);
    AddJobStat(Job_Knight, 7, 2, 3, 1, 2, 2, 4);
    AddJobStat(Job_Lord, 9, 2, 2, 2, 2, 2, 4);
    AddJobStat(Job_Samurai, 7, 3, 2, 1, 2, 2, 4);
    AddJobStat(Job_Thief, 6, 2, 1, 1, 3, 3, 4);
    AddJobStat(Job_Ninja, 6, 2, 2, 1, 3, 2, 4);
    AddJobStat(Job_Assassin, 6, 2, 2, 1, 3, 2, 4);
    AddJobStat(Job_Magus, 5, 1, 2, 3, 2, 2, 4);
    AddJobStat(Job_Priest, 4, 1, 2, 3, 2, 2, 4);
    AddJobStat(Job_Wizard, 4, 1, 2, 3, 2, 2, 4);
}

int CheckforJobSkillUnlock(Jobs job, int level)
{
    int skill = -1;
    switch (job)
    {
    case Job_Swordsman:
    case Job_Thief:
    case Job_Magus:
        switch (level)
        {
        case 2:
            skill = 0;
            break;
        case 5:
            skill = 1;
            break;
        case 8:
            skill = 2;
            break;
        case 11:
            skill = 3;
            break;
        case 14:
            skill = 4;
            break;
        }
    case Job_Knight:
    case Job_Ninja:
    case Job_Priest:
        switch (level)
        {
        case 2:
            skill = 0;
            break;
        case 5:
            skill = 1;
            break;
        case 7:
            skill = 2;
            break;
        case 10:
            skill = 3;
            break;
        case 12:
            skill = 4;
            break;
        }
    case Job_Lord:
    case Job_Samurai:
    case Job_Assassin:
        switch (level)
        {
        case 2:
            skill = 0;
            break;
        case 4:
            skill = 1;
            break;
        case 6:
            skill = 2;
            break;
        case 8:
            skill = 3;
            break;
        case 10:
            skill = 4;
            break;
        }
    }
    return skill;
}