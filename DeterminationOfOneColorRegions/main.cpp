#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindow w("D:\\git\\DeterminationOfOneColorRegions\\test.jpg");
    MainWindow w("/media/D/git/DeterminationOfOneColorRegions/test.jpg");
    w.show();

    return a.exec();
}
