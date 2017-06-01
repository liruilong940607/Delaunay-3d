#include "half_edge.h"

/*stitch vertex v and edges e together 
  to form new facets. before stitching,
  facets of the hole should be cropped off*/

void stitch( Vertex *v, vector<Edge*> &e ) {
	// remove back path
	vector<Edge*>::iterator iter;
	int i=0;
	while( i<e.size() ) {
		if(e[i]->dual==e[(i+1)%e.size()]) {
			e.erase(e.begin()+i);
			e.erase(e.begin()+i%e.size());
			if(i) i--;
		}
		else i++;
	}
	for(int i=0;i<e.size();i++) {
		e[i]->dual = new Edge();
		e[i]->dual->set(e[i],new Edge(),new Edge(),new Face(),e[i]->succ->v);
		e[i]->dual->tri->one_edge = e[i]->dual;
		e[i]->dual->succ->pred = e[i]->dual;
		e[i]->dual->succ->succ = e[i]->dual->pred;
		e[i]->dual->pred->succ = e[i]->dual;
		e[i]->dual->pred->pred = e[i]->dual->succ;
		e[i]->dual->pred->tri = e[i]->dual->tri;
		e[i]->dual->succ->tri = e[i]->dual->tri;
		e[i]->dual->succ->v = e[i]->v;
		e[i]->dual->pred->v = v;
		if (v->one_edge==NULL) v->one_edge=e[i]->dual->pred;
		if (e[i]->v->one_edge==NULL) e[i]->v->one_edge=e[i];
	}
	for(int i=0;i<e.size();i++) {
		e[i]->dual->succ->dual=e[(i+1)%e.size()]->dual->pred;
		e[(i+1)%e.size()]->dual->pred->dual=e[i]->dual->succ;
	}

}

// crop off facet tri
void crop( Face *tri ) {
	Edge *e = tri->one_edge;
	for(int i=0;i<3;i++) {
		if(e->dual==NULL) {e=e->succ;continue;}
		e->dual=NULL;
		e=e->succ;
	}
}

// delete facet tri
void de_tri( Face *tri ) {
	if ( !is_scrap(tri) ){ printf("face not cropped, delete fail."); return; }
	Edge *e = tri->one_edge;
	delete tri;
	delete e->pred,e->succ,e;
}

// judge if a facet is cropped off
bool is_scrap( Face *tri ){
	Edge *e = tri->one_edge;
	if (e->dual==NULL && 
		e->succ->dual==NULL &&
		e->pred->dual==NULL) 
		return true;
	return false;
}

//4 points form a new polyhedron, return faces
array<Face*,4> polyhedron( int p1,int p2,int p3,int p ) {
	array<Face*,4> f;
	vector<Edge*> e;
	Vertex *v1 = new Vertex(p1);
	Vertex *v2 = new Vertex(p2);
	Vertex *v3 = new Vertex(p3);
	v1->one_edge = new Edge(); 
	v1->one_edge->set(NULL,new Edge(),new Edge(),new Face(),v1);
	v3->one_edge=v1->one_edge->succ;
	v3->one_edge->set(NULL,v1->one_edge,v1->one_edge->pred,v1->one_edge->tri,v3);
	v2->one_edge=v3->one_edge->succ;
	v2->one_edge->set(NULL,v3->one_edge,v1->one_edge,v1->one_edge->tri,v2);
	v1->one_edge->tri->one_edge=v1->one_edge;
	f[0]=v1->one_edge->tri;
	e.push_back(v1->one_edge);e.push_back(v2->one_edge);e.push_back(v3->one_edge);
	Vertex *v = new Vertex(p);
	stitch(v,e);
	Edge *ed = v->one_edge; int i=1;
	do {
		f[i] = ed->tri;i++;
		ed = ed->pred->dual;
	}
	while(ed!=v->one_edge);
	return f;
}