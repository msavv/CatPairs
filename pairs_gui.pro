QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gameengine.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp

HEADERS += \
    gameengine.hh \
    mainwindow.hh \
    player.hh

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    resources/0.png \
    resources/1.png \
    resources/10.png \
    resources/11.png \
    resources/12.png \
    resources/13.png \
    resources/14.png \
    resources/15.png \
    resources/16.png \
    resources/17.png \
    resources/18.png \
    resources/19.png \
    resources/2.png \
    resources/20.png \
    resources/3.png \
    resources/4.png \
    resources/5.png \
    resources/6.png \
    resources/7.png \
    resources/8.png \
    resources/9.png

RESOURCES += \
    resources.qrc
