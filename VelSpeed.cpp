#include "VelSpeed.h"
VelSpeed::VelSpeed(QWidget *parent) : QWidget(parent)
{
     foreground = Qt::green;
     ScaleMajor = 12;
     ScaleMinor = 10;
     StartAngel = 60;
     EndAngel = 60;
     maxValue = 240;
     minValue = 0;
     units = "km/h";
     title = "Vehicle Speed";
     precision = 0;
     value = 0;
     updatetimer = new QTimer(this);
     updatetimer->setInterval(100);
     connect(updatetimer,SIGNAL(timeout()),this,SLOT(UpdateAngle()));
     updatetimer->start();
     resize(300, 300);
}
VelSpeed::~VelSpeed()
{

}
void VelSpeed::drawCrown(QPainter* painter)
{
    painter->save();
    int radius =100;
    QLinearGradient lg1(0,-radius,0,radius);
    lg1.setColorAt(0.2,Qt::white);
    lg1.setColorAt(1,Qt::black);
    painter->setBrush(lg1);
    painter->drawEllipse(-100, -100, 200 ,200);
    painter->restore();
}
void VelSpeed::drawBackground(QPainter* painter)
{
    painter->save();
    painter->setBrush(Qt::black);
    painter->drawEllipse(-90, -90, 180, 180);
    painter->restore();
}
void VelSpeed::drawScale(QPainter* painter)     //Scale
{
    painter->save();
    painter->setPen(foreground);
    painter->rotate(StartAngel);
    int steps = ScaleMajor * ScaleMinor;
    double angelStep = (360.0 - StartAngel- EndAngel) / steps;
    QPen pen = painter->pen();
    for(int i = 0;i <= steps; i++)
    {
        if(i % ScaleMinor == 0)
        {
            pen.setWidth(2);
            painter->setPen(pen);
            painter->drawLine(0,61,0,72);
        }
        else //if(i % 2 == 0)
        {
            pen.setWidth(1);
            painter->setPen(pen);
            painter->drawLine(0,67,0,72);
        }
        painter->rotate(angelStep);
    }
    painter->restore();
}
void VelSpeed::drawScaleNum(QPainter* painter)
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
    //painter->setPen(Qt::black);
    for(int i = 0; i <= ScaleMajor; i++)
    {
        sina = sin(startRad - i * deltaRad);
        cosa = cos(startRad - i * deltaRad);
        tmpVal = 1.0 * i * ((maxValue - minValue) / ScaleMajor) + minValue;
        str = QString("%1").arg(tmpVal);
        w = fm.size(Qt::TextSingleLine, str).width();
        h = fm.size(Qt::TextSingleLine, str).height();
        x = 82 * cosa - w* 2/5;
        y = -82 * sina + h/4;
        painter->drawText(x, y, str);
    }
    painter->restore();
}
void VelSpeed::drawIndicator(QPainter* painter)
{
    painter->save();
    QPolygon pts;
    pts.setPoints(3, -3, 0, 3, 0, 0, 60);
    painter->rotate(StartAngel);
    double degRotate = (360.0 - StartAngel - EndAngel) / (maxValue - minValue)*(value - minValue);
    //indicator
    painter->rotate(degRotate);
    QRadialGradient haloGradient(0,0,60,0,0);
    haloGradient.setColorAt(0,QColor(60,60,60));
    haloGradient.setColorAt(1,QColor(160,160,160));
    painter->setPen(Qt::white);
    painter->setBrush(haloGradient);
    painter->drawConvexPolygon(pts);

    painter->restore();
    //circle
    QConicalGradient coneGradient(0,0,-90);
    coneGradient.setColorAt(0, Qt::darkGray);
    coneGradient.setColorAt(0.5, Qt::white);
    coneGradient.setColorAt(1, Qt::darkGray);
    painter->setPen(Qt::NoPen);
    painter->setBrush(coneGradient);
    painter->drawEllipse(-5, -5, 10, 10);

}
void VelSpeed::drawTitle(QPainter* painter)
{
    painter->save();
    painter->setPen(foreground);
    //painter->setBrush(m_foreground);
    QString str(title); //显示仪表的功能
    QFont font = this->font();
    font.setPointSize(9);
    painter->setFont(font);
    QFontMetricsF fm(font);
    double w = fm.size(Qt::TextSingleLine,str).width();
    painter->drawText(-w / 2, -27, str);
    painter->restore();
}
void VelSpeed::drawNumericValue(QPainter* painter)
{
    //painter->save();
    QString str  =  QString("%1 %2").arg(value, 0, 'f', precision).arg(units);
    QFont font = this->font();
    font.setPointSize(9);
    painter->setFont(font);
    QFontMetricsF fm(font);
    double w = fm.size(Qt::TextSingleLine,str).width();
    painter->setPen(foreground);
    painter->drawText(-w / 2, 40, str);
    //painter->restore();
}
void VelSpeed::paintEvent(QPaintEvent* )
{
   QPainter painter(this);
   painter.translate(width()/2,height()/2);
   //printf("%d",width()/2);
   int side = qMin(width(),height());
   painter.scale(side /200.0,side /200.0);

   drawCrown(&painter);
   drawBackground(&painter);
   drawScale(&painter);
   drawIndicator(&painter);
   drawScaleNum(&painter);
   drawTitle(&painter);
   drawNumericValue(&painter);
}
void VelSpeed::UpdateAngle()
{
    static int t = 0;
    if(t > 90)
        t = 0;
    t+=1;
    value = 240*sin(t*3.14/180);
    this->update();
}
