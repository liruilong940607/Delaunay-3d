/*This cpp file mainly contains function voronoi3d

 */

#include"point_sets.h"
#include"Tetrahedron.h"
#include<time.h>
#ifndef QUICKHULL_IMPLEMENTATION
#define QUICKHULL_IMPLEMENTATION
#include "quickhull.h"
#endif

vector<vector<array<Vector3,3>>> PointSets3D::Voronoi3d(Vector3 min, Vector3 max){
    if(!Polytope.empty()) return Polytope;
    if(S.empty()) {printf("no points set input!");return Polytope;}
    if(dln.tetras.empty()) delaunay();

    vector<vector<int>> polyindex;
    vector<int> index;
    for(int i=0;i<S.size();i++) {
        polyindex.push_back( index );
    }

    for(int i=0;i<TETRA.size();i++) {
        for(int j=0;j<4;j++)
            polyindex[TETRA[i][j]].push_back(i);
    }
    vector<vector<Vector3>> polyvec;
    vector<Vector3> vec;
    for(int i=0;i<polyindex.size();i++) {
        polyvec.push_back(vec);
        for(int j=0;j<polyindex[i].size();j++)
            polyvec[i].push_back( dln.tetras[polyindex[i][j]].o );
    }

    // find out which polytope cube's 8 points belong to
    float xd = max.X-min.X;
    float yd = max.Y-min.Y;
    float zd = max.Z-min.Z;
    vector<Vector3> cube;
    cube.push_back( min ); cube.push_back(Vector3(min.X+xd, min.Y,min.Z));
    cube.push_back(Vector3(min.X,min.Y+yd,min.Z));
    cube.push_back(Vector3(min.X,min.Y,min.Z+zd));
    cube.push_back( max ); cube.push_back(Vector3(max.X-xd, max.Y,max.Z));
    cube.push_back(Vector3(max.X,max.Y-yd,max.Z));
    cube.push_back(Vector3(max.X,max.Y,max.Z-zd));
    vector<Line> Segment;
    Segment.push_back(Line(cube[0],cube[1]));
    Segment.push_back(Line(cube[0],cube[2]));
    Segment.push_back(Line(cube[1],cube[7]));
    Segment.push_back(Line(cube[7],cube[2]));
    Segment.push_back(Line(cube[5],cube[4]));
    Segment.push_back(Line(cube[4],cube[6]));
    Segment.push_back(Line(cube[6],cube[3]));
    Segment.push_back(Line(cube[3],cube[5]));
    Segment.push_back(Line(cube[1],cube[6]));
    Segment.push_back(Line(cube[7],cube[4]));
    Segment.push_back(Line(cube[2],cube[5]));
    Segment.push_back(Line(cube[0],cube[3]));

    float min_dis; int min_id;
    float dis; vector<float> Dis;
    for(int i=0; i<cube.size(); i++) {
        Dis.clear();
        min_dis=100000000.0f;
        for(int j=0; j<S.size(); j++) {
            dis=S[j].Distancef(&cube[i]);
            Dis.push_back( dis );
            if(min_dis>dis) { min_dis=dis; min_id=j; }
        }
        for(int j=0; j<Dis.size(); j++)
            if(Dis[j]==min_dis)
                polyvec[j].push_back(cube[i]);
    }

    // find out intersect point of polytope with cube's segments and plane
    Vector3 p; vector<int> v; int p_in;
    if(K.empty()) Quick_Hull3D();
    for( int i=0;i<TETRA.size();i++) {
        int v1 = TETRA[i][0]; int v2 = TETRA[i][1];
        int v3 = TETRA[i][2]; int v4 = TETRA[i][3];

        vector<array<int,3>> tris;
        array<int,3> tris1 = {v1, v2, v3};
        array<int,3> tris2 = {v2, v3, v4};
        array<int,3> tris3 = {v3, v4, v1};
        array<int,3> tris4 = {v4, v1, v2};
        tris.push_back(tris1);
        tris.push_back(tris2);
        tris.push_back(tris3);
        tris.push_back(tris4);

        for (int j = 0; j< 4; j++){
            Vector3 p;
            int max_id = 0;
            //find out tetrahedron on the convhull
            if (find_farest_voronoi( tris[j], max_id )) {
                reverse(tris[j]);
                if (find_farest_voronoi( tris[j], max_id ))
                    continue;
            }
            // find out intersect of Ray and cube's plane
            Triangle t = Triangle(S[tris[j][0]],S[tris[j][1]],S[tris[j][2]]);
            if(is_hit(t.o,t.getNormal(),min,max,p)){
                for(int k=0;k<3;k++) polyvec[tris[j][k]].push_back(p);
            }
            // find out intersect of Polytope's plane and cube's segment
            Vector3 I;
            for(int k=0;k<3;k++) {
                Vector3 V0 = (S[tris[j][k]]+S[tris[j][(k+1)%3]])*0.5f;
                Vector3 n = (S[tris[j][k]]-S[tris[j][(k+1)%3]]).Normalize();
                for(int s=0;s<Segment.size();s++) {
                    if(intersect3D_SegmentPlane(Segment[s].start,Segment[s].end,V0,n,&I)==1) {
                        int id = find_nearest_id( I );
                        if(id==tris[j][k] || id==tris[j][(k+1)%3]) {
                            polyvec[tris[j][k]].push_back(I);
                            polyvec[tris[j][(k+1)%3]].push_back(I);
                        }
                    }
                }
            }
        }

    }

    // construct polytope
    vector<array<Vector3,3>> trivec;
    PointSets3D plt; array<Vector3,3> a;
    for(int i=0;i<polyvec.size();i++) {
        Polytope.push_back( trivec );
        plt.set_points( polyvec[i] );
        plt.Quick_Hull3D();
        for(int j=0; j<plt.K.size(); j++) {
            a[0]=polyvec[i][plt.K[j][0]];
            a[1]=polyvec[i][plt.K[j][1]];
            a[2]=polyvec[i][plt.K[j][2]];
            Polytope[i].push_back( a );
        }
    }

    return Polytope;
}

int PointSets3D::get_Biggest_Inscribed_Circle() {
    if(S.empty()) {printf("no points set input!");return 0;}
    if(dln.tetras.empty()) delaunay();

    float max_r = 0.0; int max_id = 0;
    for(int i=0;i<dln.tetras.size();i++){
        Vector3 center = dln.tetras[i].o;
        float r = dln.tetras[i].r;
        if (abs(center.X-2.0f)<r)
            continue;
        if (abs(center.X+2.0f)<r)
            continue;
        if (abs(center.Y-2.0f)<r)
            continue;
        if (abs(center.Y+2.0f)<r)
            continue;
        if (abs(center.Z-2.0f)<r)
            continue;
        if (abs(center.Z+2.0f)<r)
            continue;
        if(dln.tetras[i].r>max_r) {max_r=dln.tetras[i].r;max_id=i;}
    }

    return max_id;
}
bool PointSets3D::ishas3tri(Triangle tri, Vector3 p){
    Triangle tri1 = Triangle(tri.v1,tri.v2,p);
    Triangle tri2 = Triangle(tri.v1,tri.v3,p);
    Triangle tri3 = Triangle(tri.v3,tri.v2,p);
    bool samenum[3] = {0,0,0};
    for (int i = 0; i<dln.triangles.size(); i++){
        if(dln.triangles[i].equals(tri1))
            samenum[0] = 1;
        if(dln.triangles[i].equals(tri2))
            samenum[1] = 1;
        if(dln.triangles[i].equals(tri3))
            samenum[2] = 1;
    }
    if(samenum[0]+samenum[0]+samenum[0]==3)
        return true;
    return false;
}

vector<Tetrahedron> PointSets3D::delaunay() {
    if(S.empty()) {printf("no points set input!");return dln.tetras;}
    if(!dln.tetras.empty()) return dln.tetras;

    for(int i=0;i<S.size();i++) S[i].index=i;

    dln.SetData( S );

    TETRA.clear();
    for(int i=0;i<dln.tetras.size();i++) {
        TETRA.push_back(dln.tetras[i].getVerticesIndex());
    }

    return dln.tetras;
}

void swap_float( float &x, float &y ) {
    float t = x;
    x = y;
    y = t;
}

bool PointSets3D::is_hit(Vector3 c,Vector3 n,Vector3 min,Vector3 max,Vector3 &p){

    float tx1=-(-min.X+c.X)/n.X;
    float tx2=-(-max.X+c.X)/n.X;
    float ty1=-(-min.Y+c.Y)/n.Y;
    float ty2=-(-max.Y+c.Y)/n.Y;
    float tz1=-(-min.Z+c.Z)/n.Z;
    float tz2=-(-max.Z+c.Z)/n.Z;

    if (-(-min.X+c.X)<0 && n.X==0) tx1 = -10000.0f;
    if (-(-min.X+c.X)>0 && n.X==0) tx1 = 10000.0f;

    if (-(-max.X+c.X)<0 && n.X==0) tx2 = -10000.0f;
    if (-(-max.X+c.X)>0 && n.X==0) tx2 = 10000.0f;

    if (-(-min.Y+c.Y)<0 && n.Y==0) ty1 = -10000.0f;
    if (-(-min.Y+c.Y)>0 && n.Y==0) ty1 = 10000.0f;

    if (-(-max.Y+c.Y)<0 && n.Y==0) ty2 = -10000.0f;
    if (-(-max.Y+c.Y)>0 && n.Y==0) ty2 = 10000.0f;

    if (-(-min.Z+c.Z)<0 && n.Z==0) tz1 = -10000.0f;
    if (-(-min.Z+c.Z)>0 && n.Z==0) tz1 = 10000.0f;

    if (-(-max.Z+c.Z)<0 && n.Z==0) tz2 = -10000.0f;
    if (-(-max.Z+c.Z)>0 && n.Z==0) tz2 = 10000.0f;


    if ( tx1>tx2 ) swap_float( tx1, tx2 );
    if ( ty1>ty2 ) swap_float( ty1, ty2 );
    if ( tz1>tz2 ) swap_float( tz1, tz2 );

    tx1=tx1>ty1?tx1:ty1;
    tx1=tx1>tz1?tx1:tz1;

    tx2=tx2<ty2?tx2:ty2;
    tx2=tx2<tz2?tx2:tz2;

    if ( tx1<tx2  ) {
        float tin=tx1;
        float tout=tx2;
        p = c + n * tout;
        return true;
    }
    return false;
}

bool PointSets3D::find_farest_voronoi( array<int,3> pnt, int &max_id ) {
    // find farest point from Face *tri, marked with max_id
    float d, dmax;
    dmax = -1; max_id = 0;
    for ( int j=0; j<S.size(); j++ ) {
        if ( j==pnt[0] || // those points should not be vertices of tri
             j==pnt[1] ||
             j==pnt[2] ) {}
        else {
            d = dist_p2plane( S[j], S[pnt[0]], S[pnt[1]], S[pnt[2]] );
            if (dmax<d) { dmax = d; max_id = j; }
        }
    }

    if (dmax>0) return true;
    //else if (dmax==0.0f && !exm_pnts[S_id[max_id]]) return true;

    return false;
}

int PointSets3D::find_nearest_id( Vector3 p ){
    float min_dis; int min_id;
    float dis;
    min_dis=100000000.0f;
    for(int j=0; j<S.size(); j++) {
        dis=S[j].Distancef(&p);
        if(min_dis>dis) { min_dis=dis; min_id=j; }
    }
    return min_id;
}

int PointSets3D::intersect3D_SegmentPlane( Vector3 P0, Vector3 P1, Vector3 V0, Vector3 n, Vector3* I )
{
    Vector3    u = P1 - P0;
    Vector3    w = P0 - V0;

    float     D = n.dot(u);
    float     N = -n.dot(w);

    if (fabs(D) < 0.00000001) {           // segment is parallel to plane
        if (N == 0)                      // segment lies in plane
            return 2;
        else
            return 0;                    // no intersection
    }
    // they are not parallel
    // compute intersect param
    float sI = N / D;
    if (sI < 0 || sI > 1)
        return 0;                        // no intersection

    *I = P0 + u * sI;                  // compute segment intersect point
    return 1;
}
