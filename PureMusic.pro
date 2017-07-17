#-------------------------------------------------
#
# Project created by QtCreator 2016-01-03T18:43:20
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PureMusic
TEMPLATE = app


SOURCES += main.cpp \
    qpuremusic.cpp \
    qmysystemtrayicon.cpp \
    qmyslider.cpp \
    qmygraphicsview.cpp \
    qclosedlg.cpp \
    qlrcwnd.cpp \
    qlocalwid.cpp \
    qplaywid.cpp \
    qdb.cpp \
    myitem.cpp \
    qfavwid.cpp

HEADERS  += \
    qpuremusic.h \
    qmysystemtrayicon.h \
    qmyslider.h \
    qmygraphicsview.h \
    qclosedlg.h \
    qlrcwnd.h \
    qlocalwid.h \
    qplaywid.h \
    qdb.h \
    myitem.h \
    qfavwid.h

FORMS += \
    qpuremusic.ui \
    qclosedlg.ui \
    qlocalwid.ui \
    qplaywid.ui \
    qfavwid.ui

RESOURCES += \
    qpuremusic.qrc

DISTFILES +=
