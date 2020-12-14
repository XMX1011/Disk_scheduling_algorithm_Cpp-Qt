#ifndef _SCAN_HEAD_FILE
#define _SCAN_HEAD_FILE
#include "stdc++.h"
#include <string.h>
using std::cin;
using std::cout;
using std::endl;
/** 
 *  扫描算法
 *  track为访问序列
 *  overTrack为跨越时间     ms
 *  startUp为启动时间       ms
 *  r为转速                rpm
 *  blocksPerTrack为每磁道扇区块数
 *  bitsPerTrack为每扇区字节数
 *  currentTrack为当前所在磁道
 *  direction为当前移动方向，0为内
 */
//就是单向扫到
int lowestTrack(int track[], int 200)
{
    int i, j = track[0];
    for (i = 1; i < 200; i++)
    {
        if (j > track[i])
        {
            j = track[i];
        }
    }
    return j;
}
int highestTrack(int track[], int 200)
{
    int i, j = track[0];
    for (i = 1; i < 200; i++)
    {
        if (j < track[i])
        {
            j = track[i];
        }
    }
    return j;
}
void SCAN(int track[], int overTrack, int startUp, int r, int blocksPerTrack, int bitsPerTrack, int currentTrack, bool direction)
{
    char SCANGeneratedTrack[200];
    float roundsPerMicroSecond = r / 60000;
    float moveCount;
    float trackSeekTime;
    double averageSpinDelay;
    double transmissionTime;
    float totalTime;
    // TODO:进行相关计算

    //引臂移动量
    if (direction)
    {
        moveCount = highestTrack(track,200)-currentTrack +highestTrack(track,200)-lowestTrack(track,200);
    }
    else
    {
        moveCount = currentTrack + highestTrack(track,200);
    }

    //寻道时间
    trackSeekTime = moveCount * overTrack + startUp;

    //平均旋转延迟时间
    averageSpinDelay = 1 / (2 * roundsPerMicroSecond);

    //传输时间
    transmissionTime = blocksPerTrack / roundsPerMicroSecond;

    //所有访问处理时间
    totalTime = trackSeekTime + averageSpinDelay + transmissionTime;
    
    // TODO 还需要考虑一下输出序列
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