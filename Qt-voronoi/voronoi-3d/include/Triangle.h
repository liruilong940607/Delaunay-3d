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
    Vector3 o;
    float r;
    Triangle(Vector3 v1, Vector3 v2, Vector3 v3) {
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
        getCenterCircumcircle();
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
    // 外接circle
        void getCenterCircumcircle() {

            double A[][3] = {
                {v2.X - v1.X, v2.Y-v1.Y, v2.Z-v1.Z},
                {v3.X - v1.X, v3.Y-v1.Y, v3.Z-v1.Z},
            };
            double b[] = {
                0.5 * (v2.X*v2.X - v1.X*v1.X + v2.Y*v2.Y - v1.Y*v1.Y + v2.Z*v2.Z - v1.Z*v1.Z),
                0.5 * (v3.X*v3.X - v1.X*v1.X + v3.Y*v3.Y - v1.Y*v1.Y + v3.Z*v3.Z - v1.Z*v1.Z),
            };
            double x[3];
            if (gauss(A, b, x) == 0) {
                // o = NULL;
                r = -1;
            } else {
                o = Vector3((float)x[0], (float)x[1], (float)x[2]);
                r = v1.Distancef(&o);
            }
        }

        /** LU分解による方程式の解法 **/
        double lu(double a[][3], int ip[]) {
            int n = 2;//a.length;
            double weight[n];

            for(int k = 0; k < n; k++) {
                ip[k] = k;
                double u = 0;
                for(int j = 0; j < n; j++) {
                    double t = fabs(a[k][j]);
                    if (t > u) u = t;
                }
                if (u == 0) return 0;
                weight[k] = 1/u;
            }
            double det = 1;
            for(int k = 0; k < n; k++) {
                double u = -1;
                int m = 0;
                for(int i = k; i < n; i++) {
                    int ii = ip[i];
                    double t = fabs(a[ii][k]) * weight[ii];
                    if(t>u) { u = t; m = i; }
                }
                int ik = ip[m];
                if (m != k) {
                    ip[m] = ip[k];
                    ip[k] = ik;
                    det = -det;
                }
                u = a[ik][k];
                det *= u;
                if (u == 0) return 0;
                for (int i = k+1; i < n; i++) {
                    int ii = ip[i];
                    double t = (a[ii][k] /= u);
                    for(int j = k+1; j < n; j++)
                        a[ii][j] -= t * a[ik][j];
                }
            }
            return det;
        }
        void solve(double a[][3], double b[], int ip[], double x[]) {
            int n = 2;//a.length;
            for(int i = 0; i < n; i++) {
                int ii = ip[i]; double t = b[ii];
                for (int j = 0; j < i; j++)
                    t -= a[ii][j] * x[j];
                x[i] = t;
            }
            for (int i = n-1; i >= 0; i--) {
                double t = x[i];
                int ii = ip[i];
                for(int j = i+1; j < n; j++)
                    t -= a[ii][j] * x[j];
                x[i] = t / a[ii][i];
            }
        }
        double gauss(double a[][3], double b[], double x[]) {
            int n = 2;//a.length;
            int ip[n];
            double det = lu(a, ip);

            if(det != 0) {
                solve(a, b, ip, x);
            }
            return det;
        }

};
#endif
