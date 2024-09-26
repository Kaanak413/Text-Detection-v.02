QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# Uncomment to disable deprecated APIs if using Qt 6.0.0 or higher
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Include paths for vcpkg packages
INCLUDEPATH += $$[VCPKG_ROOT]/installed/x64-windows/include
INCLUDEPATH += $$[VCPKG_ROOT]/installed/x64-windows/include/tesseract
INCLUDEPATH += $$[VCPKG_ROOT]/installed/x64-windows/include/opencv2

# Library paths for vcpkg packages
LIBS += -L$$[VCPKG_ROOT]/installed/x64-windows/lib \
        -ltesseract \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_highgui

LIBS += -lleptonica

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    textdetector.cpp

HEADERS += \
    mainwindow.h \
    textdetector.h

FORMS += \
    mainwindow.ui

QMAKE_LFLAGS += -v

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += TESSDATA_PREFIX=\\\"..//untitled3//tessdata/\\\"\

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
