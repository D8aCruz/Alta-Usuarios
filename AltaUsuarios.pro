#-------------------------------------------------
#
# Project created by QtCreator 2011-07-16T03:05:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AltaUsuarios
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    usuario.cpp

HEADERS  += mainwindow.h \
    usuario.h

FORMS    += mainwindow.ui \
    usuario.ui

OTHER_FILES += \
    emule.png

RESOURCES += \
    Resources.qrc
