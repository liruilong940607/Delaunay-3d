#include "cube.h"

float random(float start, float end){
    return float(start+(end-start)*rand()/(RAND_MAX + 1.0));
}
Cube::Cube()
{
    delaunayPointsCount = 6;
    m_count = 0;
    basic_count = 0;
    vec = SetPointsDelaunay();
    printf("setdata\n");
    d.SetData(vec);
    printf("setdata done\n");
}

void Cube::paint_delauney_process(int step, int type){
    std::vector<Event> events = d.eventvec;
    step = step<events.size() ? step:(events.size()-1);
    cur_data_draw_type = events[step].eventtype;
    Tetrahedron outer = d.bigtetra;
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
    m_data.resize(d.tetras.size() * 4 * 3 * 3);
    for (int i = 0; i < d.tetras.size() ; ++i)
    {
       Vector3 v1 = d.tetras[i].vertices[0];
       Vector3 v2 = d.tetras[i].vertices[1];
       Vector3 v3 = d.tetras[i].vertices[2];
       Vector3 v4 = d.tetras[i].vertices[3];
       add(v1); add(v2); add(v3);
       add(v2); add(v3); add(v4);
       add(v3); add(v4); add(v1);
       add(v4); add(v1); add(v2);
    }
}
void Cube::set_paint_voronoi_vertics(){
    m_data.clear();
    m_count = 0;
    m_data.resize(d.tetras.size() * 3);
    for (int i = 0; i < d.tetras.size(); ++i)
    {
       Vector3 center = d.tetras[i].o;
       add(center);
    }
}
void Cube::set_paint_voronoi_cell(){
    m_data.clear();
    m_count = 0;
    /*
     * test quickhull
     */
    PointSets3D quickhull = PointSets3D( vec );
    vector<array<int,3>> quickhull_index = quickhull.Quick_Hull3D();
    m_data.resize(quickhull_index.size() * 3 * 6);
    for (int i = 0; i < quickhull_index.size(); ++i)
    {
        printf("result ==>>>>%d %d %d\n", quickhull_index[i][0],quickhull_index[i][1],quickhull_index[i][2]);
        Vector3 v1 = vec[quickhull_index[i][0]];
        Vector3 v2 = vec[quickhull_index[i][1]];
        Vector3 v3 = vec[quickhull_index[i][2]];
        Vector3 norm = Triangle(v1,v2,v3).getNormal();
        add(v1, norm);
        add(v2, norm);
        add(v3, norm);
    }
}
void Cube::set_paint_voronoi_cell_all(){}

std::vector<Vector3> Cube::SetPointsDelaunay(){
    std::vector<Vector3> vec;
//    for (int i = 0; i < this->delaunayPointsCount; i++) {
//      float r = random(0.0, 0.5f);
//      float phi = random(-90, 90)/180.0*PI;
//      float theta = random(0, 360)/180.0*PI;
//      vec.push_back(Vector3(
//        float(r*cos(phi)*cos(theta)),
//        float(r*sin(phi)),
//        float(r*cos(phi)*sin(theta))));
//    }
     vec.push_back(Vector3(1.0f, 0.0f, 0.0f));
     vec.push_back(Vector3(-1.0f, 0.0f, 0.0f));
     vec.push_back(Vector3(0.0f, 0.5f, 0.0f));
     vec.push_back(Vector3(0.0f, -0.5f, 0.0f));
     vec.push_back(Vector3(0.0f, 0.0f, 1.0f));
     vec.push_back(Vector3(0.0f, 0.0f, -1.0f));
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
