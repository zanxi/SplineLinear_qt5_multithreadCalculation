#include "mainwindow.h"
#include <QApplication>

#include "Workers/responder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Responder pesp;



    return a.exec();
}
