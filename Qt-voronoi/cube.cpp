#include "cube.h"

float random(float start, float end){
    return float(start+(end-start)*rand()/(RAND_MAX + 1.0));
}
Cube::Cube()
{
    delaunayPointsCount = 20;
    m_count = 0;

    std::vector<Vector3> vec = SetPointsDelaunay();
    printf("setdata\n");
    //d.SetData(vec);
    printf("setdata done\n");
//    m_data.resize(d.triangles.size() * 3 * 6);
//    for (int i = 0; i < d.triangles.size(); ++i)
//    {
//        Vector3 v1 = d.triangles[i].v1;
//        Vector3 v2 = d.triangles[i].v2;
//        Vector3 v3 = d.triangles[i].v3;
//        Vector3 norm = d.triangles[i].getNormal();
//        add(v1, norm);
//        add(v2, norm);
//        add(v3, norm);
//        printf("triangle index: %d %d %d\n",v1.getindex(),v2.getindex(),v3.getindex());
//    }

    /*
     * test quickhull
     */
    PointSets3D quickhull = PointSets3D( vec );
    vector<array<int,3>> quickhull_index = quickhull.Quick_Hull3D();
    m_data.resize(quickhull_index.size() * 3 * 6);
    for (int i = 0; i < quickhull_index.size(); ++i)
    {
        Vector3 v1 = vec[quickhull_index[i][0]];
        Vector3 v2 = vec[quickhull_index[i][1]];
        Vector3 v3 = vec[quickhull_index[i][2]];
        Vector3 norm = Triangle(v1,v2,v3).getNormal();
        add(v1, norm);
        add(v2, norm);
        add(v3, norm);
    }

}

std::vector<Vector3> Cube::SetPointsDelaunay(){
    std::vector<Vector3> vec;
    for (int i = 0; i < this->delaunayPointsCount; i++) {
      float r = random(0.0, 0.5f);
      float phi = random(-90, 90)/180.0*PI;
      float theta = random(0, 360)/180.0*PI;
      vec.push_back(Vector3(
        float(r*cos(phi)*cos(theta)),
        float(r*sin(phi)),
        float(r*cos(phi)*sin(theta))));
    }
    // vec.push_back(Vector3(1.0f, 0.0f, 0.0f));
    // vec.push_back(Vector3(-1.0f, 0.0f, 0.0f));
    // vec.push_back(Vector3(0.0f, 0.5f, 0.0f));
    // vec.push_back(Vector3(0.0f, -0.5f, 0.0f));
    // vec.push_back(Vector3(0.0f, 0.0f, 1.0f));
    // vec.push_back(Vector3(0.0f, 0.0f, -1.0f));
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
