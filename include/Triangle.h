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
    Triangle(Vector3 v1, Vector3 v2, Vector3 v3) {
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
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

    bool equals(Triangle t) {
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
    }
};
#endif