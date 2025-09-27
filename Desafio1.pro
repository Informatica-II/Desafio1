TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        crypto.cpp \
        descompresion.cpp \
        main.cpp \
        solver.cpp

HEADERS += \
    crypto.h \
    descompresion.h \
    solver.h


DISTFILES += \
        Encriptado1.txt \
        pista1.txt \
        Encriptado2.txt \
        pista2.txt \
        Encriptado3.txt \
        pista3.txt \
        Encriptado4.txt \
        pista4.txt
