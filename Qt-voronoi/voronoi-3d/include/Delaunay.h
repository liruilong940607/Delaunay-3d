/**
 * Delaunay class
 *
 * @author Ruilong Li
 */
#ifndef _DELAUNAY_H
#define _DELAUNAY_H
#include "Tetrahedron.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "event.h"
using namespace std;

class Delaunay {
public:
    vector<Vector3> outer;               //
    vector<Vector3> vertices;           // 点列
    vector<Tetrahedron> tetras;     // 四面体
    vector<Triangle> triangles;        //

    vector<vector<Tetrahedron> > tmpProcess;
    vector<vector<Tetrahedron> > newProcess;
    vector<vector<Tetrahedron> > tetrasProcess;
    // vector<Line> edges;                //
    // vector<Line> surfaceEdges;   //

    vector<Event> eventvec;
    Tetrahedron bigtetra;
    Delaunay() {
        vertices.clear();
        triangles.clear();
        tetras.clear();
    }

    static bool myComp(const Vector3 &a, const Vector3 &b) {
        return a.X < b.X;
    }
    static bool myUnique(Vector3 &a,  Vector3 &b) {
        return a == b;
    }
    void clear() {
        tetras.clear();
        vertices.clear();
        triangles.clear();
    }
    // consider a point as a vector object
    void SetData(vector<Vector3> seq) {
        for(int i = 0; i<seq.size(); i++) {
            vertices.push_back(seq[i]);
        }
        sort(vertices.begin(), vertices.end(), myComp); // sort by x, fome small to big
        vertices.erase(unique(vertices.begin(), vertices.end(), myUnique), vertices.end()); // erase the same points

        tetras.clear();

        Vector3 vMax = Vector3(-999.0f, -999.0f, -999.0f);
        Vector3 vMin = Vector3( 999.0f,  999.0f,  999.0f);

        for(int i = 0; i<vertices.size(); i++) {
            Vector3 v = vertices[i];
            vMax.X = max(vMax.X, v.X);
            vMax.Y = max(vMax.Y, v.Y);
            vMax.Z = max(vMax.Z, v.Z);
            vMin.X = min(vMin.X, v.X);
            vMin.Y = min(vMin.Y, v.Y);
            vMin.Z = min(vMin.Z, v.X);
        }
        Vector3 center = Vector3();
        center.X = 0.5f * (vMax.X + vMin.X);  // fixed
        center.Y = 0.5f * (vMax.Y + vMin.Y);  // fixed
        center.Z = 0.5f * (vMax.Z + vMin.Z);  // fixed
        float r = -1;                       // 半径
        for(int i = 0; i<vertices.size(); i++) {
            Vector3 v = vertices[i];
            if (r < center.Distancef(&v))
                r = center.Distancef(&v);
        }
        r += 0.1f;

        Vector3 v1 = Vector3();
        v1.X = center.X;
        v1.Y = center.Y + 3.0f*r;
        v1.Z = center.Z;

        Vector3 v2 = Vector3();
        v2.X = center.X - 2.0f*(float)sqrt(2)*r;
        v2.Y = center.Y - r;
        v2.Z = center.Z;

        Vector3 v3 = Vector3();
        v3.X = center.X + (float)sqrt(2)*r;
        v3.Y = center.Y - r;
        v3.Z = center.Z + (float)sqrt(6)*r;

        Vector3 v4 = Vector3();
        v4.X = center.X + (float)sqrt(2)*r;
        v4.Y = center.Y - r;
        v4.Z = center.Z - (float)sqrt(6)*r;

        outer.push_back(v1);
        outer.push_back(v2);
        outer.push_back(v3);
        outer.push_back(v4);
        tetras.push_back(Tetrahedron(v1, v2, v3, v4));

        bigtetra = Tetrahedron(v1, v2, v3, v4);
        vector<Tetrahedron> tmpTList;
        vector<Tetrahedron> newTList;

        std::vector<int> isRedundancy_vec_tmp;
        Vector3 v_tmp = v4;
        eventvec.push_back(Event(CreateBigTetra,tetras,tmpTList,newTList,isRedundancy_vec_tmp,v_tmp));

        for (int i=0; i<vertices.size(); i++)  {
            Vector3 v = vertices[i];
            std::vector<int> isRedundancy_vec;
            tmpTList.clear();
            newTList.clear();
            eventvec.push_back(Event(SetCurrentPoint,tetras,tmpTList,newTList,isRedundancy_vec,v));
            for (int t=0; t<tetras.size(); t++) {
                if(tetras[t].r != -1 && tetras[t].r > v.Distancef(&tetras[t].o)){
                    tmpTList.push_back(tetras[t]);
                    eventvec.push_back(Event(JudgeIsInSphere,tetras,tmpTList,newTList,isRedundancy_vec,v));
                }
            }
            tmpProcess.push_back(tmpTList);
            for (int t=0; t<tmpTList.size(); t++) {
                Tetrahedron t1 = tmpTList[t];
                removeTetras(tetras, t1);
                v1 = t1.vertices[0];
                v2 = t1.vertices[1];
                v3 = t1.vertices[2];
                v4 = t1.vertices[3];
                newTList.push_back(Tetrahedron(v1, v2, v3, v));
                newTList.push_back(Tetrahedron(v1, v2, v4, v));
                newTList.push_back(Tetrahedron(v1, v3, v4, v));
                newTList.push_back(Tetrahedron(v2, v3, v4, v));
            }
            eventvec.push_back(Event(CreateFourNewTetraAndRemove,tetras,tmpTList,newTList,isRedundancy_vec,v));

            newProcess.push_back(newTList);
            bool isRedundancy[newTList.size()];
            for (int ii = 0; ii < newTList.size(); ii++)
                isRedundancy[ii] = false;

            for (int ii = 0; ii< newTList.size()-1; ii++)
                for (int jj = ii+1; jj < newTList.size(); jj++)
                    if(newTList[ii].equals(newTList[jj])) {
                        isRedundancy[ii] = true;
                        isRedundancy[jj] = true;
                    }
            for (int ii = 0; ii < newTList.size(); ii++)
                isRedundancy_vec.push_back(isRedundancy[ii]);
            eventvec.push_back(Event(JudgeSameAndRemove,tetras,tmpTList,newTList,isRedundancy_vec,v));

            for (int ii = 0; ii < newTList.size(); ii++)
                if (!isRedundancy[ii])
                    tetras.push_back(newTList[ii]);

            tetrasProcess.push_back(tetras);
            eventvec.push_back(Event(SetCurrentTetras,tetras,tmpTList,newTList,isRedundancy_vec,v));

        }

        bool isOuter = false;
        for (int i = 0; i<tetras.size(); i++) {
            Tetrahedron t4 = tetras[i];
            isOuter = false;
            for (int j = 0; j<t4.vertices.size(); j++)
                for (int k = 0; k<outer.size(); k++)
                    if (t4.vertices[j] == outer[k]) {
                        isOuter = true;
                        break;
                    }
            if (isOuter) {
                removeTetras(tetras, t4);
                i--;
            }
        }
        eventvec.push_back(Event(DeleteBigTetra,tetras,tmpTList,newTList,isRedundancy_vec_tmp,v_tmp));

        triangles.clear();
        vector<Triangle> triList;
        for (int i = 0; i<tetras.size(); i++) {
            Tetrahedron t = tetras[i];
            v1 = t.vertices[0];
            v2 = t.vertices[1];
            v3 = t.vertices[2];
            v4 = t.vertices[3];

            Triangle tri1 = Triangle(v1, v2, v3);
            Triangle tri2 = Triangle(v1, v3, v4);
            Triangle tri3 = Triangle(v1, v4, v2);
            Triangle tri4 = Triangle(v4, v3, v2);

            Vector3 n;

            n = tri1.getNormal();
            if(n.dot(v1) > n.dot(v4)) tri1.turnBack();
            n = tri2.getNormal();
            if(n.dot(v1) > n.dot(v2)) tri2.turnBack();
            n = tri3.getNormal();
            if(n.dot(v1) > n.dot(v3)) tri3.turnBack();
            n = tri4.getNormal();
            if(n.dot(v2) > n.dot(v1)) tri4.turnBack();

            triList.push_back(tri1);
            triList.push_back(tri2);
            triList.push_back(tri3);
            triList.push_back(tri4);
        }

        bool isSameTriangle[triList.size()];
        for(int i = 0; i < triList.size()-1; i++) {
            for(int j = i+1; j < triList.size(); j++) {
                if (triList[i].equals(triList[j])) {
                    isSameTriangle[i] = false;
                    isSameTriangle[j] = true;
                }
            }
        }
        for(int i = 0; i < triList.size(); i++) {
            if (!isSameTriangle[i])
                triangles.push_back(triList[i]);
        }
    }



private:
    void removeTetras(vector<Tetrahedron>& tetras, Tetrahedron t) {
        vector<Tetrahedron>::iterator it;
        for (it = tetras.begin(); it != tetras.end(); ) {
            if ((*it).equals(t)) {
                it = tetras.erase(it);
                return;
            }
            else
                it++;
        }
    }
};
#endif
