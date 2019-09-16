#ifndef LIGHT_H
#define LIGHT_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
namespace Ui {
class Light;
}

class Light : public QWidget
{
    Q_OBJECT

public:
    explicit Light(QWidget *parent = 0);
    ~Light();
    bool Nsignal;
    bool Psignal;
    bool Dsignal;
    bool Rsignal;

    void paintEvent(QPaintEvent *event);
    void drawShift(QPainter*);
    void drawLight();
private:
    Ui::Light *ui;
    int value;
    QTimer *updatetimer;
public slots:
    void Update();
};

#endif // LIGHT_H
