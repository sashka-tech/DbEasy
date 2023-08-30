QT           += sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DbEasy
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
PROJECT_ROOT_DIR = $${_PRO_FILE_PWD_}/
TEMP_DIR = $${PROJECT_ROOT_DIR}tmp/
OBJS_DIR = $${TEMP_DIR}objs/
BIN_DIR = $${PROJECT_ROOT_DIR}bin/

debug{
OBJECTS_DIR=$${OBJS_DIR}debug/
DESTDIR=$${BIN_DIR}debug/
}else:release{
OBJECTS_DIR=$${OBJS_DIR}release/
DESTDIR=$${BIN_DIR}release/
}

MOC_DIR=$${TEMP_DIR}moc/
RCC_DIR=$${TEMP_DIR}rcc/
UI_DIR=$${TEMP_DIR}uic/

HEADERS       = \
                conn.h \
                mainwindow.h
SOURCES       = main.cpp \
                conn.cpp \
                mainwindow.cpp
requires(qtConfig(tableview))
