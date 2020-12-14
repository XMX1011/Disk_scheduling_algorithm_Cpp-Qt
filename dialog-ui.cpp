#include "dialog.h"
#include <qgridlayout.h>
#include <QDebug>

#include <time.h>
//#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

static int trackNum0 = 10;
static double overTrack0 = 5;
static double startUp0 =5;
static int r0 = 60000;
static int blocksPerTrack0 = 64;
static int bitsPerTrack0 = 64;
static int currentTrack0 = 10;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    l1=new QLabel(this);
    l2=new QLabel(this);
    l3=new QLabel(this);
    l4=new QLabel(this);
    l5=new QLabel(this);
    l6=new QLabel(this);
    l7=new QLabel(this);
    l8= new QLabel(this);
    l9= new QLabel(this);
    l10= new QLabel(this);
    l11= new QLabel(this);
    l12= new QLabel(this);
    l13= new QLabel(this);

    li1 = new QLineEdit(this);
    li2 = new QLineEdit(this);
    li3 =new QLineEdit(this);
    li4 =new QLineEdit(this);
    li5 =new QLineEdit(this);
    li6 =new QLineEdit(this);
    li7 =new QLineEdit(this);

    btn1=new QPushButton(this);
    btn2=new QPushButton(this);
    btn3=new QPushButton(this);
    btn4=new QPushButton(this);
    btn5=new QPushButton(this);
    btn1->setText("close");
    btn2->setText("FCFS");
    btn3->setText("SSTF");
    btn4->setText("SCAN");
    btn5->setText("LOOK");

    l1->setText("磁道数量");
    l2->setText("跨越单磁道所需时间");
    l3->setText("启动时间");
    l4->setText("转速");
    l5->setText("块数");
    l6->setText("bit数");
    l7->setText("当前磁道");

    QGridLayout *mainLayout= new QGridLayout(this);
    mainLayout->addWidget(l1,0,0);
    mainLayout->addWidget(l2,1,0);
    mainLayout->addWidget(l3,2,0);
    mainLayout->addWidget(l4,3,0);
    mainLayout->addWidget(l5,4,0);
    mainLayout->addWidget(l6,5,0);
    mainLayout->addWidget(l7,6,0);
    mainLayout->addWidget(li1,0,1);
    mainLayout->addWidget(li2,1,1);
    mainLayout->addWidget(li3,2,1);
    mainLayout->addWidget(li4,3,1);
    mainLayout->addWidget(li5,4,1);
    mainLayout->addWidget(li6,5,1);
    mainLayout->addWidget(li7,6,1);
    mainLayout->addWidget(btn1,0,2);
    mainLayout->addWidget(btn2,1,2);
    mainLayout->addWidget(btn3,2,2);
    mainLayout->addWidget(btn4,3,2);
    mainLayout->addWidget(btn5,4,2);
    mainLayout->addWidget(l8,7,0);
    mainLayout->addWidget(l9,8,0);
    mainLayout->addWidget(l10,9,0);
    mainLayout->addWidget(l11,10,0);
    mainLayout->addWidget(l12,11,0);
    mainLayout->addWidget(l13,12,0);

    connect(btn1,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(btn2,SIGNAL(clicked(bool)),this,SLOT(case0out()));
    connect(btn3,SIGNAL(clicked(bool)),this,SLOT(case1out()));
    connect(btn4,SIGNAL(clicked(bool)),this,SLOT(case2out()));
    connect(btn5,SIGNAL(clicked(bool)),this,SLOT(case3out()));
}

Dialog::~Dialog()
{

}

//code
class General
{
public:
    int track[200];
    int trackNum;
    double overTrack; //ms
    double startUp;   //ms
    int r;         //rpm
    int blocksPerTrack;
    int bitsPerTrack;
    int currentTrack;
    bool direction; //true for outward

    int distance(int x, int y) { return abs(x - y); }
    int lowestTrack(int track[], int trackNum);
    int highestTrack(int track[], int trackNum);
    int locationOfLowestTrack(int track[], int trackNum);
    bool isRepeated(int track[], int i);
    void randomSequenceGenerate(int track[], int trackNum);
    int lessAndNearest(int current, int track[], int trackNum);
    int greaterAndNearest(int current, int track[], int trackNum);

};

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

    trackNum = trackNum0;
    overTrack = overTrack0;
    startUp = startUp0;
    r = r0;
    blocksPerTrack = blocksPerTrack0;
    bitsPerTrack = bitsPerTrack0;
    currentTrack = currentTrack0;
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

SSTF::SSTF()
{

    trackNum = trackNum0;
    overTrack = overTrack0;
    startUp = startUp0;
    r = r0;
    blocksPerTrack = blocksPerTrack0;
    bitsPerTrack = bitsPerTrack0;
    currentTrack = currentTrack0;
    randomSequenceGenerate(track, trackNum);
    int i, j;
    int x,min = 9999;
    double trackDistance[200];
    for (i = 1; i < trackNum; i++)
    {

        trackDistance[track[i]] = -1;

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

SCAN::SCAN()
{

    trackNum = trackNum0;
    overTrack = overTrack0;
    startUp = startUp0;
    r = r0;
    blocksPerTrack = blocksPerTrack0;
    bitsPerTrack = bitsPerTrack0;
    currentTrack = currentTrack0;
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

    vector<int> tempTarget;
    vector<int> tempLower;
    vector<int> tempHigher;
    if (direction)
    {
        moveCount = hT + lT;

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
        tempTarget.insert(tempTarget.end(), tempLower.begin(), tempLower.end());
        tempTarget.insert(tempTarget.begin(), tempHigher.begin(), tempHigher.end());
    }
    roundsPerMicroSecond = r / 60000;
    trackSeekTime = moveCount * overTrack + startUp;
    averageSpinDelay = 1 / (2 * roundsPerMicroSecond);
    transmissionTime = blocksPerTrack / roundsPerMicroSecond;
    totalTime = trackSeekTime + averageSpinDelay + transmissionTime;
}
LOOK::LOOK()
{

    trackNum = trackNum0;
    overTrack = overTrack0;
    startUp = startUp0;
    r = r0;
    blocksPerTrack = blocksPerTrack0;
    bitsPerTrack = bitsPerTrack0;
    currentTrack = currentTrack0;
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

    vector<int> tempTarget;
    vector<int> tempLower;
    vector<int> tempHigher;
    if (direction)
    {
        moveCount = hT + lT;
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
        reverse(tempHigher.begin(), tempHigher.end());
        tempTarget.insert(tempTarget.end(), tempLower.begin(), tempLower.end());
        tempTarget.insert(tempTarget.begin(), tempHigher.begin(), tempHigher.end());
    }
    roundsPerMicroSecond = r / 60000;
    trackSeekTime = moveCount * overTrack + startUp;
    averageSpinDelay = 1 / (2 * roundsPerMicroSecond);
    transmissionTime = blocksPerTrack / roundsPerMicroSecond;
    totalTime = trackSeekTime + averageSpinDelay + transmissionTime;
}

void Dialog::case0out()
{
    bool ok;
    QString str1,str2,str3,str4,str5,str6,str7;

    str1 = li1->text();
    if(str1.toInt(&ok) > 0 && str1.toInt(&ok)<200)
    trackNum0 = str1.toInt(&ok);
    str2 = li2->text();
    if(str2.toDouble(&ok) > 0)
    overTrack0=str2.toDouble(&ok);
    str3 = li3->text();
    if(str3.toDouble(&ok) > 0)
    startUp0 = str3.toDouble(&ok);
    str4 = li4->text();
    if(str4.toInt(&ok) > 0)
    r0 = str4.toInt(&ok);
    str5 = li5->text();
    if(str5.toInt(&ok) > 0)
    blocksPerTrack0 = str5.toInt(&ok);
    str6 = li6->text();
    if(str6.toInt(&ok) > 0)
    bitsPerTrack0= str6.toInt(&ok);
    str7 = li7->text();
    if(str7.toInt(&ok) > 0)
    currentTrack0 = str7.toInt(&ok);

    FCFS disk;

    QString temp0,temp1;
    if(str7.toInt(&ok) > 0)
     temp1 = str7+" ";
    for (int i = 0; i < disk.generatedTrack.size(); i++)
    {
       temp1= temp1 + temp0.setNum(disk.generatedTrack[i]) + " ";
    }
    l8->setText("随机序列为："+temp1);
    l9->setText("磁头移动距离："+temp0.setNum(disk.moveCount));
    l10->setText("寻道时间："+temp0.setNum(disk.trackSeekTime));
    l11->setText("平均延迟时间："+temp0.setNum(disk.averageSpinDelay));
    l12->setText("transmission 时间："+temp0.setNum(disk.transmissionTime));
    l13->setText("总用时："+temp0.setNum(disk.totalTime));

}

void Dialog::case1out()
{
    bool ok;
    QString str1,str2,str3,str4,str5,str6,str7;
    str1 = li1->text();
    if(str1.toInt(&ok) > 0 && str1.toInt(&ok)<200)
    trackNum0 = str1.toInt(&ok);
    str2 = li2->text();
    if(str2.toDouble(&ok) > 0)
    overTrack0=str2.toDouble(&ok);
    str3 = li3->text();
    if(str3.toDouble(&ok) > 0)
    startUp0 = str3.toDouble(&ok);
    str4 = li4->text();
    if(str4.toInt(&ok) > 0)
    r0 = str4.toInt(&ok);
    str5 = li5->text();
    if(str5.toInt(&ok) > 0)
    blocksPerTrack0 = str5.toInt(&ok);
    str6 = li6->text();
    if(str6.toInt(&ok) > 0)
    bitsPerTrack0= str6.toInt(&ok);
    str7 = li7->text();
    if(str7.toInt(&ok) > 0)
    currentTrack0 = str7.toInt(&ok);
    SSTF disk;

    QString temp0,temp1;
    if(str7.toInt(&ok) > 0)
     temp1 = str7+" ";
    for (int i = 0; i < disk.generatedTrack.size(); i++)
    {
       temp1= temp1 + temp0.setNum(disk.generatedTrack[i]) + " ";
    }
    l8->setText("随机序列为："+temp1);
    l9->setText("磁头移动距离："+temp0.setNum(disk.moveCount));
    l10->setText("寻道时间："+temp0.setNum(disk.trackSeekTime));
    l11->setText("平均延迟时间："+temp0.setNum(disk.averageSpinDelay));
    l12->setText("transmission 时间："+temp0.setNum(disk.transmissionTime));
    l13->setText("总用时："+temp0.setNum(disk.totalTime));

}
void Dialog::case2out()
{
    bool ok;
    QString str1,str2,str3,str4,str5,str6,str7;
    str1 = li1->text();
    if(str1.toInt(&ok) > 0 && str1.toInt(&ok)<200)
    trackNum0 = str1.toInt(&ok);
    str2 = li2->text();
    if(str2.toDouble(&ok) > 0)
    overTrack0=str2.toDouble(&ok);
    str3 = li3->text();
    if(str3.toDouble(&ok) > 0)
    startUp0 = str3.toDouble(&ok);
    str4 = li4->text();
    if(str4.toInt(&ok) > 0)
    r0 = str4.toInt(&ok);
    str5 = li5->text();
    if(str5.toInt(&ok) > 0)
    blocksPerTrack0 = str5.toInt(&ok);
    str6 = li6->text();
    if(str6.toInt(&ok) > 0)
    bitsPerTrack0= str6.toInt(&ok);
    str7 = li7->text();
    if(str7.toInt(&ok) > 0)
    currentTrack0 = str7.toInt(&ok);

    SCAN disk;

    QString temp0,temp1;
    if(str7.toInt(&ok) > 0)
     temp1 = str7+" ";
    for (int i = 0; i < disk.generatedTrack.size(); i++)
    {
       temp1= temp1 + temp0.setNum(disk.generatedTrack[i]) + " ";
    }
    l8->setText("随机序列为："+temp1);
    l9->setText("磁头移动距离："+temp0.setNum(disk.moveCount));
    l10->setText("寻道时间："+temp0.setNum(disk.trackSeekTime));
    l11->setText("平均延迟时间："+temp0.setNum(disk.averageSpinDelay));
    l12->setText("transmission 时间："+temp0.setNum(disk.transmissionTime));
    l13->setText("总用时："+temp0.setNum(disk.totalTime));

}
void Dialog::case3out()
{
    bool ok;
    QString str1,str2,str3,str4,str5,str6,str7;
    str1 = li1->text();
    if(str1.toInt(&ok) > 0 && str1.toInt(&ok)<200)
    trackNum0 = str1.toInt(&ok);
    str2 = li2->text();
    if(str2.toDouble(&ok) > 0)
    overTrack0=str2.toDouble(&ok);
    str3 = li3->text();
    if(str3.toDouble(&ok) > 0)
    startUp0 = str3.toDouble(&ok);
    str4 = li4->text();
    if(str4.toInt(&ok) > 0)
    r0 = str4.toInt(&ok);
    str5 = li5->text();
    if(str5.toInt(&ok) > 0)
    blocksPerTrack0 = str5.toInt(&ok);
    str6 = li6->text();
    if(str6.toInt(&ok) > 0)
    bitsPerTrack0= str6.toInt(&ok);
    str7 = li7->text();
    if(str7.toInt(&ok) > 0)
    currentTrack0 = str7.toInt(&ok);
    LOOK disk;

    QString temp0,temp1;
    if(str7.toInt(&ok) > 0)
     temp1 = str7+" ";
    for (int i = 0; i < disk.generatedTrack.size(); i++)
    {
       temp1= temp1 + temp0.setNum(disk.generatedTrack[i]) + " ";
    }
    l8->setText("随机序列为："+temp1);
    l9->setText("磁头移动距离："+temp0.setNum(disk.moveCount));
    l10->setText("寻道时间："+temp0.setNum(disk.trackSeekTime));
    l11->setText("平均延迟时间："+temp0.setNum(disk.averageSpinDelay));
    l12->setText("transmission 时间："+temp0.setNum(disk.transmissionTime));
    l13->setText("总用时："+temp0.setNum(disk.totalTime));

}

