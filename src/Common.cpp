#include "Common.h"

void SendBasicMessage(const char* text)
{
#ifdef _WIN32
    MessageBoxA(NULL, text, "", NULL);
#endif // _WIN32
    printf("dt00: %s\n", text);
}