#include "stdc++.h"
#include <iostream>
#include <algorithm>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::reverse;
using std::string;
using std::vector;

class General
{
public:
    int track[200];
    int trackNum;
    double overTrack; //ms
    double startUp;   //ms
    int r;            //rpm
    int blocksPerTrack;
    int bitsPerTrack;
    int currentTrack;
    bool direction; //true for outward

    // * 函数模块，进行重点部分的计算
    int distance(int x, int y) { return abs(x - y); }
    int lowestTrack(int track[], int trackNum);
    int highestTrack(int track[], int trackNum);
    int locationOfLowestTrack(int track[], int trackNum);
    bool isRepeated(int track[], int i);
    void randomSequenceGenerate(int track[], int trackNum);
    int lessAndNearest(int current, int track[], int trackNum);
    int greaterAndNearest(int current, int track[], int trackNum);

    // * 下面这块已经把除了
    //      1.生成序列
    //      2.寻道时间
    // * 计算完毕，重点在于序列
};

// * 上面的函数实现区
int General::lowestTrack(int track[], int trackNum)
{
    int i, j = track[0];
    for (i = 1; i < trackNum; i++)
    {
        if (j > track[i])
        {
            j = track[i];
        }
    }
    return j;
}
int General::highestTrack(int track[], int trackNum)
{
    int i, j = track[0];
    for (i = 1; i < trackNum; i++)
    {
        if (j < track[i])
        {
            j = track[i];
        }
    }
    return j;
}
int General::locationOfLowestTrack(int track[], int trackNum)
{
    int i, j = track[0];
    for (i = 1; i <= trackNum; i++)
    {
        if (j > track[i])
        {
            j = track[i];
        }
    }
    for (i = 1; i < trackNum; i++)
    {
        if (j == track[i])
        {
            return i;
        }
    }
    return 0;
}
bool General::isRepeated(int track[], int i)
{
    for (int j = 0; j < trackNum; j++)
    {
        if (i == track[j])
        {
            return true;
        }
    }
    return false;
}
void General::randomSequenceGenerate(int track[], int trackNum)
{
    int temp;
    srand((unsigned)time(NULL));
    for (int i = 0; i < trackNum; i++)
    {
        temp = rand() % 200;
        while (isRepeated(track, temp))
        {
            temp = rand() % 200;
        }
        track[i] = temp;
    }
}
int General::lessAndNearest(int currentTrack, int track[], int trackNum)
{
    int i, j = 0, k;
    int temp[200];
    for (i = 0; i < trackNum; i++)
    {
        if (track[i] < currentTrack)
        {
            temp[j] = track[i];
            j++;
        }
    }
    k = temp[0];
    for (i = 1; i < trackNum; i++)
    {
        if (k < temp[i])
        {
            k = temp[i];
        }
    }
    return k;
}
int General::greaterAndNearest(int currentTrack, int track[], int trackNum)
{
    int i, j = 0, k;
    int temp[200];
    for (i = 0; i < trackNum; i++)
    {
        if (track[i] > currentTrack)
        {
            temp[j] = track[i];
            j++;
        }
    }
    k = temp[0];
    for (i = 1; i < trackNum; i++)
    {
        if (k > temp[i])
        {
            k = temp[i];
        }
    }
    return k;
}

class FCFS : public General
{
public:
    vector<int> generatedTrack;
    double roundsPerMicroSecond;
    double moveCount;
    double trackSeekTime;
    double averageSpinDelay;
    double transmissionTime;
    double totalTime;
    int generateTrack(FCFS disk);
    FCFS();
};
class SCAN : public General
{
public:
    vector<int> generatedTrack;
    double roundsPerMicroSecond = 0;
    double moveCount = 0;
    double trackSeekTime = 0;
    double averageSpinDelay = 0;
    double transmissionTime = 0;
    double totalTime = 0;
    int generateTrack(SCAN disk);
    SCAN();
};
class SSTF : public General
{
public:
    vector<int> generatedTrack;
    double roundsPerMicroSecond = 0;
    double moveCount = 0;
    double trackSeekTime = 0;
    double averageSpinDelay = 0;
    double transmissionTime = 0;
    double totalTime = 0;
    int generateTrack(SSTF disk);
    SSTF();
};
class LOOK : public General
{
public:
    vector<int> generatedTrack;
    double roundsPerMicroSecond = 0;
    double moveCount = 0;
    double trackSeekTime = 0;
    double averageSpinDelay = 0;
    double transmissionTime = 0;
    double totalTime = 0;
    int generateTrack(LOOK disk);
    LOOK();
};

FCFS::FCFS()
{
    cin >> trackNum;
    cin >> overTrack;
    cin >> startUp;
    cin >> r;
    cin >> blocksPerTrack;
    cin >> bitsPerTrack;
    cin >> currentTrack;
    randomSequenceGenerate(track, trackNum);
    moveCount = distance(currentTrack, track[0]);
    for (int i = 1; i < trackNum; i++)
    {
        generatedTrack.push_back(track[i]);
        moveCount += distance(track[i - 1], track[i]);
    }
    roundsPerMicroSecond = r / 60000;
    trackSeekTime = moveCount * overTrack + startUp;
    averageSpinDelay = 1 / (2 * roundsPerMicroSecond);
    transmissionTime = blocksPerTrack / roundsPerMicroSecond;
    totalTime = trackSeekTime + averageSpinDelay + transmissionTime;
}
/**
 * @brief Construct a new SSTF::SSTF object
 *
 */
SSTF::SSTF()
{
    cin >> trackNum;
    cin >> overTrack;
    cin >> startUp;
    cin >> r;
    cin >> blocksPerTrack;
    cin >> bitsPerTrack;
    cin >> currentTrack;
    randomSequenceGenerate(track, trackNum);
    int i, j;
    int x, min = 9999;
    double trackDistance[200];
    for (i = 1; i < trackNum; i++)
    {
        ////向两个方向上比较距离，哪方更小选取哪方
        //if (distance(lessAndNearest(temp, track, trackNum), temp) < distance(greaterAndNearest(temp, track, trackNum), temp) && 1)
        //{
        //    moveCount += distance(lessAndNearest(temp, track, trackNum), temp);
        //    temp = lessAndNearest(temp, track, trackNum);
        //    generatedTrack.push_back(temp);
        //}
        //else if (distance(lessAndNearest(temp, track, trackNum), temp) < distance(greaterAndNearest(temp, track, trackNum), temp) && 1)
        //{
        //    moveCount += distance(greaterAndNearest(temp, track, trackNum), temp);
        //    temp = greaterAndNearest(temp, track, trackNum);
        //    generatedTrack.push_back(temp);
        //}
        trackDistance[track[i]] = -1;
        // int temp = track[i];
        for (j = 0; j < trackNum - 1; j++)
        {
            if (trackDistance[j] != -1)
            {
                trackDistance[j] = abs(track[track[i]] - track[j]);
            }
        }

        for (j = 0; j < trackNum - 1; j++)
        {
            if (trackDistance[j] != -1)
            {
                if (trackDistance[j] < min)
                {
                    min = trackDistance[i];
                    x = i;
                }
            }
        }
        if (track[i] == currentTrack)
            break;
        generatedTrack.push_back(track[i]);
    }
    moveCount += distance(currentTrack, generatedTrack[0]);
    for (i = 1; i < trackNum - 1; i++)
    {
        moveCount += distance(generatedTrack[i - 1], generatedTrack[i]);
    }
    roundsPerMicroSecond = r / 60000;
    trackSeekTime = moveCount * overTrack + startUp;
    averageSpinDelay = 1 / (2 * roundsPerMicroSecond);
    transmissionTime = blocksPerTrack / roundsPerMicroSecond;
    totalTime = trackSeekTime + averageSpinDelay + transmissionTime;
}
/**
 * @brief SCAN算法先对序列进行排列
 * 在最小最接近或最大最接近处分解成两个向量 ！！注意，根据当前direction进行逆序或顺序
 * 在决定了顺序后(SCAN没有改变vector内顺序)
 * 最后再merge成一个数组
 * OJBK
 * @param disk
 * @return int
 */
SCAN::SCAN()
{
    cin >> trackNum;
    cin >> overTrack;
    cin >> startUp;
    cin >> r;
    cin >> blocksPerTrack;
    cin >> bitsPerTrack;
    cin >> currentTrack;
    randomSequenceGenerate(track, trackNum);
    int i;
    for (i = 0; i < trackNum; i++)
    {
        generatedTrack.push_back(track[i]);
    }
    sort(generatedTrack.begin(), generatedTrack.end());
    int hT = highestTrack(track, trackNum);
    int lT = highestTrack(track, trackNum);
    int lAN = lessAndNearest(currentTrack, track, trackNum);
    // int mAN = greaterAndNearest(disk.currentTrack, disk.track, disk.trackNum);
    vector<int> tempTarget;
    vector<int> tempLower;
    vector<int> tempHigher;
    if (direction)
    {
        moveCount = hT + lT;
        // TODO 这里要进行电梯算法的序列生成
        for (i = 0; i < trackNum; i++)
        {
            if (track[i] < lAN)
            {
                tempLower.push_back(track[i]);
            }
            else
            {
                tempHigher.push_back(track[i]);
            }
        }
        /*copy(tempHigher.begin(), tempHigher.end(), tempTarget.begin());
        copy(tempLower.begin(), tempLower.end(), tempTarget.end());
        generatedTrack.clear();
        copy(tempTarget.begin(), tempTarget.end(), generatedTrack.begin());*/
        tempTarget.insert(tempTarget.begin(), tempHigher.begin(), tempHigher.end());
        tempTarget.insert(tempTarget.end(), tempLower.begin(), tempLower.end());
    }
    else
    {
        moveCount = lT + hT;
        for (i = 0; i < trackNum; i++)
        {
            if (track[i] < lAN)
            {
                tempLower.push_back(track[i]);
            }
            else
            {
                tempHigher.push_back(track[i]);
            }
        }
        reverse(tempLower.begin(), tempLower.end());
        reverse(tempHigher.begin(), tempHigher.end());
        /*copy(tempLower.begin(), tempLower.end(), tempTarget.begin());
        copy(tempHigher.begin(), tempHigher.end(), tempTarget.end());
        generatedTrack.clear();
        copy(tempTarget.begin(), tempTarget.end(), generatedTrack.begin());*/
        tempTarget.insert(tempTarget.end(), tempLower.begin(), tempLower.end());
        tempTarget.insert(tempTarget.begin(), tempHigher.begin(), tempHigher.end());
    }
    roundsPerMicroSecond = r / 60000;
    trackSeekTime = moveCount * overTrack + startUp;
    averageSpinDelay = 1 / (2 * roundsPerMicroSecond);
    transmissionTime = blocksPerTrack / roundsPerMicroSecond;
    totalTime = trackSeekTime + averageSpinDelay + transmissionTime;
}
/**
 * @brief LOOK算法也是进行排列
 * 与上面类似但是要先分解然后根据方向进行逆序
 * LOOK需要改变vector中顺序
 * 如:direction为true，即向外
 * 那么，小于currentTrack的就要逆序，然后拼接到大于cT的后面
 * @param disk
 * @return int
 */
LOOK::LOOK()
{
    cin >> trackNum;
    cin >> overTrack;
    cin >> startUp;
    cin >> r;
    cin >> blocksPerTrack;
    cin >> bitsPerTrack;
    cin >> currentTrack;
    randomSequenceGenerate(track, trackNum);
    int i;
    for (i = 0; i < trackNum; i++)
    {
        generatedTrack.push_back(track[i]);
    }
    sort(generatedTrack.begin(), generatedTrack.end());
    int hT = highestTrack(track, trackNum);
    int lT = highestTrack(track, trackNum);
    int lAN = lessAndNearest(currentTrack, track, trackNum);
    // int mAN = greaterAndNearest(disk.currentTrack, disk.track, disk.trackNum);
    vector<int> tempTarget;
    vector<int> tempLower;
    vector<int> tempHigher;
    if (direction)
    {
        moveCount = hT + lT;
        // TODO 这里要进行LOOK算法的序列生成
        for (i = 0; i < trackNum; i++)
        {
            if (track[i] < lAN)
            {
                tempLower.push_back(track[i]);
            }
            else
            {
                tempHigher.push_back(track[i]);
            }
        }
        reverse(tempLower.begin(), tempLower.end());
        /*copy(tempHigher.begin(), tempHigher.end(), tempTarget.begin());
        copy(tempLower.begin(), tempLower.end(), tempTarget.end());*/
        tempTarget.insert(tempTarget.begin(), tempHigher.begin(), tempHigher.end());
        tempTarget.insert(tempTarget.end(), tempLower.begin(), tempLower.end());
        /*generatedTrack.clear();
        copy(tempTarget.begin(), tempTarget.end(), generatedTrack.begin());*/
    }
    else
    {
        moveCount = lT + hT;
        for (i = 0; i < trackNum; i++)
        {
            if (track[i] < lAN)
            {
                tempLower.push_back(track[i]);
            }
            else
            {
                tempHigher.push_back(track[i]);
            }
        }
        reverse(tempHigher.begin(), tempHigher.end());
        /*copy(tempLower.begin(), tempLower.end(), tempTarget.begin());
        copy(tempHigher.begin(), tempHigher.end(), tempTarget.end());
        generatedTrack.clear();
        copy(tempTarget.begin(), tempTarget.end(), generatedTrack.begin());*/
        tempTarget.insert(tempTarget.end(), tempLower.begin(), tempLower.end());
        tempTarget.insert(tempTarget.begin(), tempHigher.begin(), tempHigher.end());
    }
    roundsPerMicroSecond = r / 60000;
    trackSeekTime = moveCount * overTrack + startUp;
    averageSpinDelay = 1 / (2 * roundsPerMicroSecond);
    transmissionTime = blocksPerTrack / roundsPerMicroSecond;
    totalTime = trackSeekTime + averageSpinDelay + transmissionTime;
}

int main()
{
    int argrithmSelect, i;
    cin >> argrithmSelect;
    while (!(cin >> argrithmSelect))
    {
        cin.clear();
        cin >> argrithmSelect;
    }

    switch (argrithmSelect)
    {
    case 0:
    {
        FCFS disk;
        cout << disk.currentTrack << " ";
        for (i = 0; i < disk.generatedTrack.size(); i++)
        {
            cout << disk.generatedTrack[i] << " ";
        }
        cout << endl;
        cout << disk.moveCount << endl;
        cout << disk.trackSeekTime << endl;
        cout << disk.averageSpinDelay << endl;
        cout << disk.transmissionTime << endl;
        cout << disk.totalTime << endl;
    }
    break;
    case 1:
    {
        SSTF disk;
        cout << disk.currentTrack << " ";
        for (i = 0; i < disk.generatedTrack.size(); i++)
        {
            cout << disk.generatedTrack[i] << " ";
        }
        cout << endl;
        cout << disk.moveCount << endl;
        cout << disk.trackSeekTime << endl;
        cout << disk.averageSpinDelay << endl;
        cout << disk.transmissionTime << endl;
        cout << disk.totalTime << endl;
    }
    break;
    case 2:
    {
        SCAN disk;
        cout << disk.currentTrack << " ";
        for (i = 0; i < disk.generatedTrack.size(); i++)
        {
            cout << disk.generatedTrack[i] << " ";
        }
        cout << endl;
        cout << disk.moveCount << endl;
        cout << disk.trackSeekTime << endl;
        cout << disk.averageSpinDelay << endl;
        cout << disk.transmissionTime << endl;
        cout << disk.totalTime << endl;
    }
    break;
    case 3:
    {
        LOOK disk;
        cout << disk.currentTrack << " ";
        for (i = 0; i < disk.generatedTrack.size(); i++)
        {
            cout << disk.generatedTrack[i] << " ";
        }
        cout << endl;
        cout << disk.moveCount << endl;
        cout << disk.trackSeekTime << endl;
        cout << disk.averageSpinDelay << endl;
        cout << disk.transmissionTime << endl;
        cout << disk.totalTime << endl;
    }
    break;
    default:
        break;
    }
    system("pause");
    return 0;
};