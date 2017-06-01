#ifndef _CONVHULL_H
#define _CONVHULL_H

#include"Vector3.h"
#include<stdlib.h>
#include<vector>
#include<array>

using namespace std;

class QuickHull3D {
public:
	QuickHull3D() {}
	QuickHull3D( vector<Vector3> _S ) {
		for(vector<Vector3>::iterator iter=_S.begin();
			iter != _S.end(); iter++) 
			S.push_back( *iter );
	}
	QuickHull3D( Vector3 *_S, int size ) {
		for( int i=0; i<size; i++ ) {
			S.push_back( _S[i] );
		}
	}
	void set_points( vector<Vector3> _S ) {
		for(vector<Vector3>::iterator iter=_S.begin();
			iter != _S.end(); iter++) 
			S.push_back( *iter );
	}
	void set_points( Vector3 *_S, int size ) {
		for( int i=0; i<size; i++ ) {
			S.push_back( _S[i] );
		}
	}
	/*the main function to find Hull
	  if only 1 or 2 points in S, K.size() would be zero.
	  if 3 points, K would contain one triangle facet
	 */
	vector<array<Vector3,3>> Quick_Hull3D();

	/* find first 3 points on the convex hull 
       to form triangle facet return index
	 */
	array<Vector3,3> find_extreme_points();

	// find x,y,z right most point, return index 
	array<array<int,2>,3> findmost_xyz();

	// calculate distance between P and line P1,P2
	float dist_p2line( Vector3, Vector3, Vector3 );

	/* calculate distance between P and triangle facet P1,P2,P3
       plus if normal vector point to P1
       minus else 
     */
	float dist_p2plane( Vector3, Vector3, Vector3, Vector3 );

	/* split_S() split [i,j) by plane formed by 3 points array<int,3>,
	   mark split with order k returned.
	   find_hull() pick the farest point P from normal-wise space S[i,k), 
	   form 4 new triangles and split each on S[i,k),
	   until k=i ( no more points outside )
	   push array<int,3> back into K
	 */
	int split_S( int, int, array<Vector3,3> );
	void find_hull(int, int, array<Vector3,3> );
	

private:
	vector<Vector3> S;
	vector<Vector3> S_tmp;

	// K is the convex hull finaly returned by Quick_Hull3D
	vector<array<Vector3,3>> K;

	void swap( int i, int j ) { 
		Vector3 temp = S[i];   
		S[i] = S[j];
		S[j] = temp;
	}

};




#endif