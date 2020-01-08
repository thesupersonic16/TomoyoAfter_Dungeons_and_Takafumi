#pragma once
#include "Common.h"
#include "RealLiveExtension.h"

enum ItemType
{
    ItemType_None,
    ItemType_Useless,
    ItemType_Potions,
    ItemType_Unknown,
    ItemType_Equipment, // Category
    ItemType_Weapons,
    ItemType_Armor,     // Category
    ItemType_Shields,
    ItemType_Head,
    ItemType_Body,
    ItemType_Arm,
    ItemType_Leg,
    ItemType_Accessory,
    ItemType_Hands,     // Category
    ItemType_AllItems   // Category
};

enum ItemSort
{
    ItemSort_Unknown1,
    ItemSort_Unknown2,
    ItemSort_NameAZ,
    ItemSort_NameZA,
    ItemSort_WeightLH,
    ItemSort_WeightHL,
    ItemSort_Unknown6,
    ItemSort_Unknown7,
    ItemSort_ObtainedLH,
    ItemSort_ObtainedHL,
};

typedef struct
{
    // The type of item e.g. 2 are potions
    ItemType type;
    // An ID of an icon the item will be using
    int icon;
    int attributes;
    int unknown3;
    // Bitflag of player IDs who can use an item (31 means all 5 players can use the item) Formula: 1 << PlayerID
    int equipablePlayer;
    // Bitflag of job IDs of who can use an item (1023 means all 10 jobs can use the item) Formula: 1 << JobID
    int equipableJob;
    int unknown6;
    // How much this item weights
    int weight;
    int unknown8;
    int healing;
    int unknown10;
    Stats statIncrease;
    int unknown21;
    int unknown22;
    int unknown23;
    int unknown24;
    int unknown25;
    int unknown26;
    int unknown27;
    int unknown28;
    int unknown29;
    int unknown30;
    int unknown31;
    int unknown32;
    int unknown33;
    int unknown34;
} Item;

extern Item* Items;
// Array of 350 items in storage represented in item IDs
extern int* ItemStorage;

void AddAllItems();

// Adds an item definition to the game
//   slot: The ID of the item
//   type: The type of item e.g. 2 are potions
//   icon: An ID of an icon the item will be using
//   equipablePlayer: BitFlag of player IDs who can use an item (31 means all 5 players can use the item) Formula: 1 << PlayerID
//   equipableJob: BitFlag of job IDs of who can use an item (1023 means all 10 jobs can use the item) Formula: 1 << JobID
//   weight: How much this item weights
void AddItem(int slot, ItemType type, int icon, bool twoHanded, int unknown3, int equipablePlayer, int equipableJob, int unknown6, int weight, int unknown8, int healing, int unknown10, int attackL, int attackR, int defense, int intellect, int unknown15, int dexterity, int unknown17, int carryPower, int speed, int moves, int unknown26, int unknown27, int unknown28, int unknown29, int unknown30, int unknown31, int unknown32, int unknown33, int unknown34);

// Counts the amount of items that is currently in storage
//   start: Position in storage to start counting at (0-349)
int CountItemsInStorage(int start);

// Adds a new item to the end of the game's storage
//   itemID: ID of the item to add to the end of storage
extern int AddItemToStorage(int itemID);
// Removes an item from a storage slot
//   itemSlot: Position in storage to be removed
extern int RemoveItemFromStorage(int itemSlot);

// Clears all items from storage
extern int ClearItemStorage();

// Calculates a sum of the weight of all items in storage
extern int GetTotalWeight();

// Copies and filters all items in storage and stores it in intC[1450]
//   filter: ID for a category or an ID of an item
//   playerFlags: Filter out items a Player can not use. Formula: 1 << PlayerID
//   jobFlags: Filter out items players with a set Job can not use. Formula: 1 << JobID
extern int FilterItemList(ItemType filter, int playerFlags, int jobFlags);

// Checks if an item can be consumed by a player
//   playerID: The ID of the player to check if they can consume the item
//   itemID: The ID of the consumable item
extern int CheckItemConsumable(int playerID, int itemID);

// Checks if an item can be equiped by a player
//   playerID: The ID of the player to check if they can equip the item
//   itemID: The ID of an item to check if its equipable
extern int CheckItemEquipable(int playerID, int itemID);

// Equips an item to a player
//   playerID: The ID of the player to check if they can equip the item
//   itemID: The ID of an item to check if its equipable
extern int EquipItemAuto(int playerID, int storageSlot);
