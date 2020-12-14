#include "FCFS.h"
#include "SSTF.h"
#include "SCAN.h"
#include "LOOK.h"
#include "RASG.h"
using std::cin;
using std::cout;
using std::endl;
/** 
 *  track为访问序列
 *  overTrack为跨越时间     ms
 *  startUp为启动时间       ms
 *  r为转速                rpm
 *  blocksPerTrack为每磁道扇区块数
 *  bitsPerTrack为每扇区字节数
 *  currentTrack为当前所在磁道
 *  direction为当前移动方向，0为内
 */
// 使用一段长度为200的数组，初始所有值置0，增加一次访问则++，访问完成--，然后矬子里面拔高个儿就vans了
//TODO 上面那行是放屁，根本不行，还得老法子
//！ 注意!这里采取数组表示输入的访问序列//
int main()
{
    //定义变量区
    int argrithmSelect;
    srand((unsigned)time(NULL));
    int randomNumber = rand() % 200;
    int track[200];
    int overTrack,
        startUp,
        r,
        blocksPerTrack,
        bitsPerTrack,
        currentTrack;
    bool loop = true;

    //此处为对输入序列的录入
    //已经不重复随机了
    _RASG_(track);

    //此处为对跨越时间的输入
    cout << "overTrack:" << endl;
    cin >> overTrack;

    //此处为对启动时间的输入
    cout << "startUp:" << endl;
    cin >> startUp;

    //此处为对转速的输入
    cout << "r:" << endl;
    cin >> r;

    //此处为对每磁道扇区块数的输入
    cout << "blocksPerTrack:" << endl;
    cin >> blocksPerTrack;

    //此处为对每扇区字节数的输入
    cout << "bitsPerTrack:" << endl;
    cin >> bitsPerTrack;

    //此处为对当前所在磁道的输入
    cout << "currentTrack:" << endl;
    cin >> currentTrack;

    bool direction;
    if (randomNumber % 2 == 0)
    {
        direction = true;
    }
    else
    {
        direction = false;
    } //定义并给direction赋值，毕竟随机嘛
    while (loop)
    {
        //输入对算法的选择
        cout << "which do ya want to choose, from 0~3?" << endl;
        cin >> argrithmSelect;
        switch (argrithmSelect)
        {
        case 0:
        {
            FCFS(track, overTrack, startUp, r, blocksPerTrack, bitsPerTrack, currentTrack, direction);
            break;
        }
        case 1:
        {
            SSTF(track, overTrack, startUp, r, blocksPerTrack, bitsPerTrack, currentTrack, direction);
            break;
        }
        case 2:
        {
            SCAN(track, overTrack, startUp, r, blocksPerTrack, bitsPerTrack, currentTrack, direction);
            break;
        }
        case 3:
        {
            LOOK(track, overTrack, startUp, r, blocksPerTrack, bitsPerTrack, currentTrack, direction);
            break;
        }
        }
        cout << "wanna another argrithm?" << endl;
        cout << "select 0~3 to restart" << endl;
        cout << "select -1 to stop" << endl;
        cin >> argrithmSelect;
        if (argrithmSelect == -1)
        {
            loop = false;
        }
    }
    system("pause");
    return 0;
}