#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChartView>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QDebug>
#include <QValueAxis>
#include <QtCharts/QDateTimeAxis>
#include <QTimer>
#include <QDateTime>
//#include "qcustomplot.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QtMath>
#include "thread.h"
#include "capture.h"
#include "iostream"
#include <QTabBar>
using namespace std;
//#pragma comment(lib,"ws2_32.lib")

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //保存数据
    void saveDatetime();
    void savetorque(double r);
    void savepower(double r);
    void savespeed(double r);

    void plotTorque(double r,uint16_t kz);

    void setMoto();
    void closeMoto();
    void connectCommunication();
    void connetSignals();
    void initWidget(bool fullscreen);

    void CurvePlotting();
    void CurvePlotting_Niuju();
    void CurvePlotting_Wendu();

    void connectModbus();
    void connectMotoModbus();
    void connectToPython();
    void sendToPython();
    void StatusConnect();
    qreal judgeMOtoSpeed();  //判断电机转速是否为0，是否开启电机
    void importPs();


    bool save_flag = false;
    QString str;

private:
    double tempTq=0;
    double tempPw=0;
    double tempV0=0;
    double tempV1=0;
    double tempV2=0;
    QString equipment_name;
    Ui::Widget *ui;
    QTcpServer server;          // 创建一个QTcpServer对象
    QTcpSocket *clientSocket;

    SerialThread *serial_thread = nullptr;
    ModbusThread *pressure_thread = nullptr;
    TempratureThread *temprature_thread = nullptr;
    TorqueThread *torquethread = nullptr;
    ModbusMotorThread *modbus_motor_thread = nullptr;


    QChart *Chart;             // 振动chart对象
    QChart *Chart1;
    QChart *Chart2;
    QLineSeries *LineSeries0;   // 展示在图表对象上面的线对象0
    QLineSeries *LineSeries0_1;
    QLineSeries *LineSeries0_2;
    QLineSeries *LineSeries0_3;
    QLineSeries *LineSeries1;   // 展示在图表对象上面的线对象1
    QLineSeries *LineSeries2;   // 展示在图表对象上面的线对象2
    QLineSeries *LineSeries3;   // 展示在图表对象上面的线对象3
    QLineSeries *LineSeries4;
    QLineSeries *LineSeries5;

//    QVector<QPointF> Pointf0;  // 绘制线对象所需要的数据
    QValueAxis *AxisX0;         // X轴
    QValueAxis *AxisX1;         // X轴
    QValueAxis *AxisX2;         // X轴

    QValueAxis *AxisY0;         // Y0轴
    QValueAxis *AxisY0_1;         // Y0轴
    QValueAxis *AxisY0_2;         // Y0轴
    QValueAxis *AxisY1;         // Y1轴
    QValueAxis *AxisY2;         // Y2轴
    QValueAxis *AxisY3;         // Y3轴
    QValueAxis *AxisY4;         // Y4轴
    QValueAxis *AxisY5;

    //X轴与Y轴最大值
    qreal MAX_X = 1;

    qreal MIN_Y0 = -10;
    qreal MAX_Y0 =10;
    qreal MIN_Y0_1 = -10;
    qreal MAX_Y0_1 =10;
    qreal MIN_Y0_2 = -10;
    qreal MAX_Y0_2 =10;
    qreal MAX_Y1 = 200;
    qreal MIN_Y2m = -5;  //扭矩最小
    qreal MAX_Y2 = 0.5;   //扭矩最大
    qreal MAX_Y3 = 50;  //功率
    qreal MAX_Y4 = 4000; //转速
    qreal MAX_Y5 = 0.5; //扭矩随转速

    //布局
    QHBoxLayout *Tab2_HBoxLay0;
    QHBoxLayout *Tab2_HBoxLay1;
    QHBoxLayout *Tab2_HBoxLay2;
    QHBoxLayout *Tab2_HBoxLay3;
    QVBoxLayout *Tab2_VBoxlay;
    QVBoxLayout *Tab2_VBoxlay1;

    //定时器
    QTimer* m_timer0;
    QDateTime dateTime;


    //计数器


    qreal PointCount0 = 0;//振动0
    qreal PointCount0_1 = 0;//振动1
    qreal PointCount0_2 = 0;//振动2
    qreal PointCount0_3 = 0;//振动3
    qreal PointCount1 = 0;//压力
    qreal PointCount2 = 0;//扭矩
    qreal PointCount3 = 0;//功率
    qreal PointCount4 = 0;//转速
    qreal  PointCount5 = 0;//温度


private slots:

    void mTimeout();

   //tab2
    void tab2_start();
    void tab2_pb1();
    void tab2_pb2();
    void tab2_pb3();
    void tab2_pb6();

    void serial_signal_0(int);




    //thread to widget
    void VSPStatus_slot();
    void vibration0_ui_Slot(double);
    void vibration1_ui_Slot(double);
    void vibration2_ui_Slot(double);
    void vibration3_ui_Slot(double);

    //modbus1 pressure
    void on_changePassword_clicked();
    void pressureValueSlot(qint32,uint16_t);
    void temperatureValueSlot(double);
    void rotateSpeedValueSlot(qint32,uint16_t);
    void torqueValueSlot(qint32,uint16_t);
    void powerValueSlot(uint16_t,uint16_t);
    void startMoto(uint16_t);



    void on_start_test_clicked();
    void changeMotoResult();
    void on_vibrationToPy_clicked();



    void on_saveData_clicked();
    void on_closeApp_clicked();
    void on_closeApp_2_clicked();
    void on_btn_setpassOk_clicked();
};

#endif // WIDGET_H
