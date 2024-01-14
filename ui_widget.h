/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qchartview.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_7;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_5;
    QLabel *label_title;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_8;
    QLineEdit *lineEdit_p;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    QLineEdit *lineEdit_password;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *start_test;
    QPushButton *closeApp_2;
    QPushButton *changePassword;
    QWidget *tab_2;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_6;
    QLineEdit *lineEdit_date;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_0;
    QLineEdit *lineEdit_ID;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_inputSpeed;
    QLineEdit *lineEdit_inputSpeed;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_inputSpeed_2;
    QLineEdit *lineEdit_inputSpeed_2;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_inputSpeed_3;
    QLineEdit *lineEdit_inputSpeed_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_0;
    QPushButton *closeApp;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *saveData;
    QPushButton *vibrationToPy;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_20;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_16;
    QLabel *label_status_0;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_19;
    QLabel *label_status_temprature;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_17;
    QLabel *label_status_pressure;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_18;
    QLabel *label_status_3;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_14;
    QLabel *label_status_1;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_14;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_torqueMax;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    QLineEdit *lineEdit_powerMax;
    QLabel *label_5;
    QLineEdit *lineEdit_torqueMax_2;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_12;
    QLineEdit *lineEdit_vibration1Max;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_13;
    QLineEdit *lineEdit_vibration2Max;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_15;
    QLineEdit *lineEdit_vibration3Max;
    QChartView *graphicsView;
    QVBoxLayout *verticalLayout_8;
    QChartView *graphicsView_2;
    QChartView *graphicsView_3;
    QWidget *tab_3;
    QLineEdit *lineEdit_changePassword;
    QLabel *label;
    QPushButton *btn_setpassOk;
    QLabel *label_2;
    QLineEdit *lineEdit_identify;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1298, 765);
        gridLayout_7 = new QGridLayout(Widget);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/image/Image_1698416347918_edit_521250832624108.jpg);\n"
""));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_5 = new QGridLayout(tab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_title = new QLabel(tab);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        QFont font;
        font.setPointSize(26);
        font.setBold(false);
        label_title->setFont(font);
        label_title->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 255, 255);\n"
"color: rgb(255, 85, 0);"));
        label_title->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_title, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 170, 255, 150);\n"
"font: 15pt \"Microsoft YaHei UI\";\n"
""));
        groupBox_2->setAlignment(Qt::AlignCenter);
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font1.setPointSize(15);
        font1.setBold(false);
        font1.setItalic(false);
        label_8->setFont(font1);
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_12->addWidget(label_8);

        lineEdit_p = new QLineEdit(groupBox_2);
        lineEdit_p->setObjectName(QString::fromUtf8("lineEdit_p"));
        lineEdit_p->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/image/1.jpg);\n"
"\n"
" border-radius: 10px;  border: 2px groove gray;\n"
"        border-style: outset;"));

        horizontalLayout_12->addWidget(lineEdit_p);


        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font1);
        label_11->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(255, 255, 255);\n"
""));

        horizontalLayout_11->addWidget(label_11);

        lineEdit_password = new QLineEdit(groupBox_2);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setStyleSheet(QString::fromUtf8("     border-radius: 10px;  border: 2px groove gray;\n"
"background-image: url(:/new/prefix1/image/1.jpg);\n"
"        border-style: outset;"));
        lineEdit_password->setEchoMode(QLineEdit::Password);

        horizontalLayout_11->addWidget(lineEdit_password);


        verticalLayout_4->addLayout(horizontalLayout_11);


        verticalLayout_6->addLayout(verticalLayout_4);


        gridLayout_3->addLayout(verticalLayout_6, 0, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        start_test = new QPushButton(groupBox_2);
        start_test->setObjectName(QString::fromUtf8("start_test"));
        start_test->setFont(font1);
        start_test->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(255, 85, 0);\n"
"\n"
"\n"
"        border-radius: 10px;  border: 2px groove gray;\n"
"        border-style: outset;\n"
""));
        start_test->setIconSize(QSize(128, 128));

        horizontalLayout_13->addWidget(start_test);

        closeApp_2 = new QPushButton(groupBox_2);
        closeApp_2->setObjectName(QString::fromUtf8("closeApp_2"));
        closeApp_2->setFont(font1);
        closeApp_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);\n"
"color: rgb(255, 85, 0);\n"
"     border-radius: 10px;  border: 2px groove gray;\n"
"        border-style: outset;"));

        horizontalLayout_13->addWidget(closeApp_2);

        changePassword = new QPushButton(groupBox_2);
        changePassword->setObjectName(QString::fromUtf8("changePassword"));
        changePassword->setFont(font1);
        changePassword->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);\n"
"color: rgb(255, 85, 0);\n"
"     border-radius: 10px;  border: 2px groove gray;\n"
"        border-style: outset;"));

        horizontalLayout_13->addWidget(changePassword);


        gridLayout_3->addLayout(horizontalLayout_13, 1, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_2, 1, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_6 = new QGridLayout(tab_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_5 = new QGroupBox(tab_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        gridLayout_2 = new QGridLayout(groupBox_5);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font2;
        font2.setBold(true);
        label_6->setFont(font2);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_15->addWidget(label_6);

        lineEdit_date = new QLineEdit(groupBox_5);
        lineEdit_date->setObjectName(QString::fromUtf8("lineEdit_date"));
        lineEdit_date->setStyleSheet(QString::fromUtf8("     border-radius: 10px;  border: 2px groove gray;\n"
"background-image: url(:/new/prefix1/image/1.jpg);\n"
"        border-style: outset;\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout_15->addWidget(lineEdit_date);


        verticalLayout_7->addLayout(horizontalLayout_15);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_0 = new QLabel(groupBox_5);
        label_0->setObjectName(QString::fromUtf8("label_0"));
        label_0->setFont(font2);
        label_0->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_9->addWidget(label_0);

        lineEdit_ID = new QLineEdit(groupBox_5);
        lineEdit_ID->setObjectName(QString::fromUtf8("lineEdit_ID"));
        lineEdit_ID->setStyleSheet(QString::fromUtf8("     border-radius: 10px;  border: 2px groove gray;\n"
"background-image: url(:/new/prefix1/image/1.jpg);\n"
"        border-style: outset;\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout_9->addWidget(lineEdit_ID);


        verticalLayout_7->addLayout(horizontalLayout_9);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_inputSpeed = new QLabel(groupBox_5);
        label_inputSpeed->setObjectName(QString::fromUtf8("label_inputSpeed"));
        QFont font3;
        font3.setPointSize(9);
        font3.setBold(false);
        label_inputSpeed->setFont(font3);
        label_inputSpeed->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(255, 255, 255);\n"
""));

        horizontalLayout_2->addWidget(label_inputSpeed);

        lineEdit_inputSpeed = new QLineEdit(groupBox_5);
        lineEdit_inputSpeed->setObjectName(QString::fromUtf8("lineEdit_inputSpeed"));
        lineEdit_inputSpeed->setStyleSheet(QString::fromUtf8("     border-radius: 10px;  border: 2px groove gray;\n"
"background-image: url(:/new/prefix1/image/1.jpg);\n"
"        border-style: outset;\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout_2->addWidget(lineEdit_inputSpeed);


        verticalLayout_7->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(verticalLayout_7, 0, 0, 1, 1);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_inputSpeed_2 = new QLabel(groupBox_5);
        label_inputSpeed_2->setObjectName(QString::fromUtf8("label_inputSpeed_2"));
        label_inputSpeed_2->setFont(font3);
        label_inputSpeed_2->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(255, 255, 255);\n"
""));

        horizontalLayout_21->addWidget(label_inputSpeed_2);

        lineEdit_inputSpeed_2 = new QLineEdit(groupBox_5);
        lineEdit_inputSpeed_2->setObjectName(QString::fromUtf8("lineEdit_inputSpeed_2"));
        lineEdit_inputSpeed_2->setStyleSheet(QString::fromUtf8("     border-radius: 10px;  border: 2px groove gray;\n"
"background-image: url(:/new/prefix1/image/1.jpg);\n"
"        border-style: outset;\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout_21->addWidget(lineEdit_inputSpeed_2);


        gridLayout_2->addLayout(horizontalLayout_21, 1, 0, 1, 1);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_inputSpeed_3 = new QLabel(groupBox_5);
        label_inputSpeed_3->setObjectName(QString::fromUtf8("label_inputSpeed_3"));
        label_inputSpeed_3->setFont(font3);
        label_inputSpeed_3->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(255, 255, 255);\n"
""));

        horizontalLayout_22->addWidget(label_inputSpeed_3);

        lineEdit_inputSpeed_3 = new QLineEdit(groupBox_5);
        lineEdit_inputSpeed_3->setObjectName(QString::fromUtf8("lineEdit_inputSpeed_3"));
        lineEdit_inputSpeed_3->setStyleSheet(QString::fromUtf8("     border-radius: 10px;  border: 2px groove gray;\n"
"background-image: url(:/new/prefix1/image/1.jpg);\n"
"        border-style: outset;\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout_22->addWidget(lineEdit_inputSpeed_3);


        gridLayout_2->addLayout(horizontalLayout_22, 2, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_0 = new QPushButton(tab_2);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        QFont font4;
        font4.setPointSize(16);
        font4.setBold(true);
        pushButton_0->setFont(font4);
        pushButton_0->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
"color: rgb(255, 0, 0);\n"
"\n"
"     border-radius: 10px;  border: 2px groove gray;\n"
"        border-style: outset;"));

        horizontalLayout->addWidget(pushButton_0);

        closeApp = new QPushButton(tab_2);
        closeApp->setObjectName(QString::fromUtf8("closeApp"));
        closeApp->setFont(font4);
        closeApp->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);\n"
"color: rgb(255, 85, 0);\n"
"     border-radius: 10px;  border: 2px groove gray;\n"
"        border-style: outset;"));

        horizontalLayout->addWidget(closeApp);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        saveData = new QPushButton(tab_2);
        saveData->setObjectName(QString::fromUtf8("saveData"));
        QFont font5;
        font5.setPointSize(15);
        font5.setBold(true);
        saveData->setFont(font5);
        saveData->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
"color: rgb(255, 85, 0);\n"
"     border-radius: 10px;  border: 2px groove gray;\n"
"        border-style: outset;"));
        saveData->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(saveData);

        vibrationToPy = new QPushButton(tab_2);
        vibrationToPy->setObjectName(QString::fromUtf8("vibrationToPy"));
        vibrationToPy->setFont(font5);
        vibrationToPy->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
"color: rgb(255, 85, 0);\n"
"     border-radius: 10px;  border: 2px groove gray;\n"
"        border-style: outset;"));
        vibrationToPy->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(vibrationToPy);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);


        gridLayout_6->addLayout(verticalLayout_2, 0, 0, 2, 1);

        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font6;
        font6.setPointSize(12);
        font6.setBold(true);
        groupBox->setFont(font6);
        groupBox->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        verticalLayout_10 = new QVBoxLayout(groupBox);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font6);
        label_16->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_10->addWidget(label_16);

        label_status_0 = new QLabel(groupBox);
        label_status_0->setObjectName(QString::fromUtf8("label_status_0"));
        label_status_0->setEnabled(true);
        label_status_0->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 0, 0);\n"
"     border-radius: 10px;  border: 2px groove gray;\n"
"        border-style: outset;"));

        horizontalLayout_10->addWidget(label_status_0);


        horizontalLayout_20->addLayout(horizontalLayout_10);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font6);
        label_19->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_16->addWidget(label_19);

        label_status_temprature = new QLabel(groupBox);
        label_status_temprature->setObjectName(QString::fromUtf8("label_status_temprature"));
        label_status_temprature->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);\n"
"     border-radius: 10px;  border: 2px groove gray;\n"
"        border-style: outset;"));

        horizontalLayout_16->addWidget(label_status_temprature);


        horizontalLayout_20->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font6);
        label_17->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(label_17);

        label_status_pressure = new QLabel(groupBox);
        label_status_pressure->setObjectName(QString::fromUtf8("label_status_pressure"));
        label_status_pressure->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);\n"
"     border-radius: 10px;  border: 2px groove gray;\n"
"        border-style: outset;"));

        horizontalLayout_17->addWidget(label_status_pressure);


        horizontalLayout_20->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font6);
        label_18->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_18->addWidget(label_18);

        label_status_3 = new QLabel(groupBox);
        label_status_3->setObjectName(QString::fromUtf8("label_status_3"));
        label_status_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);\n"
"     border-radius: 10px;  border: 2px groove gray;\n"
"        border-style: outset;"));

        horizontalLayout_18->addWidget(label_status_3);


        horizontalLayout_20->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font6);
        label_14->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_19->addWidget(label_14);

        label_status_1 = new QLabel(groupBox);
        label_status_1->setObjectName(QString::fromUtf8("label_status_1"));
        label_status_1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);\n"
"     border-radius: 10px;  border: 2px groove gray;\n"
"        border-style: outset;"));

        horizontalLayout_19->addWidget(label_status_1);


        horizontalLayout_20->addLayout(horizontalLayout_19);


        verticalLayout_10->addLayout(horizontalLayout_20);


        gridLayout_6->addWidget(groupBox, 0, 1, 1, 1);

        groupBox_4 = new QGroupBox(tab_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font2);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(label_4);

        lineEdit_torqueMax = new QLineEdit(groupBox_4);
        lineEdit_torqueMax->setObjectName(QString::fromUtf8("lineEdit_torqueMax"));
        lineEdit_torqueMax->setStyleSheet(QString::fromUtf8("     border-radius: 10px;  border: 2px groove gray;\n"
"background-image: url(:/new/prefix1/image/1.jpg);\n"
"        border-style: outset;\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout_4->addWidget(lineEdit_torqueMax);


        horizontalLayout_14->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font2);
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_5->addWidget(label_10);

        lineEdit_powerMax = new QLineEdit(groupBox_4);
        lineEdit_powerMax->setObjectName(QString::fromUtf8("lineEdit_powerMax"));
        lineEdit_powerMax->setStyleSheet(QString::fromUtf8("     border-radius: 10px;  border: 2px groove gray;\n"
"background-image: url(:/new/prefix1/image/1.jpg);\n"
"        border-style: outset;\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout_5->addWidget(lineEdit_powerMax);


        horizontalLayout_14->addLayout(horizontalLayout_5);


        gridLayout_4->addLayout(horizontalLayout_14, 0, 0, 1, 2);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font2);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_4->addWidget(label_5, 1, 0, 1, 1);

        lineEdit_torqueMax_2 = new QLineEdit(groupBox_4);
        lineEdit_torqueMax_2->setObjectName(QString::fromUtf8("lineEdit_torqueMax_2"));
        lineEdit_torqueMax_2->setStyleSheet(QString::fromUtf8("     border-radius: 10px;  border: 2px groove gray;\n"
"background-image: url(:/new/prefix1/image/1.jpg);\n"
"        border-style: outset;\n"
"color: rgb(0, 0, 0);"));

        gridLayout_4->addWidget(lineEdit_torqueMax_2, 1, 1, 1, 1);


        gridLayout_6->addWidget(groupBox_4, 1, 1, 1, 1);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font2);
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_6->addWidget(label_12);

        lineEdit_vibration1Max = new QLineEdit(groupBox_3);
        lineEdit_vibration1Max->setObjectName(QString::fromUtf8("lineEdit_vibration1Max"));
        lineEdit_vibration1Max->setStyleSheet(QString::fromUtf8("     border-radius: 10px;  border: 2px groove gray;\n"
"background-image: url(:/new/prefix1/image/1.jpg);\n"
"        border-style: outset;\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout_6->addWidget(lineEdit_vibration1Max);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font2);
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_7->addWidget(label_13);

        lineEdit_vibration2Max = new QLineEdit(groupBox_3);
        lineEdit_vibration2Max->setObjectName(QString::fromUtf8("lineEdit_vibration2Max"));
        lineEdit_vibration2Max->setStyleSheet(QString::fromUtf8("     border-radius: 10px;  border: 2px groove gray;\n"
"background-image: url(:/new/prefix1/image/1.jpg);\n"
"        border-style: outset;\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout_7->addWidget(lineEdit_vibration2Max);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font2);
        label_15->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_8->addWidget(label_15);

        lineEdit_vibration3Max = new QLineEdit(groupBox_3);
        lineEdit_vibration3Max->setObjectName(QString::fromUtf8("lineEdit_vibration3Max"));
        lineEdit_vibration3Max->setStyleSheet(QString::fromUtf8("     border-radius: 10px;  border: 2px groove gray;\n"
"background-image: url(:/new/prefix1/image/1.jpg);\n"
"        border-style: outset;\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout_8->addWidget(lineEdit_vibration3Max);


        verticalLayout_3->addLayout(horizontalLayout_8);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);


        verticalLayout_9->addWidget(groupBox_3);

        graphicsView = new QChartView(tab_2);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout_9->addWidget(graphicsView);


        gridLayout_6->addLayout(verticalLayout_9, 2, 0, 1, 1);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        graphicsView_2 = new QChartView(tab_2);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));

        verticalLayout_8->addWidget(graphicsView_2);

        graphicsView_3 = new QChartView(tab_2);
        graphicsView_3->setObjectName(QString::fromUtf8("graphicsView_3"));

        verticalLayout_8->addWidget(graphicsView_3);


        gridLayout_6->addLayout(verticalLayout_8, 2, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        lineEdit_changePassword = new QLineEdit(tab_3);
        lineEdit_changePassword->setObjectName(QString::fromUtf8("lineEdit_changePassword"));
        lineEdit_changePassword->setGeometry(QRect(250, 70, 121, 31));
        lineEdit_changePassword->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_changePassword->setEchoMode(QLineEdit::Password);
        label = new QLabel(tab_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 70, 91, 31));
        QFont font7;
        font7.setPointSize(14);
        label->setFont(font7);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        btn_setpassOk = new QPushButton(tab_3);
        btn_setpassOk->setObjectName(QString::fromUtf8("btn_setpassOk"));
        btn_setpassOk->setGeometry(QRect(400, 80, 75, 23));
        btn_setpassOk->setFont(font7);
        btn_setpassOk->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 30, 91, 31));
        label_2->setFont(font7);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_identify = new QLineEdit(tab_3);
        lineEdit_identify->setObjectName(QString::fromUtf8("lineEdit_identify"));
        lineEdit_identify->setGeometry(QRect(250, 30, 121, 31));
        lineEdit_identify->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_identify->setEchoMode(QLineEdit::Password);
        tabWidget->addTab(tab_3, QString());

        verticalLayout_5->addWidget(tabWidget);


        gridLayout_7->addLayout(verticalLayout_5, 0, 0, 1, 1);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label_title->setText(QCoreApplication::translate("Widget", "\351\227\275\346\227\213\347\247\221\346\212\200\350\202\241\344\273\275\346\234\211\351\231\220\345\205\254\345\217\270\346\225\260\346\215\256\346\265\213\350\257\225\347\263\273\347\273\237", nullptr));
#if QT_CONFIG(statustip)
        groupBox_2->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        groupBox_2->setTitle(QString());
        label_8->setText(QCoreApplication::translate("Widget", "\346\223\215\344\275\234\344\272\272\345\221\230\357\274\232", nullptr));
        lineEdit_p->setText(QString());
        label_11->setText(QCoreApplication::translate("Widget", "\345\257\206\347\240\201\357\274\232", nullptr));
        lineEdit_password->setText(QString());
        start_test->setText(QCoreApplication::translate("Widget", "\347\241\256\345\256\232", nullptr));
        closeApp_2->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
        changePassword->setText(QCoreApplication::translate("Widget", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Widget", "Tab 1", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("Widget", "\350\276\223\345\205\245", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "\346\265\213\350\257\225\346\227\245\346\234\237\357\274\232", nullptr));
        label_0->setText(QCoreApplication::translate("Widget", "\346\240\267\345\223\201\347\274\226\345\217\267\357\274\232", nullptr));
        label_inputSpeed->setText(QCoreApplication::translate("Widget", "\350\276\223\345\205\245\347\224\265\346\234\272\350\275\254\351\200\237\357\274\232", nullptr));
        label_inputSpeed_2->setText(QCoreApplication::translate("Widget", "\346\270\251\345\272\246\357\274\232", nullptr));
        label_inputSpeed_3->setText(QCoreApplication::translate("Widget", "\345\216\213\345\212\233\357\274\232", nullptr));
        pushButton_0->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        closeApp->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
        saveData->setText(QCoreApplication::translate("Widget", "\344\277\235\345\255\230", nullptr));
        vibrationToPy->setText(QCoreApplication::translate("Widget", "\345\220\210\345\271\266\346\225\260\346\215\256", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\351\200\232\350\256\257\347\212\266\346\200\201", nullptr));
        label_16->setText(QCoreApplication::translate("Widget", "\351\207\207\351\233\206\345\215\241\357\274\232", nullptr));
        label_status_0->setText(QString());
        label_19->setText(QCoreApplication::translate("Widget", "\346\270\251\345\272\246\344\273\252\350\241\250:", nullptr));
        label_status_temprature->setText(QString());
        label_17->setText(QCoreApplication::translate("Widget", "\345\216\213\345\212\233\344\273\252\350\241\250:", nullptr));
        label_status_pressure->setText(QString());
        label_18->setText(QCoreApplication::translate("Widget", "\347\224\265\346\234\272:", nullptr));
        label_status_3->setText(QString());
        label_14->setText(QCoreApplication::translate("Widget", "\346\211\255\347\237\251\344\273\252:", nullptr));
        label_status_1->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("Widget", "\346\211\255\347\237\251\344\273\252\345\263\260\345\200\274", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\346\211\255\347\237\251\345\235\207\345\200\274", nullptr));
        label_10->setText(QCoreApplication::translate("Widget", "\345\212\237\347\216\207\345\263\260\345\200\274\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "\346\211\255\347\237\251\345\263\260\345\200\274", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Widget", "\346\214\257\345\212\250\345\263\260\345\200\274\357\274\232", nullptr));
        label_12->setText(QCoreApplication::translate("Widget", "\346\214\257\345\212\250\351\200\232\351\201\2231\345\263\260\345\200\274\357\274\232", nullptr));
        label_13->setText(QCoreApplication::translate("Widget", "\346\214\257\345\212\250\351\200\232\351\201\2232\345\263\260\345\200\274\357\274\232", nullptr));
        label_15->setText(QCoreApplication::translate("Widget", "\346\214\257\345\212\250\351\200\232\351\201\2233\345\263\260\345\200\274\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Widget", "Tab 2", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\351\207\215\350\256\276\345\257\206\347\240\201\357\274\232", nullptr));
        btn_setpassOk->setText(QCoreApplication::translate("Widget", "\347\241\256\350\256\244", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\351\252\214\350\257\201\344\277\241\346\201\257\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("Widget", "Tab3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
