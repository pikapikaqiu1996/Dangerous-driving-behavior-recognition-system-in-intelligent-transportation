#ifndef VELSPEED_H
#define VELSPEED_H

#include <QWidget>
#include <QPainter>
//#include <QString>
//#include <QPainter>
#include <qmath.h>
#include "QTimer"
class VelSpeed : public QWidget
{
    Q_OBJECT
public:
    explicit VelSpeed(QWidget *parent = nullptr);
    ~VelSpeed();

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
    void drawCrown(QPainter*);
    void drawBackground(QPainter*);
    void drawScale(QPainter*);
    void drawScaleNum(QPainter*);
    void drawIndicator(QPainter*);
    void drawTitle(QPainter*);
    void drawNumericValue(QPainter*);
protected:

signals:

public slots:
    void UpdateAngle();
};

#endif // VELSPEED_H
/*

*/
