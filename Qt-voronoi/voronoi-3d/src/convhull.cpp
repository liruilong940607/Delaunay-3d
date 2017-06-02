/*This cpp file mainly contains function Quick_Hull3D
  that computes convex hull of point set S
  using quick hull method.

  S is vector<Vector3> with size n x 3
  and return facets set K (indices)
  K is vector<array<int,3>> with size m x 3
  for each triangle, norm vector formed by <p1,p2,p3> 
  point to the outside

  To call the function:
	PointSets3D PS( S ); --when S is a vector<Vector3>
	PointSets3D PS( S, n ); --when S is a Vector3 S[n]
    K = PS.Quick_Hull3D();  
  Or:
	PointSets3D PS;
	PS.set_points( S ); --when S is a vector<Vector3>
	PS.set_points( S, n ); --when S is a Vector3 S[n]
	K = PS.Quick_Hull3D();
 */

#include"point_sets.h"
#include"half_edge.h"

bool PointSets3D::find_farest( array<int,3> pnt, int &max_id ) {
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

	if (!(dmax<0)) {return true;}

	return false;
}

void PointSets3D::find_hull( stack<Face*> &face_stack ) {
	// choose face popped from face_stack
	Face *tri = face_stack.top(); face_stack.pop();

	// judge if it is already cropped off
	if (is_scrap(tri)) {de_tri(tri); return;}
    
	array<Edge*,3> edge = tri->getEdge();
	array<int,3> pnt = tri->getVertex();
	
	int max_id;
	if (find_farest( pnt,max_id ) ) { // if find farest point 
		exm_pnts[S_id[max_id]]=1; // marked

		array<int,3> tr1 = { pnt[0],pnt[1],S_id[max_id] };
		array<int,3> tr2 = { pnt[1],pnt[2],S_id[max_id] };
		array<int,3> tr3 = { pnt[2],pnt[0],S_id[max_id] };
		int v1 = edge[0]->dual->pred->v->id;
		int v2 = edge[1]->dual->pred->v->id;
		int v3 = edge[2]->dual->pred->v->id;

		// choose edges that point has to be stitched with
		vector<Edge*> e;
		if (is_on_line( S[tr1[0]],S[tr1[1]],S[tr1[2]] ) ||
			dist_p2plane(S[v1],S[tr1[0]],S[tr1[1]],S[tr1[2]])>0) {
			e.push_back( edge[0]->dual->succ->dual );
			e.push_back( edge[0]->dual->pred->dual );
			crop( edge[0]->dual->tri );
		}
		else e.push_back(edge[0]->dual);
		if (is_on_line( S[tr2[0]],S[tr2[1]],S[tr2[2]] ) ||
			dist_p2plane(S[v2],S[tr2[0]],S[tr2[1]],S[tr2[2]])>0) {
			e.push_back( edge[1]->dual->succ->dual );
			e.push_back( edge[1]->dual->pred->dual );
			crop( edge[1]->dual->tri );
		}
		else e.push_back(edge[1]->dual);
		if (is_on_line( S[tr3[0]],S[tr3[1]],S[tr3[2]] ) ||
			dist_p2plane(S[v3],S[tr3[0]],S[tr3[1]],S[tr3[2]])>0) {
			e.push_back( edge[2]->dual->succ->dual );
			e.push_back( edge[2]->dual->pred->dual );
			crop( edge[2]->dual->tri );
		}
		else e.push_back(edge[2]->dual);

		crop( tri );
		Vertex *v = new Vertex(S_id[max_id]);
		stitch( v, e ); 

		//generate new faces, push into stack and kill points
		vector<Face*> envolope;
		Edge *ed = v->one_edge;
		do {
			face_stack.push(ed->tri);
			envolope.push_back( ed->tri );
			ed = ed->pred->dual;
		}
		while(ed!=v->one_edge);
		kill_points( envolope );

		de_tri(tri);
	}
	else K.push_back( pnt ); // no points found, push into K
	return;
}

/*remove points from S_id if they are enclosed by faces tris
  including vertices of tris itself*/
void PointSets3D::kill_points( vector<Face*>& tris ) {
	vector<array<int,3>> pnts;
	for(int i=0;i<tris.size();i++) 
		pnts.push_back(tris[i]->getVertex());

	int k_cut = S_id.size(); int minus;
	for(int k=0; k<k_cut;) {
		minus = 0;
		for(int i=0;i<pnts.size();i++) 
			if (dist_p2plane( S[S_id[k]], S[pnts[i][0]], S[pnts[i][1]], S[pnts[i][2]] )<0)
				minus++;
		if (minus<pnts.size() && !exm_pnts[S_id[k]]) k++;
		else {--k_cut; swap(k, k_cut); }// be careful to use --k
	}
	
	S_id.resize( k_cut );

}

vector<int> PointSets3D::get_Extreme_pnts_id() {
	if (S_id.empty()) Quick_Hull3D();
	return S_id;
}

vector<bool> PointSets3D::get_Extreme_pnts_label() {
	if (exm_pnts.empty()) Quick_Hull3D();
	return exm_pnts;
}

vector<array<int,3>> PointSets3D::Quick_Hull3D() {
	S_id.clear();
	K.clear(); exm_pnts.clear();
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
	case 3:
		printf("three points! A triangle.");
		array<int,3> stri = {0,1,2};
		K.push_back(stri);
		return K;
		break;
	}
	// save point indexes to S_id, visit points via indexes
	for(int i=0; i<S.size(); S_id.push_back(i++));
	for(int i=0; i<S.size();i++) exm_pnts.push_back(0);
	stack<Face*> face_stack;

	/*find first nondegenerate polyhedron
	  construct and push 4 faces into stack*/
	array<int,4> expnt = find_nondegenerate_polyhedron();
	array<Face*,4> faces = polyhedron(expnt[0],expnt[1],expnt[2],expnt[3]);
	vector<Face*> f4;
	for(int i=0;i<4;i++) {
		face_stack.push(faces[i]);
		exm_pnts[expnt[i]]=1;
		f4.push_back(faces[i]);
	}

	kill_points( f4 );
	/*begin find hull, using iteration until stack is empty*/
	while( !face_stack.empty() ) 
		find_hull( face_stack );

	return K;
}

array<int,4> PointSets3D::find_nondegenerate_polyhedron() {
	array<array<int,2>,3> mm_id = findmost_xyz();
	// uniquify candidate
	vector<int> candidate;
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
	candidate.resize(2);
	float d; float max_d = 0.0;
	int max_id;
	// find P most far from line p1-p2
	for(int i=0; i<S.size(); i++) {
		d = dist_p2line( S[i], S[candidate[0]], S[candidate[1]] );
		if (d>max_d) { max_d = d; max_id = i; }
	}
	candidate.push_back( max_id );
	
	// find P most far from plane p1-p2-p3
	array<int,3> plane = {candidate[0],candidate[1],candidate[2]};
	int P;
	if( find_farest(plane,P) && !is_on_plane( S[P],S[plane[0]],S[plane[1]],S[plane[2]] )){}
	else {
		reverse(plane);
		find_farest(plane,P);
	}
	array<int,4> ex_points = {plane[0],plane[1],plane[2],P};
	return ex_points;
}


float PointSets3D::dist_p2plane( Vector3 p, Vector3 p1, Vector3 p2, Vector3 p3 ) {
	Vector3 p1p2 = p2-p1;
	Vector3 p1p3 = p3-p1;
	Vector3 N = p1p2.cross(p1p3);
	return (p-p1).dot(N);
}


float PointSets3D::dist_p2line( Vector3 p, Vector3 p1, Vector3 p2 ) {
	if (p==p1 || p==p2) return 0;
	Vector3 p1p = p-p1;
	Vector3 p1p2 = p2-p1;
	return (p1p2.cross(p1p)).Length()/p1p2.Length();
}

bool PointSets3D::is_on_line( Vector3 p, Vector3 p1, Vector3 p2 ) {
	if ( (p-p1).cross(p2-p).Length()==0.0f ) return true;
	return false;
}

bool PointSets3D::is_on_plane( Vector3 p, Vector3 p1, Vector3 p2, Vector3 p3 ) {
	if (is_on_line(p1,p2,p3)) {
		printf("triangle degenerate into a line!");
		return true;
	}
	if ((p-p1).dot((p2-p1).cross(p3-p1))==0.0f) 
		return true;
	return false;
}

array<array<int,2>,3> PointSets3D::findmost_xyz() {
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

