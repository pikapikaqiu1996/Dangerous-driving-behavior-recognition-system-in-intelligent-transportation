#-------------------------------------------------
#
# Project created by QtCreator 2019-05-10T15:11:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Display
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        Display.cpp \
    VelSpeed.cpp \
    MotorSpeed.cpp \
    Light.cpp \
    Fuel.cpp \
    Temp.cpp \
    detect.cpp

HEADERS += \
        Display.h \
    VelSpeed.h \
    MotorSpeed.h \
    Light.h \
    Fuel.h \
    Temp.h \
    detect.h

FORMS += \
        Display.ui \
    Light.ui \
    widget.ui \
    Fuel.ui \
    Temp.ui

RESOURCES += \
    images.qrc

INCLUDEPATH += /home/dp/software/opencv-3.2.0/include/opencv\
/home/dp/software/opencv-3.2.0/include/opencv2

LIBS+= /home/dp/software/opencv-3.2.0/build/lib/*.so
