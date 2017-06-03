#ifndef _VECTOR3_H
#define _VECTOR3_H
#include <cmath>
#include <iostream>
using namespace std;

class Vector3{
    public:
        Vector3();
        Vector3(Vector3 *);
        Vector3(const Vector3&);
        Vector3(float, float, float);
        Vector3(int, int, int);
        ~Vector3();

        float X;
        float Y;
                float Z;

        int Distance(Vector3 *);
        float Distancef(Vector3 *);
        float Length();
        Vector3 Normalize();
        Vector3 operator- (Vector3);
        Vector3 operator+ (Vector3);
        Vector3 operator+= (Vector3);
        Vector3 operator* (Vector3);
        Vector3 operator* (float);

        Vector3 operator* (int);
        Vector3 cross(Vector3 v);
        float dot(Vector3);
        bool operator== (Vector3);
        bool operator!= (Vector3);
        friend ostream& operator << (ostream&, Vector3& v);

        Vector3 normalize();  // used in deluanay
        int index; //index in origin pointset. used for deluanay => voronoi
        void setindex(int idx){index = idx;}
        int getindex(){return index;}
};
#endif

