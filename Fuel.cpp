#include "Fuel.h"
#include "ui_Fuel.h"

Fuel::Fuel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fuel)
{
    ui->setupUi(this);
    ScaleMajor = 4;
    ScaleMinor = 10;
    StartAngel = 120;
    EndAngel = 120;
    maxValue = 100;
    minValue = 0;
    value = 0;
    units = "%";
    radius1 = 120;
    radius2 = 100;
    units = "%";
    precision = 0;
    foreground = Qt::white;
    updatetimer = new QTimer(this);
    updatetimer->setInterval(100);
    connect(updatetimer,SIGNAL(timeout()),this,SLOT(UpdateAngle()));
    updatetimer->start();
    resize(250, 200);
}

Fuel::~Fuel()
{
    delete ui;
}
void Fuel::drawScale(QPainter* painter)
{
    painter->save();
    painter->setPen(foreground);
    painter->rotate(StartAngel);
    //int steps = ScaleMajor * ScaleMinor;
    double angelstep = (360.0 - StartAngel - EndAngel) / ScaleMajor;
    QPen pen = painter->pen();
    for(int i = 0; i <= ScaleMajor; i++)
    {
        //if(i % ScaleMinor == 0)
        //{
            pen.setWidth(2);
            painter->setPen(pen);
            painter->drawLine(0, 50, 0, 60);
        //}
        /*else if(i % 5 == 0)
        {
            pen.setWidth(1);
            painter->setPen(pen);
            painter->drawLine(0, 55, 0, 60);
        }*/
        painter->rotate(angelstep);
    }
    painter->restore();
}
void Fuel::drawScaleNum(QPainter* painter)
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
        x = 70 * cosa - w* 2/5;
        y = -70 * sina + h/4;
        painter->drawText(x, y, str);
    }
    painter->restore();
}
void Fuel::drawIndicator(QPainter* painter)
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
    QConicalGradient coneGradient(0,0,-90);
    coneGradient.setColorAt(0, Qt::darkGray);
    coneGradient.setColorAt(0.5, Qt::white);
    //coneGradient.setColorAt(1, Qt::darkGray);
    coneGradient.setColorAt(1, Qt::darkRed);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    //painter->setBrush(coneGradient);
    painter->drawEllipse(-5, -5, 10, 10);


}
void Fuel::drawNumericValue(QPainter* painter)
{
    //painter->save();
    QString str  =  QString("%1 %2").arg(value, 0, 'f', precision).arg(units);
    QFont font = this->font();
    font.setPointSize(9);
    painter->setFont(font);
    //QFontMetricsF fm(font);
    //double w = fm.size(Qt::TextSingleLine,str).width();
    painter->setPen(foreground);
    painter->drawText(-50, 0, str);
    //painter->restore();
}
void Fuel::drawArc(QPainter* painter)
{
   // painter->save();
    painter->setPen(foreground);
    QRect rectbig(-radius1/2, -radius1/2, radius1, radius1);
    QRect rectsmall(-radius2/2, -radius2/2, radius2, radius2);
    int startangel = 30* 16;
    int spanangel = 120* 16;
    painter->drawArc(rectbig, startangel, spanangel);
    painter->drawArc(rectsmall, startangel, spanangel);
   // painter->restore();
}
void Fuel::drawFuel()
{
     QPixmap *pixmap1;
     if(value <= 25)
     {
         pixmap1 = new QPixmap(":/warning/warning/Fuel.png");
     }
     else
     {
         pixmap1 = new QPixmap(":/warning/warning/Fuel2.jpg");
     }
     pixmap1->scaled(ui->label->size(), Qt::KeepAspectRatio);
     ui->label->setScaledContents(true);
     ui->label->setPixmap(*pixmap1);
}
void Fuel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.translate(width()/2, height()/1.2);
    double size = qMin(width(), height());
    painter.scale(size/100, size/100);
    drawScale(&painter);
    drawScaleNum(&painter);
    drawIndicator(&painter);
    drawNumericValue(&painter);
    drawArc(&painter);
    drawFuel();
}
void Fuel::UpdateAngle()
{
    static int i = 0;
    if(i > 90)
        i = 0;
    i+=1;
    value = 100*sin(i*3.14/180);
    this->update();
}

