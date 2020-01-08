#include "Common.h"
#include "RealLiveExtension.h"
#include "Functions.h"
#include "LevelingData.h"
#include "ItemData.h"
#include "EnemyData.h"
#include "Character.h"
#include <cassert>
#include <cstring>
#define EXPORT comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)
extern "C"
{
    int* intA = nullptr;
    int* intB = nullptr;
    int* intC = nullptr;
    int* intD = nullptr;
    int* intE = nullptr;
    int* intF = nullptr;

    // TODO 208 and 209 needs work
    int __stdcall reallive_dll_func_call(int func, int arg1, int arg2, int arg3, int arg4)
    {
#ifdef _WIN32
#pragma EXPORT
#endif // _WIN32
        if (func != 121 && func != 122)
        printf("Function: %d, arg1: %d, arg2: %d, arg3: %d, arg4: %d\n", func, arg1, arg2, arg3, arg4);
        switch (func)
        {
        case 20:
            InitialisePlayerData(arg1, arg2);
            break;
        case 21:
            UpdateStatDisplay(arg1, arg2);
            break;
        case 22:
            UnknownFunction_022(arg1, arg2, arg3, arg4);
            break;
        case 23:
            ResetPlayerData(arg1, arg2);
            break;
        case 24:
            UnknownFunction_024();
            break;
        case 25:
            AddExperienceToPlayer(arg1, arg2);
            break;
        case 30:
            ClearItemStorage();
            break;
        case 31:
            // Stores Item data into game's memory
            memcpy(&intC[1802], &Items[arg1], sizeof(Item));
            break;
        case 32:
            AddItemToStorage(arg1);
            break;
        case 33:
            RemoveItemFromStorage(arg1);
            break;
        case 35:
            FilterItemList(static_cast<ItemType>(arg1), arg2, arg3);
            break;
        case 36:
            GetTotalWeight();
            break;
        case 39:
            CheckItemConsumable(arg1, arg2);
            break;
        case 50:
            UnknownFunction_050();
            break;
        case 51:
            CheckItemEquipable(arg1, arg2);
            break;
        case 52:
            EquipItemAuto(arg1, arg2);
            break;
        case 55:
            UnknownFunction_055(arg1);
            break;
        case 57:
            UnknownFunction_057(arg1, arg2, arg3);
            break;
        case 100:
            SetupFloorData(arg1);
            break;
        case 110:
            UnknownFunction_110();
            break;
        case 111:
            UnknownFunction_111();
            break;
        case 113:
            UnknownFunction_113(arg1);
            break;
        case 114:
            UnknownFunction_114(arg1);
            break;
        case 120:
            UnknownFunction_120();
            break;
        case 121:
            UnknownFunction_121();
            break;
        case 122:
            UnknownFunction_122();
            break;
        case 123:
            UnknownFunction_123();
            break;
        case 124:
            UnknownFunction_124();
            break;
        case 125:
            SetupCharacterOrderDisplay();
            break;
        case 130:
            CalculateMovementRange();
            break;
        case 132:
            UnknownFunction_132(arg1, arg2);
            break;
        case 200:
            UnknownFunction_200();
            break;
        case 201:
            UnknownFunction_201();
            break;
        case 208:
            UnknownFunction_208();
            break;
        case 209:
            UnknownFunction_209();
            break;
        case 220:
            UnknownFunction_220();
            break;
        case 221:
            UnknownFunction_221();
            break;
        case 222:
            UnknownFunction_222();
            break;
        case 224:
        case 225:
        case 226:
        case 227:
            UnknownFunction_220();
            break;
        case 210:
        case 229:
            UnknownFunction_229();
            break;
        case 230:
            UnknownFunction_220();
            break;
        default:
            printf("Unknown Function: %d, arg1: %d, arg2: %d, arg3: %d, arg4: %d\n", func, arg1, arg2, arg3, arg4);
            break;
        }
        return 1;
    }

    int __stdcall reallive_dll_func_load(RealLiveState* machine, int arg1)
    {
#ifdef _WIN32
#pragma EXPORT
#endif // _WIN32
        if (machine)
        {
            intA = reinterpret_cast<int*>(machine->intA);
            intB = reinterpret_cast<int*>(machine->intB);
            intC = reinterpret_cast<int*>(machine->intC);
            intD = reinterpret_cast<int*>(machine->intD);
            intE = reinterpret_cast<int*>(machine->intE);
            intF = reinterpret_cast<int*>(machine->intF);
        }
        Players = reinterpret_cast<Player*>(intB + 0);
        Enemies = reinterpret_cast<Enemy*>(intB + 900);
        ItemStorage = static_cast<int*>(intC + 400);
        FillJobStatsList();
        AddAllItems();
        return 1;
    }

    int __stdcall reallive_dll_func_free()
    {
#ifdef _WIN32
#pragma EXPORT
#endif // _WIN32
        return 1;
    }

    int __stdcall reallive_dll_func_init()
    {
#ifdef _WIN32
#pragma EXPORT
#endif // _WIN32
        return 1;
    }
}
#ifdef _WIN32

bool WINAPI DllMain(int handle, int fdwReason, void* lpvReserved)
{
    if (fdwReason == 1)
    {
        AllocConsole();
        FILE* pCout;
        freopen_s(&pCout, "conout$", "w", stdout);
    }
    return true;
}
#endif