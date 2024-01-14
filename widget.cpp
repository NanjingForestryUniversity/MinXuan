#include "widget.h"
#include "ui_widget.h"
#include "capture.h"
#include "QPainter"
#include <QMutex>
#include <fstream>
#include <QFileDialog>
#include <QDir>
#define SavePath "C:/Users/14542/Desktop/SavePath.txt"
int entercount=0;
double speedTemp=0;
double sum=0,average=0;
int num=0;
int torquetotxtcount;
QString password;
QString file0path ;
QFile file0(file0path);
QString file1path;
QFile file1(file1path);
QString file2path;
QFile file2(file2path);
QString file3path;
QString fileSpath;
QString fileTpath;

QString filePpath ;
QString fileDatepath;
QString fileTSPpath;
QFile fileDate(fileDatepath);



QFile file3(file3path);
QFile fileTSP(fileTSPpath);
QFile fileT;
QFile fileS;
QFile fileP;
// int num=0;
//int num1=0;
//标志位
uint8_t start_flag;
uint8_t cpstart_flag=1;


bool is_timeout;
QMutex sendPy;

bool pyAcceptFlag=true;
//modbus
extern plc_fds fd;
modbus_t* pressure_LowMachine;
modbus_t* temprature_Lowmachine;
extern QMutex moto_mutex;
//采集卡
Capture* cap;


extern U32 *g_pAIBuf;

//电机转速相关参数，用来判断电机转速是否为0

qreal MotoSpeedStatus=1;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    importPs();
    initWidget(false);

/************通讯状态******************/
    connectModbus();
    connectMotoModbus();
    connectToPython();
    StatusConnect();         //采集卡连接状态


    /************通信线程启动******************/
    connectCommunication();

    /************时间戳**********************/
    m_timer0 = new QTimer();
    m_timer0->setSingleShot(false);
    m_timer0->start(1000);

    /************信号与槽连接******************/

    connetSignals();



}

Widget::~Widget()
{

    delete ui;
}

void Widget::saveDatetime()
{
    QString name;
    name =ui->lineEdit_p->text();
    equipment_name = ui->lineEdit_ID->text();
    fileDatepath = "F:/data/"+equipment_name+"时间.txt";
    QFile fileDate(fileDatepath);
    if (!fileDate.open(QIODevice::Append| QIODevice::Text)) {
        qDebug() << "无法打开时间文件";

    }
    QTextStream dateout(&fileDate);//写入
    dateout<<name<<"\t"<<str<<endl;
    fileDate.close();
}

void Widget::savetorque(double r)
{
    //存数据
    equipment_name = ui->lineEdit_ID->text();
    fileTpath = "F:/data/"+equipment_name+"扭矩.txt";
    QFile fileT(fileTpath);

    if(! fileT.open(QIODevice::Append| QIODevice::Text))  //Append追加，不会覆盖之前的文件
    {
        QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！","确定");
        return;
    }

    QTextStream out(&fileT);//写入
    //    out<<"扭矩"<<endl;
    out <<"speedTemp: "<<speedTemp<<"\t"<<"torque: "<<r<<endl;
    fileT.close();

}

void Widget::savepower(double r)
{
    equipment_name = ui->lineEdit_ID->text();
    filePpath = "F:/data/"+equipment_name+"功率.txt";
    QFile fileP(filePpath);
    //存数据
    if(save_flag)
    {
        if(! fileP.open(QIODevice::Append| QIODevice::Text))  //Append追加，不会覆盖之前的文件
        {
            QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！","确定");
            return;
        }

        QTextStream out(&fileP);//写入
        //    out<<"功率"<<endl;
        out <<r<<endl;
        fileP.close();
    }
}

void Widget::savespeed(double r)
{
    equipment_name = ui->lineEdit_ID->text();
    fileSpath = "F:/data/"+equipment_name+"转速.txt";
    QFile fileS(fileSpath);
    if(save_flag)
    {

        if(! fileS.open(QIODevice::Append| QIODevice::Text))  //Append追加，不会覆盖之前的文件
        {
            QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！","确定");
            return;
        }

        QTextStream out(&fileS);//写入
        //    out<<"转速"<<endl;
        out <<r<<endl;


        fileS.close();
    }
}

void Widget::plotTorque(double r, uint16_t k)
{
     LineSeries5->append(QPointF(k, r));


}

void Widget::setMoto()
{
    //设置电机变频器的值，启动电机


        modbus_motor_thread->start();
        torquethread->start();
        pressure_thread->start();
        temprature_thread->start();



}

void Widget::closeMoto()
{

        QPixmap pixmap = ui->graphicsView_3->grab();
        equipment_name = ui->lineEdit_ID->text();
        QString filePath = "F:/data/" + equipment_name + "扭矩随转速变化";


        QString chart2view = filePath + ".jpg"; // 通过在文件名后添加.jpg扩展名构建.jpg文件的完整路径
        AxisX0->setMin(0);
        AxisX0->setMax(MAX_X);

        AxisX1->setMin(0);
        AxisX1->setMax(MAX_X);
//        AxisX2->setMax(0);
//        AxisX2->setMax(MAX_X);



        // 将截图保存为.jpg文件
        pixmap.save(chart2view);
        bool ret = cap->stopCapture();
        if(ret==true)
        {
        qDebug() << "采集卡停止采集";
        }
        ui->lineEdit_torqueMax->clear();
        ui->lineEdit_torqueMax_2->clear();
        start_flag = 0;
        disconnect(cap,SIGNAL(vibrationValue0(double)),this,SLOT(vibration0_ui_Slot(double)));
//        disconnect(cap,SIGNAL(vibrationValue1(double)),this,SLOT(vibration1_ui_Slot(double)));
//        disconnect(cap,SIGNAL(vibrationValue2(double)),this,SLOT(vibration2_ui_Slot(double)));
//        disconnect(pressure_thread,SIGNAL(pressureValue(qint32,uint16_t)), this, SLOT(pressureValueSlot(qint32,uint16_t)));
//        disconnect(temprature_thread,SIGNAL(temperatureValue(double)),this,SLOT(temperatureValueSlot(double)));
        disconnect(torquethread,SIGNAL(rotateSpeedValue(qint32,uint16_t)),this,SLOT(rotateSpeedValueSlot(qint32,uint16_t)));
        disconnect(torquethread,SIGNAL(torqueValue(qint32,uint16_t)),this,SLOT(torqueValueSlot(qint32,uint16_t)));
        disconnect(torquethread,SIGNAL(powerValue(uint16_t,uint16_t)),this,SLOT(powerValueSlot(uint16_t,uint16_t)));
//        disconnect(modbus_motor_thread,SIGNAL(startMoto(uint16_t)),this,SLOT(startMoto(uint16_t)));
        ui->pushButton_0->setText("开始采集");

        //        modbus_motor_thread->terminate();
        moto_mutex.lock();
        modbus_write_register(fd.d2, 0x0603, 0);
        //        modbus_write_register(fd.d2, 0x030A, 0);

        moto_mutex.unlock();





}

void Widget::connectCommunication()
{
    pressure_thread = new ModbusThread();
    temprature_thread = new TempratureThread();
    modbus_motor_thread = new ModbusMotorThread();
    torquethread = new TorqueThread();
}

void Widget::connetSignals()
{
    //Timer
    connect(m_timer0, SIGNAL(timeout()), this, SLOT(mTimeout()));

    //tab2
    connect(ui->pushButton_0,SIGNAL(clicked()), this, SLOT(tab2_start()));
    connect(ui->lineEdit_inputSpeed,SIGNAL(returnPressed()),this,SLOT(changeMotoResult()));
    //thread to widget

    connect(cap,SIGNAL(vibrationValue3(double)),this,SLOT(vibration3_ui_Slot(double)));



}

void Widget::initWidget(bool fullscreen)
{
    ui->tabWidget->findChildren<QTabBar*>().at(0)->hide();
    ui->tabWidget->setCurrentIndex(0);
//    ui->label_title->setStyleSheet("QLabel{background-color:transparent;}");
    if(fullscreen)
        this->showFullScreen();
    /**************标志位初始化*******************/

    start_flag = 0;
    g_pAIBuf = nullptr;
//    ui->label_status_2->setStyleSheet("QLabel{background-color:rgb(255,0,0);}");
    cap = new Capture();

    /************绘制曲线******************/
    CurvePlotting();
    CurvePlotting_Niuju();
    CurvePlotting_Wendu();

}

/*****************振动图表初始化、实例化****************************/
void Widget::CurvePlotting()
{

    Chart = new QChart();

    AxisX0 = new QValueAxis();
    AxisY0 = new QValueAxis();
    AxisY0_1 = new QValueAxis();
    AxisY0_2 = new QValueAxis();

    //2
    LineSeries0 = new QSplineSeries();
    LineSeries0->setPen(QPen(QColor(255, 0, 0), 3));

    LineSeries0->setName("振动0");
    LineSeries0_1 = new QSplineSeries();
    LineSeries0_1->setPen(QPen(QColor(0, 255, 0), 3));
    LineSeries0_1->setName("振动1");
    LineSeries0_2 = new QSplineSeries();
    LineSeries0_2->setPen(QPen(QColor(0, 0, 255), 3));
    LineSeries0_2->setName("振动2");
    LineSeries0_3 = new QSplineSeries();
    //    LineSeries0->setPen(QPen(QColor(255, 0, 0), 3));
    LineSeries0_3->setName("振动3");

    //3

    //  Chart->setTitle("实时动态曲线示例");
    Chart->setBackgroundBrush(QColor(255,255,255));
//    QChartView::setRubberBand(QChartView::RectangleRubberBand);
    Chart->addSeries(LineSeries0);
    Chart->addSeries(LineSeries0_1);
    Chart->addSeries(LineSeries0_2);
    Chart->addSeries(LineSeries0_3);

    /*****************YO轴设置  振动****************************/
    /* 设置显示格式 */
    AxisY0->setLabelFormat("%i");
    /* y轴标题 */
    AxisY0->setTitleText("振动(10e-4mm/s)");
    /* y轴标题位置（设置坐标轴的方向） */
    Chart->addAxis(AxisY0, Qt::AlignLeft);
    /* 设置y轴范围 */
    AxisY0->setRange(MIN_Y0, MAX_Y0);
    /* 将splineSeries附加于y轴上 */
    LineSeries0->attachAxis(AxisY0);

    /*****************Y0_1轴设置  振动****************************/
    /* 设置显示格式 */
    AxisY0_1->setLabelFormat("%i");
    /* y轴标题 */
    AxisY0_1->setTitleText("振动1(10e-4mm/s)");
//    /* y轴标题位置（设置坐标轴的方向） */
    Chart->addAxis(AxisY0_1, Qt::AlignLeft);
    /* 设置y轴范围 */
    AxisY0_1->setRange(MIN_Y0_1, MAX_Y0_1);
    /* 将splineSeries附加于y轴上 */

    LineSeries0_1->attachAxis(AxisY0_1);
    AxisY0_1->setVisible(false);

    /*****************Y0_2轴设置  振动****************************/
    /* 设置显示格式 */
    AxisY0_2->setLabelFormat("%i");
    /* y轴标题 */
    AxisY0_2->setTitleText("振动2(10e-4mm/s)");
    /* y轴标题位置（设置坐标轴的方向） */
    Chart->addAxis(AxisY0_2, Qt::AlignLeft);
    /* 设置y轴范围 */
    AxisY0_2->setRange(MIN_Y0_2, MAX_Y0_2);
    /* 将splineSeries附加于y轴上 */
    LineSeries0_2->attachAxis(AxisY0_2);
    AxisY0_2->setVisible(false);

    /* 设置显示格式 */
    AxisX0->setLabelFormat("%.1f");
    /* x轴标题 */
//    AxisX0->setTitleText("时间/s");
    AxisX0->setTickCount(1);
    /* x轴标题位置（设置坐标轴的方向） */
    Chart->addAxis(AxisX0, Qt::AlignBottom);
    /* 设置x轴范围 */
    AxisX0->setRange(0, MAX_X);
    /* 将splineSeries附加于x轴上 */

    LineSeries0->attachAxis(AxisX0);
    LineSeries0_1->attachAxis(AxisX0);
    LineSeries0_2->attachAxis(AxisX0);
//    LineSeries0_3->attachAxis(AxisX0);

    /*****************chart设置****************************/
    /* 将图表的内容设置在图表视图上 */
    ui->graphicsView->setChart(Chart);
    /* 设置抗锯齿 */
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);

}

void Widget::CurvePlotting_Niuju()
{
    /*****************各组件实例化****************************/

    Chart1 = new QChart();
    AxisX1 = new QValueAxis();

    AxisY2 = new QValueAxis();
    AxisY3 = new QValueAxis();
    AxisY4 = new QValueAxis();

    LineSeries2 = new QSplineSeries();
    LineSeries2->setName("扭矩");
    LineSeries2->setPen(QPen(QColor(255, 0, 0), 3));
    LineSeries3 = new QSplineSeries();
    LineSeries3->setName("功率");
    LineSeries3->setPen(QPen(QColor(0, 255, 0), 3));
    LineSeries4 = new QSplineSeries();
    LineSeries4->setName("转速");
    LineSeries4->setPen(QPen(QColor(0, 0, 255), 3));

    //3

    //  Chart->setTitle("实时动态曲线示例");
    Chart1->setBackgroundBrush(QColor(255,255,255));

//    Chart1->addSeries(LineSeries1);
    Chart1->addSeries(LineSeries2);
    Chart1->addSeries(LineSeries3);
    Chart1->addSeries(LineSeries4);
//    Chart->addSeries(LineSeries5);

    /*****************Y2轴设置   扭矩****************************/
    /* 设置显示格式 */
    AxisY2->setLabelFormat("%.1f");
    /* y轴标题 */
    AxisY2->setTitleText("扭矩N·m");
    /* y轴标题位置（设置坐标轴的方向） */
    Chart1->addAxis(AxisY2, Qt::AlignLeft);
    /* 设置y轴范围 */
    AxisY2->setRange(0, MAX_Y2);
    /* 将splineSeries附加于y轴上 */
    LineSeries2->attachAxis(AxisY2);
    /*****************Y3轴设置   功率****************************/
    /* 设置显示格式 */
    AxisY3->setLabelFormat("%i");
    /* y轴标题 */
    AxisY3->setTitleText("功率W");
    /* y轴标题位置（设置坐标轴的方向） */
    Chart1->addAxis(AxisY3, Qt::AlignLeft);
    /* 设置y轴范围 */
    AxisY3->setRange(0, MAX_Y3);
    /* 将splineSeries附加于y轴上 */
    LineSeries3->attachAxis(AxisY3);
    //4 Y?
    /*****************Y4轴设置 转速****************************/
    /* 设置显示格式 */
    AxisY4->setLabelFormat("%i");
    /* y轴标题 */
    AxisY4->setTitleText("转速n");
    /* y轴标题位置（设置坐标轴的方向） */
    Chart1->addAxis(AxisY4, Qt::AlignLeft);
    /* 设置y轴范围 */
    AxisY4->setRange(0, MAX_Y4);
    /* 将splineSeries附加于y轴上 */
    LineSeries4->attachAxis(AxisY4);
    /*****************X轴设置****************************/
    /* 设置显示格式 */
    AxisX1->setLabelFormat("%.1f");
    /* x轴标题 */
//    AxisX0->setTitleText("时间/s");
    AxisX1->setTickCount(1);
    /* x轴标题位置（设置坐标轴的方向） */
    Chart1->addAxis(AxisX1, Qt::AlignBottom);
    /* 设置x轴范围 */
    AxisX1->setRange(0, MAX_X);
    /* 将splineSeries附加于x轴上 */

//    LineSeries1->attachAxis(AxisX0);
    LineSeries2->attachAxis(AxisX1);
    LineSeries3->attachAxis(AxisX1);
    LineSeries4->attachAxis(AxisX1);
//    LineSeries5->attachAxis(AxisX0);


    /*****************chart设置****************************/
    /* 将图表的内容设置在图表视图上 */
    ui->graphicsView_2->setChart(Chart1);
    /* 设置抗锯齿 */
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing, true);

}

void Widget::CurvePlotting_Wendu()
{
    /*****************各组件实例化****************************/

    Chart2 = new QChart();
    AxisX2 = new QValueAxis();


    //下面为注释的温度
//    AxisY1 = new QValueAxis();
    AxisY5 = new QValueAxis();
//    LineSeries1 = new QSplineSeries();
//    LineSeries1->setName("压力");

    LineSeries5 = new QSplineSeries();
    LineSeries5->setName("扭矩");
    LineSeries5->setPen(QPen(QColor(255,0,0), 3));

    //  Chart->setTitle("实时动态曲线示例");
    Chart2->setBackgroundBrush(QColor(255,255,255));

//    Chart2->addSeries(LineSeries1);

    Chart2->addSeries(LineSeries5);


    //    /*****************Y1轴设置   压力****************************/
    /* 设置显示格式 */
//    AxisY1->setLabelFormat("%i");
//    /* y轴标题 */
//    AxisY1->setTitleText("压力/N");
//    /* y轴标题位置（设置坐标轴的方向） */
//    Chart2->addAxis(AxisY1, Qt::AlignLeft);
//    /* 设置y轴范围 */
//    AxisY1->setRange(0, MAX_Y1);
//    /* 将splineSeries附加于y轴上 */
//    LineSeries1->attachAxis(AxisY1);
    //    /*****************Y5轴设置温度****************************/
    /* 设置显示格式 */
    AxisY5->setLabelFormat("%.1f");
    /* y轴标题 */
    AxisY5->setTitleText("扭矩");
    AxisY5->setTickCount(5);
    /* y轴标题位置（设置坐标轴的方向） */
    Chart2->addAxis(AxisY5, Qt::AlignLeft);
    /* 设置y轴范围 */
    AxisY5->setRange(0, MAX_Y5);
    /* 将splineSeries附加于y轴上 */
    LineSeries5->attachAxis(AxisY5);
    /*****************X轴设置****************************/
    /* 设置显示格式 */
    AxisX2->setLabelFormat("%.1f");
    /* x轴标题 */
    AxisX2->setTitleText("转速");
    AxisX2->setTickCount(4);
    /* x轴标题位置（设置坐标轴的方向） */
    Chart2->addAxis(AxisX2, Qt::AlignBottom);
    /* 设置x轴范围 */
    AxisX2->setRange(0, 4000);
    /* 将splineSeries附加于x轴上 */

//    LineSeries1->attachAxis(AxisX2);

    LineSeries5->attachAxis(AxisX2);


    /*****************chart设置****************************/
    /* 将图表的内容设置在图表视图上 */
    ui->graphicsView_3->setChart(Chart2);
    /* 设置抗锯齿 */
    ui->graphicsView_3->setRenderHint(QPainter::Antialiasing, true);

}

void Widget::connectModbus()                //modbus连接
{
    //扭矩仪
    int status = -1;
    fd.d1 = modbus_new_rtu("COM4", 19200, 'N', 8, 1);
    modbus_set_slave(fd.d1, 3); //设置modbus从机地址
    status = modbus_connect(fd.d1);
    if(status == -1)
    {
        qDebug() << "modbus connect failed";
//        ui->label_status_1->setStyleSheet("QLabel{background-color:rgb(255,0,0);}");
        ui->label_status_1->setText("未连接");
        ui->label_status_1->setStyleSheet("QLabel{color:rgb(255,0,0);}");
    }
    else
    {
        qDebug() << "status" << status;
        qDebug() << "connect plc success";
//        ui->label_status_1->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
        ui->label_status_1->setText("已连接");
        ui->label_status_1->setStyleSheet("QLabel{color:rgb(0,255,0);}");
    }
    modbus_set_response_timeout(fd.d1, 0, 1000000);

    //压力仪表
    int status1 = -1;
    pressure_LowMachine = modbus_new_rtu("COM2", 19200, 'N', 8, 1);
    modbus_set_slave(pressure_LowMachine, 1); //设置modbus从机地址
    status1 = modbus_connect(pressure_LowMachine);
    if(status1 == -1)
    {
        qDebug() << "pressure instrument connect failed!!!";
//        ui->label_status_pressure->setStyleSheet("QLabel{background-color:rgb(255,0,0);}");
        ui->label_status_pressure->setText("未连接");
        ui->label_status_pressure->setStyleSheet("QLabel{color:rgb(255,0,0);}");
    }
    else
    {
        qDebug() << "status" << status1;
        qDebug() << "connect pressure instrument";
//        ui->label_status_pressure->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
        ui->label_status_pressure->setText("已连接");
        ui->label_status_pressure->setStyleSheet("QLabel{color:rgb(0,255,0);}");
    }
    modbus_set_response_timeout(fd.d1, 0, 1000000);

    //温控仪表
    int status2 = -1;
    temprature_Lowmachine = modbus_new_rtu("COM1", 19200, 'N', 8, 1);
    modbus_set_slave(temprature_Lowmachine, 2); //设置modbus从机地址
    status2 = modbus_connect(temprature_Lowmachine);
    if(status2 == -1)
    {
        qDebug() << "temprature instrument connect failed!!!";
//        ui->label_status_temprature->setStyleSheet("QLabel{background-color:rgb(255,0,0);}");
        ui->label_status_temprature->setText("未连接");
        ui->label_status_temprature->setStyleSheet("QLabel{color:rgb(255,0,0);}");
    }
    else
    {
        qDebug() << "status" << status2;
        qDebug() << "connect temprature instrument";
//        ui->label_status_temprature->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
        ui->label_status_temprature->setText("已连接");
        ui->label_status_temprature->setStyleSheet("QLabel{color:rgb(0,255,0);}");
    }
    modbus_set_response_timeout(temprature_Lowmachine, 0, 1000000);
}

void Widget::connectMotoModbus()
{
    //建立连接
    int status = -1;
    fd.d2 = modbus_new_rtu("COM3", 19200, 'N', 8, 2);
    modbus_set_slave(fd.d2, 4); //设置modbus从机地址
    status = modbus_connect(fd.d2);
    if(status == -1)
    {
        qDebug() << "modbus moto connect failed";
//        ui->label_status_3->setStyleSheet("QLabel{background-color:rgb(255,0,0);}");
        ui->label_status_3->setText("未连接");
        ui->label_status_3->setStyleSheet("QLabel{color:rgb(255,0,0);}");
    }
    else
    {
        qDebug() << "status" << status;
        qDebug() << "connect plc success";
//        ui->label_status_3->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
        ui->label_status_3->setText("已连接");
        ui->label_status_3->setStyleSheet("QLabel{color:rgb(0,255,0);}");
    }
    modbus_set_response_timeout(fd.d2, 0, 1000000);
}

void Widget::connectToPython()           //通过tcp与python建立连接
{
    // 监听在指定端口上
    if (!server.listen(QHostAddress::Any,21122)) {
        qDebug() << "Server could not start.";
        return;
    }

    qDebug() << "Server is listening on port " << 21122;
    // 等待连接
    clientSocket = server.nextPendingConnection();
    while(pyAcceptFlag)
    {
        // 等待连接
        server.waitForNewConnection(50000,&is_timeout);
        if (!is_timeout)
        {

            // 接受连接
            clientSocket = server.nextPendingConnection();
//            ui->label_status_2->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
//            ui->label_status_2->setText("已连接");
//            ui->label_status_2->setStyleSheet("QLabel{color:rgb(0,255,0);}");
            qDebug()<<"connect py successfully";
            pyAcceptFlag=false;

        }else{
//            ui->label_status_2->setStyleSheet("QLabel{background-color:rgb(255,0,0);}");
//            ui->label_status_2->setText("未连接");
//            ui->label_status_2->setStyleSheet("QLabel{color:rgb(255,0,0);}");
        }
    }


}

void Widget::sendToPython()         //发送给python
{
    equipment_name = ui->lineEdit_ID->text();


    QString file0path = "F:/data/"+equipment_name+"振动0.txt";
    QFile file0(file0path);
    QString file1path = "F:/data/"+equipment_name+"振动1.txt";
    QFile file1(file1path);
    QString file2path = "F:/data/"+equipment_name+"振动2.txt";
    QFile file2(file2path);

    if(!is_timeout)
    {


        // 如果文件未打开，尝试打开文件
        if (file0.open(QIODevice::ReadWrite)) {

            qDebug() << "文件0成功打开";
            file0.seek(0);

            QByteArray data0 = file0.readAll();
            clientSocket->write(data0);
            //            qDebug()<<"data1: "<<data0;
            clientSocket->write("--EOF--");
            clientSocket->write("\n");

            file0.close();
            if(file1.open(QIODevice::ReadWrite)){
                qDebug() << "文件1成功打开";
                file1.seek(0);

                QByteArray data1 = file1.readAll();
                clientSocket->write(data1);
                //                qDebug()<<"data1: "<<data1;
                clientSocket->write("--EOF--");
                clientSocket->write("\n");
                file1.close();

                if(file2.open(QIODevice::ReadWrite)){
                    qDebug() << "文件2成功打开";
                    file2.seek(0);
                    QByteArray data2 = file2.readAll();
                    clientSocket->write(data2);
                    //                    qDebug()<<"data2: "<<data2;
                    clientSocket->write("--EOF--");
                    clientSocket->write("\n");
                    file2.close();

                    clientSocket->flush();
                    clientSocket->waitForBytesWritten();

                }

            }else{
                qDebug()<<"文件1打开失败";
            }

        } else {
            qDebug() << "文件打开失败";
        }

        // 接收来自Python的数据
        bool readyToRead = clientSocket->waitForReadyRead(5000);
        qDebug()<<"receive status: "<<readyToRead;
        if (readyToRead) {
            QByteArray receivedData = clientSocket->readAll();
            qDebug() << "Received data from Python: " << receivedData;
            QMessageBox::information(NULL, "旋转接头的结果：", receivedData, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);



        }else {
            qDebug() << "Timeout: Failed to receive data from Python.";
        }




    }
//        //关闭连接
//        clientSocket->close();
//        server.close();


}





void Widget::StatusConnect()
{
//    int cardConnectCount=0;
    //采集卡通讯状态显示
    if(cap->nErr_device == NoError)
    {
//        ui->label_status_0->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
        ui->label_status_0->setText("已连接");
        ui->label_status_0->setStyleSheet("QLabel{color:rgb(0,255,0);}");

    }
    else
    {
//        ui->label_status_0->setStyleSheet("QLabel{background-color:rgb(255,0,0);}");
        ui->label_status_0->setText("未连接");
        ui->label_status_0->setStyleSheet("QLabel{color:rgb(255,0,0);}");

//        while(cardConnectCount<=3)
//        {
//            if(cap!=nullptr){
//                delete cap;
//                cap = new Capture();
//            }
//            if(cap->nErr_device == NoError)
//            {
//                ui->label_status_0->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
//                cout<<"连接成功！！！！"<<endl;

//            }
//            else
//            {
//                ui->label_status_0->setStyleSheet("QLabel{background-color:rgb(255,0,0);}");
//                cout<<"第"<<cardConnectCount+1<<"次重连失败！！！！"<<endl;
//                cardConnectCount++;
//            }

//        }

    }
}

qreal Widget::judgeMOtoSpeed()
{
    uint16_t sp1;
    uint16_t sp2;
    uint16_t spDouble;
    while(MotoSpeedStatus!=0)
    {
        modbus_read_registers(fd.d1,0x0002,1,&sp1);  //扭矩整数部分
        modbus_read_registers(fd.d1,0x0003,1,&sp2);  //扭矩整数部分
        modbus_read_registers(fd.d1,0x0007,1,&spDouble); //转速小数部分
        qint32 spInt = static_cast<qint32>(static_cast<qint32>(sp1)<<16) | sp2;
        MotoSpeedStatus = spInt/qPow(10,spDouble);
        qDebug()<<"result: "<<MotoSpeedStatus;
        modbus_write_register(fd.d2,0x0603,0);

        MotoSpeedStatus=0;
    }
    qDebug()<<"电机转速为0";
    return MotoSpeedStatus;



}

void Widget::importPs()
{
    QString fileps = "F:/1121/test-master/password.txt";
    QFile filepassword(fileps);
    if (!filepassword.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开时间文件";

    }
    QTextStream in(&filepassword);
    password=in.readAll();
    filepassword.close();
}

void Widget::mTimeout()                   //显示时间
{
    dateTime= QDateTime::currentDateTime();//获取系统当前的时间

    str = dateTime.toString("yyyy-MM-dd hh:mm:ss");//格式化时间
    ui->lineEdit_date->setText(str);

}


/*
 * 按下开启按钮，flag置0，开始变停止字样
 * 再按下按钮，flag置1，停止变开始字样
 * */
void Widget::tab2_start()
{
    m_timer0->start(1000);
    if(start_flag)
    {
        closeMoto();
    }
    else                     //开始，将start_flag置1
    {
        bool ret = cap ->init_Capture();
        if(ret==true)
        {
            qDebug() << "采集卡开始采集";
        }

        start_flag = 1;
        connect(cap,SIGNAL(vibrationValue0(double)),this,SLOT(vibration0_ui_Slot(double)));
//        connect(cap,SIGNAL(vibrationValue1(double)),this,SLOT(vibration1_ui_Slot(double)));
//        connect(cap,SIGNAL(vibrationValue2(double)),this,SLOT(vibration2_ui_Slot(double)));
        //modbus
//        connect(pressure_thread,SIGNAL(pressureValue(qint32,uint16_t)), this, SLOT(pressureValueSlot(qint32,uint16_t)), Qt::BlockingQueuedConnection);
//        connect(temprature_thread,SIGNAL(temperatureValue(double)),this,SLOT(temperatureValueSlot(double)));
        connect(torquethread,SIGNAL(rotateSpeedValue(qint32,uint16_t)),this,SLOT(rotateSpeedValueSlot(qint32,uint16_t)));
        connect(torquethread,SIGNAL(torqueValue(qint32,uint16_t)),this,SLOT(torqueValueSlot(qint32,uint16_t)));
        connect(torquethread,SIGNAL(powerValue(uint16_t,uint16_t)),this,SLOT(powerValueSlot(uint16_t,uint16_t)));

        //        judgeMOtoSpeed();
        setMoto();
        PointCount0 = 0;
        PointCount0_1 = 0;
        PointCount0_2 = 0;
        PointCount0_3 = 0;
        PointCount1 = 0;
        PointCount2 = 0;
        PointCount3 = 0;
        PointCount4 = 0;
        PointCount5 = 0;
        LineSeries0->clear();
        LineSeries0_1->clear();
        LineSeries0_2->clear();
        LineSeries0_3->clear();
//        LineSeries1->clear();
        LineSeries2->clear();
        LineSeries3->clear();
        LineSeries4->clear();
        LineSeries5->clear();
//        AxisY4->setRange(0, MAX_Y4);
//        LineSeries4->attachAxis(AxisY4);
        cap->count0=0;
        cap->count1=0;
        cap->count2=0;
        if (file0.exists()) {
            // 删除文件
            if (!file0.remove()) {
                qDebug() << "无法删除文件";
            }

        }
        file0.close();
        if (file1.exists()) {
            // 删除文件
            if (!file1.remove()) {
                qDebug() << "无法删除文件";
            }
        }
        file1.close();
        if (file2.exists()) {
            // 删除文件
            if (!file2.remove()) {
                qDebug() << "无法删除文件";
            }
        }
        file2.close();


        ui->pushButton_0->setText("停止采集");

    }


}
/*
 * 设置开始，1，2，3，4，all的按键
 * */
void Widget::tab2_pb1()     //显示振动信号曲线，隐藏其余曲线
{
    LineSeries0->show();
    LineSeries0_1->show();
    LineSeries0_2->show();
    LineSeries0_3->show();

    LineSeries1->hide();
    LineSeries2->hide();
    LineSeries3->hide();
    LineSeries4->hide();
    LineSeries5->hide();

    AxisY0->show();
//    AxisY1->hide();
    AxisY2->hide();
    AxisY3->hide();
    AxisY4->hide();
    AxisY5->hide();
}

void Widget::tab2_pb2()
{
    LineSeries1->show();
    LineSeries0->hide();
    LineSeries0_1->hide();
    LineSeries0_2->hide();
    LineSeries0_3->hide();
    LineSeries2->hide();
    LineSeries3->hide();
    LineSeries4->hide();
    LineSeries5->show();

//    AxisY1->show();
    AxisY0->hide();
    AxisY0_1->hide();
    AxisY0_2->hide();
    AxisY2->hide();
    AxisY3->hide();
    AxisY4->hide();
    AxisY5->show();
}

void Widget::tab2_pb3()
{
    LineSeries2->show();
    LineSeries1->hide();
    LineSeries0->hide();
    LineSeries0_1->hide();
    LineSeries0_2->hide();
    LineSeries0_3->hide();
    LineSeries3->show();
    LineSeries4->show();
    LineSeries5->hide();

    AxisY2->show();
//    AxisY1->hide();
    AxisY0->hide();
    AxisY0_1->hide();
    AxisY0_2->hide();

    AxisY3->show();
    AxisY4->show();
    AxisY5->hide();
}

void Widget::tab2_pb6()
{
    LineSeries0->show();
    LineSeries0_1->show();
    LineSeries0_2->show();
    LineSeries0_3->show();
    LineSeries1->show();
    LineSeries2->show();
    LineSeries3->show();
    LineSeries4->show();
    LineSeries5->show();

    AxisY0->show();
//    AxisY1->show();
    AxisY2->show();
    AxisY3->show();
    AxisY4->show();
    AxisY5->show();
}

void Widget::serial_signal_0(int b)
{
    //    if(PointCount0 > MAX_X)
    //    {
    //        LineSeries0->remove(0);

    //        Chart->axisX()->setMin(PointCount0 - MAX_X);
    //        Chart->axisX()->setMax(PointCount0);                    // 更新X轴范围

    //    }
    //    LineSeries0->append(QPointF(PointCount0, b));  // 更新显示（随机生成10以内的一个数）
    //    PointCount0++;



    qDebug() << "bbbbb" << b;

}




void Widget::VSPStatus_slot()
{
    ui->label_status_0->setStyleSheet("QLabel{background-color:rgb(255,0,0);}");
    QMessageBox::warning(this,tr("提示"),tr("振动信号串口打开失败!"),QMessageBox::Ok);

}

void Widget::vibration0_ui_Slot(double temp1)    //振动
{
//    cap->count0++;

    if(tempV0<temp1){
        tempV0 = temp1;
    }
    QString vibrationMax = QString::number(tempV0);
    ui->lineEdit_vibration1Max->setText(vibrationMax);

//    if(cap->count0==512){

//        sendToPython();
//    }
    equipment_name = ui->lineEdit_ID->text();

    QString file0path = "F:/data/"+equipment_name+"振动0.txt";
    QFile file0(file0path);
    //存数据
    if(save_flag)
    {
        saveDatetime();
        if(! file0.open(QIODevice::Append| QIODevice::Text))  //Append追加，不会覆盖之前的文件
        {
            QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！","确定");
            return;
        }

        QTextStream out(&file0);//写入
        //    out<<str<<"\t";
        out <<temp1<<endl;


        file0.close();
    }

    //    i++;
    //更新y轴范围
    if(temp1>MAX_Y0)
    {
        MAX_Y0=temp1+10;
        AxisY0->setMax(MAX_Y0);

    }
    if(temp1<MIN_Y0)
    {
        MIN_Y0=temp1-5;
        AxisY0->setMin(MIN_Y0);

    }

    // 更新X轴范围

    if(PointCount0 > MAX_X)
    {
//        for(int i=0;i<LineSeries0->count();i++)
//        {
//            qreal x=LineSeries0->at(i).x();
//            if(x>=0&&x<=MAX_X){
//                LineSeries0->clear();
//            }
//        }
        LineSeries0->clear();
        PointCount0=0;
        Chart->axisX()->setMin(0);
        Chart->axisX()->setMax(MAX_X);


    }
    LineSeries0->append(QPointF(PointCount0, temp1));  // 更新显示（收到采集卡的数据并显示）
    PointCount0+=0.002;
}

void Widget::vibration1_ui_Slot(double temp2)
{

    if(tempV1<temp2){
        tempV1 = temp2;
    }
    QString vibration2Max = QString::number(tempV1);
    ui->lineEdit_vibration2Max->setText(vibration2Max);
    //存数据
    equipment_name = ui->lineEdit_ID->text();

    QString file1path = "F:/data/"+equipment_name+"振动1.txt";
    QFile file1(file1path);
    if(save_flag)
    {
        if(!file1.open(QIODevice::Append| QIODevice::Text))
        {
            QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！","确定");
            return;
        }
        QTextStream out(&file1);//写入
        //    out<<str<<"\t";
        out <<temp2<<endl;
        file1.close();

    }

//    if(count1==1023){

//        file1.seek(0);

//        QByteArray data1 = file1.readAll();
//        clientSocket->write(data1);
//        //            qDebug()<<"data1: "<<data0;
//        clientSocket->write("--EOF--");
//        clientSocket->write("\n");
//    }


    qDebug()<<"振动1: "<<temp2;

    //更新y轴范围


    if(temp2>MAX_Y0_1)
    {
        MAX_Y0_1= temp2+5;
        AxisY0_1->setMax(MAX_Y0_1);
    }
    if(temp2<MIN_Y0_1)
    {
        MIN_Y0_1=temp2;
        AxisY0_1->setMin(MIN_Y0_1);
    }

    if(PointCount0_1 > MAX_X)
    {
        LineSeries0_1->clear();
        Chart->axisX()->setMin(0);
        Chart->axisX()->setMax(MAX_X);
        PointCount0_1=0;                  // 更新X轴范围

    }
    LineSeries0_1->append(QPointF(PointCount0_1, temp2));  // 更新显示（收到采集卡的数据并显示）
    PointCount0_1+=0.002;

}

void Widget::vibration2_ui_Slot(double temp3)
{

    if(tempV2<temp3){
        tempV2 = temp3;
    }
    QString vibration3Max = QString::number(tempV2);
    ui->lineEdit_vibration3Max->setText(vibration3Max);
    equipment_name = ui->lineEdit_ID->text();

    QString file2path = "F:/data/"+equipment_name+"振动2.txt";
    QFile file2(file2path);
    if(temp3>MAX_Y0_2)
    {
        MAX_Y0_2=temp3;
        AxisY0_2->setMax(MAX_Y0_2);

    }
    if(temp3<MIN_Y0_2)
    {
        MIN_Y0_2=temp3;
        AxisY0_2->setMin(MIN_Y0_2);

    }

    //存数据
    if(save_flag)
    {
        if(! file2.open(QIODevice::Append| QIODevice::Text))  //Truncate截断，会覆盖之前的文件
        {
            QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！","确定");
            return;
        }
        QTextStream out(&file2);//写入
        //    out<<str<<"\t";
        out <<temp3<<endl;
        file2.close();
    }

//    if(count2==1023){
//        file2.open(QIODevice::ReadWrite);
//        file2.seek(0);

//        QByteArray data2 = file2.readAll();
//        clientSocket->write(data2);
//        //            qDebug()<<"data1: "<<data0;
//        clientSocket->write("--EOF--");
//        clientSocket->write("\n");
//        file2.close();
//        // 接收来自Python的数据
//        bool readyToRead = clientSocket->waitForReadyRead();
//        qDebug()<<"receive status: "<<readyToRead;
//        if (readyToRead) {
//            QByteArray receivedData = clientSocket->readAll();
//            qDebug() << "Received data from Python: " << receivedData;
//            QMessageBox::information(NULL, "旋转接头的结果：", receivedData, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);



//        }else {
//            qDebug() << "Timeout: Failed to receive data from Python.";
//        }
//    }

    //    qDebug()<<"振动2: "<<temp3;
    if(PointCount0_2 > MAX_X)
    {
        LineSeries0_2->clear();
        Chart->axisX()->setMin(0);
        Chart->axisX()->setMax(MAX_X);
        PointCount0_2=0;                  // 更新X轴范围
    }
    LineSeries0_2->append(QPointF(PointCount0_2, temp3));  // 更新显示（收到采集卡的数据并显示）
    PointCount0_2+=0.002;


}

void Widget::vibration3_ui_Slot(double temp4)
{
    if(save_flag)
    {
        //存数据
        QTextStream out(&file3);//写入

        out<<str<<"\t";
        out <<temp4<<endl;
        file3.close();
    }


    qDebug()<<"振动3: "<<temp4;
    if(PointCount0_3 > MAX_X)
    {

        LineSeries0_3->clear();
        Chart->axisX()->setMin(0);
        Chart->axisX()->setMax(MAX_X);
        PointCount0_3=0;                      // 更新X轴范围

    }
    LineSeries0_3->append(QPointF(PointCount0_3, temp4));  // 更新显示（收到采集卡的数据并显示）
    PointCount0_3+=0.001953125;
}

void Widget::pressureValueSlot(qint32 preInt,uint16_t preDouble)  //压力
{
    double result = preInt/qPow(10,preDouble);   //转化为小数
    qDebug()<<"真实测量值; "<<result;

    equipment_name = ui->lineEdit_ID->text();
    QString filepresspath = "F:/data/"+equipment_name+"压力.txt";
    QFile filepressure(filepresspath);

//    if(save_flag)
//    {
//        //存数据
//        if(num1<=14)
//        {
            if(! filepressure.open(QIODevice::Append| QIODevice::Text))  //Append追加，不会覆盖之前的文件
            {
                QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！","确定");
                return;
            }

            QTextStream out(&filepressure);//写入
            //    out<<"温度"<<endl;
            out <<result<<endl;
//            num1++;
//        }
        filepressure.close();
//    }

    if(result>MAX_Y1)
    {
        MAX_Y1=result;
//        AxisY1->setMax(MAX_Y1);

    }
    if(PointCount1 > MAX_X)
    {
        LineSeries1->clear();
        Chart2->axisX()->setMin(0);
        Chart2->axisX()->setMax(MAX_X);
        PointCount1=0;                     // 更新X轴范围
//        LineSeries1->remove(0);

      /*  Chart->axisX()->setMin(PointCount1 - MAX_X);
        Chart->axisX()->setMax(PointCount1);    */              // 更新X轴范围

    }
    LineSeries1->append(QPointF(PointCount1, result));  // 更新显示（随机生成10以内的一个数）
    PointCount1+=0.07;



    //    qDebug() << "ttttt: " << temp;
}

void Widget::temperatureValueSlot(double low_results)  //温度
{
    qDebug()<<"cllllllll温度为："<<low_results;
//    QString text = QString::number(low_results);
//    ui->label_temperature->setText(text);


    //存数据
    equipment_name = ui->lineEdit_ID->text();
    QString filetemppath = "F:/data/"+equipment_name+"温度.txt";
    QFile filetemprature(filetemppath);
//    if(save_flag)
//    {
//        //存数据
//        if(num<=24)
//        {
            if(! filetemprature.open(QIODevice::Append| QIODevice::Text))  //Append追加，不会覆盖之前的文件
            {
                QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！","确定");
                return;
            }

            QTextStream out(&filetemprature);//写入
            //    out<<"温度"<<endl;
            out <<low_results<<endl;
//            num++;
//        }
        filetemprature.close();
//    }


    if(low_results>MAX_Y5)
    {
        MAX_Y5=low_results;
        AxisY5->setMax(MAX_Y5);

    }
    if(PointCount5 > MAX_X)
    {

        //        Chart->axisX()->setMin(0);
        //        Chart->axisX()->setMax(MAX_X);

        //        LineSeries4->remove(0);
        LineSeries5->clear();
        Chart2->axisX()->setMin(0);
        Chart2->axisX()->setMax(MAX_X);               // 更新X轴范围
        PointCount5=0;

    }
    LineSeries5->append(QPointF(PointCount5, low_results));  // 更新显示（随机生成10以内的一个数）
    PointCount5+=0.04;
}

void Widget::rotateSpeedValueSlot(qint32 spI, uint16_t spD)  //转速
{
    modbus_motor_thread->start();
    double result = spI/qPow(10,spD);   //转化为小数
    qDebug()<<result;
    //存数据
    savespeed(result);
    speedTemp=result;


//    if(result>MAX_Y4)
//    {
//        MAX_Y4=result+20;
//        AxisY4->setMax(MAX_Y4);

//    }
    if(PointCount4 > MAX_X)
    {

//        Chart->axisX()->setMin(0);
//        Chart->axisX()->setMax(MAX_X);

//        LineSeries4->remove(0);
        LineSeries4->clear();
        Chart1->axisX()->setMin(0);
        Chart1->axisX()->setMax(MAX_X);               // 更新X轴范围
        PointCount4=0;

    }
    LineSeries4->append(QPointF(PointCount4, result));
    PointCount4+=0.04;

}

void Widget::torqueValueSlot(qint32 tqI, uint16_t tqD)   //扭矩
{
    double result = tqI/qPow(10,tqD);   //转化为小数
    qDebug()<<result;
    double abs_result = qAbs(result);
    if(tempTq<abs_result){
        tempTq = abs_result;
    }

    QString torqueMax = QString::number(tempTq);
    ui->lineEdit_torqueMax_2->setText(torqueMax);

    //存全部数据
    equipment_name = ui->lineEdit_ID->text();
    QString fileTpath = "F:/data/"+equipment_name+"扭矩完整数值.txt";
    QFile fileT(fileTpath);

    if(! fileT.open(QIODevice::Append| QIODevice::Text))  //Append追加，不会覆盖之前的文件
    {
        QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！","确定");
        return;
    }

    QTextStream out(&fileT);//写入
    //    out<<"扭矩"<<endl;
    out <<"speed: "<<speedTemp<<"\t"<<"torque: "<<abs_result<<endl;
    fileT.close();


    //存输入转速的扭矩均值、扭矩峰值


    if(save_flag&&speedTemp==modbus_motor_thread->enterSpeed){

        sum+=abs_result;
        num++;
        average = sum/num;
        qDebug()<<"average: "<<average;
        savetorque(abs_result);
    }
    if((!save_flag)&&speedTemp==modbus_motor_thread->enterSpeed)
    {
        plotTorque(average,modbus_motor_thread->enterSpeed);
        QString torqueAverage = QString::number(average);
        ui->lineEdit_torqueMax->setText(torqueAverage);



        if(torquetotxtcount==0)
        {

            qDebug()<<"average: "<<average;
            equipment_name = ui->lineEdit_ID->text();
            //            QString filetotrqueSavepath = "F:/MinXuan/1023/数据/扭矩转速.txt";
            QString filetotrqueSavepath = "F:/data/"+equipment_name+"扭矩平均和峰值.txt";
            QFile outputFile(filetotrqueSavepath);
            if (outputFile.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&outputFile);

                // Set the codec to handle Chinese characters (UTF-8)


                out << "speed: " << modbus_motor_thread->enterSpeed << "\t" << "average: " << average<<"\t"<<"torqueMax: "<<tempTq<<endl;

                outputFile.close();
                qDebug() << "Data written to" << filetotrqueSavepath;
            } else {
                qDebug() << "Error: Could not open file for writing.";
            }
            torquetotxtcount++;
        }
    }

//    if(abs_result>MAX_Y2)
//    {
//        MAX_Y2=abs_result+20;
//        AxisY2->setMax(MAX_Y2);

//    }
//    if(result<MIN_Y2m)
//    {
//        MIN_Y2m=result;
//        AxisY2->setMin(MIN_Y2m);

//    }
    if(PointCount2 > MAX_X)
    {
        LineSeries2->clear();
        Chart1->axisX()->setMin(0);
        Chart1->axisX()->setMax(MAX_X);
        PointCount2=0;

        /* LineSeries2->remove(0);

        Chart->axisX()->setMin(PointCount0 - MAX_X);
        Chart->axisX()->setMax(PointCount0);  */                  // 更新X轴范围

    }
    LineSeries2->append(QPointF(PointCount2, abs_result));  // 更新显示（随机生成10以内的一个数）
    PointCount2+=0.04;

}

void Widget::powerValueSlot(uint16_t pwI, uint16_t pwD)  //功率
{
    double result = pwI/qPow(10,pwD);   //转化为小数
    qDebug()<<"--------->功率在界面上显示： "<<result;


    if(tempPw<result){
        tempPw = result;
    }
    QString powerMax = QString::number(tempPw);
    ui->lineEdit_powerMax->setText(powerMax);

    savepower(result);
    if(result>MAX_Y3)
    {
        MAX_Y3=result+20;
        AxisY3->setMax(MAX_Y3);

    }
    if(PointCount3 > MAX_X)
    {
        LineSeries3->clear();
        Chart1->axisX()->setMin(0);
        Chart1->axisX()->setMax(MAX_X);
        PointCount3=0;
        /*LineSeries3->remove(0);

        Chart->axisX()->setMin(PointCount3 - MAX_X);
        Chart->axisX()->setMax(PointCount3);  */                  // 更新X轴范围

    }
    LineSeries3->append(QPointF(PointCount3, result));  // 更新显示（随机生成10以内的一个数）
    PointCount3+=0.04;
}

void Widget::startMoto(uint16_t d2_results)
{
    if(d2_results == 0)
    {
        ui->label_status_3->setStyleSheet("QLabel{background-color:rgb(255,0,0);}");
        //        ui->tab2_label_connect1->setText(QString::fromLocal8Bit("未连接"));
        //        d1_flag = 0;
    }
    else
    {
        ui->label_status_3->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
        //        ui->tab2_label_connect1->setText(QString::fromLocal8Bit("已连接"));
        //        d1_flag = 1;
    }

    //    if(d1_flag)
    //    {
    //        ui->tab2_btn_control1->setText(QString::fromLocal8Bit("关"));
    //    }
    //    else
    //    {
    //        ui->tab2_btn_control1->setText(QString::fromLocal8Bit("开"));
    //    }


}











//输入密码，密码119
void Widget::on_start_test_clicked()
{

    QString input = ui->lineEdit_password->text();
    if(input==password&&ui->lineEdit_p->text()!=""){
        ui->tabWidget->setCurrentIndex(1);
    }else if(input==password&&ui->lineEdit_p->text()==""){
        QMessageBox::information(this,"提示","请输入操作人员！");
    }else{
        QMessageBox::information(this,"提示","密码错误！");
        input.clear();
        ui->lineEdit_password->text();
    }

}

void Widget::changeMotoResult()
{
    entercount++;
    qDebug()<<"entercount: "<<entercount;
    num=0;sum=0;
    torquetotxtcount=0;
    QString input = ui->lineEdit_inputSpeed->text();
    modbus_motor_thread->enterSpeed = input.toInt();
    qDebug()<< " modbus_motor_thread->enterSpeed : " << modbus_motor_thread->enterSpeed ;
    if(modbus_motor_thread->enterSpeed==0)
    {
        closeMoto();
    }
    QMessageBox::question(this,"提示","已载入转速","确定");

}




/*
 * 将单个数据合并为一个表格
 * */
void Widget::on_vibrationToPy_clicked()
{

//    equipment_name = ui->lineEdit_ID->text();
//    QString file0path = "F:/data/"+equipment_name+"扭矩平均和峰值.txt";
//    QFile file(file0path);

//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        qDebug() << "无法打开文件";
//        return;
//    }

//    // 创建一个 QCustomPlot 对象
//    QCustomPlot *customPlot = new QCustomPlot();

//    // 添加一个图表层
//    customPlot->addGraph();

//    // 设置横轴和纵轴的标签
//    customPlot->xAxis->setLabel("转速");
//    customPlot->yAxis->setLabel("扭矩均值");




//    QTextStream in(&file);

//    // 逐行读取数据并添加到图表中
//    while (!in.atEnd()) {
//        QString line = in.readLine();
//        QStringList columns = line.split("\t");

//        if (columns.size() >= 4) {
//            bool x_ok, y_ok;
//            double x = columns[1].toDouble(&x_ok); // 第一列数据作为 x 值
//            double y = columns[4].toDouble(&y_ok); // 第四列数据作为 y 值

//            if (x_ok && y_ok) {
//                customPlot->graph(0)->addData(x, y); // 添加数据到图表中
//            }
//        }
//    }

//    file.close(); // 关闭文件

//    // 设置图表坐标范围
//    customPlot->xAxis->setRange(0, 3000); // 设置 x 轴范围
//    customPlot->yAxis->setRange(0, 1); // 设置 y 轴范围

//    // 显示图表
//    customPlot->replot();

//    // 假设你有一个 QMainWindow 或其他窗口来显示图表
//    // 将图表添加到布局中
//    QVBoxLayout *layout = new QVBoxLayout(this);
//    layout->addWidget(customPlot);


//    equipment_name = ui->lineEdit_ID->text();


//    QString file0path = "F:/MinXuan/1023/"+equipment_name+"振动0.txt";
//    QFile file0(file0path);
//    QString file1path = "F:/MinXuan/1023/"+equipment_name+"振动1.txt";
//    QFile file1(file1path);
//    QString file2path = "F:/MinXuan/1023/"+equipment_name+"振动2.txt";
//    QFile file2(file2path);
//    fileTpath = "F:/MinXuan/1023/"+equipment_name+"扭矩.txt";
//    QFile fileT(fileTpath);

//    fileSpath = "F:/MinXuan/1023/"+equipment_name+"转速.txt";
//    QFile fileS(fileSpath);
//    filePpath = "F:/MinXuan/1023/"+equipment_name+"功率.txt";
//    QFile fileP(filePpath);
//    fileDatepath = "F:/MinXuan/1023/"+equipment_name+"时间.txt";
//    QFile fileDate(fileDatepath);
//    if (!file0.open(QIODevice::ReadWrite)) {
//        qDebug() << "无法打开文件1";

//    }

//    // 打开第二个文件

//    if (!file1.open(QIODevice::ReadWrite)) {
//        qDebug() << "无法打开文件2";
//    }

//    // 打开第三个文件

//    if (!file2.open(QIODevice::ReadWrite)) {
//        qDebug() << "无法打开文件3";

//    }
//    if (!fileT.open(QIODevice::ReadWrite)) {
//        qDebug() << "无法打开扭矩";

//    }

//    if (!fileS.open(QIODevice::ReadWrite)) {
//        qDebug() << "无法打开转速";
//    }

//    if (!fileP.open(QIODevice::ReadWrite)) {
//        qDebug() << "无法打开功率";

//    }
//    if (!fileDate.open(QIODevice::ReadWrite)) {
//        qDebug() << "无法打开时间文件";

//    }

//    fileDate.seek(0);
//    file0.seek(1);
//    file1.seek(2);
//    file2.seek(3);
//    fileT.seek(4);
//    fileS.seek(5);
//    fileP.seek(6);

//    // 创建目标文件
//    QString outputPath = "F:/MinXuan/1023/"+equipment_name+"合并后的数据.txt";
//    QFile outputFile(outputPath);
//    if (outputFile.exists()) {
//        // 删除文件
//        if (!outputFile.remove()) {
//            qDebug() << "无法删除文件";
//        }
//    }
//    if (!outputFile.open(QIODevice::Append | QIODevice::Text)) {
//        qDebug() << "无法创建目标文件";

//    }

//    // 创建文本流
//    QTextStream outputStream(&outputFile);

//    // 逐行读取并写入第一个文件的内容
//    outputStream <<"time"<<"\t"<<"\t"<<"\t"<<"channel0"<<"\t"<<"channel1"<<"\t"<<"channel2"<<"\t"<<"torque"<<"\t"<<"speed"<<"\t"<<"power"<<"\n";
//    while (!file0.atEnd()||!file1.atEnd()||!file2.atEnd())
//    {
//        QString lineD = fileDate.readLine().trimmed();
//        QString line0 = file0.readLine().trimmed();
//        QString line1 = file1.readLine().trimmed();
//        QString line2 = file2.readLine().trimmed();
//        QString lineT = fileT.readLine().trimmed();
//        QString lineS = fileS.readLine().trimmed();
//        QString lineP = fileP.readLine().trimmed();
//        outputStream<<lineD<<"\t"<<line0<<"\t"<<line1<<"\t"<<line2<<"\t"<<lineT<<"\t"<<lineS<<"\t"<<lineP<<endl;

//    }
//    // 关闭文件
//    fileDate.close();
//    file1.close();
//    file2.close();
//    file3.close();
//    fileT.close();
//    fileS.close();
//    fileP.close();
//    outputFile.close();

//    qDebug() << "文件合并完成";


}








void Widget::on_saveData_clicked()
{
    if(!save_flag){
        ui->saveData->setText(QString::fromStdString("不保存"));
        save_flag=true;
    }else{
        ui->saveData->setText(QString::fromStdString("保存"));
        save_flag=false;
    }
}

//退出程序
void Widget::on_closeApp_clicked()
{
    QApplication* app;
    app->quit();
}


void Widget::on_closeApp_2_clicked()
{
    QApplication* app;
    app->quit();
}


void Widget::on_changePassword_clicked()
{
    ui->tabWidget->setCurrentIndex(2);

}


void Widget::on_btn_setpassOk_clicked()
{

    if(ui->lineEdit_identify->text()!="12138")
    {
         QMessageBox::critical(this,"错误","验证信息错误，请重新输入！","确定");
        ui->lineEdit_identify->clear();
         ui->lineEdit_changePassword->clear();
        return;
    }
    QString newpassword=ui->lineEdit_changePassword->text();

    qDebug()<<"password: "<<newpassword;
    QString fileps = "F:/1121/test-master/password.txt";
    QFile filepassword(fileps);
    if (!filepassword.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "无法打开时间文件";

    }
    QTextStream out(&filepassword);
    out<<newpassword;
    filepassword.close();
    importPs();
    ui->tabWidget->setCurrentIndex(0);

}

