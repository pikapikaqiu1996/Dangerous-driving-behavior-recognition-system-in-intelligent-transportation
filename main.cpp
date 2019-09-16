#include "Display.h"
#include <QApplication>
#include "detect.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widget w1;
    w1.setWindowTitle("FaceDetect by dp\zyj");
    w1.show();
    Display w;
    w.show();

    return a.exec();
}
