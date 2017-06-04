/**
 * Tetrahedron class
 *
 * @author Ruilong Li
 */

#ifndef _TETRAHEDRON_H
#define _TETRAHEDRON_H

#include "Triangle.h"
#include <vector>
#include <cmath>
#include <array>
using namespace std;

class Tetrahedron {
public:
    vector<Vector3> vertices;
    Vector3 o;      // 外接circle 中心
    float   r;          // 外接circle 半径
    Tetrahedron(){}
    Tetrahedron(vector<Vector3> v) {
        this->vertices = v;
        getCenterCircumcircle();
    }

    Tetrahedron(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4) {
        vector<Vector3> vertices;
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        vertices.push_back(v4);
        this->vertices = vertices;
        getCenterCircumcircle();
    }

    bool equals(Tetrahedron t) {
        int count = 0;
        for (int i = 0; i<this->vertices.size(); i++)
            for (int j = 0; j<t.vertices.size(); j++)
                if (this->vertices[i] == t.vertices[j])
                    count++;
        if (count == 4) return true;
        return false;
    }

    vector<Line> getLines() {
        vector<Line> lines;
        lines.push_back(Line(vertices[0], vertices[1]));
        lines.push_back(Line(vertices[0], vertices[2]));
        lines.push_back(Line(vertices[0], vertices[3]));
        lines.push_back(Line(vertices[1], vertices[2]));
        lines.push_back(Line(vertices[1], vertices[3]));
        lines.push_back(Line(vertices[2], vertices[3]));
        return lines;
    }
    array<int,4> getVerticesIndex() {
        array<int,4> a={vertices[0].index,
                        vertices[1].index,
                        vertices[2].index,
                        vertices[3].index};
        return a;
    }
private:
    // 四面体外接球
    void getCenterCircumcircle() {
        Vector3 v1 = vertices[0];
        Vector3 v2 = vertices[1];
        Vector3 v3 = vertices[2];
        Vector3 v4 = vertices[3];

        double A[][3] = {
            {v2.X-v1.X, v2.Y-v1.Y, v2.Z-v1.Z},
            {v3.X-v1.X, v3.Y-v1.Y, v3.Z-v1.Z},
            {v4.X-v1.X, v4.Y-v1.Y, v4.Z-v1.Z}
        };
        double b[] = {
            0.5 * (v2.X*v2.X - v1.X*v1.X + v2.Y*v2.Y - v1.Y*v1.Y + v2.Z*v2.Z - v1.Z*v1.Z),
            0.5 * (v3.X*v3.X - v1.X*v1.X + v3.Y*v3.Y - v1.Y*v1.Y + v3.Z*v3.Z - v1.Z*v1.Z),
            0.5 * (v4.X*v4.X - v1.X*v1.X + v4.Y*v4.Y - v1.Y*v1.Y + v4.Z*v4.Z - v1.Z*v1.Z)
        };
        double x[3] = {0., 0., 0.};

        double det = (v2.X-v1.X) * (v3.Y-v1.Y) * (v4.Z-v1.Z) + (v3.X-v1.X) * (v4.Y-v1.Y) * (v2.Z-v1.Z) + (v4.X-v1.X) * (v2.Y-v1.Y) * (v3.Z-v1.Z)
        - (v2.X-v1.X) * (v4.Y-v1.Y) *(v3.Z-v1.Z) - (v3.X-v1.X) * (v2.Y-v1.Y) * (v4.Z-v1.Z) - (v4.X-v1.X) * (v3.Y-v1.Y) * (v2.Z-v1.Z);

        if (det == 0) {
            r = -1;
        }
        else {
            double A_inverse[][3] = {
                {(v3.Y-v1.Y)*(v4.Z-v1.Z)-(v3.Z-v1.Z)*(v4.Y-v1.Y),  (v2.Z-v1.Z)*(v4.Y-v1.Y)-(v2.Y-v1.Y)*(v4.Z-v1.Z),  (v2.Y-v1.Y)*(v3.Z-v1.Z)-(v2.Z-v1.Z)*(v3.Y-v1.Y)},
                {(v3.Z-v1.Z)*(v4.X-v1.X)-(v3.X-v1.X)*(v4.Z-v1.Z),  (v2.X-v1.X)*(v4.Z-v1.Z)-(v2.Z-v1.Z)*(v4.X-v1.X),  (v3.X-v1.X)*(v2.Z-v1.Z)-(v2.X-v1.X)*(v3.Z-v1.Z)},
                {(v3.X-v1.X)*(v4.Y-v1.Y)-(v3.Y-v1.Y)*(v4.X-v1.X),  (v2.Y-v1.Y)*(v4.X-v1.X)-(v2.X-v1.X)*(v4.Y-v1.Y),  (v2.X-v1.X)*(v3.Y-v1.Y)-(v3.X-v1.X)*(v2.Y-v1.Y)}
            };

            for (int i=0; i<3; i++) {
                for (int j=0; j<3; j++)
                    x[i] += A_inverse[i][j] * b[j];
                x[i] /= det;
            }
            o = Vector3((float)x[0], (float)x[1], (float)x[2]);
            r = v1.Distancef(&o);
        }
    }
};

#endif
