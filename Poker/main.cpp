#include "mainwindow.h"

#include <QApplication>
#include "iostream"


int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //QPixmap myPixmap( ":/images/poker-holdem-karty.jpg" );
    //label1->setPixmap( myPixmap );

    return a.exec();
}
