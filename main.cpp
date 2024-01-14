#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
    qRegisterMetaType<uint16_t>("uint16_t");
    qRegisterMetaType<I32>("I32");
    w.show();

    return a.exec();
}
