#pragma once
#include "RealLiveExtension.h"
// 20 - Player Functions
extern int InitialisePlayerData(int IsEnemy, int playerSlot);
extern int UpdateStatDisplay(int arg1, int playerSlot);
extern int UnknownFunction_022(int arg1, int playerSlot, int arg3, int arg4);
extern int ResetPlayerData(int IsEnemy, int playerSlot);
extern int UnknownFunction_024();
extern int AddExperienceToPlayer(int playerSlot, int exp);

// 30 - Item Functions

// 50
extern int UnknownFunction_050();
extern int UnknownFunction_055(int arg1);
extern int UnknownFunction_057(int playerID, int arg2, int storageSlot);
extern int SetupFloorData(int floor);

// 110
extern int UnknownFunction_110();
extern int UnknownFunction_111();
extern int UnknownFunction_113(int playerID);
extern int UnknownFunction_114(int playerID);

// 120
extern int UnknownFunction_120();
extern int UnknownFunction_121();
extern int UnknownFunction_122();
extern int UnknownFunction_123();

// 130 - Turn Order?
extern int UnknownFunction_124();
extern int SetupCharacterOrderDisplay();
extern int CalculateMovementRange();
extern int UnknownFunction_132(int isEnemy, int playerSlot);

// 200
extern int UnknownFunction_200();
extern int UnknownFunction_201();
extern int UnknownFunction_208();
extern int UnknownFunction_209();

// 220
extern int UnknownFunction_220();
extern int UnknownFunction_221();
extern int UnknownFunction_222();
extern int UnknownFunction_229();

extern bool sub_10016CF0();
extern bool sub_10016E70();