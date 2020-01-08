#include "Character.h"
#include "LevelingData.h"

Player* Players = nullptr;

void ClearPlayerData(int playerSlot)
{
    memset(&Players[playerSlot], 0, sizeof(Player));
}

void ResetPlayerData(int playerSlot)
{
    ClearPlayerData(playerSlot);
    Player* player = &Players[playerSlot];
    player->level = 1;
    player->jobLevel = 1;
    player->experience = LevelRequirements[player->level + 1];


    // Setup Jobs and positions
    switch (playerSlot)
    {
    case Char_Tomoya:
        player->x = 4;
        player->y = 6;
        player->rotation = Rot_East;
        player->job = Job_Swordsman;
        player->unlockedJobs[player->job] = true;
        break;
    case Char_Tomoyo:
        player->x = 4;
        player->y = 8;
        player->rotation = Rot_East;
        player->job = Job_Swordsman;
        player->unlockedJobs[player->job] = true;
        break;
    case Char_Kanako:
        player->x = 4;
        player->y = 11;
        player->rotation = Rot_East;
        player->job = Job_Swordsman;
        player->unlockedJobs[player->job] = true;
        break;
    case Char_Tomo:
        player->x = 4;
        player->y = 13;
        player->rotation = Rot_East;
        player->job = Job_Magus;
        player->unlockedJobs[player->job] = true;
        break;
    case Char_Fuko:
        player->x = 4;
        player->y = 10;
        player->rotation = Rot_East;
    default:
        player->job = Job_None;
        break;
    }
    
    player->spawnX = player->x;
    player->spawnY = player->y;
    player->spawnRotation = player->rotation;
}

// Adds 
Stats* AddStatToPlayer(Player* player, Stats* right)
{
    player->currentStat.attackR    += right->attackR;
    player->currentStat.attackL    += right->attackL;
    player->currentStat.defense    += right->defense;
    player->currentStat.intellect  += right->intellect;
    player->currentStat.unknown4   += right->unknown4;
    player->currentStat.dexterity  += right->dexterity;
    player->currentStat.unknown6   += right->unknown6;
    player->currentStat.carryPower += right->carryPower;
    player->currentStat.speed      += right->speed;
    player->currentStat.moves      += right->moves;
    return &player->currentStat;
}