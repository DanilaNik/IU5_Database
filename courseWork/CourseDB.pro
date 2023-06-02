#QT       += core gui
QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminpanel.cpp \
    comand.cpp \
    comandu.cpp \
    comanies.cpp \
    company.cpp \
    companyu.cpp \
    main.cpp \
    mainwindow.cpp \
    product.cpp \
    productu.cpp \
    razrab.cpp \
    razrabu.cpp \
    userpanel.cpp \
    version.cpp \
    versionu.cpp

HEADERS += \
    adminpanel.h \
    comand.h \
    comandu.h \
    comanies.h \
    company.h \
    companyu.h \
    mainwindow.h \
    product.h \
    productu.h \
    razrab.h \
    razrabu.h \
    userpanel.h \
    version.h \
    versionu.h

FORMS += \
    adminpanel.ui \
    comand.ui \
    comandu.ui \
    comanies.ui \
    company.ui \
    companyu.ui \
    mainwindow.ui \
    product.ui \
    productu.ui \
    razrab.ui \
    razrabu.ui \
    userpanel.ui \
    version.ui \
    versionu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
