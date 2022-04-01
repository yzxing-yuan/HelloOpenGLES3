#-------------------------------------------------
#
# Project created by QtCreator 2022-01-18T22:56:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloOpenGLES3
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
    Common/esTransform.c \
    esShapes.c \
        main.cpp \
        mainwindow.cpp \
    esUtil.c \
    hellotriangle.cpp

HEADERS += \
    IGlesHandle.hpp \
    common.hpp \
    illumination.hpp \
        mainwindow.h \
    esUtil.h \
    GLES3/gl3.h \
    GLES3/gl3platform.h \
    EGL/egl.h \
    EGL/eglext.h \
    EGL/eglplatform.h \
    KHR/khrplatform.h \
    hellotriangle.h \
    matrixtransform.hpp

#Windows
LIBS += -L. -lEGL -lGLESv2
#Linux
#LIBS += -L/usr/lib/x86_64-linux-gnu -lEGL -lGLESv2

RESOURCES += \
    shaders.qrc

DISTFILES +=
