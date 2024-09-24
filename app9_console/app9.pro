QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TARGET = spline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Debug/data.cpp \
    Debug/datetime.cpp \
    Debug/logger.cpp \
    NumericalCalculation/interpolation.cpp \
    NumericalCalculation/polynomial.cpp \
    Workers/abstractrequest.cpp \
    Workers/dispatcher.cpp \
    Workers/request.cpp \
    Workers/responder.cpp \
    Workers/worker.cpp \
    csv/csvfile.cpp \
    datamodelinput.cpp \
    datamodelinterpolation.cpp \
    datasystems.cpp \
    json/json_w.cpp \
    main.cpp \
    utils/Utils.cpp

HEADERS += \
    Debug/data.h \
    Debug/datetime.h \
    Debug/logger.h \
    NumericalCalculation/interpolation.h \
    NumericalCalculation/polynomial.h \
    Workers/abstractrequest.h \
    Workers/dispatcher.h \
    Workers/request.h \
    Workers/responder.h \
    Workers/worker.h \
    csv/csvfile.h \
    datamodelinput.h \
    datamodelinterpolation.h \
    datasystems.h \
    json/json_w.h \
    thrsafe/ReadersWriterLock.h \
    thrsafe/libh.h \
    thrsafe/shd.h \
    thrsafe/thr_safe.h \
    thrsafe/tsmap.h \
    utils/Utils.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
