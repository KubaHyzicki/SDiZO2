TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    fileread.cpp \
    graph.cpp \
    interface.cpp \
    kruskal.cpp \
    prim.cpp \
    dijkstra.cpp \
    bellman_ford.cpp \
    linuxtime.cpp

HEADERS += \
    graph.h \
    interface.h \
    linuxtime.h
