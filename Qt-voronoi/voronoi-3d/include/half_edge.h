#ifndef HALF_EDGE
#define HALF_EDGE

#include "Vector3.h"
#include <array>
#include <stdlib.h>
#include <vector>
using namespace std;

struct Edge;
struct Face;
struct Vertex;

struct Vertex {
public:
	Vertex( int d ){ id = d; one_edge = NULL; }
	Vertex( int d, Edge *e ) { id = d; one_edge = e;}
	int id;
	Edge *one_edge;
};

struct Edge {
	Edge(){succ=pred=dual=NULL;
	       tri=NULL;
	       v=NULL;}
	void set( Edge *d,Edge *p,Edge *s,Face *f,Vertex *_v) {
		dual=d; pred=p; succ=s ; tri=f; v=_v;
	}
	Edge *dual, *pred, *succ;
	Face *tri;
	Vertex *v;
	int getVertex() {return v->id;}
};

struct Face {
public:
	Face(){one_edge=NULL;}
	Edge *one_edge;
	array<Edge*,3> getEdge() {
		array<Edge*,3> a;
		a[0]=one_edge->pred;
		a[1]=one_edge;
		a[2]=one_edge->succ;
		return a;
	}
	array<int,3> getVertex() {
		array<int,3> a;
		a[0]=one_edge->pred->v->id;
		a[1]=one_edge->v->id;
		a[2]=one_edge->succ->v->id;
		return a;
	}
	void reverse() {
		int v = one_edge->succ->v->id;
		one_edge->succ->v->id=one_edge->pred->v->id;
		one_edge->pred->v->id=v;
	}
};



void stitch( Vertex*, vector<Edge*>& );
void de_tri( Face *tri );
void crop( Face* tri );
bool is_scrap( Face *tri );
array<Face*,4> polyhedron( int,int,int,int );


#endif