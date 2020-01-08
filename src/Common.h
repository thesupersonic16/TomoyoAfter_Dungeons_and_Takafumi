#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _WIN32
#include <windows.h>
#define FUNC_EXPORT __declspec(dllexport)
#else
#define FUNC_EXPORT __attribute__ ((visibility ("default")))
#define __stdcall
#endif // _WIN32

extern void SendBasicMessage(const char* text);

#define STAGE_WIDTH 20
#define STAGE_HEIGHT 20

enum MemoryLocation
{
    LocationA,
    LocationB,
    LocationC,
    LocationD,
    LocationE,
    LocationF,
    LocationG,
    LocationZ
};

enum Rotation
{
    Rot_NULL = -1,
    Rot_North,
    Rot_East,
    Rot_South,
    Rot_West
};

struct Stats
{
    int attackR;
    int attackL;
    int defense;
    int intellect;
    int unknown4;
    int dexterity;
    int unknown6;
    int carryPower;
    int speed;
    int moves;
};

struct RealLiveState
{
    long cbSize;      /* Size of the structure */
    void *hMainWindow; /* Handle of the RealLive window  */
    long *intA;
    long *intB;
    long *intC;
    long *intD;
    long *intE;
    long *intF;
    long *intG;
    long *intZ;
    char **strS;
    char **strM;
    struct {          /* DC array: */
        void **pData;     /* Pixel data */
        long *pWidth;     /* DC width */
        long *pHeight;    /* DC height */
    } BankInfo[16];
    char *szGamePath; /* Game root directory (path of GAMEEXE.INI) */
    char *szSavePath; /* Save directory */
    char *szBgmPath;  /* BGM directory */
    char *szKoePath;  /* KOE directory */
    char *szMovPath;  /* MOV directory */
    char *szDataPath; /* Base directory for other resources (wav, g00, etc.) */
};

