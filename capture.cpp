#include "capture.h"
#include <queue>



U32 *g_pAIBuf=NULL;                 //数据指针

extern void AI_EndCallBack();

void Capture::run()
{
    init_Capture();
}

Capture::Capture(QObject *parent) : QThread(parent)//进行DMA缓冲区的内存分配，并检查分配是否成功。
{
    /*
     * 查找设备
     * */
    bool ret = findDevice();

    if(ret==false){
        qDebug()<<"cannot find device";
    }else{
        qDebug()<<"find device";
    }
    qDebug()<<"g_hCard: "<<g_hCard;


    /*
     * allocate a memory for user DMA buffer提供数据内存空间
     * */
    DWORD mem_size = AI_SAMPLE_COUNT * sizeof(I32) * 3; // 空间大小
    m_hMem = GlobalAlloc(GMEM_ZEROINIT, mem_size);      //设初值为0
    g_pAIBuf = (U32*)GlobalLock(m_hMem);
    if (g_pAIBuf == NULL)
    {
        qDebug()<<"Memory allocation failed "<<MB_OK;

    }
}


//析构函数释放之前在构造函数中分配的内存。
Capture::~Capture()
{
    if(m_hMem != NULL)
    {
        GlobalUnfix(m_hMem);
        GlobalUnlock(m_hMem);
        GlobalFree(m_hMem);

        m_hMem = NULL;
    }

    if(g_pAIBuf!=NULL)
    {
        delete []g_pAIBuf;
    }
}


bool Capture::init_Capture()
{
    I16 err;
    /*
     * 注册g_hCard（若不注册，下面配置通道直接返回错误码），注册设备名：card
     * 错误码：
     *
     * */
    card = UD_Register_Card(USB_2405, g_hCard);
    if(card<0)
    {
        printf("UD_Register_Card Error: %d\n", card);
    }
    /*
     *  配置通道0 1 2 3
     *  通过模块ID ModuleNum通知UD-DASK库为USB-2405模块选择的模拟输入类型。
     *  在调用函数执行连续模拟输入操作之前，必须调用此函数。
     *  Informs UD-DASK library of the analog input-type selected for the USB-2405 module
     *  with module ID ModuleNum. You must call this function before calling function to
     *  perform continuous analog input operation.
     *  该配置包括三个部分-输入型、耦合型和IEPE设置。
     *  请按位或相关设置。有效设置如下所示：输入类型的有效设置为：P2405_AI_Differential或P2405_AI_PseudoDifferential
     *  有效的耦合类型设置为：P2405_AI_Coupling_AC或P2405_AI_Coupling_None。
     *  有效的IEPE设置为：P2405_AI_EnableIEPE或P2405_AI_DisableIEPE
     * */
    err = UD_AI_2405_Chan_Config(card, ( P2405_AI_DisableIEPE | P2405_AI_Coupling_None | P2405_AI_Differential),  \
                                 ( P2405_AI_DisableIEPE | P2405_AI_Coupling_None | P2405_AI_Differential),  \
                                 ( P2405_AI_DisableIEPE | P2405_AI_Coupling_None | P2405_AI_Differential),  \
                                 ( P2405_AI_DisableIEPE | P2405_AI_Coupling_None | P2405_AI_Differential) );
    if (err != NoError)
    {
        qDebug()<<"UD_AI_2405_Chan_Config error= "<<err;

        return false;
    }

    /*
     * 通过模块ID ModuleNum通知UD-DASK库USB-2405模块的触发设置。
     * 在调用函数执行连续模拟输入操作之前，必须调用此函数。
     * Trigger-Mode::   P2405_AI_TRGMOD_POST: Post-trigger.
                        P2405_AI_TRGMOD_DELAY: Delay-trigger.
                        P2405_AI_TRGMOD_PRE: Pre-trigger.
                        P2405_AI_TRGMOD_MIDDLE: Middle-trigger.
                        P2405_AI_TRGMOD_GATED: Gated-trigger.
     * */
    err = UD_AI_2405_Trig_Config(card, P2405_AI_CONVSRC_INT, P2405_AI_TRGMOD_POST, P2405_AI_TRGSRC_SOFT, 0, 0, 0, 0 );
    if (err != NoError)
    {
        qDebug()<<"UD_AIO_2405_TrgSource_Config error= "<<err;

        return false;
    }


    /*
     * 启动双缓冲数据采集模式1
     *
     * Enable / disable the double-buffered data acquisition mode.
     * */
    err = UD_AI_AsyncDblBufferMode(card, 1); // double-buffer mode
    if (err != NoError)
    {
        qDebug()<<"UD_AI_AsyncDblBufferMode error= "<<err;
        return false;
    }

    /*
     * 回调函数（将数据发给界面显示）
     * 控制并通知用户的应用程序何时发生指定的DAQ事件。
     * 通知通过用户指定的回调函数执行。
     * */
    err = UD_AI_EventCallBack_x64 (card, 1/* enable*/ ,DBEvent, (ULONG_PTR) AI_EndCallBack );
    if (err != NoError)
    {
        qDebug()<<"UD_AI_2405_SampleRate_Set() failed, error code = "<<err;
        return false;
    }

    /*
     * 将每个通道里都设置好输入电压m_wRange
     * m_wChan[]存放id号
     * */
    for( int i=0; i<m_wSelectedChans; i++ )
    {
        m_wChan[i] = i;

        m_wGain[i] = m_wRange;
        qDebug()<<"m_wGain"<<i<<": "<<m_wGain[i];
    }


    /*
     * 此功能以接近指定速率的速率对指定模拟输入通道执行连续A/D转换。
     * 此功能利用通道增益队列功能执行多通道模拟输入。
     * */
    err = UD_AI_ContReadMultiChannels(card, m_wSelectedChans, m_wChan, m_wGain, (U16*)g_pAIBuf, (AI_SAMPLE_COUNT*m_wSelectedChans), (F64)m_fSampleRate, ASYNCH_OP);
    if (err != NoError)
    {
        qDebug()<<"UD_AI_ContReadMultiChannels error=  "<<err;
        return false;
    }
    return true;
}


/*
 * 停止采集
 * */
bool Capture::stopCapture()
{
    U32 count;
    I16 ret = UD_AI_AsyncClear(card, &count);
    if (ret != NoError)
    {
        qDebug()<<"UD_AI_AsyncClear error=  "<<ret;
        return false;
    }
    //    qDebug()<<"停止采集"<<ret;
     UD_AI_EventCallBack_x64 (card, 0 , DBEvent, NULL );
//    UD_AI_EventCallBack_x64 (card, 1 , AIEnd, NULL );



    UD_Release_Card(card);


    return true;
}


//看设备是否存在
bool Capture::findDevice()
{
    U16 wModuleNum;
    U16 i;
    nErr_device = UD_Device_Scan(&wModuleNum, AvailModules);

    qDebug()<<"wModuleNum： "<<wModuleNum<<"wCardID:  "<<AvailModules[0].wCardID<<"wModuleType: "<<AvailModules[0].wModuleType;
                                                                                                                   g_hCard = AvailModules[0].wCardID;
    if( nErr_device != NoError )
    {
        qDebug()<<"scan device failure!!!";
        return FALSE;
    }

    for( i = 0; i < wModuleNum; i++ )
    {
        if( AvailModules[i].wModuleType == USB_2405 )
        {
            g_hCard = AvailModules[i].wCardID;
            break;
        }
    }
    return true;
}


int Capture::display_buffer_data(U32 *pBuf)
{
    U32 index;
    double newY = -1;

    U32 dwSampleCount;
    I32 ai_data;
    //AI_SAMPLE_COUNT  20480
    //m_wSelectedChans 3
    dwSampleCount = (AI_SAMPLE_COUNT*m_wSelectedChans)/2;

//    dwSampleCount = AI_SAMPLE_COUNT/2;  //half-buffer
//    qDebug()<<"g_pAIBuf: "<<*g_pAIBuf;

    for(index=0; index<dwSampleCount; index+=2)   //采样点数512，256为半个缓冲区
    {
        U32 dwTemp=0;
        cur_channel = index%(m_wSelectedChans);

        dwTemp = pBuf[index];
//        qDebug()<<"cur_channel: "<<cur_channel<<"  dwTemp: "<<dwTemp;

        //当数据高8位为1时，将其放在-10到10v的y负半轴
        if( dwTemp & 0x00800000 )
        {
            dwTemp = (dwTemp | 0xFF000000);
            ai_data = (I32)(dwTemp);
            newY=-(double)(10*(1-(((double)(ai_data + 0x7FFFFF)/0x7FFFFF))));
        }

        //将数据放在y正半轴
        else
        {
            ai_data = (I32)(dwTemp);
            newY=(double)((10*((double)(ai_data)/0x7FFFFF)));
        }
        qDebug()<<"cur_channel: "<<cur_channel<<"  ai_data: "<<ai_data;
        qDebug()<<"newY: "<<newY;

        switch(cur_channel)
        {
        case 0:
            qDebug()<<"cur_channel: "<<cur_channel<<"index: "<<index<<"  ai_data: "<<ai_data;
            qDebug()<<"ai_data channel 0: : "<<newY;

            emit  vibrationValue0(newY);
            count0++;
//            qDebug()<<"v0计数: "<<count0;
            break;
        case 1:
            emit vibrationValue1(newY);
            count1++;
            break;
        case 2:
            qDebug()<<"ai_data channel 2: "<<newY;
            emit vibrationValue2(newY);
            break;
        case 3:
            qDebug()<<"ai_data channel 3: "<<newY;
            emit vibrationValue3(newY);
            count2++;
            break;
        }
       Sleep(5);

    }



    return 0;
}




