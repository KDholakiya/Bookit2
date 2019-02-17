QT       += core gui widgets network
TARGET = Bookit2
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11
SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dataprovider.cpp \
    contentshoecase.cpp \
    card.cpp \
    detailsviewer.cpp \
    detailsdialog.cpp \
    paymentwindow.cpp \
    checkout.cpp \
    invoice.cpp

HEADERS += \
        mainwindow.h \
    dataprovider.h \
    contentshoecase.h \
    card.h \
    detailsviewer.h \
    detailsdialog.h \
    paymentwindow.h \
    checkout.h \
    invoice.h

FORMS += \
        mainwindow.ui \
    contentshoecase.ui \
    card.ui \
    detailsviewer.ui \
    detailsdialog.ui \
    paymentwindow.ui \
    checkout.ui
win32 {
    RC_FILE = icon.rc
}
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
    icon.rc

RESOURCES += \
    res.qrc
