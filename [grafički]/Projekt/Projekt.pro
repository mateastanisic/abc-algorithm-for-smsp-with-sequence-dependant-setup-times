#-------------------------------------------------
#
# Project created by QtCreator 2019-02-03T23:22:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projekt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    smsp.cpp \
    population.cpp \
    permutation.cpp \
    abc.cpp

HEADERS += \
        mainwindow.h \
    smsp.h \
    population.h \
    permutation.h \
    abc.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    PROB858.TXT \
    PROB857.TXT \
    PROB856.TXT \
    PROB855.TXT \
    PROB854.TXT \
    PROB853.TXT \
    PROB852.TXT \
    PROB851.TXT \
    PROB758.TXT \
    PROB757.TXT \
    PROB756.TXT \
    PROB755.TXT \
    PROB754.TXT \
    PROB753.TXT \
    PROB752.TXT \
    PROB751.TXT \
    PROB708.TXT \
    PROB707.TXT \
    PROB706.TXT \
    PROB705.TXT \
    PROB704.TXT \
    PROB703.TXT \
    PROB702.TXT \
    PROB701.TXT \
    PROB658.TXT \
    PROB657.TXT \
    PROB656.TXT \
    PROB655.TXT \
    PROB654.TXT \
    PROB653.TXT \
    PROB652.TXT \
    PROB651.TXT \
    PROB608.TXT \
    PROB607.TXT \
    PROB606.TXT \
    PROB605.TXT \
    PROB604.TXT \
    PROB603.TXT \
    PROB602.TXT \
    PROB601.TXT \
    PROB558.TXT \
    PROB557.TXT \
    PROB556.TXT \
    PROB555.TXT \
    PROB554.TXT \
    PROB553.TXT \
    PROB552.TXT \
    PROB551.TXT \
    PROB508.TXT \
    PROB507.TXT \
    PROB506.TXT \
    PROB505.TXT \
    PROB504.TXT \
    PROB503.TXT \
    PROB502.TXT \
    PROB501.TXT \
    PROB408.TXT \
    PROB407.TXT \
    PROB406.TXT \
    PROB405.TXT \
    PROB404.TXT \
    PROB403.TXT \
    PROB402.TXT \
    PROB401.TXT \
    FORMAT.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB858.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB857.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB856.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB855.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB854.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB853.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB852.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB851.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB758.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB757.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB756.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB755.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB754.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB753.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB752.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB751.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB708.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB707.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB706.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB705.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB704.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB703.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB702.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB701.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB658.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB657.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB656.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB655.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB654.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB653.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB652.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB651.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB608.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB607.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB606.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB605.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB604.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB603.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB602.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB601.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB558.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB557.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB556.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB555.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB554.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB553.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB552.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB551.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB508.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB507.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB506.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB505.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB504.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB503.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB502.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB501.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB408.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB407.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB406.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB405.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB404.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB403.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB402.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB401.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/FORMAT.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB858.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB857.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB856.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB855.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB854.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB853.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB852.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB851.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB758.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB757.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB756.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB755.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB754.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB753.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB752.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB751.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB708.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB707.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB706.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB705.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB704.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB703.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB702.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB701.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB658.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB657.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB656.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB655.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB654.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB653.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB652.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB651.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB608.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB607.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB606.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB605.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB604.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB603.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB602.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB601.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB558.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB557.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB556.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB555.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB554.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB553.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB552.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB551.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB508.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB507.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB506.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB505.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB504.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB503.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB502.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB501.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/FORMAT.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB858.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB857.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB856.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB855.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB854.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB853.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB852.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB851.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB758.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB757.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB756.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB755.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB754.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB753.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB752.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB751.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB708.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB707.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB706.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB705.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB704.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB703.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB702.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB701.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB658.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB657.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB656.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB655.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB654.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB653.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB652.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB651.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB608.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB607.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB606.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB605.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB604.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB603.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB602.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB601.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB558.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB557.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB556.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB555.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB554.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB553.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB552.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB551.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB508.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB507.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB506.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB505.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB504.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB503.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB502.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/PROB501.TXT \
    ../build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug/FORMAT.TXT
