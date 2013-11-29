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
#include <QFileDialog>
MainWindow::MainWindow(QString path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    source(path)
{ 
    analyzedPixelsVertical   = 0;
    analyzedPixelsHorizontal = 0;

    qDebug() << path;
    //source = new QFile(path);
    if (!source.open(QIODevice::ReadOnly))
        qDebug() << QString("Can't open %1.").arg(path);
    QByteArray buffer = source.readAll();
    qDebug() << buffer.size();
    image = QImage::fromData(buffer,"JPG");
    ui->setupUi(this);
    updateImage();
    analyzedPixelsVertical = new bool* [image.width() ];
        analyzedPixelsHorizontal = new bool* [image.width() ];
        for (int i = 0; i < image.width(); i++)
        {
            analyzedPixelsVertical[i] = new bool  [image.height()];
            analyzedPixelsHorizontal[i] = new bool  [image.height()];
            for (int j = 0; j <  image.height(); j++)
            {
                analyzedPixelsVertical[i][j] = false;
                analyzedPixelsHorizontal[i][j] = false;
            }
        }
    trashHold = 20;

}

MainWindow::~MainWindow()
{
    delete ui;
    for (int i = 0; i < image.width(); i++)
    {
        delete analyzedPixelsVertical[i];
        delete analyzedPixelsHorizontal[i];
    }
    delete[] analyzedPixelsVertical;
    delete[] analyzedPixelsHorizontal;

}



void MainWindow::on_pushButton_clicked()
{

    analyze(0,0,qRgb(0,0,0));
    markBoundaryPixels();
    updateImage();
}

void MainWindow::updateImage()
{
    ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::openImage()
{
    qDebug() << "Worked.";
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
    QRgb value = image.pixel(x,y);
    if (abs(qRed(value) - qRed(previousValue)) > trashHold ||
        abs(qGreen(value) - qGreen(previousValue)) > trashHold ||
        abs(qBlue(value) - qBlue(previousValue)) > trashHold)
    {
        boundaryPixels.push_back(QPair<int,int>(x,y));
    }

    if ((x + 1) < image.width()  && !analyzedPixelsHorizontal[x + 1][y])
    {
        analyzedPixelsHorizontal[x + 1][y] = true;
        analyze(x + 1, y, value);
    }
    if ((y + 1) < image.height() && !analyzedPixelsVertical[x][y + 1])
    {
        analyzedPixelsVertical[x][y + 1] = true;
        analyze(x, y + 1, value);
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

void MainWindow::on_actionOpen_triggered()
{
    source.close();
    boundaryPixels.clear();
    if (analyzedPixelsVertical && analyzedPixelsHorizontal)
    {
        for (int i = 0; i < image.width(); i++)
        {
            delete analyzedPixelsVertical[i];
            delete analyzedPixelsHorizontal[i];
        }
        delete[] analyzedPixelsVertical;
        delete[] analyzedPixelsHorizontal;
        analyzedPixelsVertical   = 0;
        analyzedPixelsHorizontal = 0;
    }
    QString path = QFileDialog::getOpenFileName(this,"Open an image your want to mark","../");
    source.setFileName(path);
    if (!source.open(QIODevice::ReadOnly))
        qDebug() << QString("Can't open %1.").arg(path);
    QByteArray buffer = source.readAll();
    image = QImage::fromData(buffer,"JPG");

    analyzedPixelsVertical = new bool* [image.width() ];
    analyzedPixelsHorizontal = new bool* [image.width() ];
    for (int i = 0; i < image.width(); i++)
    {
        analyzedPixelsVertical[i] = new bool  [image.height()];
        analyzedPixelsHorizontal[i] = new bool  [image.height()];
        for (int j = 0; j <  image.height(); j++)
        {
            analyzedPixelsVertical[i][j] = false;
            analyzedPixelsHorizontal[i][j] = false;
        }
    }


    updateImage();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
