#ifndef _FCFS_HEADER_FILE
#define _FCFS_HEADER_FILE
#include "stdc++.h"
#include <string.h>
using std::cin;
using std::cout;
using std::endl;
int distance(int x, int y)
{
    return abs(x - y);
}
void FCFS(int track[], int overTrack, int startUp, int r, int blocksPerTrack, int bitsPerTrack, int currentTrack, bool direction)
{
    char FCFSGeneratedTrack[200];
    double roundsPerMicroSecond = r / 60000;
    double moveCount;
    double trackSeekTime;
    double averageSpinDelay;
    double transmissionTime;
    double totalTime;
    // TODO:进行相关计算

    //引臂移动量
    moveCount = distance(currentTrack, track[0]);
    for (int i = 1; i < 200; i++)
    {
        moveCount += distance(track[i - 1], track[i]);
    }

    //寻道时间
    trackSeekTime = moveCount * overTrack + startUp;

    //平均旋转延迟时间
    averageSpinDelay = 1 / (2 * roundsPerMicroSecond);

    //传输时间
    transmissionTime = blocksPerTrack / roundsPerMicroSecond;

    //所有访问处理时间
    totalTime = trackSeekTime + averageSpinDelay + transmissionTime;
    for (int j = 0; j < 200; j++)
    {
        cout << track[j] << " ";
    }
    cout << endl;
    cout << moveCount << endl;
    cout << trackSeekTime << endl;
    cout << averageSpinDelay << endl;
    cout << transmissionTime << endl;
    cout << totalTime << endl;
}
#endif