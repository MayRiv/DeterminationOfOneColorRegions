#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QImage>
#include <QDebug>
#include <stdio.h>
#include <QByteArray>
#include <QRgb>
#include <QVector>
#include <QPair>
MainWindow::MainWindow(QString path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    source(path)
{ 
    qDebug() << path;
    //source = new QFile(path);
    if (!source.open(QIODevice::ReadOnly))
        qDebug() << QString("Can't open %1.").arg(path);
    QByteArray buffer = source.readAll();
    qDebug() << buffer.size();
    image = QImage::fromData(buffer,"JPG");
    ui->setupUi(this);
    updateImage();
    analyzedPixels = new short* [image.width() ];
    for (int i = 0; i < image.width(); i++)
    {
        analyzedPixels[i] = new short  [image.height()];
        for (int j = 0; j <  image.height(); j++)
        {
            analyzedPixels[i][j] = 0;
        }
    }

    trashHold = 20;
}

MainWindow::~MainWindow()
{
    delete ui;
    for (int i = 0; i < image.width(); i++)
       delete analyzedPixels[i];
    delete[] analyzedPixels;
}



void MainWindow::on_pushButton_clicked()
{

    analyze(0,0,qRgb(0,0,0));
    for (int i = 0; i < image.width(); i++)
        for (int j = 0; j < image.height(); j++)
            analyzedPixels[i][j]=0;
    analyze2(0,0,qRgb(0,0,0));
//    analyze();
    markBoundaryPixels();
    for (int i = 0; i < image.width(); i++)
        for (int j = 0; j < image.height(); j++)
            analyzedPixels[i][j]=0;
    updateImage();
}

void MainWindow::updateImage()
{
    ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::line(int x1, int y1, int x2, int y2, QRgb color)
{
    int xLength = x2 - x1;
    int yLength = y2 - y1;
    int max = abs(xLength);
    if (max < abs(yLength)) max = abs(yLength);
    float x = (float)x1;
    float y = (float)y1;
    for (int j = 0; j < max; j++ )
    {
        image.setPixel((int)x,(int)y,color);
        x+=xLength / max;
        y+=yLength / max;
    }
}

int MainWindow::max(int a, int b)
{
    if (a > b) return a;
    else return b;
}



void MainWindow::analyze(int x, int y, QRgb previousValue)
{
    analyzedPixels[x][y]++;
    QRgb value = image.pixel(x,y);
    if (abs(qRed(value) - qRed(previousValue)) > trashHold ||
        abs(qGreen(value) - qGreen(previousValue)) > trashHold ||
        abs(qBlue(value) - qBlue(previousValue)) > trashHold)
    {
        boundaryPixels.push_back(QPair<int,int>(x,y));
    }

    if ((y + 1) < image.height() && analyzedPixels[x][y + 1] != 2) analyze(x, y + 1, value);
    if ((x + 1) < image.width()  && analyzedPixels[x + 1][y] != 2) analyze(x + 1, y, value);

}

void MainWindow::analyze2(int x, int y, QRgb previousValue)
{
    analyzedPixels[x][y]++;
    //qDebug() << analyzedPixels[x][y];
    QRgb value = image.pixel(x,y);
    if (abs(qRed(value) - qRed(previousValue)) > trashHold ||
        abs(qGreen(value) - qGreen(previousValue)) > trashHold ||
        abs(qBlue(value) - qBlue(previousValue)) > trashHold)
    {
        boundaryPixels.push_back(QPair<int,int>(x,y));
    }

    if ((x + 1) < image.width()  && analyzedPixels[x + 1][y] != 2) analyze2(x + 1, y, value);
    if ((y + 1) < image.height() && analyzedPixels[x][y + 1] != 2) analyze2(x, y + 1, value);
}



void MainWindow::analyze()
{
    for (int j= 1; j < image.height() - 1; j+= 1)
        for (int i=1; i < image.width() - 1; i+=1)
        {
            if (   (abs(qRed(image.pixel(i,j)) - qRed(image.pixel(i - 1,j))) > trashHold        ||
                    abs(qGreen(image.pixel(i,j)) - qGreen(image.pixel(i - 1,j))) > trashHold    ||
                    abs(qBlue(image.pixel(i,j)) - qBlue(image.pixel(i - 1,j))) > trashHold)     ||

                   (abs(qRed(image.pixel(i,j)) - qRed(image.pixel(i + 1,j))) > trashHold        ||
                    abs(qGreen(image.pixel(i,j)) - qGreen(image.pixel(i + 1,j))) > trashHold    ||
                    abs(qBlue(image.pixel(i,j)) - qBlue(image.pixel(i + 1,j))) > trashHold)     ||

                    (abs(qRed(image.pixel(i,j)) - qRed(image.pixel(i,j - 1))) > trashHold       ||
                     abs(qGreen(image.pixel(i,j)) - qGreen(image.pixel(i,j - 1))) > trashHold   ||
                     abs(qBlue(image.pixel(i,j)) - qBlue(image.pixel(i,j - 1))) > trashHold)    ||

                    (abs(qRed(image.pixel(i,j)) - qRed(image.pixel(i,j + 1))) > trashHold       ||
                     abs(qGreen(image.pixel(i,j)) - qGreen(image.pixel(i,j + 1))) > trashHold   ||
                     abs(qBlue(image.pixel(i,j)) - qBlue(image.pixel(i,j + 1))) > trashHold)
                )
            {
                 boundaryPixels.push_back(QPair<int,int>(i,j));
            }
        }
}

void MainWindow::markBoundaryPixels()
{
    //line(0,0,5,5,qRgb(225,5,5));
    for (int i = 0; i < boundaryPixels.size() - 1; i++)
    {
        //line(boundaryPixels[i].first,boundaryPixels[i].second,boundaryPixels[i+1].first,boundaryPixels[i+1].second,qRgb(225,5,5));
        image.setPixel(boundaryPixels[i].first,boundaryPixels[i].second,qRgb(225,5,5));
    }



}
