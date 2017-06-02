#-------------------------------------------------
#
# Project created by QtCreator 2017-05-31T16:29:54
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt-voronoi
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    glwidget.cpp \
    logo.cpp \
    voronoi-3d/src/Vector3.cpp \
    voronoi-3d/src/Triangle.cpp \
    voronoi-3d/src/Tetrahedron.cpp \
    voronoi-3d/src/Line.cpp \
    voronoi-3d/src/Delaunay.cpp \
    cube.cpp \
    voronoi-3d/src/convhull.cpp \
    voronoi-3d/src/half_edge_manipulation.cpp

HEADERS  += widget.h \
    glwidget.h \
    logo.h \
    voronoi-3d/include/Vector3.h \
    voronoi-3d/include/Triangle.h \
    voronoi-3d/include/Tetrahedron.h \
    voronoi-3d/include/Line.h \
    voronoi-3d/include/Delaunay.h \
    cube.h \
    voronoi-3d/include/half_edge.h \
    voronoi-3d/include/point_sets.h


INCLUDEPATH += voronoi-3d/include
# ubuntu
#LIBS += -lglut -lGLU
# mac
#LIBS+= -L/usr/local/lib -lglfw3
INCLUDEPATH+=/usr/local/include
LIBS += -framework opengl -framework glut
