#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QThread>
#include <QSerialPort>
#include "src/modbus.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QMutex>
#include "QFile"

typedef struct
{
    modbus_t* d1;
    modbus_t* d2;
}plc_fds;

extern plc_fds fd;
class SerialThread : public QThread
{
    Q_OBJECT
public:
    explicit SerialThread(QObject *parent = nullptr);
    void ReadData();
    QList<QByteArray> data_vibration;

protected:
    void run();

signals:
    void serial_signal(int);
    void VSPStatus();


public slots:

private:
    QSerialPort *serial;


};

class ModbusThread : public QThread
{
    Q_OBJECT
public:
    explicit ModbusThread(QObject *parent = nullptr);

protected:
    void run();

signals:
    void pressureValue(qint32,uint16_t);


public slots:

private:

};
class TempratureThread : public QThread
{
    Q_OBJECT
public:
    explicit TempratureThread(QObject *parent = nullptr);

protected:
    void run();

signals:

    void temperatureValue(double);


public slots:

private:

};

class TorqueThread : public QThread
{
    Q_OBJECT
public:
    explicit TorqueThread(QObject *parent = nullptr);

protected:
    void run();

signals:

    void rotateSpeedValue(qint32,uint16_t);
    void torqueValue(qint32,uint16_t);
    void powerValue(uint16_t,uint16_t);
//    void temperatureValue(uint16_t);

public slots:

private:

};

class ModbusMotorThread : public QThread
{
    Q_OBJECT
public:
    explicit ModbusMotorThread(QObject *parent = nullptr);
    ~ModbusMotorThread();
    void exitThread();
    bool isStop;
    uint16_t enterSpeed;
protected:
    void run();

signals:
    void startMoto(uint16_t);


public slots:

private:


};
#endif // THREAD_H
