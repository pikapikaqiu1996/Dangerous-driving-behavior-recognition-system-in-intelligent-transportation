#include "detect.h"
#include "ui_widget.h"
#include <QDebug>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QFileDialog>
#include <QString>
using namespace std;

QString mydialog(QString title)
{
    QString path;
    QFileDialog *fileDialog = new QFileDialog();//创建一个QFileDialog对象，构造函数中的参数可以有所添加。
    fileDialog->setWindowTitle(title);//设置文件保存对话框的标题
    fileDialog->setFileMode(QFileDialog::AnyFile);//设置文件对话框弹出的时候显示任何文件，不论是文件夹还是文件
    fileDialog->setViewMode(QFileDialog::Detail);//文件以详细的形式显示，显示文件名，大小，创建日期等信息；
    fileDialog->setGeometry(0,0,300,150);//设置文件对话框的显示位置
    fileDialog->setDirectory(".");//设置文件对话框打开时初始打开的位置
    if(fileDialog->exec() == QDialog::Accepted)
    {
        //注意使用的是QFileDialog::Accepted或者QDialog::Accepted,不是QFileDialog::Accept
        path = fileDialog->selectedFiles()[0];//得到用户选择的文件名
    }
    delete fileDialog;
    return path;
}

widget::widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
    state = 0;
    connect(&theTimer, &QTimer::timeout, this, &widget::updateImage);//连接信号与槽，图像刷新
    //if(!face_cascade.load("/home/dp/software/opencv-3.2.0/data/haarcascades/haarcascade_frontalface_alt.xml"))
    //if(!face_cascade.load("/home/dp/software/opencv-3.2.0/data/haarcascades/haarcascade_eye.xml"))
    if(!face_cascade.load("/home/dp/software/opencv-3.2.0/data/haarcascades/haarcascade_lefteye_2splits.xml"))
    {
        qDebug() << "load xml file failed";
    }
    num = 0;
    ui->label->setText("FaceNum: " + QString::number(num));
    srcImage = Mat::zeros(480, 640, CV_8UC3);//图像显示部分初始设置黑色
    this->update();
}

widget::~widget()
{
    delete ui;
}
void widget::on_button1_clicked()
{
    if(state == 0)
    {
        state = 1;
        if(videoCap.open(0))//摄像头读取视频流
        {
            srcImage = Mat::zeros(videoCap.get(CV_CAP_PROP_FRAME_HEIGHT), videoCap.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
            theTimer.start(33);//time信号
        }
    }
}
void widget::on_button2_clicked()
{
    if(state == 0)
    {
        state = 2;
        string path_ = mydialog("Open Video").toStdString();
        if(videoCap.open(path_))
        {
            srcImage = Mat::zeros(videoCap.get(CV_CAP_PROP_FRAME_HEIGHT), videoCap.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
            theTimer.start(33);
        }
    }
}
void widget::on_button3_clicked()
{
    if(state == 0)
    {
        state = 3;
        string path_ = mydialog("Open Picture").toStdString();
        srcImage = imread(path_);
        updateImage();
    }
}
void widget::on_button4_clicked()
{
    num = 0;
    switch(state)
    {
        case 0: break;
        case 1:
                srcImage = Mat::zeros(480, 640, CV_8UC3);
                theTimer.stop();
                this->update();
                videoCap.release();
                break;
        case 2:
                srcImage = Mat::zeros(480, 640, CV_8UC3);
                theTimer.stop();
                this->update();
                videoCap.release();
                break;
        case 3:
                srcImage = Mat::zeros(480, 640, CV_8UC3);
                this->update();
                break;
    }
    state = 0;
}
void widget::updateImage()
{
    if(state == 1 || state == 2)
    {
        videoCap >> srcImage;
    }
    if(srcImage.data)
    {
        vector<Rect> faces;
        face_cascade.detectMultiScale(srcImage, faces, 1.1, 3, 0, Size(50,50), Size(500,500));
        num = faces.size();
        if(faces.size() >= 1)
        {
            for(size_t i=0;i<faces.size();i++)
            {
                Point p1(faces[i].x, faces[i].y);
                Point p2(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
                rectangle(srcImage, p2, p1, cvScalar(0, 0, 255), 1, 4, 0);
            }
        }
        cvtColor(srcImage, srcImage, CV_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR
        cv::resize(srcImage, srcImage, Size(640,480));
        this->update();  //发送刷新消息
     }
}
void widget
::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    ui->label->setText("FaceNum: " + QString::number(num));
    QImage image1 = QImage((uchar*)(srcImage.data), srcImage.cols, srcImage.rows, QImage::Format_RGB888);
    painter.drawImage(QPoint(0,0), image1);
}
