#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QPair>
#include <QVector>
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
private:
    void line(int x1,int y1,int x2,int y2, QRgb color);
    int max(int a, int b);
    void analyze(int x, int y, QRgb previousValue);
    void analyze2(int x, int y, QRgb previousValue);
    void analyze();
    void markBoundaryPixels();
    Ui::MainWindow *ui;
    QImage image;
    short** analyzedPixels;
    QFile source;
    int trashHold;
    QVector<QPair<int,int> > boundaryPixels;
};

#endif // MAINWINDOW_H
