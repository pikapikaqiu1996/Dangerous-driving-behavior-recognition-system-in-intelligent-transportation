#include "Light.h"
#include "ui_Light.h"

Light::Light(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Light)
{
    ui->setupUi(this);
    Nsignal = 0;
    Psignal = 0;
    Dsignal = 0;
    Rsignal = 0;
    value = 0;
    updatetimer = new QTimer(this);
    updatetimer->setInterval(100);
    connect(updatetimer,SIGNAL(timeout()),this,SLOT(Update()));
    updatetimer->start();
}

Light::~Light()
{
    delete ui;
}
void Light::drawShift(QPainter* painter)
{
    painter->save();
    painter = new QPainter(this);
    QFont font;
    font.setPointSize(20);
    painter->setFont(font);
    QPen pen = painter->pen();
    if(Psignal == 0)
        pen.setColor(Qt::darkGray);
    else
        pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->drawText(620, 65, "P");

    if(Nsignal == 0)
        pen.setColor(Qt::darkGray);
    else
        pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->drawText(618, 98, "N");
    if(Dsignal == 0)
        pen.setColor(Qt::darkGray);
    else
        pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->drawText(618, 131, "D");
    if(Rsignal == 0)
        pen.setColor(Qt::darkGray);
    else
        pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->drawText(618, 164, "R");
    painter->restore();
}
void Light::drawLight()
{
    QPixmap *pixmap1;
    QPixmap *pixmap2;
    QPixmap *pixmap3;
    QPixmap *pixmap4;
    QPixmap *pixmap5;
    QPixmap *pixmap6;
    QPixmap *pixmap7;

    if(value == 1)
    {
        pixmap1 = new QPixmap(":/light/light/dengpao.png");
        pixmap2 = new QPixmap(":/light/light/far.png");
        pixmap3 = new QPixmap(":/light/light/frost.png");
        pixmap4 = new QPixmap(":/light/light/near.png");
        pixmap5 = new QPixmap(":/light/light/timg.png");
        pixmap6 = new QPixmap(":/light/light/you.png");
        pixmap7 = new QPixmap(":/light/light/zuo.png");
    }
    else
    {
        pixmap1 = new QPixmap(":/light/light/dengpao2.jpg");
        pixmap2 = new QPixmap(":/light/light/far2.jpg");
        pixmap3 = new QPixmap(":/light/light/frost2.jpg");
        pixmap4 = new QPixmap(":/light/light/near2.jpg");
        pixmap5 = new QPixmap(":/light/light/timg2.jpg");
        pixmap6 = new QPixmap(":/light/light/you2.jpg");
        pixmap7 = new QPixmap(":/light/light/zuo2.jpg");
    }
    pixmap1->scaled(ui->label->size(), Qt::KeepAspectRatio);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*pixmap1);

    pixmap2->scaled(ui->label_2->size(), Qt::KeepAspectRatio);
    ui->label_2->setScaledContents(true);
    ui->label_2->setPixmap(*pixmap2);

    //QPixmap *pixmap3 = new QPixmap(":/light/light/frost.png");
    pixmap3->scaled(ui->label_3->size(), Qt::KeepAspectRatio);
    ui->label_3->setScaledContents(true);
    ui->label_3->setPixmap(*pixmap3);

    //QPixmap *pixmap4 = new QPixmap(":/light/light/near.png");
    pixmap4->scaled(ui->label_4->size(), Qt::KeepAspectRatio);
    ui->label_4->setScaledContents(true);
    ui->label_4->setPixmap(*pixmap4);

    //QPixmap *pixmap5 = new QPixmap(":/light/light/timg.png");
    pixmap5->scaled(ui->label_5->size(), Qt::KeepAspectRatio);
    ui->label_5->setScaledContents(true);
    ui->label_5->setPixmap(*pixmap5);

    //QPixmap *pixmap6 = new QPixmap(":/light/light/you.png");
    pixmap6->scaled(ui->label_6->size(), Qt::KeepAspectRatio);
    ui->label_6->setScaledContents(true);
    ui->label_6->setPixmap(*pixmap6);

    //QPixmap *pixmap7 = new QPixmap(":/light/light/zuo.png");
    pixmap7->scaled(ui->label_7->size(), Qt::KeepAspectRatio);
    ui->label_7->setScaledContents(true);
    ui->label_7->setPixmap(*pixmap7);

/***************      WARNING     *********************************/
    QPixmap *pixmap8;
    QPixmap *pixmap9;
    QPixmap *pixmap10;
    QPixmap *pixmap11;
    QPixmap *pixmap14;

    if(value == 1)
    {
        pixmap8 = new QPixmap(":/warning/warning/door.png");
        pixmap9 = new QPixmap(":/warning/warning/houbeixiang.png");
        pixmap10 = new QPixmap(":/warning/warning/belt.png");
        pixmap11 = new QPixmap(":/warning/warning/tired.png");
        pixmap14= new QPixmap(":/warning/warning/smoke.png");
    }
    else
    {
        pixmap8 = new QPixmap(":/warning/warning/door2.jpg");
        pixmap9 = new QPixmap(":/warning/warning/houbeixiang2.jpg");
        pixmap10 = new QPixmap(":/warning/warning/belt2.jpg");
        pixmap11 = new QPixmap(":/warning/warning/tired2.jpg");
        pixmap14= new QPixmap(":/warning/warning/smoke2.jpg");
    }

    pixmap8->scaled(ui->label_8->size(), Qt::KeepAspectRatio);
    ui->label_8->setScaledContents(true);
    ui->label_8->setPixmap(*pixmap8);

    pixmap9->scaled(ui->label_9->size(), Qt::KeepAspectRatio);
    ui->label_9->setScaledContents(true);
    ui->label_9->setPixmap(*pixmap9);

    //QPixmap *pixmap10 = new QPixmap(":/warning/warning/belt.png");
    pixmap10->scaled(ui->label_10->size(), Qt::KeepAspectRatio);
    ui->label_10->setScaledContents(true);
    ui->label_10->setPixmap(*pixmap10);

    //QPixmap *pixmap11 = new QPixmap(":/warning/warning/tired.png");
    pixmap11->scaled(ui->label_11->size(), Qt::KeepAspectRatio);
    ui->label_11->setScaledContents(true);
    ui->label_11->setPixmap(*pixmap11);

    /*QPixmap *pixmap12 = new QPixmap(":/warning/warning/Temp2.jpg");
    pixmap12->scaled(ui->label_12->size(), Qt::KeepAspectRatio);
    ui->label_12->setScaledContents(true);
    ui->label_12->setPixmap(*pixmap12);

    QPixmap *pixmap13 = new QPixmap(":/warning/warning/Fuel2.jpg");
    pixmap13->scaled(ui->label_13->size(), Qt::KeepAspectRatio);
    ui->label_13->setScaledContents(true);
    ui->label_13->setPixmap(*pixmap13);*/

    //QPixmap *pixmap14 = new QPixmap(":/warning/warning/phone.png");
    pixmap14->scaled(ui->label_14->size(), Qt::KeepAspectRatio);
    ui->label_14->setScaledContents(true);
    ui->label_14->setPixmap(*pixmap14);
}

void Light::paintEvent(QPaintEvent *)
{
    QPainter *painter;
    painter = new QPainter(this);
    QPen pen = painter->pen();
    pen.setWidth(2);
    pen.setColor(Qt::white);
    painter->setPen(pen);
    painter->drawLine(360, 30, 650, 30);
    painter->drawLine(360, 190, 650, 190);
    painter->drawLine(600, 30, 600, 190);

    drawShift(painter);
    drawLight();
}
void Light::Update()
{
    static int i = 0;
    i++;
    if(i == 10)
    {
       i = 0;
       if(value == 1)
           value = 0;
       else if(value == 0)
           value = 1;
       if(Nsignal == 1)
           Nsignal = 0;
       else if (Nsignal == 0)
           Nsignal = 1;
    }
    this->update();
}
