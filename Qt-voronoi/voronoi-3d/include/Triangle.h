/**
 * Triangle class
 *
 * @author Ruilong Li
 */
#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "Line.h"
#include <vector>
using namespace std;

class Triangle {
public:
    Vector3 v1, v2, v3;
    Vector3 o;  // 外接园圆心
    float r;   // 外接圆半径

    Triangle(Vector3 v1, Vector3 v2, Vector3 v3) {
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
        getCircumcircle();
    }
    Vector3 getNormal() {
        Vector3 edge1 = Vector3(v2.X-v1.X, v2.Y-v1.Y, v2.Z-v1.Z);
        Vector3 edge2 = Vector3(v3.X-v1.X, v3.Y-v1.Y, v3.Z-v1.Z);

        Vector3 normal = edge1.cross(edge2);
        normal.normalize();
        return normal;
    }

    void turnBack() {
        Vector3 tmp = this->v3;
        this->v3 = this->v1;
        this->v1 = tmp;
    }

    vector<Line> getLines() {
        vector<Line> l;
        l.push_back(Line(v1, v2));
        l.push_back(Line(v2, v3));
        l.push_back(Line(v3, v1));
        return l;
    }


    /*bool equals(Triangle t) {
        vector<Line> lines1 = this->getLines();
        vector<Line> lines2 = t.getLines();

        int cnt = 0;
        for(int i = 0; i < lines1.size(); i++) {
            for(int j = 0; j < lines2.size(); j++) {
                if (lines1[i].equals(lines2[j]))
                    cnt++;
            }
        }
        if (cnt == 3) return true;
        else return false;
    }*/

    bool equals(Triangle t) {
        int cnt = 0;
        if (v1 == t.v1)  cnt++;
        if (v1 == t.v2)  cnt++;
        if (v1 == t.v3)  cnt++;

        if (v2 == t.v1)  cnt++;
        if (v2 == t.v2)  cnt++;
        if (v2 == t.v3)  cnt++;

        if (v3 == t.v1)  cnt++;
        if (v3 == t.v2)  cnt++;
        if (v3 == t.v3)  cnt++;

        if (cnt == 3)
            return true;
        else
            return false;
    }

    void getCircumcircle() {
        Vector3 normal = getNormal();

        double A[][3] = {
            {v2.X-v1.X, v2.Y-v1.Y, v2.Z-v1.Z},
            {v3.X-v1.X, v3.Y-v1.Y, v3.Z-v1.Z},
            {normal.X, normal.Y, normal.Z}
        };
        double b[] = {
            0.5 * (v2.X*v2.X - v1.X*v1.X + v2.Y*v2.Y - v1.Y*v1.Y + v2.Z*v2.Z - v1.Z*v1.Z),
            0.5 * (v3.X*v3.X - v1.X*v1.X + v3.Y*v3.Y - v1.Y*v1.Y + v3.Z*v3.Z - v1.Z*v1.Z),
            (normal.X*v1.X + normal.Y*v1.Y + normal.Z*v1.Z)
        };
        double x[3] = {0.,0.,0.};

        double det = (v3.X-v1.X) * normal.Y * (v2.Z-v1.Z)+ (v2.X-v1.X) * (v3.Y-v1.Y) * normal.Z + normal.X * (v2.Y-v1.Y) * (v3.Z-v1.Z)
               - (v2.X-v1.X) * normal.Y *(v3.Z-v1.Z) - (v3.X-v1.X) * (v2.Y-v1.Y) * normal.Z - normal.X * (v3.Y-v1.Y) * (v2.Z-v1.Z);

        if (det == 0) {
            r = -1;
        }
        else {
            double A_inverse[][3] = {
                {(v3.Y-v1.Y)*normal.Z-(v3.Z-v1.Z)*normal.Y,  (v2.Z-v1.Z)*normal.Y-(v2.Y-v1.Y)*normal.Z,  (v2.Y-v1.Y)*(v3.Z-v1.Z)-(v2.Z-v1.Z)*(v3.Y-v1.Y)},
                {(v3.Z-v1.Z)*normal.X-(v3.X-v1.X)*normal.Z,  (v2.X-v1.X)*normal.Z-(v2.Z-v1.Z)*normal.X,  (v3.X-v1.X)*(v2.Z-v1.Z)-(v2.X-v1.X)*(v3.Z-v1.Z)},
                {(v3.X-v1.X)*normal.Y-(v3.Y-v1.Y)*normal.X,  (v2.Y-v1.Y)*normal.X-(v2.X-v1.X)*normal.Y,  (v2.X-v1.X)*(v3.Y-v1.Y)-(v3.X-v1.X)*(v2.Y-v1.Y)}
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
