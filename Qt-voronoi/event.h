#ifndef EVENT_H
#define EVENT_H
#include <vector>
#include "Tetrahedron.h"

enum Delaunay_Event  {
    CreateBigTetra,
    SetCurrentPoint,
    JudgeIsInSphere,
    CreateFourNewTetraAndRemove,
    JudgeSameAndRemove,
    SetCurrentTetras,
    DeleteBigTetra
};

class Event
{
public:
    Event();

    Event(Delaunay_Event event,
          std::vector<Tetrahedron> tetras,
          std::vector<Tetrahedron> tmpTList,
          std::vector<Tetrahedron> newTList,
          std::vector<int> newTList_isRedundancy,
          Vector3 v);

    Delaunay_Event eventtype;
    std::vector<Tetrahedron> tetras;
    std::vector<Tetrahedron> tmpTList;
    std::vector<Tetrahedron> newTList;
    std::vector<int> newTList_isRedundancy;
    Vector3 v;
};

#endif // EVENT_H
