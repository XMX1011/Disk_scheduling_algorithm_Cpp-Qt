#ifndef _SSTF_HEAD_FILE
#define _SSTF_HEAD_FILE
#include "stdc++.h"
#include <string.h>
using std::cin;
using std::cout;
using std::endl;
/** 
 *  最短查找时间优先算法
 *  track为访问序列
 *  overTrack为跨越时间     ms
 *  startUp为启动时间       ms
 *  r为转速                rpm
 *  blocksPerTrack为每磁道扇区块数
 *  bitsPerTrack为每扇区字节数
 *  currentTrack为当前所在磁道
 *  direction为当前移动方向，0为内
 */
// TODO:每次都判断是否到达输入的队列的一端(最小或最大)
// 如果是一端则直接把刚才基础的加上最小最大的差值作为总共移动距离
// 每次都把最近的(这里要写个函数判断两端哪个更近)

void SSTF(int track[], int overTrack, int startUp, int r, int blocksPerTrack, int bitsPerTrack, int currentTrack, bool direction)
{
    char SSTFGeneratedTrack[200];
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