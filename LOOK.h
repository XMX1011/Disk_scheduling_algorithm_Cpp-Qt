#ifndef _LOOK_HEAD_FILE
#define _LOOK_HEAD_FILE
#include "stdc++.h"
#include <string.h>
using std::cin;
using std::cout;
using std::endl;
//电梯算法ですwww

/**
 * 这样吧，数组储存路径，不管具体的空间节省不节省
 * 比如下面一队
 * 3,9,58,13,180,76,82,9,77,3,82,3
 * 初始设为位置10
 * 然后方向为向内则应该为下面路径
 * 10->3->9->58->180->76->9->77->3->82->3->82->3
 * 总计路程为
 * 方向为向外则
 * 10->13->58->76->77->82->82->180->9->9->3->3->3
 * 总计路程为(180-10)+(180-3)=347
 * 
 */

// 找到整个查找队列中第一个处于最内侧轨道请求在数组中的位置
int locationOfLowestTrack(int track[], int 200)
{
    int i, j = track[0];
    for (i = 1; i <= 200; i++)
    {
        if (j > track[i])
        {
            j = track[i];
        }
    }
    for (i = 1; i < 200; i++)
    {
        if (j == track[i])
        {
            return i;
        }
    }
    return 0;
}

//应该分别写一个得知第一个最内侧轨道和最外侧轨道的函数
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

void LOOK(int track[], int overTrack, int startUp, int r, int blocksPerTrack, int bitsPerTrack, int currentTrack, bool direction)
{
    cout << "testing,still in progress" << endl;
    if (direction)
    {
        printf("outward\n");
        //此时向外
    }
    else
    {
        printf("inward\n");
        //此时向内
    }
    int LOOKGeneratedTrack[200] = {0};
    float roundsPerMicroSecond = r / 60000;
    float moveCount;
    float trackSeekTime;
    double averageSpinDelay;
    double transmissionTime;
    float totalTime;

    //引臂移动量
    // TODO 这里还需要再考虑考虑
    if (direction)
    {
        moveCount = (highestTrack(track, 200) - currentTrack) + (1);
    }
    else
    {
        moveCount = (highestTrack(track, 200) - lowestTrack(track, 200)) + (currentTrack - lowestTrack(track, 200));
    }

    //寻道时间
    trackSeekTime = moveCount * overTrack + startUp;

    //平均旋转延迟时间
    averageSpinDelay = 1 / (2 * roundsPerMicroSecond);

    //传输时间
    transmissionTime = blocksPerTrack / roundsPerMicroSecond;

    //所有访问处理时间
    totalTime = trackSeekTime + averageSpinDelay + transmissionTime;

    // TODO 现在这里重点就是如何输出合适的队列
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