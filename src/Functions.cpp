#include "Common.h"
#include "Functions.h"
#include "EnemyData.h"
#include "LevelingData.h"
#include "ItemData.h"
#include "Character.h"


int InitialisePlayerData(int IsEnemy, int playerSlot)
{
    if (IsEnemy)
    {
        memset(&Enemies[playerSlot], 0, sizeof(Enemy));
        Enemies[playerSlot].type = EnemyType_None;
        Enemies[playerSlot].level = 1;
    }
    else
    {
        ResetPlayerData(playerSlot);
    }
    intB[1700] = 0;
    return 0;
}

// Don't ask how this works, I don't even know myself -SuperSonic16
int UpdateStatDisplay(int arg1, int playerSlot)
{
    if (!arg1)
    {
        auto player = &Players[playerSlot];
        player->maxHealth = player->unknown017 + player->unknown043;
        player->unknown056 = 0;
        player->currentStat = player->offsetStat;
        AddStatToPlayer(player, &player->unknown33);
        int temp = (int)((unsigned long long)0x66666667 * intC[playerSlot + 1954] >> 34);
        player->currentStat.speed -= (temp >> 31) + temp;
    }
    int temp = 0;
    for (int i = 0; i < 5; ++i)
        temp += Players[i].alive;
    temp = 200 * temp / 100;
    if (temp > 999)
        temp = 999;
    intB[1700] = temp;
    return 0;
}

int UnknownFunction_022(int arg1, int playerSlot, int arg3, int arg4)
{
    if (arg1)
    {
        Enemies[playerSlot].health = Enemies[playerSlot].maxHealth;
        Enemies[playerSlot].unknown18 = Enemies[playerSlot].unknown06;
        memcpy(&Enemies[playerSlot].battleStats, &Enemies[playerSlot].baseStats, sizeof(Stats));
    }
    else
    {
        Player& player = Players[playerSlot];
        if (arg3 == 1)
        {
            // If player is dead
            if (!player.currentHealth)
                player.currentHealth = 1;
        }
        if (player.maxHealth < player.currentHealth || arg3 == 2)
            player.currentHealth = player.maxHealth;
        // Skills
        // Personal Skills
        for (int i = 0; i < 10; ++i)
        {
            if (!player.unlockedPersonalSkills[i])
                player.personalSkills[i] = SkillStatus_NotObtained;
            else if (((arg4 == 1 && (player.personalSkills[i] != SkillStatus_Unknown)) || arg4 == 2 || (!arg4 && player.personalSkills[i] != SkillStatus_NotObtained)))
                player.personalSkills[i] = SkillStatus_Ready;
        }
        // Job Skills
        for (int i = 0; i < 5; ++i)
        {
            if (!player.unlockedJobSkills[i])
                player.jobSkills[i] = SkillStatus_NotObtained;
            else if (((arg4 == 1 && (player.jobSkills[i] != SkillStatus_Unknown)) || arg4 == 2 || (!arg4 && player.jobSkills[i] != SkillStatus_NotObtained)))
                player.jobSkills[i] = SkillStatus_Ready;
        }
        
        // Copy stats for battle
        player.battleStat = player.currentStat;
        return 0;
    }
    return 0;
}

int ResetPlayerData(int IsEnemy, int playerSlot)
{
    if (IsEnemy)
    {
        memset(&Enemies[playerSlot].unknown29, 0, 10 * 4);
    }
    else
    {
        Player& player = Players[playerSlot];
        player.x = player.spawnX;
        player.y = player.spawnY;
        player.rotation = player.spawnRotation;
        memset(&player.unknown102, 0, 77 * 4);
    }
    return 0;
}

int UnknownFunction_024()
{
    memset(&intF[1500], 0, 80 * 4);
    return 0;
}

int AddExperienceToPlayer(int playerSlot, int exp)
{
    Player& player = Players[playerSlot];
    int locF = 4 * (5 * playerSlot + 375);
    if (player.experience - exp > 0)
    {
        player.experience -= exp;
        intF[1580] = 0;
    }
    else
    {
        bool maxLevel = false;
        intF[1580] = exp - player.experience;
        if (player.level >= 99)
            maxLevel = true;
        else
        {
            ++player.level;
           intF[locF] = 1;
        }
        if (player.jobLevel < 99)
            ++player.jobLevel;
        player.experience = LevelRequirements[player.level + 1];
        if (LevelRequirements[player.level + 1] != -1)
        {
            intF[locF + 0] = 1;
            intF[locF + 2] = player.level | (1 << LevelRequirements[player.level + 1]);
        }
        // Job skill Unlocking
        int skill = CheckforJobSkillUnlock(player.job, player.jobLevel);
        
        if (skill != -1 && !player.unlockedJobSkills[skill])
        {
            intF[locF + 0] = 1;
            intF[locF + 2] |= (1 << skill);
        }

        // Increase Character Stats 
        // When at level 10 or under, every stat gets increased by 3 but Health gets increased by 10.
        // When between level 11 and 40, every stat gets increased by a predefined rate depended by the job.
        // When over level 40, every stat goes up by 1 including Health.
        // On every 5 levels, A character gains Speed.
        if (!maxLevel)
        {
            if (player.level > 10)
            {
                if (player.level > 40)
                {
                    for (int i = 0; i < 6; ++i)
                        ++intF[locF + 3 + i];
                }
                else
                {
                    BaseStatIncrease &increase = JobStats[player.job];
                    intF[locF + 3 + 0 ] = increase.HP;
                    intF[locF + 3 + 1 ] = increase.Attack;
                    intF[locF + 3 + 2 ] = increase.Defence;
                    intF[locF + 3 + 3 ] = increase.Intellect;
                    intF[locF + 3 + 4 ] = increase.Dexterity;
                    intF[locF + 3 + 5 ] = increase.CarryPower;
                    intF[locF + 3 + 16] = increase.Bonus;
                    if (player.level % 5 == 0)
                        ++intF[locF + 3 + 6]; // Speed
                }
            }
            else
            {
                intF[locF + 3] += 10; // Health
                intF[locF + 16] += 3; // Bonus
                for (int i = 1; i < 6; ++i)
                    intF[locF + 3 + i] += 2;
                if (player.level % 5 == 0)
                    ++intF[locF + 3 + 6]; // Speed
            }
        }

        // Make sure values are always in range of 0-99
        for (int i = 0; i < 8; ++i)
        {
            if (intF[locF + 3 + i] >= 0)
            {
                if (intF[locF + 3 + i] > 99)
                intF[locF + 3 + i] = 99;
            }
            else
                intF[locF + 3 + i] = 0;
        }
        if (intF[locF + 3 + 16] >= 0)
        {
            if (intF[locF + 3 + 16] > 99)
                intF[locF + 3 + 16] = 99;
        }
        else
            intF[locF + 3 + 16] = 0;
    }

    return 0;
}


int UnknownFunction_050()
{
    for (int i = 1948; i < 1974; ++i)
        intC[i] = 0;
    for (int i = 1900; i < 1948; ++i)
        intC[i] = -1;
    return 0;
}

int UnknownFunction_053(int playerID, int arg2, int storageSlot)
{
    return 0;
}


int UnknownFunction_055(int playerID)
{
    memcpy(&intC[1940], &intC[1900 + playerID * 8], 8 * 4);
    intC[1953] = intC[1948 + playerID];
    intC[1959] = intC[1954 + playerID];
    return 0;
}

int UnknownFunction_057(int playerID, int arg2, int storageSlot)
{
    Item* item1 = &Items[ItemStorage[storageSlot]];
    Item* item2 = nullptr;
    Item* item3 = nullptr;
    int unknown = 1540;
    if (intC[unknown] != -1)
        item2 = &Items[ItemStorage[unknown++]];
    if (intC[unknown] != -1)
        item3 = &Items[ItemStorage[unknown++]];

    bool canDualWield = false;
    switch (Players[playerID].job)
    {
        case Job_Swordsman:
        case Job_Knight:
        case Job_Lord:
        case Job_Samurai:
        case Job_Thief:
        case Job_Ninja:
        case Job_Assassin:
            canDualWield = true;
            break;
        default:
            break;
    }
    if (!arg2)
    {
        switch (item1->type)
        {
            case ItemType_Useless:
                intC[1940] = -1;
                return 0;
            case ItemType_Weapons:
                intC[1940] = storageSlot;
                if (item1->attributes == 1 && item3->attributes == 3)
                    intC[1941] = -1;
                if (item1->attributes == 1 && item3->type == ItemType_Weapons && !canDualWield)
                    intC[1941] = -1;
                if (item1->attributes == 3)
                    intC[1941] = -1;
                    break;
            case ItemType_Shields:
                intC[1940] = storageSlot;
                if (item3->attributes == 3)
                    intC[1941] = -1;
        }
        return 0;
    }
    else
    {
        if (item1->type == ItemType_Useless)
        {
            intC[1941] = -1;
            return 0;
        }
        if (item1->type != ItemType_Weapons)
        {
            if (item1->type == ItemType_Shields)
            {
                intC[1941] = storageSlot;
                if (item2->attributes == 3)
                    intC[1940] = -1;
            }
        }
    }
    intC[1941] = storageSlot;
    if (item1->attributes == 1)
    {
        if (item2->attributes == 3)
            intC[1940] = -1;
        if (canDualWield)
            return 0;
        if (item2->type == ItemType_Weapons)
            intC[1940] = -1;
        intC[1940] = intC[1941];
        intC[1941] = -1;
    }
    else
    {
        if (item1->attributes != 3)
            return 0;
        intC[1940] = -1;
        if (canDualWield)
            return 0;
        intC[1940] = intC[1941];
        intC[1941] = -1;
    }
    return 0;
}

int SetupFloorData(int floor)
{
    int offset2 = 900;
    
    // Platform
    intF[15] =  2; // X
    intF[16] =  5; // Y
    intF[17] =  5; // H
    intF[18] = 10; // W

    memset(&intF[20], -1, 20 * 4);
    intF[41] = 0;
    intF[42] = 0;
    intF[43] = 0;
    intF[44] = 0;
    intF[45] = 0;
    intF[46] = 0;

    // Seems the game uses these for looks
    intF[47] = 0; // Seconds
    intF[48] = 15; // Minutes

    intF[81] = 0;
    intF[82] = 0;
    intF[83] = 0;
    

    // Debug
    Players[0].battleStat.moves = 8;
    AddItemToStorage(1716);
    AddItemToStorage(1620);

    ResetEnemyData();
    AddEnemyDataByFloor(floor);
    
    // Count Enemies
    int enemyCount = 0;
    for (int i = 0; i < 20; ++i)
        if (Enemies[i].active)
            ++enemyCount;
    intF[39] = enemyCount;
    intF[40] = enemyCount;

    printf("SetupFloorData: Finished Preparing Floor: %d with %d Enemies.\n", floor, enemyCount);
    return 0;
}

int UnknownFunction_110()
{
    int loc = 90;
    int counter = 5;
    do
    {
        for (int i = 0; i < 15; ++i)
            intF[loc + i] = 0;
        intF[loc + 15] = 1;
        loc += 16;
        --counter;
    } while (counter);
    for (int i = 170; i < 263; ++i)
        intF[i] = 0;
    return 0;
}

int UnknownFunction_111()
{
    for (int i = 90; i < 263; ++i)
        intF[i] = 0;
    return 0;
}

int UnknownFunction_113(int playerID)
{
    if (intF[262] == 1)
    {
        if (intF[playerID + 250] < intF[playerID + 255] - 1)
        {
            intF[playerID + 250]++;
            return 0;
        }
        intF[playerID + 250] = 15;
    }
    return 0;
}

// Good
int UnknownFunction_114(int playerID)
{
    intF[260] = intF[16 * playerID + 90 + intF[playerID + 250]];
    intF[261] = intF[16 * playerID + 170 + intF[playerID + 250]];
    intF[262] = 0;
    return 0;
}


int SetupCharacterOrderDisplay()
{
    int turns = 0;
    int characterOrder[25];
    int characterSpeed[25];
    for (int i = 0; i < 5; ++i)
    {
        if (Players[i].alive && Players[i].unknown093 != 99)
        {
            characterOrder[turns] = i;
            characterSpeed[turns++] = Players[i].battleStat.speed;
        }
    }
    for (int i = 0; i < 20; ++i)
    {
        if (Enemies[i].active && Enemies[i].unknown29 != 99)
        {
            characterOrder[turns] = i + 5;
            characterSpeed[turns++] = Enemies[i].battleStats.speed;
        }
    }
    for (int i = turns - 1; i > 0; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            int left = characterSpeed[j + 0];
            int right = characterSpeed[j + 1];
            // If right is faster than left, then swap positions
            if (left < right)
            {
                int buf = characterOrder[j + 0];
                characterOrder[j + 0] = characterOrder[j + 1];
                characterOrder[j + 1] = buf;
                characterSpeed[j + 0] = right;
                characterSpeed[j + 1] = left;
            }
        }
    }
    if (turns > 0)
    {
        int padding = 100;
        int turnOrderWidth = 950;
        int spacing = (turnOrderWidth - padding) / turns;
        int* characterSlot = characterOrder;
        do
        {
            //if (*characterSlot >= 5)
            //    Enemies[*characterSlot - 5].turnPosition = turnOrderWidth;
            //else
            //    Players[*characterSlot].turnPosition = turnOrderWidth;
            ++characterSlot;
            turnOrderWidth -= spacing;
        } while (--turns);
    }
    return 0;
}

int UnknownFunction_120()
{
    for (int i = 270; i < 348; ++i)
        intF[i] = 0;
    return 0;
}

// Imcomplete, Maybe, something is up with dt00.dll+84B0
int UnknownFunction_121()
{
    intF[345] = 0;
    for (int i = 0; i < 5; ++i)
    {
        auto player = &Players[i];
        if (player->alive && player->unknown093 != 99)
        {
            intF[270 + i] = player->turnPosition;
            player->turnPosition += player->battleStat.speed + 10;
            intF[295 + i] = player->turnPosition;
            // TODO Add Skills
            if (player->turnPosition > 1000)
            {
                player->turnPosition -= 1000;
                intF[320 + intF[345]++] = i;
            }
        }
    }
    for (int i = 0; i < 20; ++i)
    {
        auto enemy = &Enemies[i];
        if (enemy->active && enemy->unknown29 != 99)
        {
            intF[275 + i] = enemy->turnPosition;
            enemy->turnPosition += enemy->battleStats.speed + 10;
            intF[300 + i] = enemy->turnPosition;
            if (enemy->turnPosition > 1000)
            {
                enemy->turnPosition -= 1000;
                intF[320 + intF[345]++] = i + 5;
            }
        }
    }
    return 0;
}

int UnknownFunction_122()
{
    int entityCount = intF[345];
    if (entityCount <= 1)
        return 0;

    for (int x = entityCount - 1; x > 0; --x)
    {
        int entitySlot = 0; // The first 5 are for Players, while the other 20 is for Enemies
        for (int y = x; y > 0; --y)
        {
            int left, right = 0;
            int &rSlot = intF[320 + entitySlot + 0];
            int &lSlot = intF[320 + entitySlot + 1];
            if (rSlot >= 5)
                right = Enemies[rSlot - 5].turnPosition;
            else
                right = Players[rSlot - 0].turnPosition;
            if (lSlot >= 5)
                left = Enemies[lSlot - 5].turnPosition;
            else
                left = Players[lSlot - 0].turnPosition;

            if (left < right)
            {
                int buffer = rSlot;
                rSlot = lSlot;
                lSlot = buffer;
            }
            ++entitySlot;
        }
    }
    return 0;
}

// TODO: Needs Checking
int UnknownFunction_123()
{
    int counter = 0;
    int old = intF[345];
    intF[345] = intF[345] - 1;
    if (intF[345] - 1 >= 0 && intF[345] != 1)
    {
        while (true)
        {
            int entitySlot = intF[320 + counter];
            if (entitySlot >= 5)
            {
                if (Enemies[entitySlot - 5].unknown29  == 99 ||
                    Players[entitySlot - 0].unknown093 == 99)
                {
                    if (counter < intF[345] - 2)
                        memcpy(&intF[320 + counter], &intF[321 + counter], intF[345] - counter);
                    intF[345] = intF[345] - 1;
                }
            }
            ++counter;
            if (counter >= intF[345] - 1)
            {
                intF[345] = old;
                return 0;
            }
        }
    }
    intF[345] = old;
    return 0;
}

// Good
int UnknownFunction_124()
{
    int temp = intF[intF[345] + 319];
    if (temp >= 5)
    {
        temp -= 5;
        intF[346] = 1;
    }
    else
    {
        intF[346] = 0;
    }
    intF[347] = temp;
    return 0;
}

void CalculateMovementRange_ProcessTile(int x, int y, Rotation rotation, int distance)
{
    if (!(x >= 0 && x < STAGE_WIDTH && y >= 0 && y < STAGE_HEIGHT))
        return;
    int indexPosition = x + y * STAGE_HEIGHT;
    if (distance > 0)
    {
        if (rotation != Rot_NULL)
            --distance;
        if (intD[indexPosition] == -1 || intD[indexPosition] > intD[1205] - distance)
        {
            intD[indexPosition] = intD[1205] - distance;
            intD[indexPosition + 400] = rotation;
            if (rotation != Rot_South)
                CalculateMovementRange_ProcessTile(x + 0, y - 1, Rot_North, distance);
            if (rotation != Rot_West)
                CalculateMovementRange_ProcessTile(x + 1, y - 0, Rot_East, distance);
            if (rotation != Rot_North)
                CalculateMovementRange_ProcessTile(x - 0, y + 1, Rot_South, distance);
            if (rotation != Rot_East)
                CalculateMovementRange_ProcessTile(x - 1, y + 0, Rot_West, distance);
        }
    }
}

int CalculateMovementRange()
{
    memset(intD, -1, 1200 * 4);
    // Players
    for (int i = 0; i < 5; ++i)
        if (Players[i].alive && Players[i].turnPosition != 99)
            intD[Players[i].x + 20 * Players[i].y + 800] = i;
    // Enemies
    for (int i = 0; i < 20; ++i)
        if (Enemies[i].active && Enemies[i].turnPosition != 99)
            intD[Enemies[i].x + 20 * Enemies[i].y + 800] = i + 5;

    CalculateMovementRange_ProcessTile(intD[1201], intD[1202], Rotation(intD[1204]), intD[1205]);
    int indexPosition = intD[1201] + intD[1202] * STAGE_HEIGHT; // x * w + y
    int counter1 = 0;
    int counter2 = 0;
    for (int i = 0; i < STAGE_WIDTH * STAGE_HEIGHT; ++i)
    {
        if (intD[i] == -1)
            continue;
        if (intD[1200])
        {
            if (intD[1200] != 1)
                continue;
            if (intD[800 + i] != -1 && intD[800 + i] >= 5 && i != indexPosition)
            {
                intD[1650 + counter2++] = i;
                continue;
            }
            intD[1210 + counter1] = i;
        }
        else
        {
            if (intD[800 + i] != -1 && intD[800 + i] < 5 && i != indexPosition)
            {
                intD[1650 + counter2++] = i;
                continue;
            }
            intD[1210 + counter1] = i;
        }
        counter1++;
    }
    intD[1610] = counter1;
    intD[1675] = counter2;
    return 0;
}

// Incomplete
// Seems to be used to check if enemy is in range to turn or attack
int UnknownFunction_132(int isEnemy, int playerSlot)
{
    printf("Function: %d, isEnemy: %d, playerSlot: %d\n", 132, isEnemy, playerSlot);
    Rotation rotation = Rot_North;
    int positionX = 0;
    int positionY = 0;
    int indexPosition = 0;
    int loc = 0;
    if (isEnemy)
    {
        rotation = Enemies[playerSlot].rotation;
        positionX = Enemies[playerSlot].x;
        positionY = Enemies[playerSlot].y;
        indexPosition = positionX + 20 * positionY;
    }
    else
    {
        rotation = Players[playerSlot].rotation;
        positionX = Players[playerSlot].x;
        positionY = Players[playerSlot].y;
        indexPosition = positionX + 20 * positionY;
    }
    int rotation2 = 1 << (rotation + 4);
    intD[1850] = 0;
    int v11 = 1; // Unknown 
    int v12 = 0; // Unknown 
    int width = 4; // Unknown 
    int v26 = 1; // Unknown 
    int v28 = 1; // Unknown 
    int* temp = new int[20*20];
    int* v22 = temp;
    if (0 < width)
    {
        int v18 = 20 * (positionY + v12);
        int counter = width;
        do
        {
            for (int i = (positionX + v11); i < (positionX + v11 + v26); ++v22)
            {
                //if (*v22)
                {
                    if (v18 >= 0 && v18 < 400 && i >= 0 && i < 20)
                    {
                        int v20 = i + v18;
                        if (i + v18 != isEnemy)
                        {
                            intD[intD[1850] + 1700] = v20;
                            if (v28 && v28 == 1)
                                intD[intD[1850] + 1700] = v20 + 400;
                            intD[1850] = intD[1850] + 1;
                        }
                    }
                }
                ++i;
            }
            v18 += 20;
            --counter;
        } while (counter);
    }
    delete[] temp;
    return 0;
}

int UnknownFunction_200()
{
    memset(&intF[356], 0, 37 * 4);

    // ResetA
    intF[354] = intD[346];
    intF[355] = intD[347];
    intF[356] = 0;
    intF[357] = 0;
    intF[358] = 0;
    intF[359] = 0;
    intF[360] = 0;
    intF[361] = 0;
    intF[362] = 0;
    intF[366] = 0;
    intF[376] = 0;
    intF[385] = 0;
    intF[386] = 0;
    intF[387] = 0;
    intF[388] = 0;
    intF[389] = -1;
    intF[390] = 0;
    intF[391] = 0;
    intF[392] = 0;
    intF[518] = 0;
    intF[544] = 0;
    intF[545] = 0;
    intF[547] = 0;
    intF[570] = 0;
    
    intF[351] = 99;
    intD[1850] = 0;
    return 0;
}

int UnknownFunction_201()
{
    //for (int i = 356; i <= 570; ++i)
    //    intF[i] = 0;


    // ResetA
    intF[354] = intD[346];
    intF[355] = intD[347];
    intF[356] = 0;
    intF[357] = 0;
    intF[358] = 0;
    intF[359] = 0;
    intF[360] = 0;
    intF[361] = 0;
    intF[362] = 0;
    intF[366] = 0;
    intF[376] = 0;
    intF[385] = 0;
    intF[386] = 0;
    intF[387] = 0;
    intF[388] = 0;
    intF[389] = -1;
    intF[390] = 0;
    intF[391] = 0;
    intF[392] = 0;
    intF[518] = 0;
    intF[544] = 0;
    intF[545] = 0;
    intF[547] = 0;
    intF[570] = 0;

    intF[584] = 0;
    intF[585] = 0;
    intF[586] = 0;
    intF[587] = 0;
    intF[588] = 0;
    intF[589] = 0;
    intF[590] = 0;
    intF[591] = 0;
    intF[592] = 0;
    intF[593] = 0;
    intF[594] = 0;
    intF[595] = 0;
    intF[596] = 0;
    intF[597] = 0;
    intF[598] = 0;
    intF[599] = 0;
    intF[600] = 0;


    int playerID = intF[347];
    auto player = &Players[playerID];
    if (player->alive && player->unknown093 != 99)
    {
        int i = 0;
        bool skip = false;
        while((&player->unknown148)[i++] != 35)
        {
            if (i >= 3)
            {
                skip = true;
                break;
            }
        }
        if (!skip)
            intF[350] = 9;

        if (intF[350] == 2)
        {
            i = 0;
            skip = false;
            while ((&player->unknown167)[i++] != 48)
            {
                if (i >= 2)
                {
                    skip = true;
                    break;
                }
            }
            if (!skip)
                intF[350] = 9;
        }
        if (intF[350] == 2)
        {
            i = 0;
            skip = false;
            while ((&player->unknown177)[i++])
            {
                if (i >= 1)
                {
                    skip = true;
                    break;
                }
            }
            if (!skip)
                intF[350] = 9;
        }
        if (intF[350] == 2)
        {
            switch (intF[260])
            {
            case 1:
                intF[350] = 3;
                return 0;
            case 2:
                intF[350] = 4;
                return 0;
            case 3:
                intF[350] = 5;
                return 0;
            case 4:
                intF[350] = 6;
                return 0;
            case 5:
                intF[350] = 7;
                return 0;
            case 6:
            case 7:
                intF[350] = 8;
                return 0;
            default:
                return 0;
            }
        }
    }
    return 0;
}

int UnknownFunction_208()
{


    // ResetA
    intF[354] = intD[346];
    intF[355] = intD[347];
    intF[356] = 0;
    intF[357] = 0;
    intF[358] = 0;
    intF[359] = 0;
    intF[360] = 0;
    intF[361] = 0;
    intF[362] = 0;
    intF[366] = 0;
    intF[376] = 0;
    intF[385] = 0;
    intF[386] = 0;
    intF[387] = 0;
    intF[388] = 0;
    intF[389] = -1;
    intF[390] = 0;
    intF[391] = 0;
    intF[392] = 0;
    intF[518] = 0;
    intF[544] = 0;
    intF[545] = 0;
    intF[547] = 0;
    intF[570] = 0;

    if (intF[351])
    {
        if (intF[351] == 1)
            intF[351] = 99;
    }
    else
    {
        //TODO FUNC 10013C90
        intF[351] = 1;
    }
    return 0;
}


// Incomplete TODO Needs to be done next
int UnknownFunction_209()
{
    //printf("Function: %d\n", 209);
    //for (int i = 356; i <= 570; ++i)
    //    intF[i] = 0;
    //intD[1850] = 0;
    //intF[389] = -1;
    //intF[354] = intD[346];
    //intF[355] = intD[347];

    // ResetA
    intF[354] = intD[346];
    intF[355] = intD[347];
    intF[356] = 0;
    intF[357] = 0;
    intF[358] = 0;
    intF[359] = 0;
    intF[360] = 0;
    intF[361] = 0;
    intF[362] = 0;
    intF[366] = 0;
    intF[376] = 0;
    intF[385] = 0;
    intF[386] = 0;
    intF[387] = 0;
    intF[388] = 0;
    intF[389] = -1;
    intF[390] = 0;
    intF[391] = 0;
    intF[392] = 0;
    intF[518] = 0;
    intF[544] = 0;
    intF[545] = 0;
    intF[547] = 0;
    intF[570] = 0;
    int temp = 0;
    if (intF[351] != 0 || (intF[351] = 1, sub_10016CF0() != 1))
    {
        if (intF[351] != 1 || (intF[351] = 2, sub_10016E70() != 1))
        {
            if (intF[351] != 2 || (intF[351] = 3, temp != 1))
            {
                if (intF[351] != 3 || (intF[351] = 4, temp != 1))
                {
                    if (intF[351] != 4 || (intF[351] = 5, temp != 1))
                    {
                        if (intF[351] != 5 || (intF[351] = 6, temp != 1))
                        {
                            if (intF[351] != 6 || (intF[351] = 7, temp != 1))
                            {
                                if (intF[351] != 7 || (intF[351] = 8, temp != 1))
                                {
                                    if (intF[351] != 8 || (intF[351] = 9, temp != 1))
                                    {
                                        if (intF[351] != 9 || (intF[351] = 10, temp != 1))
                                        {
                                            if (intF[351] != 10 || (intF[351] = 11, temp != 1))
                                            {
                                                if (intF[351] == 11)
                                                    intF[351] = 99;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int UnknownFunction_220()
{
    // ResetA
    intF[354] = intD[346];
    intF[355] = intD[347];
    intF[356] = 0;
    intF[357] = 0;
    intF[358] = 0;
    intF[359] = 0;
    intF[360] = 0;
    intF[361] = 0;
    intF[362] = 0;
    intF[366] = 0;
    intF[376] = 0;
    intF[385] = 0;
    intF[386] = 0;
    intF[387] = 0;
    intF[388] = 0;
    intF[389] = -1;
    intF[390] = 0;
    intF[391] = 0;
    intF[392] = 0;
    intF[518] = 0;
    intF[544] = 0;
    intF[545] = 0;
    intF[547] = 0;
    intF[570] = 0;
    intF[351] = 99;
    return 0;
}

int UnknownFunction_221()
{
    memset(&intF[356], 0, 37 * 4);
    intF[354] = intF[346];
    intF[355] = intF[347];
    intF[389] = -1;
    intF[518] = 0;
    intF[544] = 0;
    intF[545] = 0;
    intF[547] = 0;
    intF[570] = 0;

    auto enemy = &Enemies[intF[347]];
    if (enemy->unknown35)
        intF[350] = 9;
    if (intF[350] == 2)
    {
        if (intF[41] == 1)
            intF[350] = 4;
        if (intF[350] == 2)
        {
            switch (enemy->type)
            {
            case EnemyType_RedBeastman:
            case EnemyType_GreenBeastman:
            case EnemyType_BlueBeastman:
            case 3:
            case 4:
            case EnemyType_Golem:
            case 6:
                intF[350] = 3;
                break;
            default:
                return 0;
            }
        }
    }
    return 0;
}

// Imcomplete
int UnknownFunction_222()
{
    intF[354] = intF[346];
    intF[355] = intF[347];
    intF[389] = -1;
    intF[518] = 0;
    intF[544] = 0;
    intF[545] = 0;
    intF[547] = 0;
    intF[570] = 0;

    if (intF[351] == 1)
    {
        intF[351] = 99;
    }
    else
    {
        intF[351] = 1;
    }
    return 0;
}

int UnknownFunction_229_sub_10016510()
{
    int enemySlot = intF[347];
    auto enemy = &Enemies[enemySlot];
    if (enemy->unknown35)
    {
        if (enemy->unknown36 != -1)
        {
            --enemy->unknown36;
            if (enemy->unknown35 > 0)
                return 0;

            intF[547] = 1;
            intF[548] = 0;
            intF[549] =  enemySlot + 5;
            intF[550 + intF[570]] = enemy->unknown35;
            ++intF[570];
            enemy->unknown35 = 0;
            return 1;
        }
    }
    return 0;
}

int UnknownFunction_229()
{
    intF[354] = intF[346];
    intF[355] = intF[347];
    intF[389] = -1;
    intF[518] = 0;
    intF[544] = 0;
    intF[545] = 0;
    intF[547] = 0;
    intF[570] = 0;
    intD[1850] = 0;

    if (intF[351] || (intF[351] = 1, UnknownFunction_229_sub_10016510() != 1))
    {
        if (intF[351] == 1)
            intF[351] = 99;
    }
    return 0;
}























bool sub_10016CF0()
{
    int playerID = intF[347];
    auto player = &Players[playerID];
    if (player->alive && player->unknown093 != 99)
    {
        int i = 0;
        while ((&player->unknown148)[i] != 36)
        {
            ++i;
            if (i >= 3)
                return false;
        }
        intF[379] = 0;
        if (intB[0] == 1 && intB[93] != 99)
            intF[379] = 1;
        intF[380] = 0;
        if (intB[179] == 1 && intB[272] != 99)
            intF[380] = 1;
        intF[381] = 0;
        if (intB[358] == 1 && intB[451] != 99)
            intF[381] = 1;
        intF[382] = 0;
        if (intB[537] == 1 && intB[630] != 99)
            intF[382] = 1;
        intF[383] = 0;
        if (intB[716] == 1 && intB[809] != 99)
            intF[383] = 1;
        if (intF[379] == 1)
        {
            intF[376] = 1;
            intF[377] = playerID;
            intF[378] = 36;
            intF[intF[518] + 393] = 0;
            intF[intF[518] + 418] = 1;
            intF[intF[518] + 443] = 6;
            intF[intF[518] + 468] = 2 * player->level;
            intF[intF[518]++ + 493] = 0;
            return true;
        }
    }
    return false;
}

bool sub_10016E70()
{
    int playerID = intF[347];
    auto player = &Players[playerID];
    if (player->alive && player->unknown093 != 99)
    {
        int i = 0;
        while ((&player->unknown148)[i] != 37)
        {
            ++i;
            if (i >= 3)
                return false;
        }
        intF[379] = 0;
        if (intB[0] == 1 && intB[93] != 99)
            intF[379] = 1;
        intF[380] = 0;
        if (intB[179] == 1 && intB[272] != 99)
            intF[380] = 1;
        intF[381] = 0;
        if (intB[358] == 1 && intB[451] != 99)
            intF[381] = 1;
        intF[382] = 0;
        if (intB[537] == 1 && intB[630] != 99)
            intF[382] = 1;
        intF[383] = 0;
        if (intB[716] == 1 && intB[809] != 99)
            intF[383] = 1;
        if (intF[379] == 1)
        {
            intF[376] = 1;
            intF[377] = playerID;
            intF[378] = 37;
            intF[intF[518] + 393] = 0;
            intF[intF[518] + 418] = 1;
            intF[intF[518] + 443] = 6;
            intF[intF[518] + 468] = 2 * player->level;
            intF[intF[518]++ + 493] = 0;
            return true;
        }
    }
    return false;
}
