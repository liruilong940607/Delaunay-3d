/*This cpp file mainly contains function Quick_Hull3D
  that computes convex hull of point set S
  using quick hull method.

  S is vector<Vector3> with size n x 3
  and return facets set K (indices)
  K is vector<array<Vector3,3>> with size m x (3 x 3)
  for each triangle, norm vector formed by <p1,p2,p3> 
  point to the outside

  To call the function:
	QuickHull3D QH( S ); --when S is a vector<Vector3>
	QuickHull3D QH( S, n ); --when S is a Vector3 S[n]
    K = QH.Quick_Hull3D();  
  Or:
	QuickHull3D QH;
	QH.set_points( S ); --when S is a vector<Vector3>
	QH.set_points( S, n ); --when S is a Vector3 S[n]
	K = QH.Quick_Hull3D();
 */

#include"convhull.h"


void QuickHull3D::find_hull(int i, int k, array<Vector3,3> pnt ) {

	if (k==i) { K.push_back( pnt ); return; }
	float d, dmax; int max_id;
	dmax = -1; max_id = i;
	for ( int j=i; j<k; j++ ) {
		d = dist_p2plane( S[j], pnt[0], pnt[1], pnt[2] );
		if (dmax<d) { dmax = d; max_id = j; }
	}
	array<Vector3,3> tr1 = { pnt[0],pnt[1],S[max_id] };
	array<Vector3,3> tr2 = { pnt[1],pnt[2],S[max_id] };
	array<Vector3,3> tr3 = { pnt[2],pnt[0],S[max_id] };

	find_hull( i, split_S(i,k,tr1), tr1 );
	find_hull( i, split_S(i,k,tr2), tr2 );
	find_hull( i, split_S(i,k,tr3), tr3 );

}

int QuickHull3D::split_S( int i, int j, array<Vector3,3> pnt ) {
	float d; int k_split = j;
	for( int k=i; k<k_split;) {
		d = dist_p2plane( S[k], pnt[0], pnt[1], pnt[2] );
		if (d<0 || S[k]==pnt[0] || 
			       S[k]==pnt[1] || 
				   S[k]==pnt[2] )  /*points on the triangle facet should be considered
								     throw points from triangle itself to the right
								     to avoid dead recursion*/
			{--k_split; swap(k, k_split); }// be careful to use --k
		else k++;
	}
	return k_split;
}

vector<array<Vector3,3>> QuickHull3D::Quick_Hull3D() {
	if (!S.size()) { printf("No points input!"); return K; }
	switch (S.size()) {
	case 1:
		printf("only one point at (%f, %f, %f)", S[0].X,S[0].Y,S[0].Z);
		return K;
		break;
	case 2:
		printf("only two points! It's a line.");
		return K;
		break;
	}

	/*find right most points along axis x,y,z */
	array<Vector3,3> expnt = find_extreme_points();
	

	// divide S into 2 point sets S1 and S2
	int k = split_S( 0, S.size(), expnt );
	// find hull use recursion
	find_hull( 0, k, expnt );
	// reverse array and find hull in minus space
	Vector3 temp = expnt[0]; expnt[0] = expnt[2]; expnt[2] = temp;
	int new_k = split_S( k, S.size(), expnt );//pick out points from expnt
	find_hull( k, new_k, expnt );

	return K;
}


array<Vector3,3> QuickHull3D::find_extreme_points() {
	array<array<int,2>,3> mm_id = findmost_xyz();
	// uniquify candidate
	vector<int> candidate;
	array<Vector3,3> ex_points;
	bool find;
	for(int i=0; i<3; i++)
	for(int j=0; j<2; j++) {
		find = false;
		for(vector<int>::iterator iter=candidate.begin();
			iter!=candidate.end(); iter++) {
				if (mm_id[i][j]==(*iter)) { find = true; break; }
		}
		if (!find) candidate.push_back( mm_id[i][j] );
	}
	if (candidate.size()<3){
		float d; float max_d = 0.0;
		int max_id;
		// find P most far from line p1-p2
		for(int i=0; i<S.size(); i++) {
			d = dist_p2line( S[i], S[candidate[0]], S[candidate[1]] );
			if (d>max_d) { max_d = d; max_id = i; }
		}
		candidate.push_back( max_id );
	}
	for(int i=0;i<3;i++) { 
		ex_points[i]=S[candidate[i]];
	}
	return ex_points;
}


float QuickHull3D::dist_p2plane( Vector3 p, Vector3 p1, Vector3 p2, Vector3 p3 ) {
	Vector3 p1p2 = p2-p1;
	Vector3 p1p3 = p3-p1;
	Vector3 N = p1p2.cross(p1p3);
	return (p-p1).dot(N);
}


float QuickHull3D::dist_p2line( Vector3 p, Vector3 p1, Vector3 p2 ) {
	if (p==p1 || p==p2) return 0;
	Vector3 p1p = p-p1;
	Vector3 p1p2 = p2-p1;
	return (p1p2.cross(p1p)).Length()/p1p2.Length();
}


array<array<int,2>,3> QuickHull3D::findmost_xyz() {
	vector<Vector3>::iterator iter;
	array<array<int,2>,3> id = { { {0,0},{0,0},{0,0} } };
	float xmax = S[0].X; float xmin = S[0].X;
	float ymax = S[0].Y; float ymin = S[0].Y;
	float zmax = S[0].Z; float zmin = S[0].Z;
	for ( iter=S.begin(); iter!=S.end(); iter++ ) {
		if ( (*iter).X>xmax ) {
			xmax = (*iter).X;
			id[0][0] = iter-S.begin();
		}
		if ( xmin>(*iter).X ) {
			xmin = (*iter).X;
			id[0][1] = iter-S.begin();
		}
		if ( (*iter).Y>ymax ) {
			ymax = (*iter).Y;
			id[1][0] = iter-S.begin();
		}
		if ( ymin>(*iter).Y ) {
			ymin = (*iter).Y;
			id[1][1] = iter-S.begin();
		}
		if ( (*iter).Z>zmax ) {
			zmax = (*iter).Z;
			id[2][0] = iter-S.begin();
		}
		if ( zmin>(*iter).Z ) {
			zmin = (*iter).Z;
			id[2][1] = iter-S.begin();
		}
	}
	return id;
}

