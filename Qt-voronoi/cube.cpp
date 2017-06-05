#include "cube.h"
#ifndef QUICKHULL_IMPLEMENTATION
#define QUICKHULL_IMPLEMENTATION
#include "quickhull.h"
#endif
float random(float start, float end){
    return float(start+(end-start)*rand()/(RAND_MAX + 1.0));
}
Cube::Cube()
{
    delaunayPointsCount = 20;
    m_count = 0;
    basic_count = 0;
    vec = SetPointsDelaunay();
    printf("setdata\n");
    ps3d.set_points(vec);
    vector<Tetrahedron> teras = ps3d.delaunay();
    printf("setdata done\n");

    ps3d.Voronoi3d(Vector3(-2.0f,-2.0f,-2.0f),Vector3(2.0f,2.0f,2.0f));
    polytope = ps3d.Polytope;
    int idx = ps3d.get_Biggest_Inscribed_Circle();
    o = ps3d.dln.tetras[idx].o;
    r = ps3d.dln.tetras[idx].r;
    //d.SetData(vec);


}

void Cube::paint_delauney_process(int step, int type){
    std::vector<Event> events = ps3d.dln.eventvec;
    step = step<events.size() ? step:(events.size()-1);
    cur_data_draw_type = events[step].eventtype;
    Tetrahedron outer = ps3d.dln.bigtetra;
    if (type==0 || type==5){//tetras
        m_data.clear();
        m_count = 0;
        m_data.resize(events[step].tetras.size() * 4 * 3 * 3);
        for (int i = 0; i < events[step].tetras.size() ; ++i)
        {
           Vector3 v1 = events[step].tetras[i].vertices[0];
           Vector3 v2 = events[step].tetras[i].vertices[1];
           Vector3 v3 = events[step].tetras[i].vertices[2];
           Vector3 v4 = events[step].tetras[i].vertices[3];
           add(v1); add(v2); add(v3);
           add(v2); add(v3); add(v4);
           add(v3); add(v4); add(v1);
           add(v4); add(v1); add(v2);
        }
    }
    if (type==1){//tmpTList;
        m_data.clear();
        m_count = 0;
        m_data.resize(events[step].tmpTList.size() * 4 * 3 * 3);
        for (int i = 0; i < events[step].tmpTList.size() ; ++i)
        {
           Vector3 v1 = events[step].tmpTList[i].vertices[0];
           Vector3 v2 = events[step].tmpTList[i].vertices[1];
           Vector3 v3 = events[step].tmpTList[i].vertices[2];
           Vector3 v4 = events[step].tmpTList[i].vertices[3];
           add(v1); add(v2); add(v3);
           add(v2); add(v3); add(v4);
           add(v3); add(v4); add(v1);
           add(v4); add(v1); add(v2);
        }
    }
    if (type==2){//newTList
        m_data.clear();
        m_count = 0;
        m_data.resize(events[step].newTList.size() * 4 * 3 * 3);
        for (int i = 0; i < events[step].newTList.size() ; ++i)
        {
           Vector3 v1 = events[step].newTList[i].vertices[0];
           Vector3 v2 = events[step].newTList[i].vertices[1];
           Vector3 v3 = events[step].newTList[i].vertices[2];
           Vector3 v4 = events[step].newTList[i].vertices[3];
           add(v1); add(v2); add(v3);
           add(v2); add(v3); add(v4);
           add(v3); add(v4); add(v1);
           add(v4); add(v1); add(v2);
        }
    }
    if (type==3){//newTList_isRedundancy
        m_data.clear();
        m_count = 0;
        m_data.resize(events[step].newTList.size() * 4 * 3 * 3);
        for (int i = 0; i < events[step].newTList.size() ; ++i)
        {
            if (!events[step].newTList_isRedundancy[i])
                continue;
            Vector3 v1 = events[step].newTList[i].vertices[0];
            Vector3 v2 = events[step].newTList[i].vertices[1];
            Vector3 v3 = events[step].newTList[i].vertices[2];
            Vector3 v4 = events[step].newTList[i].vertices[3];
            add(v1); add(v2); add(v3);
            add(v2); add(v3); add(v4);
            add(v3); add(v4); add(v1);
            add(v4); add(v1); add(v2);
        }
    }
    if (type==4){//points
        m_data.clear();
        m_count = 0;
        m_data.resize(1 * 3);
        add(events[step].v);
    }
}

void Cube::set_paint_points(){
    m_data.clear();
    m_count = 0;
    m_data.resize(vec.size() * 3);
    for (int i = 0; i < vec.size(); ++i)
    {
       Vector3 v = vec[i];
       add(v);
    }
}
void Cube::set_paint_delauny(){
    m_data.clear();
    m_count = 0;
    m_data.resize(ps3d.dln.tetras.size() * 4 * 3 * 3);
    for (int i = 0; i < ps3d.dln.tetras.size() ; ++i)
    {
       Vector3 v1 = ps3d.dln.tetras[i].vertices[0];
       Vector3 v2 = ps3d.dln.tetras[i].vertices[1];
       Vector3 v3 = ps3d.dln.tetras[i].vertices[2];
       Vector3 v4 = ps3d.dln.tetras[i].vertices[3];
       add(v1); add(v2); add(v3);
       add(v2); add(v3); add(v4);
       add(v3); add(v4); add(v1);
       add(v4); add(v1); add(v2);
    }
}
void Cube::set_paint_voronoi_vertics(){
    m_data.clear();
    m_count = 0;
    m_data.resize(ps3d.dln.tetras.size() * 3);
    for (int i = 0; i < ps3d.dln.tetras.size(); ++i)
    {
       Vector3 center = ps3d.dln.tetras[i].o;
       add(center);
    }
}
void Cube::set_paint_voronoi_cell(){
    m_data.clear();
    m_count = 0;
    /*
     * test quickhull
     */
    qh_vertex_t vertices[delaunayPointsCount];
    for (int i = 0; i < this->delaunayPointsCount; i++) {
        vertices[i].x = vec[i].X;
        vertices[i].y = vec[i].Y;
        vertices[i].z = vec[i].Z;
    }
    qh_mesh_t m = qh_quickhull3d(vertices, delaunayPointsCount);
    m_data.resize(m.nindices * 6);
    for (int i = 0, j = 0; i < m.nindices; i += 3, j++) {
        if ( m.indices[i+0] < m.nvertices && m.indices[i+1] < m.nvertices && m.indices[i+2] < m.nvertices &&  m.normalindices[j] < m.nnormals ) {
            qh_vertex_t * v0 = m.vertices + m.indices[i+0];
            qh_vertex_t * v1 = m.vertices + m.indices[i+1];
            qh_vertex_t * v2 = m.vertices + m.indices[i+2];

            printf("j: %d, x,y.z: %f %f %f\n",j,v0->x, v0->y, v0->z);
            printf("j: %d, x,y.z: %f %f %f\n",j,v1->x, v1->y, v1->z);
            printf("j: %d, x,y.z: %f %f %f\n",j,v2->x, v2->y, v2->z);

            Vector3 vec1 = Vector3(float(v0->x),float(v0->y),float(v0->z));
            Vector3 vec2 = Vector3(float(v1->x),float(v1->y),float(v1->z));
            Vector3 vec3 = Vector3(float(v2->x),float(v2->y),float(v2->z));

            Vector3 norm = Triangle(vec1,vec2,vec3).getNormal();
            add(vec1, norm);
            add(vec2, norm);
            add(vec3, norm);

        }
    }




//    //PointSets3D quickhull = PointSets3D( vec );
//    printf("polytope size: %d\n",ps3d.Polytope.size());
//    vector<array<Vector3,3>> quickhull_index = polytope[0];
//    m_data.resize(quickhull_index.size() * 3 * 6);
//    printf("polytope[0] size: %d\n",ps3d.Polytope[0].size());
//    for (int i = 0; i < quickhull_index.size(); ++i)
//    {
//        Vector3 v1 = quickhull_index[i][0];
//        Vector3 v2 = quickhull_index[i][1];
//        Vector3 v3 = quickhull_index[i][2];
//        printf("v1: %f %f %f\n",v1.X, v1.Y, v1.Z);
//        printf("v2: %f %f %f\n",v2.X, v2.Y, v2.Z);
//        printf("v3: %f %f %f\n",v3.X, v3.Y, v3.Z);
//        printf("=============\n");
//        Vector3 norm = Triangle(v1,v2,v3).getNormal();
//        add(v1, norm);
//        add(v2, norm);
//        add(v3, norm);
//    }
}
int Cube::set_paint_voronoi_cell_all(int idx){
    if (idx==-1)
        return ps3d.Polytope.size();
    m_data.clear();
    m_count = 0;
    /*
     * test quickhull
     */
    //PointSets3D quickhull = PointSets3D( vec );
    printf("polytope size: %d\n",ps3d.Polytope.size());
    vector<array<Vector3,3>> quickhull_index = polytope[idx];
    m_data.resize(quickhull_index.size() * 3 * 6);
    printf("polytope[0] size: %d\n",ps3d.Polytope[0].size());
    for (int i = 0; i < quickhull_index.size(); ++i)
    {
        Vector3 v1 = quickhull_index[i][0];
        Vector3 v2 = quickhull_index[i][1];
        Vector3 v3 = quickhull_index[i][2];
        printf("v1: %f %f %f\n",v1.X, v1.Y, v1.Z);
        printf("v2: %f %f %f\n",v2.X, v2.Y, v2.Z);
        printf("v3: %f %f %f\n",v3.X, v3.Y, v3.Z);
        printf("=============\n");
        Vector3 norm = Triangle(v1,v2,v3).getNormal();
        add(v1, norm);
        add(v2, norm);
        add(v3, norm);
    }
}

std::vector<Vector3> Cube::SetPointsDelaunay(){
    std::vector<Vector3> vec;
    for (int i = 0; i < this->delaunayPointsCount; i++) {
      float r = random(0.0, 1.0f);
      float phi = random(-90, 90)/180.0*PI;
      float theta = random(0, 360)/180.0*PI;
      vec.push_back(Vector3(
        random(-1.0f, 1.0f),
        random(-1.0f, 1.0f),
        random(-1.0f, 1.0f)));
    }
//     vec.push_back(Vector3(1.7f, 0.0f, 1.7f));
//     vec.push_back(Vector3(1.7f, 0.0f, -1.7f));
//     vec.push_back(Vector3(0.0f, 1.0f, 0.0f));
//     vec.push_back(Vector3(0.0f, -1.0f, 0.0f));
//     vec.push_back(Vector3(-1.7f, 0.0f, 1.7f));
//     vec.push_back(Vector3(-1.7f, 0.0f, -1.7f));
//    vec.push_back(Vector3(0.0f, 0.0f, 0.0f));
//    vec.push_back(Vector3(1.0f, 0.0f, 0.0f));
//    vec.push_back(Vector3(0.0f, 1.0f, 0.0f));
//    vec.push_back(Vector3(0.0f, 0.0f, 1.0f));
//    vec.push_back(Vector3(0.3f, 0.3f, 0.3f));
//    vec.push_back(Vector3(0.5f, 0.5f, 0.5f));
//    vec.push_back(Vector3(0.5f, 0.5f, 1.5f));
//    vec.push_back(Vector3(0.3f, 0.8f, 0.8f));
    for (int i = 0; i < this->delaunayPointsCount; i++) {
        vec[i].setindex(i);
    }
    return vec;
}
void Cube::add(const Vector3 &v, const Vector3 &n)
{
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.X;
    *p++ = v.Y;
    *p++ = v.Z;
    *p++ = n.X;
    *p++ = n.Y;
    *p++ = n.Z;
    m_count += 6;
}
void Cube::add(const Vector3 &v)
{
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.X;
    *p++ = v.Y;
    *p++ = v.Z;
    m_count += 3;
}
void Cube::add(const Vector3 &v, QVector<GLfloat> data, int &count)
{
    GLfloat *p = data.data() + count;
    *p++ = v.X;
    *p++ = v.Y;
    *p++ = v.Z;
    count += 3;
}
