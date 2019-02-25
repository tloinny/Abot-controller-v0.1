SOURCES += \
    main.cpp \
    mainwindow.cpp \
    serial.cpp \
    infowindow.cpp \
    slider.cpp \
    myspinbox.cpp \
    myslider.cpp

QT += widgets gui
QT += serialport
RC_ICONS = robor_arm.ico
HEADERS += \
    mainwindow.h \
    serial.h \
    infowindow.h \
    slider.h \
    myspinbox.h \
    myslider.h

DISTFILES +=

RESOURCES += \
    resource.qrc
