#ifndef _RASG_HEAD_FILE
#define _RASG_HEAD_FILE
#include "stdc++.h"
bool isRepeated(int track[], int i)
{
    for (int j = 0; j < 200; j++)
    {
        if (i == track[j])
        {
            return true;
        }
    }
    return false;
}
void _RASG_(int track[])
{
    int temp;
    srand((unsigned)time(NULL));
    for (int i = 0; i < 200; i++)
    {
        temp = rand() % 200;
        while (isRepeated(track, temp))
        {
            temp = rand() % 200;
        }
        track[i] = temp;
    }
}
#endif