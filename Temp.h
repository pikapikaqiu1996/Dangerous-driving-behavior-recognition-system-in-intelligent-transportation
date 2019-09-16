#ifndef TEMP_H
#define TEMP_H

#include <QWidget>
#include <QPainter>
#include "qmath.h"
#include <QTimer>
#include <QPixmap>

namespace Ui {
class Temp;
}

class Temp : public QWidget
{
    Q_OBJECT

public:
    explicit Temp(QWidget *parent = 0);
    ~Temp();
    void paintEvent(QPaintEvent *event);
protected:
    void drawScale(QPainter*);
    void drawScaleNum(QPainter*);
    void drawIndicator(QPainter*);
    void drawNumericValue(QPainter*);
    void drawArc(QPainter*);
    void drawTemp();
private:
    Ui::Temp *ui;
    int ScaleMajor;
    int ScaleMinor;
    int StartAngel;
    int EndAngel;
    int maxValue;
    int minValue;
    double value;
    int precision;
    int radius1, radius2;
    QString units;
    //QString title;
    QColor foreground;
    QTimer *updatetimer;
public slots:
    void UpdateAngle();
};

#endif // TEMP_H
