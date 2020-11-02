QT       += core gui serialport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aquiredatadialog.cpp \
    backgroundserialread.cpp \
    catchgrapheditor.cpp \
    catchgraphview.cpp \
    cmdbtn.cpp \
    connection.cpp \
    dialogs/exportseriesdialog.cpp \
    fftdialog.cpp \
    fileexport.cpp \
    filters/fftwrapper.cpp \
    filtersetterdialog.cpp \
    floatviewsetter.cpp \
    main.cpp \
    mainwindow.cpp \
    motorsdialog.cpp \
    plottingdialog.cpp \
    serialconnection.cpp \
    serieswrapper.cpp \
    singlesetter.cpp \
    xyseriesiodevice.cpp

HEADERS += \
    Commands.h \
    Filter/Filter.h \
    aquiredatadialog.h \
    backgroundserialread.h \
    catchgrapheditor.h \
    catchgraphview.h \
    cmdbtn.h \
    connection.h \
    dialogs/exportseriesdialog.h \
    fft-real/Array.h \
    fft-real/Array.hpp \
    fft-real/DynArray.h \
    fft-real/DynArray.hpp \
    fft-real/FFTReal.h \
    fft-real/FFTReal.hpp \
    fft-real/OscSinCos.h \
    fft-real/OscSinCos.hpp \
    fft-real/def.h \
    fftdialog.h \
    fileexport.h \
    filters/BiquadBS.h \
    filters/DynamicNotch.h \
    filters/fftwrapper.h \
    filtersetterdialog.h \
    floatviewsetter.h \
    mainwindow.h \
    motorsdialog.h \
    plottingdialog.h \
    serialconnection.h \
    serieswrapper.h \
    singlesetter.h \
    xyseriesiodevice.h

FORMS += \
    aquiredatadialog.ui \
    catchgrapheditor.ui \
    cmdbtn.ui \
    connection.ui \
    dialogs/exportseriesdialog.ui \
    fftdialog.ui \
    filtersetterdialog.ui \
    floatviewsetter.ui \
    mainwindow.ui \
    motorsdialog.ui \
    plottingdialog.ui \
    serialconnection.ui \
    singlesetter.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
