#include "Display.h"
#include "ui_Display.h"

Display::Display(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Display)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("background:black");
    velspeed = new VelSpeed(this);
    velspeed->show();
    velspeed->setGeometry(20, 220, 500, 500);
    motorspeed = new MotorSpeed(this);
    motorspeed->show();
    motorspeed->setGeometry(580, 290, 400, 400);
    temp = new Temp(this);
    temp->show();
    temp->setGeometry(15, 0, 310, 200);
    fuel = new Fuel(this);
    fuel->show();
    fuel->setGeometry(700, 0, 280 ,200);
    light = new Light(this);
    light->show();
    //light->

}

Display::~Display()
{
    delete ui;
}


