#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QPair>
#include <QVector>
#include "pointsgroup.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QString path = 0,QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();
    void updateImage();
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
private:
    void line(int x1,int y1,int x2,int y2, QRgb color);
    int max(int a, int b);
    void analyze(int x, int y, QRgb previousValue);
    void analyze(int x, int y,PointsGroup* pointsGroup );
    void markBoundaryPixels();
    Ui::MainWindow *ui;
    QImage image;
    bool** analyzedPixelsVertical;
    bool** analyzedPixelsHorizontal;
    QFile source;
    int trashHold;
    QVector<QPair<int,int> > boundaryPixels;
    QVector<PointsGroup*> groups;
};

#endif // MAINWINDOW_H
