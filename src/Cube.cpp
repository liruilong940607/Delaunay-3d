#include "Cube.h"
using namespace std;
float random(float start, float end){
    return float(start+(end-start)*rand()/(RAND_MAX + 1.0));
}
Cube::Cube(){
    this->delaunayPointsCount = 5;
    this->delaunayPointsArray = NULL;
}

Cube::~Cube(){
    delete[] this->delaunayPointsArray;
}

void Cube::Init(){
    glGenBuffers(1, &this->PointsArrayID);
    //srand((unsigned)time(0)); 
    // glGenBuffers(1, &VertexArrayID);
    // glBindBuffer(GL_ARRAY_BUFFER, VertexArrayID);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    //RandomizePoints();
    SetPointsDelaunay();
    
    GLfloat *tri_data = new GLfloat[d.triangles.size()*3*3];
    for (int i = 0; i < d.triangles.size(); ++i)
    {
        Vector3 v1 = d.triangles[i].v1;
        Vector3 v2 = d.triangles[i].v2;
        Vector3 v3 = d.triangles[i].v3;
        cout<<"======"<<endl;
        cout<<" "<<v1.X <<" "<<v1.Y<<" "<<v1.Z<<endl;
        cout<<" "<<v2.X <<" "<<v2.Y<<" "<<v2.Z<<endl;
        cout<<" "<<v3.X <<" "<<v3.Y<<" "<<v3.Z<<endl;
        cout<<"======"<<endl;
        tri_data[i*3*3+0] = v1.X; tri_data[i*3*3+1] = v1.Y;  tri_data[i*3*3+2] = v1.Z;
        tri_data[i*3*3+3] = v2.X; tri_data[i*3*3+4] = v2.Y;  tri_data[i*3*3+5] = v2.Z;
        tri_data[i*3*3+6] = v3.X; tri_data[i*3*3+7] = v3.Y;  tri_data[i*3*3+8] = v3.Z;
    }

    glGenBuffers(1, &VertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexArrayID);
    glBufferData(GL_ARRAY_BUFFER, d.triangles.size()*3*3*4, tri_data, GL_STATIC_DRAW);

}

void Cube::Draw(){
    
    glBindBuffer(GL_ARRAY_BUFFER, VertexArrayID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,// attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, d.triangles.size()*3);//12 // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, PointsArrayID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,// attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0);
    glDrawArrays(GL_POINTS, 0, this->delaunayPoints.size()*3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}

void Cube::Update(double deltaTime){

}
void Cube::SetPointsDelaunay(){
    vector<Vector3> vec;
    // for (int i = 0; i < this->delaunayPointsCount; i++) {
    //   float r = random(0.0, 2.0f);
    //   float phi = random(-90, 90)/180.0*PI;
    //   float theta = random(0, 360)/180.0*PI;
    //   vec.push_back(Vector3(
    //     float(r*cos(phi)*cos(theta)), 
    //     float(r*sin(phi)), 
    //     float(r*cos(phi)*sin(theta))));
    // }
    vec.push_back(Vector3(-1.0f,-1.0f,0.0f));
    vec.push_back(Vector3(1.0f,-1.0f,0.0f));
    vec.push_back(Vector3(-1.0f,1.0f,0.0f));
    vec.push_back(Vector3(0.0f,0.0f,1.0f));
    vec.push_back(Vector3(1.0f,1.0f,0.0f));
    //vec.push_back(Vector3(0.0f,0.0f,-1.0f));
    d.SetData(vec);

    this->delaunayPoints.clear();
    delete[] this->delaunayPointsArray;
    this->delaunayPointsArray = new GLfloat[this->delaunayPointsCount*3];

    for(int i = 0; i < this->delaunayPointsCount; i ++){
        Vector3 point = d.vertices[i];
        this->delaunayPoints.push_back(point);
        this->delaunayPointsArray[i*3] = point.X;
        this->delaunayPointsArray[i*3+1] = point.Y;
        this->delaunayPointsArray[i*3+2] = point.Z;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, this->PointsArrayID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->delaunayPointsCount*3, this->delaunayPointsArray, GL_DYNAMIC_DRAW);
}
void Cube::RandomizePoints(){
    std::vector<Vector3> bounds = this->GetBoundaries();
    std::default_random_engine generator;
    generator.seed((unsigned long)time(NULL));
    std::uniform_real_distribution<float> distributionX(bounds[0].X, bounds[1].X);
    std::uniform_real_distribution<float> distributionY(bounds[0].Y, bounds[1].Y);
    std::uniform_real_distribution<float> distributionZ(bounds[0].Z, bounds[1].Z);

    this->delaunayPoints.clear();
    delete[] this->delaunayPointsArray;
    this->delaunayPointsArray = new GLfloat[this->delaunayPointsCount*3];

    for(int i = 0; i < this->delaunayPointsCount; i ++){
        Vector3 point(distributionX(generator), distributionY(generator), distributionZ(generator));
        this->delaunayPoints.push_back(point);
        this->delaunayPointsArray[i*3] = point.X;
        this->delaunayPointsArray[i*3+1] = point.Y;
        this->delaunayPointsArray[i*3+2] = point.Z;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, this->PointsArrayID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->delaunayPointsCount*3, this->delaunayPointsArray, GL_DYNAMIC_DRAW);
}

std::vector<Vector3> Cube::GetBoundaries(){
    std::vector<Vector3> bounds;
    bounds.push_back(Vector3());
    bounds.push_back(Vector3());

    for(int i = 0; i < 12*3; i += 3){
        if(bounds[0].X > g_vertex_buffer_data[i]){
            bounds[0].X = g_vertex_buffer_data[i];
        }else if(bounds[1].X < g_vertex_buffer_data[i]){
            bounds[1].X = g_vertex_buffer_data[i];
        }
    }
    for(int i = 1; i < 12*3; i += 3){
        if(bounds[0].Y > g_vertex_buffer_data[i]){
            bounds[0].Y = g_vertex_buffer_data[i];
        }else if(bounds[1].Y < g_vertex_buffer_data[i]){
            bounds[1].Y = g_vertex_buffer_data[i];
        }
    }
    for(int i = 2; i < 12*3; i += 3){
        if(bounds[0].Z > g_vertex_buffer_data[i]){
            bounds[0].Z = g_vertex_buffer_data[i];
        }else if(bounds[1].Z < g_vertex_buffer_data[i]){
            bounds[1].Z = g_vertex_buffer_data[i];
        }
    }
    return bounds;
}
