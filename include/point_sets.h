#ifndef _POINTSETS_H
#define _POINTSETS_H

#include"Vector3.h"
#include<stdlib.h>
#include<vector>
#include<array>
#include<stack>
#include"half_edge.h"

using namespace std;

class PointSets3D {
public:
	PointSets3D() { S.clear(); }
	PointSets3D( vector<Vector3> _S ) {
		S.clear();
		for(vector<Vector3>::iterator iter=_S.begin();
			iter != _S.end(); iter++) 
			S.push_back( *iter );
	}
	PointSets3D( Vector3 *_S, int size ) {
		S.clear();
		for( int i=0; i<size; i++ ) {
			S.push_back( _S[i] );
		}
	}
	void set_points( vector<Vector3> _S ) {
		S.clear(); S_id.clear(); exm_pnts.clear();
		for(vector<Vector3>::iterator iter=_S.begin();
			iter != _S.end(); iter++) 
			S.push_back( *iter );
	}
	void set_points( Vector3 *_S, int size ) {
		S.clear(); S_id.clear(); exm_pnts.clear();
		for( int i=0; i<size; i++ ) {
			S.push_back( _S[i] );
		}
	}



	/*the main function to find Hull
	  if only 1 or 2 points in S, K.size() would be zero.
	  if 3 points, K would contain one triangle facet
	 */
	vector<array<int,3>> Quick_Hull3D();
	vector<int> get_Extreme_pnts_id();
	vector<bool> get_Extreme_pnts_label();
	

	/*construct voronoi3d by delaunay triangulation*/
	//vector<array<int,4>> Delaunay();
	//vector<vector<array<int,3>>> Voronoi3d( float,float,float,float);
	//int get_Biggest_Circle();


private:
	/* find first 3 points on the convex hull 
       to form triangle facet return index
	 */
	array<int,4> find_nondegenerate_polyhedron();




	// find x,y,z right most point, return index 
	array<array<int,2>,3> findmost_xyz();



	// calculate distance between P and line P1,P2
	float dist_p2line( Vector3, Vector3, Vector3 );



	/* calculate distance between P and triangle facet P1,P2,P3
       plus if normal vector point to P1
       minus else 
     */
	float dist_p2plane( Vector3, Vector3, Vector3, Vector3 );



	// judge if p,p1,p2 are on the same line
	bool is_on_line( Vector3,Vector3,Vector3 );

	// judge if p,p1,p2,p3 are on the same plane
	bool is_on_plane( Vector3,Vector3,Vector3,Vector3 );


	/* split_S() split [i,j) by plane formed by 3 points array<int,3>,
	   mark split with order k returned.
	   find_hull() pick the farest point P from normal-wise space S[i,k), 
	   form 4 new triangles and split each on S[i,k),
	   until k=i ( no more points outside )
	   push array<int,3> back into K
	 */
	void kill_points( vector<Face*>& );
	void find_hull( stack<Face*>& );
	bool find_farest( array<int,3>, int& );
	void swap( int i, int j ) { 
		int temp = S_id[i];   
		S_id[i] = S_id[j];
		S_id[j] = temp;
	}
	void reverse(array<int,3>& a) {
		int temp = a[0]; a[0] = a[2]; a[2] = temp;
	}


	// calculate centre of circumcircle
	Vector3 circle_centre( Vector3,Vector3,Vector3,Vector3 );
	

	// S is the points set
	vector<Vector3> S;

	// K is the convex hull finaly returned by Quick_Hull3D()
	vector<array<int,3>> K;
	vector<int> S_id; // extreme points saved after Quick_Hull3D()
	vector<bool> exm_pnts; // points'label(0-in/1-out) saved 


	// TRI is the results of triangulation returned by Delaunay()
	vector<array<int,4>> TRI;
	vector<float> TRI_radius;// radius of circumcircle of TRI
	vector<Vector3> Vor_Vertex;// voronoi vertices, same indices with TRI
	vector<vector<array<int,3>>> Polytope;//polytope returned by voronoi3d, restricted by viewport
	

	

};




#endif