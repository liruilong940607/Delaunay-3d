#ifndef CUBE_H
#define CUBE_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>
#include "Vector3.h"
#include "Delaunay.h"
#include <random>
#include <vector>
#include "point_sets.h"
#include <map>
#define PI 3.141592653589

class Cube
{
public:
    Cube();
    const GLfloat *constData() const { return m_data.constData(); }
    int count() const { return m_count; }
    int vertexCount() const { return m_count / 3; }

    Delaunay d;
    void set_paint_points();
    void set_paint_delauny();
    void set_paint_voronoi_vertics();
    void set_paint_voronoi_cell();
    void set_paint_voronoi_cell_all();
private:
    std::vector<Vector3> SetPointsDelaunay();
    void add(const Vector3 &v, const Vector3 &n);
    void add(const Vector3 &v);
    QVector<GLfloat> m_data;
    int m_count;
    int delaunayPointsCount;
    std::vector<Vector3> vec;

};

#endif // CUBE_H
