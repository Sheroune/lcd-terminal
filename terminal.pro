QT += widgets serialport
requires(qtConfig(combobox))

TARGET = terminal
TEMPLATE = app

SOURCES += \
    lcdwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    console.cpp

HEADERS += \
    lcdinput.h \
    lcdwindow.h \
    mainwindow.h \
    settingsdialog.h \
    console.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    terminal.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/serialport/terminal
INSTALLS += target
