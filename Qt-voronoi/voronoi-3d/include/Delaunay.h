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
using namespace std;

class Delaunay {
public:
    vector<Vector3> vertices;     // 与えられた点列
    vector<Tetrahedron> tetras;   // 四面体リスト
    vector<Line> edges;
    vector<Line> surfaceEdges;
    vector<Triangle> triangles;


    Delaunay() {
    }

    void SetData(vector<Vector3> seq) {
        for(int i = 0; i<seq.size(); i++) {
            vertices.push_back(seq[i]);
        }

        tetras.clear();
        edges.clear();

        // 1    : 点群を包含する四面体を求める
        //   1-1: 点群を包含する球を求める
        Vector3 vMax = Vector3(-999.0f, -999.0f, -999.0f);
        Vector3 vMin = Vector3( 999.0f,  999.0f,  999.0f);
        for(int i = 0; i<seq.size(); i++) {
            Vector3 v = seq[i];
            cout << "points " << i << ": " << v.X << " " << v.Y << " " << v.Z <<endl;
            if (vMax.X < v.X) vMax.X = v.X;
            if (vMax.Y < v.Y) vMax.Y = v.Y;
            if (vMax.Z < v.Z) vMax.Z = v.Z;
            if (vMin.X > v.X) vMin.X = v.X;
            if (vMin.Y > v.Y) vMin.Y = v.Y;
            if (vMin.Z > v.Z) vMin.Z = v.Z;
        }
        cout<<"vMax: "<<vMax.X<<" "<<vMax.Y<<" "<<vMax.Z<<endl;
        cout<<"vMin: "<<vMin.X<<" "<<vMin.Y<<" "<<vMin.Z<<endl;
        Vector3 center = Vector3();     // 外接球の中心座標
        center.X = 0.5f * (vMax.X - vMin.X);//fixed
        center.Y = 0.5f * (vMax.Y - vMin.Y);//fixed
        center.Z = 0.5f * (vMax.Z - vMin.Z);//fixed
        float r = -1;                       // 半径
        for(int i = 0; i<seq.size(); i++) {
            Vector3 v = seq[i];
            if (r < center.Distancef(&v)) 
                r = center.Distancef(&v);
        }
        r += 0.1f;                          // ちょっとおまけ
        cout<<"circle.o: "<<center.X<<" "<<center.Y<<" "<<center.X<<" circle.r: "<<r<<endl;
        //   1-2: 追求在球上的四面体 
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

        vector<Vector3> outer;
        outer.push_back(v1);
        outer.push_back(v2);
        outer.push_back(v3);
        outer.push_back(v4);
        tetras.push_back(Tetrahedron(v1, v2, v3, v4));
        cout<<"outer 1: "<<v1.X<<" "<<v1.Y<<" "<<v1.Z<<endl;
        cout<<"outer 2: "<<v2.X<<" "<<v2.Y<<" "<<v2.Z<<endl;
        cout<<"outer 3: "<<v3.X<<" "<<v3.Y<<" "<<v3.Z<<endl;
        cout<<"outer 4: "<<v4.X<<" "<<v4.Y<<" "<<v4.Z<<endl;
        cout<<"Tetrahedron: "<<tetras[0].o.X<<" "<<tetras[0].o.Y<<" "<<tetras[0].o.Z<<" r: "<<tetras[0].r<<endl;
        
        // 幾何形状を動的に変化させるための一時リスト
        vector<Tetrahedron> tmpTList;
        vector<Tetrahedron> newTList;
        vector<Tetrahedron> removeTList;

        cout<<"======[start]======"<<endl;

        for (int i=0; i<seq.size(); i++) {
            Vector3 v = seq[i];
            tmpTList.clear();
            newTList.clear();
            removeTList.clear();

            for (int t=0; t<tetras.size(); t++) {
                if(tetras[t].r != -1 && tetras[t].r > v.Distancef(&tetras[t].o))
                    tmpTList.push_back(tetras[t]);
            }

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

            bool isRedundancy[newTList.size()];
            for (int ii = 0; ii < newTList.size(); ii++) 
                isRedundancy[ii] = false;
            for (int ii = 0; ii< newTList.size(); ii++) 
                for (int jj = ii+1; jj < newTList.size(); jj++) 
                    if(newTList[ii].equals(newTList[jj])) {
                        isRedundancy[ii] = true;
                        isRedundancy[jj] = true;
                    }
            
            for (int ii = 0; ii < newTList.size(); ii++) {
                if (!isRedundancy[ii]) {
                    tetras.push_back(newTList[ii]);
                }
            }
        }
       
        cout<<"======[end]======"<<endl;
       
        cout<<"stage1"<<endl;       
        cout << "outer size: " << outer.size() << endl;
        bool isOuter = false;
        for (int i = 0; i<tetras.size(); i++) {
            Tetrahedron t4 = tetras[i];
            isOuter = false;
            for (int j = 0; j<t4.vertices.size(); j++) {
                Vector3 p1 = t4.vertices[j];
                for (int k = 0; k<outer.size(); k++) {
                    Vector3 p2 = outer[k];
                    if (p1.X == p2.X && p1.Y == p2.Y && p1.Z == p2.Z) {
                        isOuter = true;//true;
                    }
                }
            }
            if (isOuter) {
                cout << "tetras size: " << tetras.size() << endl;
                removeTetras(tetras, t4);
                i--;
            }
        }

        cout<<"stage2"<<endl;
        triangles.clear();
        bool isSame = false;
        for (int i = 0; i<tetras.size(); i++) {
        	Tetrahedron t = tetras[i];
            for (int j = 0; j<t.getLines().size(); j++) {
                Line l1 = t.getLines()[j];
                isSame = false;
                for (int k = 0; k<edges.size(); k++) {
                    Line l2 = edges[k];
                    if (l2.equals(l1)) {
                        isSame = true;
                        break;
                    }
                }
                if (!isSame) {
                    edges.push_back(l1);
                }
            }
        }

        // 面を求める
        cout<<"stage3"<<endl;
        vector<Triangle> triList;
        for (int i = 0; i<tetras.size(); i++) {
            Tetrahedron t = tetras[i];
            v1 = t.vertices[0];
            v2 = t.vertices[1];
            v3 = t.vertices[2];
            v4 = t.vertices[3];

            printf("======================\n");
            printf("%f %f %f\n", v1.X, v1.Y, v1.Z);
            printf("%f %f %f\n", v2.X, v2.Y, v2.Z);
            printf("%f %f %f\n", v3.X, v3.Y, v3.Z);
            printf("%f %f %f\n", v4.X, v4.Y, v4.Z);

            Triangle tri1 = Triangle(v1, v2, v3);
            Triangle tri2 = Triangle(v1, v3, v4);
            Triangle tri3 = Triangle(v1, v4, v2);
            Triangle tri4 = Triangle(v4, v3, v2);

            Vector3 n;
            // 面の向きを決める
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
                    isSameTriangle[i] = false;
                    isSameTriangle[j] = true;
                }
            }
        }
        for(int i = 0; i < triList.size(); i++) {
            if (!isSameTriangle[i]) 
                triangles.push_back(triList[i]);
        }

        cout<<"stage5"<<endl;
        surfaceEdges.clear();
        vector<Line> surfaceEdgeList;
        for(int i = 0; i < triangles.size(); i++) {
        	Triangle tri = triangles[i];
        	for (int j = 0; j < tri.getLines().size(); j++) {
        	   surfaceEdgeList.push_back(tri.getLines()[j]);
        	}
        }
        cout<<"stage6"<<endl;
        bool isRedundancy[surfaceEdgeList.size()];
        for(int i = 0; i < surfaceEdgeList.size()-1; i++) {
            for (int j = i+1; j < surfaceEdgeList.size(); j++) {
                if (surfaceEdgeList[i].equals(surfaceEdgeList[j])) 
                    isRedundancy[j] = true;
            }
        }
        cout<<"stage7"<<endl;
        for (int i = 0; i < surfaceEdgeList.size(); i++) {
            if (!isRedundancy[i]) 
                surfaceEdges.push_back(surfaceEdgeList[i]);
        }
        cout<<"stage8"<<endl;
    }

private:
    void removeTetras(vector<Tetrahedron>& tetras, Tetrahedron t) {
        vector<Tetrahedron>::iterator it;
        for (it = tetras.begin(); it != tetras.end(); ) {
            if ((*it).equals(t))
                it = tetras.erase(it);
            else
                it++;
        }
    }
};
#endif
