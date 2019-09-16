#ifndef FUEL_H
#define FUEL_H

#include <QWidget>
#include <QPainter>
#include "qmath.h"
#include <QTimer>
#include <QPixmap>
namespace Ui {
class Fuel;
}

class Fuel : public QWidget
{
    Q_OBJECT

public:
    explicit Fuel(QWidget *parent = 0);
    ~Fuel();

    void paintEvent(QPaintEvent *event);
    void drawScale(QPainter*);
    void drawScaleNum(QPainter*);
    void drawIndicator(QPainter*);
    void drawNumericValue(QPainter*);
    void drawFuel();
    void drawArc(QPainter*);
private:
    Ui::Fuel *ui;
    int ScaleMajor;
    int ScaleMinor;
    int StartAngel;
    int EndAngel;
    int maxValue;
    int minValue;
    int value;
    int precision;
    int radius1, radius2;
    QString units;
    //QString title;
    QColor foreground;
    QTimer *updatetimer;

signals:

public slots:
    void UpdateAngle();
};

#endif // FUEL_H
