#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include "cv.h"
#include "highgui.h"
#include "opencv.hpp"
using namespace cv;
namespace Ui {
class widget;
}


class widget : public QWidget
{
    Q_OBJECT
public:
    explicit widget(QWidget *parent = 0);
    ~widget();
private slots:       //声明槽
    void on_button1_clicked();
    void on_button2_clicked();
    void updateImage();
    void on_button4_clicked();
    void on_button3_clicked();
private:
    Ui::widget *ui;          //ui界面对象指针
    QTimer theTimer;
    //QTimer 计时用；
    QLabel *imageLabel;
    Mat srcImage;
    VideoCapture videoCap;
    CascadeClassifier face_cascade;
    int state;//状态 camera是1，video是2，picture是3，back返回0
    int num;//检测到的人脸数量
protected:
    void paintEvent(QPaintEvent *e);
};
#endif // WIDGET_H

