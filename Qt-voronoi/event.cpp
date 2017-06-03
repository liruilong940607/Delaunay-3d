#include "event.h"

Event::Event()
{

}

Event::Event(Delaunay_Event event,
      std::vector<Tetrahedron> tetras,
      std::vector<Tetrahedron> tmpTList,
      std::vector<Tetrahedron> newTList,
      std::vector<int> newTList_isRedundancy,
      Vector3 v){
    this->eventtype = event;
    this->tetras = tetras;
    this->tmpTList = tmpTList;
    this->newTList = newTList;
    this->newTList_isRedundancy = newTList_isRedundancy;
    this->v = v;
}
