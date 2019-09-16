#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>

#include "VelSpeed.h"
#include "MotorSpeed.h"
#include "Temp.h"
#include "Fuel.h"
#include "Light.h"
namespace Ui {
class Display;
}

class Display : public QWidget
{
    Q_OBJECT

public:
    explicit Display(QWidget *parent = 0);
    ~Display();

private:
    Ui::Display *ui;
    VelSpeed* velspeed;
    MotorSpeed* motorspeed;
    Temp* temp;
    Fuel* fuel;
    Light* light;
};

#endif // DISPLAY_H
