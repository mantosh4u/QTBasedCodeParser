TEMPLATE = app

INCLUDEPATH += C:/SourceCode/LSourceCode/boost_1_58_0
LIBS += "-LC:/SourceCode/LSourceCode/boost_1_58_0/stage/lib/"


QT += qml quick widgets

SOURCES += main.cpp \
    filescan.cpp \
    directorystore.cpp \
    fascade.cpp \
    mainguiwindow.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    filescan.h \
    directorystore.h \
    fascade.h \
    mainguiwindow.h \
    getfilenamevisitor.h
