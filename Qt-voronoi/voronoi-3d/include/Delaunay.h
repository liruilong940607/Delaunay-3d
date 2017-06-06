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
        cout << "input points num is : " << seq.size() << endl;
        for(int i = 0; i<seq.size(); i++) {
            vertices.push_back(seq[i]);
        }
        sort(vertices.begin(), vertices.end(), myComp); // sort by x, fome small to big
        vertices.erase(unique(vertices.begin(), vertices.end(), myUnique), vertices.end()); // erase the same points
        cout << "need to process num is: " << vertices.size() << endl;

        tetras.clear();

        Vector3 vMax = Vector3(-9999.0f, -9999.0f, -9999.0f);
        Vector3 vMin = Vector3( 9999.0f,  9999.0f,  9999.0f);

        for(int i = 0; i<vertices.size(); i++) {
            Vector3 v = vertices[i];
            vMax.X = max(vMax.X, v.X);
            vMax.Y = max(vMax.Y, v.Y);
            vMax.Z = max(vMax.Z, v.Z);
            vMin.X = min(vMin.X, v.X);
            vMin.Y = min(vMin.Y, v.Y);
            vMin.Z = min(vMin.Z, v.X);
        }
        cout << "vMax: " << vMax.X << " " << vMax.Y << " " << vMax.Z << endl;
        cout << "vMin: " << vMin.X << " " << vMin.Y << " " << vMin.Z << endl;
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
        cout << "circle.o: " << center << " circle.r: " << r << endl;
        cout << "get circle" << endl;

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

        cout << "outer 1: " << v1<< endl;
        cout << "outer 2: " << v2 << endl;
        cout << "outer 3: " << v3 << endl;
        cout << "outer 4: " << v4 << endl;
        bigtetra = Tetrahedron(v1, v2, v3, v4);
        vector<Tetrahedron> tmpTList;
        vector<Tetrahedron> newTList;

        std::vector<int> isRedundancy_vec_tmp;
        Vector3 v_tmp = v4;
        eventvec.push_back(Event(CreateBigTetra,tetras,tmpTList,newTList,isRedundancy_vec_tmp,v_tmp));

        for (int i=0; i<vertices.size(); i++)  {
            cout << "i: " << i << endl;
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
            cout << "tetras" << endl;
            tmpProcess.push_back(tmpTList);
            for (int t=0; t<tmpTList.size(); t++) {
                Tetrahedron t1 = tmpTList[t];
                removeTetras(tetras, t1);
                v1 = t1.vertices[0];
                v2 = t1.vertices[1];
                v3 = t1.vertices[2];
                v4 = t1.vertices[3];
                /*newTList.push_back(Tetrahedron(v1, v2, v3, v));
                newTList.push_back(Tetrahedron(v1, v2, v4, v));
                newTList.push_back(Tetrahedron(v1, v3, v4, v));
                newTList.push_back(Tetrahedron(v2, v3, v4, v));*/
                Tetrahedron new1(v1, v2, v3, v);
                Tetrahedron new2(v1, v2, v4, v);
                Tetrahedron new3(v1, v3, v4, v);
                Tetrahedron new4(v2, v3, v4, v);

                if (new1.r > 0)
                    newTList.push_back(new1);
                if (new2.r > 0)
                    newTList.push_back(new2);
                if (new3.r > 0)
                    newTList.push_back(new3);
                if (new4.r > 0)
                    newTList.push_back(new4);
            }
            eventvec.push_back(Event(CreateFourNewTetraAndRemove,tetras,tmpTList,newTList,isRedundancy_vec,v));
            cout << "newTList" << endl;
            newProcess.push_back(newTList);
            bool isRedundancy[newTList.size()];
            for (int ii = 0; ii < newTList.size(); ii++)
                isRedundancy[ii] = false;

            for (int ii = 0; ii< newTList.size()-1; ii++)
                for (int jj = ii+1; jj < newTList.size(); jj++)
                    if(newTList[ii].equals(newTList[jj])) {
                        isRedundancy[ii] = true;
                        isRedundancy[jj] = true;
                        // cout << "i: " << newTList[ii].vertices[0] << newTList[ii].vertices[1] << newTList[ii].vertices[2] << newTList[ii].vertices[3] << endl;
                        // cout << "j: " << newTList[jj].vertices[0] << newTList[jj].vertices[1] << newTList[jj].vertices[2] << newTList[jj].vertices[3] << endl;
                    }
            for (int ii = 0; ii < newTList.size(); ii++)
                isRedundancy_vec.push_back(isRedundancy[ii]);
            eventvec.push_back(Event(JudgeSameAndRemove,tetras,tmpTList,newTList,isRedundancy_vec,v));

            for (int ii = 0; ii < newTList.size(); ii++)
                if (!isRedundancy[ii])
                    tetras.push_back(newTList[ii]);
            cout << "delete" << endl;
            tetrasProcess.push_back(tetras);
            eventvec.push_back(Event(SetCurrentTetras,tetras,tmpTList,newTList,isRedundancy_vec,v));

        }
        cout << "before outer size: " << tetras.size() << endl;

        /*tmpTList.clear();
        for (int i=0; i<tetras.size()-1; i++)
            for (int j=i+1; j<tetras.size(); j++)
                if (tetras[i].equals(tetras[j]))
                    tmpTList.push_back(tetras[j]);
        for (int i=0; i<tmpTList.size(); i++)
            removeTetras(tetras, tmpTList[i]);*/

        cout << "after outer size: " << tetras.size() << endl;
        //*********************************
        vector<Vector3> addPoints;
        for (int m=0; m<outer.size(); m++) {
           cout << "m: " << m << endl;
           tmpTList.clear();
           newTList.clear();
           addPoints.clear();

           for (int i = 0; i<tetras.size(); i++) {
               Tetrahedron t = tetras[i];
               for (int j = 0; j<t.vertices.size(); j++)
                   if (t.vertices[j] == outer[m]) {
                       newTList.push_back(t);
                       for (int k= 0; k<t.vertices.size(); k++)  {
                           if (t.vertices[k] != outer[m]) {
                               bool same = false;
                               for (int u=0; u<addPoints.size(); u++)
                                   if (t.vertices[k] == addPoints[u]) {
                                       same = true;
                                       break;
                                   }
                               if (same == false)
                                   addPoints.push_back(t.vertices[k]);
                           }
                       }
                       break;
                   }
           }
           for (int i=0; i<newTList.size(); i++)
               removeTetras(tetras, newTList[i]);

            cout << "addPoint size: " << addPoints.size() << endl;
           for (int i=0; i<addPoints.size()-3; i++) {
               for (int j=i+1; j<addPoints.size()-2; j++) {
                   for (int k=j+1; k<addPoints.size()-1; k++) {
                       for (int w=k+1; w<addPoints.size(); w++) {
                           // cout << i << ' ' << j << ' ' << k << ' ' << w << endl;
                           Tetrahedron tmpT(addPoints[i], addPoints[j], addPoints[k], addPoints[w]);
                           if (tmpT.r > 0)
                               tmpTList.push_back(tmpT);
                       }
                   }
               }
           }
           cout << "tmpList size: " << tmpTList.size() << endl;
           cout << "outer size: " << tetras.size() << endl;

           vector<Tetrahedron> tmpAdd;
           tmpAdd.clear();
           bool flag;
           for (int i=0; i<tmpTList.size(); i++) {
               flag = true;
               for (int j=0; j<vertices.size(); j++) {
                   if(tmpTList[i].r > vertices[j].Distancef(&tmpTList[i].o)) {
                       flag = false;
                       break;
                   }
               }
               if (flag)
                   tmpAdd.push_back(tmpTList[i]);
           }

           for (int i=0; i<tmpAdd.size(); i++) {
               flag = true;
               for (int j=0; j<tetras.size(); j++) {
                   if (tmpAdd[i].equals(tetras[j])) {
                       flag = false;
                       break;
                   }
               }
               if (flag)
                   tetras.push_back(tmpAdd[i]);
           }
           cout << "outer size: " << tetras.size() << endl;
       }

       eventvec.push_back(Event(DeleteBigTetra,tetras,tmpTList,newTList,isRedundancy_vec_tmp,v_tmp));

       // *********************************

        cout<<"stage1"<<endl;
        /*cout << "outer size: " << outer.size() << endl;
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
        */

        cout<<"stage2"<<endl;
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
        cout<<"stage4"<<endl;
        bool isSameTriangle[triList.size()];
        for(int i = 0; i < triList.size()-1; i++) {
            for(int j = i+1; j < triList.size(); j++) {
                if (triList[i].equals(triList[j])) {
                    isSameTriangle[i] = true;
                    isSameTriangle[j] = true;
                }
            }
        }
        for(int i = 0; i < triList.size(); i++) {
            if (!isSameTriangle[i])
                triangles.push_back(triList[i]);
        }
        cout<<"stage5"<<endl;
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
