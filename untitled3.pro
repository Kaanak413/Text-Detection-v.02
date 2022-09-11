QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += ..\build-untitled3-Desktop_Qt_5_14_0_MSVC2015_64bit-Release\opencvinclude
LIBS +=-L..\build-untitled3-Desktop_Qt_5_14_0_MSVC2015_64bit-Release\opencvlib\
-lopencv_core2413\
-lopencv_imgproc2413\
-lopencv_highgui2413


INCLUDEPATH +=..\build-untitled3-Desktop_Qt_5_14_0_MSVC2015_64bit-Release\tessinclude
LIBS +=-L..\build-untitled3-Desktop_Qt_5_14_0_MSVC2015_64bit-Release\tesslib\
-ltesseract41\
-lleptonica-1.82.0




SOURCES += \
    main.cpp \
    mainwindow.cpp \
    textdetector.cpp

HEADERS += \
    mainwindow.h \
    textdetector.h

FORMS += \
    mainwindow.ui



DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += TESSDATA_PREFIX=\\\"..//untitled3//tessdata/\\\"
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
