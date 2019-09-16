#include "Temp.h"
#include "ui_Temp.h"

Temp::Temp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Temp)
{
    ui->setupUi(this);
    foreground = Qt::white;
    StartAngel = 120;
    EndAngel = 120;
    ScaleMajor = 3;
    ScaleMinor = 10;
    maxValue = 100;
    minValue = 40;
    value = 40;
    radius1 = 100;
    radius2 = 120;
    precision = 0;
    units = "℃";
    updatetimer = new QTimer(this);
    updatetimer->setInterval(100);
    connect(updatetimer,SIGNAL(timeout()),this,SLOT(UpdateAngle()));
    updatetimer->start();
    resize(300, 200);
}

Temp::~Temp()
{
    delete ui;
}
void Temp::drawScale(QPainter* painter)
{
    painter->save();
    painter->setPen(foreground);
    painter->rotate(StartAngel);
    int steps = ScaleMajor;
    double angelstep = (360.0 - StartAngel - EndAngel) / steps;
    QPen pen = painter->pen();
    for(int i = 0; i <= steps; i++)
    {
            pen.setWidth(2);
            painter->setPen(pen);
            painter->drawLine(0, 50, 0, 60);
        painter->rotate(angelstep);
    }
    painter->restore();
}
void Temp::drawScaleNum(QPainter* painter)
{
    painter->save();
    painter->setPen(foreground);
    double startRad = (360 - StartAngel - 90) * 3.14 / 180;
    double deltaRad = (360 - StartAngel - EndAngel) * 3.14 / 180 / ScaleMajor;
    double sina, cosa;
    double x, y;
    QFont font = this->font();
    font.setPointSize(7);
    painter->setFont(font);
    QFontMetrics fm(font);
    double w, h, tmpVal;
    QString str;
    for(int i = 0; i <= ScaleMajor; i++)
    {
        sina = sin(startRad - i * deltaRad);
        cosa = cos(startRad - i * deltaRad);
        tmpVal = 1.0 * i * ((maxValue - minValue) / ScaleMajor) + minValue;
        str = QString("%1").arg(tmpVal);
        w = fm.size(Qt::TextSingleLine, str).width();
        h = fm.size(Qt::TextSingleLine, str).height();
        x = 70 * cosa - w* 2/5;
        y = -70 * sina + h/4;
        painter->drawText(x, y, str);
    }
    painter->restore();
}
void Temp::drawIndicator(QPainter* painter)
{
    painter->save();
    QPolygon pts;
    pts.setPoints(3, -3, 0, 3, 0, 0, 48);
    painter->rotate(StartAngel);
    double degRotate = (360.0 - StartAngel - EndAngel) / (maxValue - minValue)*(value - minValue);
    //indicator
    painter->rotate(degRotate);
    //QRadialGradient haloGradient(0,0,60,0,0);
    //haloGradient.setColorAt(0,QColor(60,60,60));
    //haloGradient.setColorAt(1,QColor(160,160,160));
    painter->setPen(Qt::red);
    //painter->setBrush(haloGradient);
    painter->setBrush(Qt::red);
    painter->drawConvexPolygon(pts);

    painter->restore();
    //circle
    QConicalGradient coneGradient(0,0,-90.0);
    coneGradient.setColorAt(0, Qt::red);
    coneGradient.setColorAt(0.5, Qt::red);
    coneGradient.setColorAt(1, Qt::red);
    painter->setPen(Qt::NoPen);
    painter->setBrush(coneGradient);
    painter->drawEllipse(-5, -5, 10, 10);
}
void Temp::drawNumericValue(QPainter* painter)
{
    //painter->save();
    QString str  =  QString("%1 %2").arg(value, 0, 'f', precision).arg(units);
    QFont font = this->font();
    font.setPointSize(9);
    painter->setFont(font);
    //QFontMetricsF fm(font);
    //double w = fm.size(Qt::TextSingleLine,str).width();
    painter->setPen(foreground);
    painter->drawText(30, 0, str);
    //painter->restore();
}
void Temp::drawArc(QPainter* painter)
{
   // painter->save();
    painter->setPen(foreground);
    QRect rectbig(-radius1/2, -radius1/2, radius1, radius1);
    QRect rectsmall(-radius2/2, -radius2/2, radius2, radius2);
    int startangel = 30* 16;
    int spanangel = 120* 16;
    painter->drawArc(rectbig, startangel, spanangel);
    painter->drawArc(rectsmall, startangel, spanangel);
    //painter->setBrush(Qt::green);
   // painter->restore();
}
void Temp::drawTemp()
{
    QPixmap *pixmap13;
    if(value >= 85)
        pixmap13 = new QPixmap(":/warning/warning/Temp.png");
    else
        pixmap13 = new QPixmap(":/warning/warning/Temp2.jpg");
    pixmap13->scaled(ui->label->size(), Qt::KeepAspectRatio);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*pixmap13);
}
void Temp::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.translate(width() / (2),height()/1.2);
    //painter.translate(width() / (2),height()/2);
    int side =qMin(width(),height());
    painter.scale(side/90.0, side/ 90.0);

    drawScale(&painter);
    drawScaleNum(&painter);
    drawIndicator(&painter);
    drawNumericValue(&painter);
    drawArc(&painter);
    drawTemp();
}
void Temp::UpdateAngle()
{
    static int i = 0;
    if(i > 90)
        i = 0;
    i+=1;
    value = 60*sin(i*3.14/180)+40;
    this->update();
}
