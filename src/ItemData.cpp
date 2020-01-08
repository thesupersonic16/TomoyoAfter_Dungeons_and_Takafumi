// Please We need to find a better way of handling this. This is just f**king horrible.

#include "ItemData.h"
#include "Character.h"

#define ALLPLAYERS 31
#define ALLJOBS 1023

Item* Items = new Item[1800];
int* ItemStorage = nullptr;

void AddItem(int slot, ItemType type, int icon, bool twoHanded, int unknown3, int equipablePlayer, int equipableJob, int unknown6, int weight, int unknown8, int healing, int unknown10, int attackL, int attackR, int defense, int intellect, int unknown15, int dexterity, int unknown17, int carryPower, int speed, int moves, int unknown26, int unknown27, int unknown28, int unknown29, int unknown30, int unknown31, int unknown32, int unknown33, int unknown34)
{
    Items[slot].type = type;
    Items[slot].icon = icon;
    Items[slot].attributes = (twoHanded ? 2 : 0) | (type == ItemType_Weapons);
    Items[slot].unknown3 = unknown3;
    Items[slot].equipablePlayer = equipablePlayer;
    Items[slot].equipableJob = equipableJob;
    Items[slot].unknown6 = unknown6;
    Items[slot].weight = weight;
    Items[slot].unknown8 = unknown8;
    Items[slot].healing = healing;
    Items[slot].unknown10 = unknown10;
    Items[slot].statIncrease.attackL = attackL;
    Items[slot].statIncrease.attackR = attackR;
    Items[slot].statIncrease.defense = defense;
    Items[slot].statIncrease.intellect = intellect;
    Items[slot].statIncrease.unknown4 = unknown15;
    Items[slot].statIncrease.dexterity = dexterity;
    Items[slot].statIncrease.unknown6 = unknown17;
    Items[slot].statIncrease.carryPower = carryPower;
    Items[slot].statIncrease.speed = speed;
    Items[slot].statIncrease.moves = moves;
    Items[slot].unknown21 = 268982768; // Unknown
    Items[slot].unknown22 = 268982768; // Unknown
    Items[slot].unknown23 = 268982768; // Unknown
    Items[slot].unknown24 = 268982768; // Unknown
    Items[slot].unknown25 = 268982768; // Unknown
    Items[slot].unknown26 = unknown26;
    Items[slot].unknown27 = unknown27;
    Items[slot].unknown28 = unknown28;
    Items[slot].unknown29 = unknown29;
    Items[slot].unknown30 = unknown30;
    Items[slot].unknown31 = unknown31;
    Items[slot].unknown32 = unknown32;
    Items[slot].unknown33 = unknown33;
    Items[slot].unknown34 = unknown34;
}

int CountItemsInStorage(int start)
{
    for (int i = start; i < 350; ++i)
    {
        if (!ItemStorage[i])
            return i - start;
    }
    return 350;
}

int AddItemToStorage(int itemID)
{
    int count = CountItemsInStorage(0);
    if (count == 350)
        printf("AddItemToStorage: WARNING: >= 350 Items Detected!\n");
    else
    {
        // Add item to the end of storage
        ItemStorage[count + 000] = itemID;
        ItemStorage[count + 350] = 0;
        ItemStorage[count + 700] = -1;
        GetTotalWeight();
        printf("AddItemToStorage: Added new Item %d into storage slot %d.\n", itemID, count);
    }
    return 0;
}

int RemoveItemFromStorage(int itemSlot)
{
    int count = CountItemsInStorage(itemSlot);
    if (count == 350)
        printf("AddItemToStorage: WARNING: >= 350 Items Detected!\n");
    else
    {
        // Shift all items back by 1
        for (int i = 0; i < count; ++i)
        {
            ItemStorage[itemSlot + i + 000] = ItemStorage[itemSlot + i + 1 + 000];
            ItemStorage[itemSlot + i + 350] = ItemStorage[itemSlot + i + 1 + 350];
            ItemStorage[itemSlot + i + 700] = ItemStorage[itemSlot + i + 1 + 700];
        }
        // Erase Last item
        ItemStorage[itemSlot + count + 000] = 0;
        ItemStorage[itemSlot + count + 350] = 0;
        ItemStorage[itemSlot + count + 400] = -1;
        // Recalculate Weight
        GetTotalWeight();
        printf("RemoveItemFromStorage: Removed item from storage slot %d.\n", itemSlot);
    }
    return 0;
}

int CheckItemConsumable(int playerID, int itemID)
{
    Player* player = &Players[playerID];
    Item* item = &Items[itemID];
    bool useable = false;
    // Health Potion
    if (item->type == 2)
    {
        if (player->currentHealth < player->maxHealth)
            useable = true;
    }
    else if (item->type != 3) // Unknown
    {
        if ((item->healing > 0 && player->unknown017 < 500) ||
            (item->statIncrease.attackR > 0 && player->unknown33.attackR < 500) ||
            (item->statIncrease.attackL > 0 && player->unknown33.attackL < 500) ||
            (item->statIncrease.defense > 0 && player->unknown33.defense < 500) ||
            (item->statIncrease.intellect > 0 && player->unknown33.intellect < 500) ||
            (item->statIncrease.unknown4 > 0 && player->unknown33.unknown4 < 500) ||
            (item->statIncrease.dexterity > 0 && player->unknown33.dexterity < 500) ||
            (item->statIncrease.unknown6 > 0 && player->unknown33.unknown6 < 500) ||
            (item->statIncrease.carryPower > 0 && player->unknown33.carryPower < 500) ||
            (item->statIncrease.speed > 0 && player->unknown33.speed < 500) ||
            (item->statIncrease.moves > 0 && player->unknown33.moves < 500)
            )
            useable = true;
    }
    intC[1837] = useable;
    return 0;
}

int CheckItemEquipable(int playerID, int itemID)
{
    Item* item = &Items[itemID];
    int playerFlag = 1 << playerID;
    int jobFlag = 1 << Players[playerID].job;

    intC[1972] = (playerFlag & item->equipablePlayer && jobFlag & item->equipableJob) ? 1 : 0;
    return 0;
}

int EquipItemAuto(int playerID, int storageSlot)
{
    Item* item = &Items[ItemStorage[storageSlot]];
    Player* player = &Players[playerID];
    
    switch (item->type)
    {
    case ItemType_Weapons:
        break;
    case ItemType_Shields:
        break;
    case ItemType_Head:
        break;
    case ItemType_Body:
        break;
    case ItemType_Arm:
        break;
    case ItemType_Leg:
        intC[1972] = intC[storageSlot + 1100] != 8 * playerID + 5;
        intC[1973] = 5;
        break;
    case ItemType_Accessory:
        break;
    default:
        break;
    }
    
    return 0;
}

int ClearItemStorage()
{
    memset(ItemStorage, 0, 350 * 3);
    return 0;
}

int GetTotalWeight()
{
    int weight = 0;
    for (int i = 0; i < 350; ++i)
    {
        if (!ItemStorage[i])
        {
            intC[1801] = weight;
            return weight;
        }
        weight += Items[ItemStorage[i]].weight;
    }
    printf("GetTotalWeight: WARNING: >= 350 Items Detected!\n");
    return 0;
}

int FilterItemList(ItemType filter, int playerFlags, int jobFlags)
{
    int filteredItemCount = 0;
    int filteredItems[350];
    int itemslot = 0;
    for (int storageSlot = 0; storageSlot < 350; ++storageSlot)
    {
        if (!(itemslot = ItemStorage[storageSlot]))
            break;
        ItemType type = Items[itemslot].type;
        if (filter)
        {
            bool pass = filter == type;
            switch (filter)
            {
            case ItemType_Useless:
                pass |= type == ItemType_Potions;
                pass |= type == ItemType_Unknown;
                break;
            case ItemType_Equipment:
                pass |= type == ItemType_Weapons;
                pass |= type == ItemType_Shields;
                pass |= type == ItemType_Head;
                pass |= type == ItemType_Body;
                pass |= type == ItemType_Arm;
                pass |= type == ItemType_Leg;
                pass |= type == ItemType_Accessory;
                break;
            case ItemType_Armor:
                pass |= type == ItemType_Shields;
                pass |= type == ItemType_Head;
                pass |= type == ItemType_Body;
                pass |= type == ItemType_Arm;
                pass |= type == ItemType_Leg;
                break;
            case ItemType_Hands:
                pass |= type == ItemType_Weapons;
                pass |= type == ItemType_Shields;
                break;
            case ItemType_AllItems:
                pass = true;
            }
            if (pass)
                if (Items[itemslot].equipablePlayer & playerFlags && Items[itemslot].equipableJob & jobFlags)
                    filteredItems[filteredItemCount++] = storageSlot;
        }
    }
    // Logging
    printf("ListItemsWithFilter: Listed %d Items using filter of %d.\n", filteredItemCount, filter);

    // Sort Items by Type
    if (filter == ItemType_Hands)
    {
        for (int i = filteredItemCount - 1; i > 0; --i)
        {
            for (int ii = 0; ii < i; ++ii)
            {
                if (Items[intC[filteredItems[ii + 1] + 400]].type < 
                    Items[intC[filteredItems[ii + 0] + 400]].type)
                {
                    int buffer = filteredItems[ii];
                    filteredItems[ii + 0] = filteredItems[ii + 1];
                    filteredItems[ii + 1] = buffer;
                }
            }
        }
    }
    
    memcpy(&intC[1450], filteredItems, 350 * sizeof(int));
    intC[1800] = filteredItemCount;
    return 0;
}

void AddAllItems()
{
    memset(Items, 0, 1800 * sizeof(Item));
    //       ID      Item Type      Icon 2Handed       PFLAGS    JFLAGS      Weight  Heal    |         statIncrease        |
    AddItem( 100, ItemType_Potions  ,  1, false,  0, ALLPLAYERS, ALLJOBS,   0, 10, 0,  30, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300);
    AddItem( 101, ItemType_Potions  ,  2, false,  0, ALLPLAYERS, ALLJOBS,   1, 20, 0,  80, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0, 300, 300, 300, 300, 300, 300, 300);
    AddItem( 102, ItemType_Potions  ,  3, false,  0, ALLPLAYERS, ALLJOBS,   2, 30, 0, 200, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0, 300, 300, 300, 300);
    AddItem( 200, ItemType_Unknown  ,  4, false,  0, ALLPLAYERS, ALLJOBS,   0, 10, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 300, ItemType_Weapons  ,  5, false,  2, ALLPLAYERS, ALLJOBS, 214,  4, 0,   0, 0,   4,  0,  0, 0, 0, 0, 0,  0, 0,  30,  30,  15,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 301, ItemType_Weapons  ,  5, false,  2, ALLPLAYERS, ALLJOBS, 295, 12, 0,   0, 0,  26,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,  30,  30,  15,   0,   0,   0,   0);
    AddItem( 302, ItemType_Weapons  ,  5, false,  2, ALLPLAYERS, ALLJOBS, 206, 18, 0,   0, 0,  60,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 400, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 171, 10, 0,   0, 0,   1,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 401, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 172, 10, 0,   0, 0,   2,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 402, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 173, 10, 0,   0, 0,   3,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 403, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 174, 14, 0,   0, 0,  10,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 404, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 175, 14, 0,   0, 0,  11,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 405, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 176, 14, 0,   0, 0,  12,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 406, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 177, 18, 0,   0, 0,  20,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 407, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 178, 18, 0,   0, 0,  21,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 408, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 179, 18, 0,   0, 0,  22,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 409, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 180, 18, 0,   0, 0,  23,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 410, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 228, 18, 0,   0, 0,  24,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 411, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 229, 18, 0,   0, 0,  34,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 412, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 230, 18, 0,   0, 0,  44,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 413, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 231, 22, 0,   0, 0,  58,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   5,   5,   5,   0);
    AddItem( 414, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 232, 22, 0,   0, 0,  68,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   5,   5,   5,   0);
    AddItem( 415, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 233, 22, 0,   0, 0,  78,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   5,   5,   5,   0);
    AddItem( 416, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 234, 24, 0,   0, 0,  80,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem( 417, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 235, 24, 0,   0, 0,  85,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem( 418, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 236, 24, 0,   0, 0,  90,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem( 419, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 237, 24, 0,   0, 0, 100,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem( 420, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 285,  6, 0,   0, 0,   4,  0,  0, 0, 0, 0, 0,  0, 0,  30,  30,  15,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 421, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 286, 22, 0,   0, 0, 106,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   6);
    AddItem( 422, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 199,  8, 0,   0, 0,   8,  0,  0, 0, 0, 0, 0,  0, 0,   0,  30,  30,  15,   0,   0,   0,   0,   0,   0);
    AddItem( 423, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 205, 10, 0,   0, 0,  12,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,  30,  30,  15,   0,   0,   0,   0,   0);
    AddItem( 424, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 189, 14, 0,   0, 0,  16,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,  30,  30,  15,   0,   0,   0,   0,   0);
    AddItem( 425, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 292, 16, 0,   0, 0,  24,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,  30,  30,  15,   0,   0,   0,   0);
    AddItem( 426, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 158,  9, 0,   0, 0,  19,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  30,  30,  15,   0,   0,   0);
    AddItem( 427, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 157, 18, 0,   0, 0,  38,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  30,  30,  15,   0,   0,   0);
    AddItem( 428, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 208, 20, 0,   0, 0,  46,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  30,  30,  15,   0,   0);
    AddItem( 429, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 207, 20, 0,   0, 0,  52,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  30,  30,  15,   0,   0);
    AddItem( 430, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 153, 22, 0,   0, 0,  72,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  30,  30,  15,   0);
    AddItem( 431, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 213, 24, 0,   0, 0,  84,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 432, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 150, 13, 0,   0, 0,  45,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 433, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 149, 26, 0,   0, 0,  90,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 434, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 193, 14, 0,   0, 0,  48,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  30,  30);
    AddItem( 435, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 192, 28, 0,   0, 0,  96,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  30,  30);
    AddItem( 436, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 135, 15, 0,   0, 0,  59,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  30);
    AddItem( 437, ItemType_Weapons  ,  6, false,  3, ALLPLAYERS, ALLJOBS, 134, 30, 0,   0, 0, 118,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  30);
    AddItem( 500, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 114, 12, 0,   0, 0,   1,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 501, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 115, 12, 0,   0, 0,   2,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 502, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 116, 12, 0,   0, 0,   3,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 503, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 117, 16, 0,   0, 0,   6,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 504, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 118, 16, 0,   0, 0,   7,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 505, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 119, 16, 0,   0, 0,   8,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 506, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 120, 20, 0,   0, 0,  12,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 507, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 121, 20, 0,   0, 0,  13,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 508, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 122, 20, 0,   0, 0,  14,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 509, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 123, 20, 0,   0, 0,  15,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 510, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 159, 12, 0,   0, 0,   2,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 511, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 160, 12, 0,   0, 0,   3,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 512, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 161, 12, 0,   0, 0,   4,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 513, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 162, 16, 0,   0, 0,   9,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 514, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 163, 16, 0,   0, 0,  10,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 515, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 164, 16, 0,   0, 0,  11,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 516, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 165, 20, 0,   0, 0,  17,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 517, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 166, 20, 0,   0, 0,  18,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 518, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 167, 20, 0,   0, 0,  19,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 519, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 168, 20, 0,   0, 0,  20,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 520, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 273, 12, 0,   0, 0,   3,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 521, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 274, 12, 0,   0, 0,   4,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 522, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 275, 12, 0,   0, 0,   5,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 523, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 276, 16, 0,   0, 0,  12,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 524, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 277, 16, 0,   0, 0,  13,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 525, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 278, 16, 0,   0, 0,  14,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 526, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 279, 20, 0,   0, 0,  22,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 527, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 280, 20, 0,   0, 0,  23,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 528, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 281, 20, 0,   0, 0,  24,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 529, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 282, 20, 0,   0, 0,  25,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 530, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 261,  4, 0,   0, 0,   2,  0,  0, 0, 0, 0, 0,  0, 0,  30,  30,  15,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 531, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 260,  8, 0,   0, 0,   5,  0,  0, 0, 0, 0, 0,  0, 0,  30,  30,  15,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 532, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 265,  6, 0,   0, 0,   5,  0,  0, 0, 0, 0, 0,  0, 0,   0,  30,  30,  15,   0,   0,   0,   0,   0,   0);
    AddItem( 533, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 264, 12, 0,   0, 0,  10,  0,  0, 0, 0, 0, 0,  0, 0,   0,  30,  30,  15,   0,   0,   0,   0,   0,   0);
    AddItem( 534, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 204, 10, 0,   0, 0,  14,  0,  0, 0, 0, 0, 0,  0, 0,   0,  30,  30,  15,   0,   0,   0,   0,   0,   0);
    AddItem( 535, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 203,  7, 0,   0, 0,  10,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,  30,  30,  15,   0,   0,   0,   0,   0);
    AddItem( 536, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 202, 15, 0,   0, 0,  20,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,  30,  30,  15,   0,   0,   0,   0,   0);
    AddItem( 537, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 147, 12, 0,   0, 0,  30,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,  30,  30,  15,   0,   0,   0,   0);
    AddItem( 538, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 210, 16, 0,   0, 0,  25,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,  30,  30,  15,   0,   0,   0,   0);
    AddItem( 539, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 209, 16, 0,   0, 0,  35,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  30,  30,  15,   0,   0,   0);
    AddItem( 540, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 146, 16, 0,   0, 0,  40,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  30,  30,  15,   0,   0,   0);
    AddItem( 541, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 196, 10, 0,   0, 0,  32,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  30,  30,  15,   0,   0,   0);
    AddItem( 542, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 201, 10, 0,   0, 0,  23,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  30,  30,  15,   0,   0,   0);
    AddItem( 543, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 200, 20, 0,   0, 0,  46,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  30,  30,  15,   0,   0,   0);
    AddItem( 544, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 181, 24, 0,   0, 0,  50,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  30,  30,  15,   0,   0);
    AddItem( 545, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 169, 24, 0,   0, 0,  54,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  30,  30,  15,   0,   0);
    AddItem( 546, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 170, 24, 0,   0, 0,  62,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  30,  30,  15,   0,   0);
    AddItem( 547, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 144, 10, 0,   0, 0,  34,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  30,  30,  15,   0);
    AddItem( 548, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 143, 20, 0,   0, 0,  68,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  30,  30,  15,   0);
    AddItem( 549, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 113, 28, 0,   0, 0,  74,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  30,  30,  15,   0);
    AddItem( 550, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 183, 28, 0,   0, 0,  80,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  30,  30,  15,   0);
    AddItem( 551, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 191, 14, 0,   0, 0,  43,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 552, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 190, 28, 0,   0, 0,  86,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 553, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 137, 30, 0,   0, 0,  90,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 554, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 136, 30, 0,   0, 0,  98,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 555, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 287, 20, 0,   0, 0,  80,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  30,  30);
    AddItem( 556, ItemType_Weapons  ,  7, false,  5, ALLPLAYERS, ALLJOBS, 288, 34, 0,   0, 0,  80,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  10,  20);
    AddItem( 557, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 155, 46, 0,   0, 0, 100,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  30,  30);
    AddItem( 558, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 156, 50, 0,   0, 0, 112,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  30,  30);
    AddItem( 559, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 186, 40, 0,   0, 0, 118,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  30,  30);
    AddItem( 560, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 188, 20, 0,   0, 0,  64,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  30);
    AddItem( 561, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 187, 40, 0,   0, 0, 128,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  30);
    AddItem( 562, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 111, 18, 0,   0, 0,  75,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  30);
    AddItem( 563, ItemType_Weapons  ,  7, false,  4, ALLPLAYERS, ALLJOBS, 110, 36, 0,   0, 0, 150,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5);
    AddItem( 600, ItemType_Weapons  ,  8, false,  6, ALLPLAYERS, ALLJOBS, 284, 16, 0,   0, 0,  14,  0,  0, 0, 0, 0, 0,  0, 0,   0,  30,  30,  15,   0,   0,   0,   0,   0,   0);
    AddItem( 601, ItemType_Weapons  ,  8, false,  6, ALLPLAYERS, ALLJOBS, 291, 16, 0,   0, 0,  16,  0,  0, 0, 0, 0, 0,  0, 0,   0,  30,  30,  15,   0,   0,   0,   0,   0,   0);
    AddItem( 602, ItemType_Weapons  ,  8, false,  6, ALLPLAYERS, ALLJOBS, 290, 20, 0,   0, 0,  26,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,  30,  30,  15,   0,   0,   0,   0,   0);
    AddItem( 603, ItemType_Weapons  ,  8, false,  6, ALLPLAYERS, ALLJOBS, 310, 24, 0,   0, 0,  45,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,  30,  30,  15,   0,   0,   0,   0);
    AddItem( 604, ItemType_Weapons  ,  8, false,  6, ALLPLAYERS, ALLJOBS, 100, 28, 0,   0, 0,  75,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  20,  30,  15,   0,   0);
    AddItem( 605, ItemType_Weapons  ,  8, false,  6, ALLPLAYERS, ALLJOBS, 100, 32, 0,   0, 0,  92,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  20,  30,  15,   0);
    AddItem( 606, ItemType_Weapons  ,  8, false,  6, ALLPLAYERS, ALLJOBS, 112, 40, 0,   0, 0, 115,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  20,  30,  15);
    AddItem( 607, ItemType_Weapons  ,  8, false,  6, ALLPLAYERS, ALLJOBS, 102, 50, 0,   0, 0, 145,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  20,  30);
    AddItem( 700, ItemType_Weapons  ,  9, false,  7, ALLPLAYERS, ALLJOBS, 296, 32, 0,   0, 0,  80,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 701, ItemType_Weapons  ,  9, false,  7, ALLPLAYERS, ALLJOBS, 297, 32, 0,   0, 0,  94,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 702, ItemType_Weapons  ,  9, false,  7, ALLPLAYERS, ALLJOBS, 105, 36, 0,   0, 0, 105,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  40,  40);
    AddItem( 703, ItemType_Weapons  ,  9, false,  7, ALLPLAYERS, ALLJOBS, 103, 20, 0,   0, 0,  60,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  30);
    AddItem( 704, ItemType_Weapons  ,  9, false,  7, ALLPLAYERS, ALLJOBS, 104, 40, 0,   0, 0, 120,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5);
    AddItem( 800, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 300, 14, 0,   0, 0,   1,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 801, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 301, 14, 0,   0, 0,   3,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 802, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 302, 14, 0,   0, 0,   5,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 803, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 303, 18, 0,   0, 0,  10,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 804, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 304, 18, 0,   0, 0,  13,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 805, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 305, 18, 0,   0, 0,  16,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 806, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 306, 22, 0,   0, 0,  20,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 807, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 307, 22, 0,   0, 0,  23,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 808, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 308, 22, 0,   0, 0,  26,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 809, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 309, 22, 0,   0, 0,  29,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 810, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 238, 26, 0,   0, 0,  30,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 811, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 239, 26, 0,   0, 0,  40,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 812, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 240, 26, 0,   0, 0,  50,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 813, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 241, 30, 0,   0, 0,  60,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   5,   5,   5,   0);
    AddItem( 814, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 242, 30, 0,   0, 0,  80,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   5,   5,   5,   0);
    AddItem( 815, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 243, 30, 0,   0, 0,  90,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   5,   5,   5,   0);
    AddItem( 816, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 244, 38, 0,   0, 0,  80,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem( 817, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 245, 38, 0,   0, 0,  90,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem( 818, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 246, 38, 0,   0, 0, 110,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem( 819, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 247, 38, 0,   0, 0, 120,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem( 820, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 152,  7, 0,   0, 0,   3,  0,  0, 0, 0, 0, 0,  0, 0,  30,  30,  15,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 821, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 151, 14, 0,   0, 0,   6,  0,  0, 0, 0, 0, 0,  0, 0,  30,  30,  15,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 822, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 139, 10, 0,   0, 0,  11,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,  30,  30,  15,   0,   0,   0,   0,   0);
    AddItem( 823, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 138, 20, 0,   0, 0,  23,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,  30,  30,  15,   0,   0,   0,   0,   0);
    AddItem( 824, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 212, 14, 0,   0, 0,  25,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  30,  30,  15,   0,   0,   0);
    AddItem( 825, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 211, 28, 0,   0, 0,  50,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  30,  30,  15,   0,   0,   0);
    AddItem( 826, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 266, 32, 0,   0, 0,  78,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  30,  30,  15,   0);
    AddItem( 827, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 109, 16, 0,   0, 0,  42,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  30,  30,  15,   0);
    AddItem( 828, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 108, 32, 0,   0, 0,  84,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  30,  30,  15,   0);
    AddItem( 829, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 217, 35, 0,   0, 0,  94,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 830, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 216, 20, 0,   0, 0,  52,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 831, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 215, 40, 0,   0, 0, 104,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 832, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 195, 23, 0,   0, 0,  61,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  30,  30);
    AddItem( 833, ItemType_Weapons  , 10, false,  8, ALLPLAYERS, ALLJOBS, 194, 46, 0,   0, 0, 122,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  30,  30);
    AddItem( 900, ItemType_Weapons  , 11, false,  9, ALLPLAYERS, ALLJOBS, 124, 14, 0,   0, 0,   1,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 901, ItemType_Weapons  , 11, false,  9, ALLPLAYERS, ALLJOBS, 125, 14, 0,   0, 0,   2,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 902, ItemType_Weapons  , 11, false,  9, ALLPLAYERS, ALLJOBS, 126, 14, 0,   0, 0,   3,  0,  0, 0, 0, 0, 0,  0, 0,   5,   5,   5,   0,   0,   0,   0,   0,   0,   0);
    AddItem( 903, ItemType_Weapons  , 11, false,  9, ALLPLAYERS, ALLJOBS, 127, 20, 0,   0, 0,   8,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 904, ItemType_Weapons  , 11, false,  9, ALLPLAYERS, ALLJOBS, 128, 20, 0,   0, 0,  10,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 905, ItemType_Weapons  , 11, false,  9, ALLPLAYERS, ALLJOBS, 129, 20, 0,   0, 0,  12,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   5,   5,   5,   0,   0,   0,   0,   0);
    AddItem( 906, ItemType_Weapons  , 11, false,  9, ALLPLAYERS, ALLJOBS, 130, 26, 0,   0, 0,  16,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 907, ItemType_Weapons  , 11, false,  9, ALLPLAYERS, ALLJOBS, 131, 26, 0,   0, 0,  18,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 908, ItemType_Weapons  , 11, false,  9, ALLPLAYERS, ALLJOBS, 132, 26, 0,   0, 0,  20,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 909, ItemType_Weapons  , 11, false,  9, ALLPLAYERS, ALLJOBS, 133, 26, 0,   0, 0,  22,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 910, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 248, 22, 0,   0, 0,  26,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 911, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 249, 22, 0,   0, 0,  32,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 912, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 250, 22, 0,   0, 0,  38,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem( 913, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 251, 28, 0,   0, 0,  50,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   5,   5,   5,   0);
    AddItem( 914, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 252, 28, 0,   0, 0,  60,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   5,   5,   5,   0);
    AddItem( 915, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 253, 28, 0,   0, 0,  70,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   5,   5,   5,   0);
    AddItem( 916, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 254, 35, 0,   0, 0,  86,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem( 917, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 255, 35, 0,   0, 0,  90,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem( 918, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 256, 35, 0,   0, 0,  96,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem( 919, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 257, 35, 0,   0, 0, 102,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem( 920, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 294, 14, 0,   0, 0,  10,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,  30,  30,  15,   0,   0,   0,   0,   0);
    AddItem( 921, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 272, 14, 0,   0, 0,  12,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,  30,  30,  15,   0,   0,   0,   0,   0);
    AddItem( 922, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 293, 16, 0,   0, 0,  16,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,  30,  30,  15,   0,   0,   0,   0,   0);
    AddItem( 923, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 185, 16, 0,   0, 0,  18,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,  30,  30,  15,   0,   0,   0,   0);
    AddItem( 924, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 184, 20, 0,   0, 0,  20,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,  30,  30,  15,   0,   0,   0,   0);
    AddItem( 925, ItemType_Weapons  , 11, false,  9, ALLPLAYERS, ALLJOBS, 267, 24, 0,   0, 0,  35,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  30,  30,  15,   0,   0,   0);
    AddItem( 926, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 148, 24, 0,   0, 0,  35,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  30,  30,  15,   0,   0,   0);
    AddItem( 927, ItemType_Weapons  , 11, false, 11, ALLPLAYERS, ALLJOBS, 263, 14, 0,   0, 0,  24,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  30,  30,  15,   0,   0);
    AddItem( 928, ItemType_Weapons  , 11, false, 11, ALLPLAYERS, ALLJOBS, 262, 28, 0,   0, 0,  48,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  30,  30,  15,   0,   0);
    AddItem( 929, ItemType_Weapons  , 11, false, 12, ALLPLAYERS, ALLJOBS, 268, 28, 0,   0, 0,  50,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  30,  30,  15,   0,   0);
    AddItem( 930, ItemType_Weapons  , 11, false, 13, ALLPLAYERS, ALLJOBS, 299, 15, 0,   0, 0,  32,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  30,  30,  15,   0);
    AddItem( 931, ItemType_Weapons  , 11, false, 13, ALLPLAYERS, ALLJOBS, 298, 30, 0,   0, 0,  64,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  30,  30,  15,   0);
    AddItem( 932, ItemType_Weapons  , 11, false, 14, ALLPLAYERS, ALLJOBS, 270, 30, 0,   0, 0,  33,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  30,  30,  15,   0);
    AddItem( 933, ItemType_Weapons  , 11, false, 14, ALLPLAYERS, ALLJOBS, 269, 60, 0,   0, 0,  66,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  30,  30,  15,   0);
    AddItem( 934, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 259, 16, 0,   0, 0,  41,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 935, ItemType_Weapons  , 11, false, 10, ALLPLAYERS, ALLJOBS, 258, 32, 0,   0, 0,  82,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem( 936, ItemType_Weapons  , 11, false, 15, ALLPLAYERS, ALLJOBS, 198, 18, 0,   0, 0,  43,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  30,  30);
    AddItem( 937, ItemType_Weapons  , 11, false, 15, ALLPLAYERS, ALLJOBS, 197, 36, 0,   0, 0,  86,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  30,  30);
    AddItem( 938, ItemType_Weapons  , 11, false, 15, ALLPLAYERS, ALLJOBS, 145, 36, 0,   0, 0, 102,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  10,  20);
    AddItem( 939, ItemType_Weapons  , 11, false, 16, ALLPLAYERS, ALLJOBS, 142, 19, 0,   0, 0,  52,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  30);
    AddItem( 940, ItemType_Weapons  , 11, false, 16, ALLPLAYERS, ALLJOBS, 141, 38, 0,   0, 0, 105,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5);
    AddItem(1000, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 218, 16, 0,   0, 0,  28,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem(1001, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 219, 16, 0,   0, 0,  36,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem(1002, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 220, 16, 0,   0, 0,  42,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   5,   5,   5,   0,   0,   0);
    AddItem(1003, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 221, 20, 0,   0, 0,  46,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   5,   5,   5,   0);
    AddItem(1004, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 222, 20, 0,   0, 0,  56,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   5,   5,   5,   0);
    AddItem(1005, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 223, 20, 0,   0, 0,  64,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   5,   5,   5,   0);
    AddItem(1006, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 224, 30, 0,   0, 0,  62,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem(1007, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 225, 30, 0,   0, 0,  68,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem(1008, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 226, 30, 0,   0, 0,  76,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem(1009, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 227, 30, 0,   0, 0,  86,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   5);
    AddItem(1010, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 289, 10, 0,   0, 0,  26,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  30,  30,  15,   0,   0,   0);
    AddItem(1011, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 154, 20, 0,   0, 0,  40,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  30,  30,  15,   0,   0);
    AddItem(1012, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 271, 30, 0,   0, 0,  62,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  30,  30,  15,   0);
    AddItem(1013, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 140, 35, 0,   0, 0,  80,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  15);
    AddItem(1014, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 107, 20, 0,   0, 0,  60,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  30,  30);
    AddItem(1015, ItemType_Weapons  , 12, true , 17, ALLPLAYERS, ALLJOBS, 106, 40, 0,   0, 0, 120,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5);
    AddItem(1100, ItemType_Weapons  , 13, true , 18, ALLPLAYERS, ALLJOBS, 283, 15, 0,   0, 0,  56,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  10,  10,   5,   0);
    AddItem(1101, ItemType_Weapons  , 13, true , 18, ALLPLAYERS, ALLJOBS, 182, 20, 0,   0, 0,  90,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5);
    AddItem(1200, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 420, 14, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1201, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 421, 14, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1202, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 422, 14, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1203, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 423, 14, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1204, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 424, 16, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1205, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 425, 16, 0,   0, 0,   0,  6,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1206, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 426, 16, 0,   0, 0,   0,  7,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1207, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 427, 16, 0,   0, 0,   0,  8,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1208, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 428, 18, 0,   0, 0,   0,  9,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1209, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 429, 18, 0,   0, 0,   0, 10,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1210, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 543,  6, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,  99,  99,  50,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1211, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 542, 12, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,  99,  99,  50,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1212, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 471,  7, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,   0,   0,  99,  99,  50,   0,   0,   0,   0,   0);
    AddItem(1213, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 470, 14, 0,   0, 0,   0,  6,  0, 0, 0, 0, 0,  0, 0,   0,   0,  99,  99,  50,   0,   0,   0,   0,   0);
    AddItem(1214, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 461,  8, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,  99,  99,  50,   0,   0,   0,   0);
    AddItem(1215, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 460, 16, 0,   0, 0,   0, 10,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,  99,  99,  50,   0,   0,   0,   0);
    AddItem(1216, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 537, 10, 0,   0, 0,   0,  7,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  99,  99,  50,   0,   0,   0);
    AddItem(1217, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 536, 20, 0,   0, 0,   0, 14,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  99,  99,  50,   0,   0,   0);
    AddItem(1218, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 499,  8, 0,   0, 0,   0,  8,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  99,  99,  50,   0,   0);
    AddItem(1219, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 498, 16, 0,   0, 0,   0, 16,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  99,  99,  50,   0,   0);
    AddItem(1220, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 479, 12, 0,   0, 0,   0,  9,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  99,  99,  50,   0);
    AddItem(1221, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 478, 24, 0,   0, 0,   0, 18,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  99,  99,  50,   0);
    AddItem(1222, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 521, 15, 0,   0, 0,   0, 11,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1223, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 520, 30, 0,   0, 0,   0, 22,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1224, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 419, 11, 0,   0, 0,   0, 12,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1225, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 418, 22, 0,   0, 0,   0, 24,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1226, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 481, 12, 0,   0, 0,   0, 13,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1227, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 480, 24, 0,   0, 0,   0, 26,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1228, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 413, 13, 0,   0, 0,   0, 14,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1229, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 412, 26, 0,   0, 0,   0, 28,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  20,  20);
    AddItem(1230, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 407, 12, 0,   0, 0,   0, 15,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  99);
    AddItem(1231, ItemType_Shields  , 14, false,  0, ALLPLAYERS, ALLJOBS, 406, 24, 0,   0, 0,   0, 30,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  20);
    AddItem(1300, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 488,  8, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1301, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 489,  8, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1302, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 490,  8, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1303, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 491,  8, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1304, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 492, 10, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1305, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 493, 10, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1306, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 494, 10, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1307, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 495, 10, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1308, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 496, 12, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1309, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 497, 12, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1310, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 511,  3, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,  99,  99,  50,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1311, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 510,  6, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,  99,  99,  50,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1312, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 505,  3, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,   0,   0,  99,  99,  50,   0,   0,   0,   0,   0);
    AddItem(1313, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 504,  6, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,   0,   0,  99,  99,  50,   0,   0,   0,   0,   0);
    AddItem(1314, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 515,  4, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  99,  99,  50,   0,   0,   0);
    AddItem(1315, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 514,  8, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  99,  99,  50,   0,   0,   0);
    AddItem(1316, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 469,  6, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  99,  99,  50,   0,   0);
    AddItem(1317, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 468, 12, 0,   0, 0,   0,  6,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  99,  99,  50,   0,   0);
    AddItem(1318, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 435,  5, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  99,  99,  50,   0);
    AddItem(1319, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 434, 10, 0,   0, 0,   0,  8,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  99,  99,  50,   0);
    AddItem(1320, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 519, 10, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1321, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 518, 20, 0,   0, 0,   0, 10,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1322, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 483,  8, 0,   0, 0,   0,  6,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1323, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 482, 16, 0,   0, 0,   0, 12,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1324, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 539,  7, 0,   0, 0,   0,  7,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1325, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 538, 14, 0,   0, 0,   0, 14,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1326, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 417,  9, 0,   0, 0,   0,  8,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  99);
    AddItem(1327, ItemType_Head     , 15, false,  0, ALLPLAYERS, ALLJOBS, 416, 18, 0,   0, 0,   0, 16,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  20);
    AddItem(1400, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 436, 12, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1401, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 437, 12, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1402, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 438, 12, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1403, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 439, 12, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1404, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 440, 16, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1405, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 441, 16, 0,   0, 0,   0,  6,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1406, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 442, 16, 0,   0, 0,   0,  7,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1407, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 443, 16, 0,   0, 0,   0,  8,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1408, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 444, 20, 0,   0, 0,   0,  9,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1409, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 445, 20, 0,   0, 0,   0, 10,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1410, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 545,  5, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,  99,  99,  50,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1411, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 544, 10, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,  99,  99,  50,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1412, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 477,  5, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,   0,  99,  99,  50,   0,   0,   0,   0,   0,   0);
    AddItem(1413, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 476, 10, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,  99,  99,  50,   0,   0,   0,   0,   0,   0);
    AddItem(1414, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 541,  6, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,  99,  99,  50,   0,   0,   0,   0,   0);
    AddItem(1415, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 540, 12, 0,   0, 0,   0,  8,  0, 0, 0, 0, 0,  0, 0,   0,   0,  99,  99,  50,   0,   0,   0,   0,   0);
    AddItem(1416, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 405,  7, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,  99,  99,  50,   0,   0,   0,   0);
    AddItem(1417, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 404, 14, 0,   0, 0,   0, 10,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,  99,  99,  50,   0,   0,   0,   0);
    AddItem(1418, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 475,  8, 0,   0, 0,   0,  7,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  99,  99,  50,   0,   0,   0);
    AddItem(1419, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 474, 16, 0,   0, 0,   0, 14,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  99,  99,  50,   0,   0,   0);
    AddItem(1420, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 463, 10, 0,   0, 0,   0,  8,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  99,  99,  50,   0,   0);
    AddItem(1421, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 462, 20, 0,   0, 0,   0, 16,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  99,  99,  50,   0,   0);
    AddItem(1422, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 501, 12, 0,   0, 0,   0,  9,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  99,  99,  50,   0,   0);
    AddItem(1423, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 500, 24, 0,   0, 0,   0, 18,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  99,  99,  50,   0,   0);
    AddItem(1424, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 459,  9, 0,   0, 0,   0, 10,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  99,  99,  50,   0);
    AddItem(1425, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 458, 18, 0,   0, 0,   0, 20,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  99,  99,  50,   0);
    AddItem(1426, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 467, 13, 0,   0, 0,   0, 11,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  99,  99,  50,   0);
    AddItem(1427, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 466, 26, 0,   0, 0,   0, 22,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  99,  99,  50,   0);
    AddItem(1428, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 547, 11, 0,   0, 0,   0, 13,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1429, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 546, 22, 0,   0, 0,   0, 26,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1430, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 473, 20, 0,   0, 0,   0, 14,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1431, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 472, 40, 0,   0, 0,   0, 28,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1432, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 525, 13, 0,   0, 0,   0, 16,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1433, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 524, 26, 0,   0, 0,   0, 32,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1434, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 457, 17, 0,   0, 0,   0, 17,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1435, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 456, 34, 0,   0, 0,   0, 34,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1436, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 523, 15, 0,   0, 0,   0, 19,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  99);
    AddItem(1437, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 522, 30, 0,   0, 0,   0, 38,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  99);
    AddItem(1438, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 409, 18, 0,   0, 0,   0, 20,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  99);
    AddItem(1439, ItemType_Body     , 16, false,  0, ALLPLAYERS, ALLJOBS, 408, 36, 0,   0, 0,   0, 40,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  15);
    AddItem(1500, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 446,  8, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1501, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 447,  8, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1502, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 448,  8, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1503, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 449,  8, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1504, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 450, 10, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1505, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 451, 10, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1506, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 452, 10, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1507, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 453, 10, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1508, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 454, 12, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1509, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 455, 12, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1510, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 513,  3, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,  99,  99,  50,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1511, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 512,  6, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,  99,  99,  50,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1512, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 433,  4, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,   0,   0,  99,  99,  50,   0,   0,   0,   0,   0);
    AddItem(1513, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 432,  8, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,  99,  99,  50,   0,   0,   0,   0,   0);
    AddItem(1514, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 503,  5, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  99,  99,  50,   0,   0,   0);
    AddItem(1515, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 502, 10, 0,   0, 0,   0,  6,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  99,  99,  50,   0,   0,   0);
    AddItem(1516, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 401, 10, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  99,  99,  50,   0);
    AddItem(1517, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 400, 20, 0,   0, 0,   0, 10,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  99,  99,  50,   0);
    AddItem(1518, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 431,  7, 0,   0, 0,   0,  6,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1519, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 430, 14, 0,   0, 0,   0, 12,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1520, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 485,  8, 0,   0, 0,   0,  7,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1521, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 484, 16, 0,   0, 0,   0, 14,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1522, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 411,  9, 0,   0, 0,   0,  8,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  99);
    AddItem(1523, ItemType_Arm      , 17, false,  0, ALLPLAYERS, ALLJOBS, 410, 18, 0,   0, 0,   0, 16,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  20);
    AddItem(1600, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 526,  8, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1601, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 527,  8, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1602, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 528,  8, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1603, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 529,  8, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1604, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 530, 10, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1605, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 531, 10, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,   0,   0,  10,  10,  10,   0,   0,   0,   0,   0);
    AddItem(1606, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 532, 10, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1607, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 533, 10, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1608, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 534, 12, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1609, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 535, 12, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  10,  10,  10,   0,   0,   0);
    AddItem(1610, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 507,  3, 0,   0, 0,   0,  1,  0, 0, 0, 0, 0,  0, 0,  99,  99,  50,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1611, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 506,  6, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,  99,  99,  50,   0,   0,   0,   0,   0,   0,   0);
    AddItem(1612, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 549,  3, 0,   0, 0,   0,  2,  0, 0, 0, 0, 0,  0, 0,   0,   0,  99,  99,  50,   0,   0,   0,   0,   0);
    AddItem(1613, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 548,  6, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,  99,  99,  50,   0,   0,   0,   0,   0);
    AddItem(1614, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 465,  4, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  99,  99,  50,   0,   0,   0);
    AddItem(1615, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 464,  8, 0,   0, 0,   0,  6,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,  99,  99,  50,   0,   0,   0);
    AddItem(1616, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 403,  5, 0,   0, 0,   0,  4,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  99,  99,  50,   0,   0);
    AddItem(1617, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 402, 10, 0,   0, 0,   0,  8,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,  99,  99,  50,   0,   0);
    AddItem(1618, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 509,  7, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  99,  99,  50,   0);
    AddItem(1619, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 508, 14, 0,   0, 0,   0, 10,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,  99,  99,  50,   0);
    AddItem(1620, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 517, 10, 0,   0, 0,   0,  6,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1621, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 516, 20, 0,   0, 0,   0, 12,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,  99,  99,  50);
    AddItem(1622, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 487,  8, 0,   0, 0,   0,  7,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1623, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 486, 16, 0,   0, 0,   0, 14,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,  99,  99);
    AddItem(1624, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 415,  9, 0,   0, 0,   0,  8,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  99);
    AddItem(1625, ItemType_Leg      , 18, false,  0, ALLPLAYERS, ALLJOBS, 414, 18, 0,   0, 0,   0, 16,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  20);
    AddItem(1700, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 619,  5, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,   0,   0,   4,   4,   4,   4,   4,   4,   4,   4);
    AddItem(1701, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 612,  5, 0,   0, 0,   3,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   4,   4,   4,   4,   4,   4,   4);
    AddItem(1702, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 613,  5, 0,   0, 0,   0,  3,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   4,   4,   4,   4,   4,   4);
    AddItem(1703, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 614,  5, 0,   0, 0,   0,  0,  3, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   4,   4,   4,   4,   4);
    AddItem(1704, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 608,  5, 0,   0, 0,   0,  0,  5, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1);
    AddItem(1705, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 624,  5, 0,   0, 0,   0,  0, 10, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1);
    AddItem(1706, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 606,  5, 0,   0, 0,   0,  0, 15, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1);
    AddItem(1707, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 625,  5, 0,   0, 0,   5,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1);
    AddItem(1708, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 620,  5, 0,   0, 0,  10,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1);
    AddItem(1709, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 610,  5, 0,   0, 0,   0,  5,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1);
    AddItem(1710, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 618,  5, 0,   0, 0,   0, 10,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1);
    AddItem(1711, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 616,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  5, 0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1);
    AddItem(1712, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 621,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0, 10, 0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1);
    AddItem(1713, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 615,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1);
    AddItem(1714, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 623,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1);
    AddItem(1715, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 622,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1);
    AddItem(1716, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 617,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1);
    AddItem(1717, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 609,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1);
    AddItem(1718, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 602,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1);
    AddItem(1719, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 601,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1);
    AddItem(1720, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 603,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1);
    AddItem(1721, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 607,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1);
    AddItem(1722, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 605,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1);
    AddItem(1723, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 604,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4);
    AddItem(1724, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 611,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1);
    AddItem(1725, ItemType_Accessory, 19, false,  0, ALLPLAYERS, ALLJOBS, 600,  5, 0,   0, 0,   0,  0,  0, 0, 0, 0, 0,  0, 0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1);

}