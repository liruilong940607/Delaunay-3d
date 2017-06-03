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
        double x[3];

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



    /*void getCenterCircumcircle() {
        Vector3 v1 = vertices[0];
        Vector3 v2 = vertices[1];
        Vector3 v3 = vertices[2];
        Vector3 v4 = vertices[3];
        double A[][3] = {
            {v2.X - v1.X, v2.Y-v1.Y, v2.Z-v1.Z},
            {v3.X - v1.X, v3.Y-v1.Y, v3.Z-v1.Z},
            {v4.X - v1.X, v4.Y-v1.Y, v4.Z-v1.Z}
        };
        double b[] = {
            0.5 * (v2.X*v2.X - v1.X*v1.X + v2.Y*v2.Y - v1.Y*v1.Y + v2.Z*v2.Z - v1.Z*v1.Z),
            0.5 * (v3.X*v3.X - v1.X*v1.X + v3.Y*v3.Y - v1.Y*v1.Y + v3.Z*v3.Z - v1.Z*v1.Z),
            0.5 * (v4.X*v4.X - v1.X*v1.X + v4.Y*v4.Y - v1.Y*v1.Y + v4.Z*v4.Z - v1.Z*v1.Z)
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
    // LU分解による方程式の解法
    double lu(double a[][3], int ip[]) {
        int n = 3;//a.length;
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
        int n = 3;//a.length;
        for(int i = 0; i < n; i++) {
            int ii = ip[i];
            double t = b[ii];
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
        int n = 3;//a.length;
        int ip[n];
        double det = lu(a, ip);
        if(det != 0) {
            solve(a, b, ip, x);
        }
        return det;
    }
    */
};

#endif
