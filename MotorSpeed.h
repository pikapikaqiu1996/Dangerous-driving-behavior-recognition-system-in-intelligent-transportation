#ifndef MOTORSPEED_H
#define MOTORSPEED_H

#include <QWidget>
#include <QPainter>
#include "qmath.h"
#include "QTimer"
class MotorSpeed : public QWidget
{
    Q_OBJECT
public:
    explicit MotorSpeed(QWidget *parent = nullptr);
    ~MotorSpeed();

    void paintEvent(QPaintEvent *);
private:
    int ScaleMajor;
    int ScaleMinor;
    int StartAngel;
    int EndAngel;
    int maxValue;
    int minValue;
    double value;
    int precision;
    QString units;
    QString title;
    QColor foreground;
    QTimer *updatetimer;
protected:
    void drawCrown(QPainter*);
    void drawBackgroud(QPainter*);
    void drawScale(QPainter*);
    void drawScaleNum(QPainter*);
    void drawIndicator(QPainter*);
    void drawTitle(QPainter*);
    void drawNumericValue(QPainter*);
signals:

public slots:
    void UpdateAngle();
};

#endif // MOTORSPEED_H
