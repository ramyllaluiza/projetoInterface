QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    incluircd.cpp \
    incluirdvd.cpp \
    incluirlivro.cpp \
    loja.cpp \
    main.cpp \
    mainloja.cpp

HEADERS += \
    incluircd.h \
    incluirdvd.h \
    incluirlivro.h \
    loja.h \
    mainloja.h

FORMS += \
    incluircd.ui \
    incluirdvd.ui \
    incluirlivro.ui \
    mainloja.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    loja.txt
