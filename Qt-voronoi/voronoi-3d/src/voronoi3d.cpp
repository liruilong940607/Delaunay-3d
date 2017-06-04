/*This cpp file mainly contains function voronoi3d

 */

#include"point_sets.h"
#include"Tetrahedron.h"
#include<time.h>




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

    //find out tetrahedron on the convhull
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
            if (find_farest_voronoi( tris[j], max_id ))
                reverse(tris[j]);
                if (find_farest_voronoi( tris[j], max_id ))
                    continue;
            Triangle t = Triangle(S[tris[j][0]],S[tris[j][1]],S[tris[j][2]]);
            printf("%d\n", i);
            if(is_hit(t.o,t.getNormal(),min,max,p))
                for(int k=0;k<3;k++) polyvec[tris[j][k]].push_back(p);
        }

    }

//    for( int i=0;i<TETRA.size();i++) {

//        if(exm_pnts[TETRA[i][0]]+exm_pnts[TETRA[i][1]]+
//           exm_pnts[TETRA[i][2]]+exm_pnts[TETRA[i][3]]>2){ // three points on the convhull
//            v.clear();
//            for(int j=0;j<4;j++)
//                if(exm_pnts[TETRA[i][j]]) v.push_back(TETRA[i][j]);
//                else p_in = TETRA[i][j];
//            Triangle t = Triangle(S[v[0]],S[v[1]],S[v[2]]);
//            if(dist_p2plane(S[p_in],S[v[0]],S[v[1]],S[v[2]])>0)
//                t = Triangle(S[v[2]],S[v[1]],S[v[0]]);
//            printf("%d\n", i);
//            if(is_hit(t.o,t.getNormal(),min,max,p))
//                for(int j=0;j<3;j++) polyvec[v[j]].push_back(p);
//        }
//    }

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
    for(int i=0;i<dln.tetras.size();i++)
        if(dln.tetras[i].r>max_r) {max_r=dln.tetras[i].r;max_id=i;}

    return max_id;
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
    for ( int j=0; j<S_id.size(); j++ ) {
        if ( S_id[j]==pnt[0] || // those points should not be vertices of tri
             S_id[j]==pnt[1] ||
             S_id[j]==pnt[2] ) {}
        else {
            d = dist_p2plane( S[S_id[j]], S[pnt[0]], S[pnt[1]], S[pnt[2]] );
            if (dmax<d) { dmax = d; max_id = j; }
        }
    }

    if (dmax>0) return true;
    //else if (dmax==0.0f && !exm_pnts[S_id[max_id]]) return true;

    return false;
}


//int voronoi3d_demo() {
//    srand((unsigned)time(0));
//    //vector<Vector3> s;
//    Triangle TT = Triangle(Vector3(0.0f,0.0f,0.0f),Vector3(1.0f,0.0f,0.0f),
//                    Vector3(0.0f,1.0f,0.0f));
//    printf("center %f %f %f\n",TT.o.X,TT.o.Y,TT.o.Z);
//    Vector3 s[8] = {Vector3(0,0,0),Vector3(1,0,0),
//                    Vector3(0,1,0),Vector3(0,0,1),
//                    Vector3(0.3f,0.3f,0.3f),
//                    Vector3(0.5f,0.5f,0.5f),
//                    Vector3(0.5f,0.5f,1.5f),
//                    Vector3(0.3f,0.8f,0.8f),

//    };
//    //Vector3 v;
//    //for(int i=0;i<8;i++) s.push_back( v.Rand_Vector(0,10) );

//    PointSets3D PS( s,8 );

//    // print S
//    for(int i=0;i<8;i++) printf("(%f %f %f)\n",s[i].X,s[i].Y,s[i].Z);

//    PS.Voronoi3d( Vector3(-2,-2,-2),Vector3(2,2,2) );




//    return 0;
//}
