#-------------------------------------------------
#
# Project created by QtCreator 2015-06-11T20:20:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GTGenerator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \        
    diagramitem.cpp \
    diagramscene.cpp \    
    diagramview.cpp \
    colorlistwidgetitem.cpp \
    diagramsceneinfo.cpp \
    diagramroi.cpp \
    gtmainwindow.cpp \
    taggingwidget.cpp \
    gtprojectwidget.cpp \
    newgtprojectwizard.cpp

HEADERS  += mainwindow.h \    
    diagramitem.h \
    diagramscene.h \   
    diagramview.h \
    colorlistwidgetitem.h \
    diagramsceneinfo.h \
    diagramroi.h \
    gtmainwindow.h \
    taggingwidget.h \
    gtprojectwidget.h \
    newgtprojectwizard.h

FORMS    += mainwindow.ui \
    gtmainwindow.ui \
    taggingwidget.ui \
    newgtprojectwizard.ui
