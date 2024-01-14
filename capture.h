 /*
 * 采集卡qt
 * */
#ifndef CAPTURE_H
#define CAPTURE_H
#include <QThread>
#include <QObject>
#include <QDebug>
#include "usbdask64.h"

#define MAX_CHAN_2405	4   //最大通道数

using namespace std;

class Capture : public QThread
{
    Q_OBJECT
protected:
    void run();
public:
    explicit Capture(QObject *parent = nullptr);
    ~Capture();
    bool init_Capture();
    bool stopCapture();
    bool findDevice();
    int display_buffer_data(U32* pBuf);
//    bool saveData();
//    HANDLE m_hMem=NULL;


    I16 card;                       //采集卡ID：注册之后
    I16 nErr_device;


    //计数器
    uint64_t count0=0;
    uint64_t count1=0;
    uint64_t count2=0;

private:
    I16 g_hCard = NULL;             //采集卡ID：注册之前

    U16  m_wChan[MAX_CHAN_2405];
    U16  m_wGain[MAX_CHAN_2405];
    USBDAQ_DEVICE AvailModules[MAX_USB_DEVICE];

    HANDLE m_hMem=NULL;            //内存空间的句柄
    ULONG AI_SAMPLE_COUNT=512;   //采样点数
    double m_fSampleRate=1024;    //采样频率  1秒中1024个数据点

    U16 m_wSelectedChans=3;        //选择的通道个数
    int cur_channel;               //通道0 1 2
    U16  m_wRange=AD_B_10_V;       //模拟输入范围（-10v~10v）

signals:
    void vibrationValue0(double);
    void vibrationValue1(double);
    void vibrationValue2(double);
    void vibrationValue3(double);


};




#endif // CAPTURE_H
