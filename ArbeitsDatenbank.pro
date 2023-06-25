QT       += \
    core \
    gui \
    sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DBAccess.cpp \
    accountdock.cpp \
    admin.cpp \
    adminsession.cpp \
    arbeit.cpp \
    arbeitdock.cpp \
    createarbeitdock.cpp \
    createdozentdock.cpp \
    dozent.cpp \
    dozentensession.cpp \
    logindock.cpp \
    main.cpp \
    mainwindow.cpp \
    updatepasswortdock.cpp

HEADERS += \
    DBAccess.h \
    accountdock.h \
    admin.h \
    adminsession.h \
    arbeit.h \
    arbeitdock.h \
    createarbeitdock.h \
    createdozentdock.h \
    dozent.h \
    dozentensession.h \
    logindock.h \
    mainwindow.h \
    updatepasswortdock.h

FORMS += \
    accountdock.ui \
    arbeitdock.ui \
    createarbeitdock.ui \
    createdozentdock.ui \
    logindock.ui \
    mainwindow.ui \
    updatepasswortdock.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
