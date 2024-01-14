#include "thread.h"
#include "capture.h"
#include "queue"
#include "QDataStream"
#include "iostream"

using namespace std;
#define ResultPath "C:/Users/14542/Desktop/Log.txt"
extern QFile file0;
extern QFile file1;
extern QFile file2;
extern QFile file3;
extern modbus_t* pressure_LowMachine;
extern modbus_t* temprature_Lowmachine;

QMutex stop_mutex;
modbus_t* pl;
plc_fds fd =
    {
        //          .d1 = NULL,
        //          .d2 = NULL,
};
extern uint8_t start_flag;

QMutex pressure_mutex;
QMutex torque_mutex;
QMutex temprature_mutex;
QMutex moto_mutex;
extern modbus_t* LowMachine;
extern Capture* cap;
extern U32 *g_pAIBuf;       //capture.cpp的全局变量

extern std::queue<qreal> dataQueue0;
void AI_EndCallBack()
{

    /*
         * 根据所选的连续AI函数，循环缓冲区的一半数据将保存到用户缓冲区
         * （如果连续AI函数为：UD_AI_ContReadChannel和UD_AI_ContReadMultiChannels）
         * 或登录到磁盘文件(如果连续AI函数为：UD_AI_ContReadChannelToFile和UD_AI_ContReadMultiChannelsToFile)。
         * 您可以重复执行此函数以返回数据的连续半缓冲区。
    * */

    I16 err = UD_AI_AsyncDblBufferTransfer32(cap->card, g_pAIBuf);

    cap->display_buffer_data(g_pAIBuf);





}

SerialThread::SerialThread(QObject *parent) : QThread(parent)
{

}



void SerialThread::run()
{
    serial = new QSerialPort();

    //连接信号槽
    connect(serial, &QSerialPort::readyRead, this, &SerialThread::ReadData);


}

void SerialThread::ReadData()
{

}

//温度，压力，扭矩仪通过modbus读取
ModbusThread::ModbusThread(QObject *parent) : QThread(parent)
{

}

void ModbusThread::run()
{


    //传输数据
    while (1)
    {

        uint16_t pressI1;
        uint16_t pressI2;
        uint16_t pressDouble;
        uint16_t temp;


        if(start_flag)
        {
            //压力
            pressure_mutex.lock();
            int ret = modbus_read_registers(pressure_LowMachine, 0x0000, 1, &pressI1);
            qDebug()<<ret;
            qDebug()<<"pressI1: "<<pressI1;
            qDebug()<<"pressI2: "<<pressI2;
            modbus_read_registers(pressure_LowMachine, 0x0001, 1, &pressI2);
            int ret1 = modbus_read_registers(pressure_LowMachine,0x0002,1,&pressDouble);
            qDebug()<<"压力小数部分读取状态："<<ret;

                qDebug()<<"pressDouble: "<<pressDouble;
            qint32 pressInt = static_cast<qint32>(static_cast<qint32>(pressI1)<<16) | pressI2;
            emit pressureValue(pressInt,pressDouble);
            pressure_mutex.unlock();


        }

    }

}




//modbus控制电机
ModbusMotorThread::ModbusMotorThread(QObject *parent):QThread(parent),isStop(false)
{

}

ModbusMotorThread::~ModbusMotorThread()
{

}

void ModbusMotorThread::exitThread()
{
    stop_mutex.lock();
    isStop=true;
    stop_mutex.unlock();
}

void ModbusMotorThread::run()
{



    if(start_flag)
    {
        moto_mutex.lock();
        int ret = modbus_write_register(fd.d2,0x0603,enterSpeed);
        qDebug()<<"写0603： "<<ret;
//        int ret1 = modbus_write_register(fd.d2,0x030A,1);
//        qDebug()<<"写030A： "<<ret1;
        moto_mutex.unlock();

    }

    //        emit startMoto(temp);

}


//温度线程modbus
TempratureThread::TempratureThread(QObject *parent)
{

}

void TempratureThread::run()
{
    uint16_t temp;
    uint16_t temp1;
    while(1)
    {
        if(start_flag)
        {

            temprature_mutex.lock();

            int ret = modbus_read_input_registers(temprature_Lowmachine,0x0000,2,&temp);
//            int ret1 = modbus_read_input_registers(temprature_Lowmachine,0x0001,1,&temp1);
            qDebug()<<"温度1 "<<temp1<<ret;

            qDebug()<<"温度: "<<temp<<ret;

            // 创建一个指向temp的指针
            uint16_t *tempPtr = &temp;

            // 通过指针访问temp的地址加1的值
            uint16_t temp1 = *(tempPtr + 1);
            // 合并两个 uint16 整数成一个 32 位整数
            int32_t combinedValue = ((int32_t)*tempPtr << 16) | temp1;
            // 将合并后的整数解释为 32 位浮点数
            float result_advance,result;
            memcpy(&result_advance, &combinedValue, sizeof(float));
            // 将浮点数保留一位小数并存储到另一个变量中
            result = ((int)(result_advance * 10 + 0.5)) / 10.0;
            qDebug()<<"result: "<<result;



            emit temperatureValue(result);
            temprature_mutex.unlock();





        }
    }
}

TorqueThread::TorqueThread(QObject *parent)
{

}

void TorqueThread::run()
{
    while(1)
    {
        if(start_flag)
        {
            uint16_t sp1;
            uint16_t sp2;
            uint16_t spDouble;

            uint16_t tq1;
            uint16_t tq2;
            uint16_t tqDouble;

            uint16_t pw1;
            uint16_t pw2;
            uint16_t pwDouble;

            //扭矩
            torque_mutex.lock();
            modbus_read_registers(fd.d1,0x0000,1,&tq1);  //扭矩整数部分
            modbus_read_registers(fd.d1,0x0001,1,&tq2);  //扭矩整数部分
            int ret = modbus_read_registers(fd.d1,0x0006,1,&tqDouble); //扭矩小数部分
            qDebug()<<"------------>扭矩小数部分ret: "<<ret;
            qDebug()<<"tq1: "<<tq1;
            qint32 tqInt = static_cast<qint32>(static_cast<qint32>(tq1)<<16) | tq2;
            qDebug()<<"tq2: "<<tq2;

            emit torqueValue(tqInt,tqDouble);
            qDebug()<<"ccccccccccccccccctqInt: "<<tqInt<<"tqDouble: "<<tqDouble;
            //            msleep(40);
            torque_mutex.unlock();
            //转速
            torque_mutex.lock();
            modbus_read_registers(fd.d1,0x0002,1,&sp1);  //转速整数部分
            modbus_read_registers(fd.d1,0x0003,1,&sp2);  //转速整数部分
            modbus_read_registers(fd.d1,0x0007,1,&spDouble); //转速小数部分
            qint32 spInt = static_cast<qint32>(static_cast<qint32>(sp1)<<16) | sp2;

            qDebug()<<"------>扭矩仪转速spInt: "<<spInt<<"spDouble: "<<spDouble;
            emit rotateSpeedValue(spInt,spDouble);
            //            msleep(40);
            torque_mutex.unlock();



            //功率
            torque_mutex.lock();
            modbus_read_registers(fd.d1,0x0004,1,&pw1);  //功率整数部分
            modbus_read_registers(fd.d1,0x0005,1,&pw2);  //功率整数部分

            modbus_read_registers(fd.d1,0x0008,1,&pwDouble); //功率小数部分
            uint16_t pwInt = static_cast<uint16_t>(static_cast<uint16_t>(pw1)<<16) | pw2;

            qDebug()<<"------>>>>>>>扭矩仪功率pwInt: "<<pwInt<<"pwDouble: "<<pwDouble;
            emit powerValue(pwInt,pwDouble);
            //            msleep(40);
            torque_mutex.unlock();




        }
    }



}
