#include "glwidget.h"
#include <random>
#ifndef QUICKHULL_IMPLEMENTATION
#define QUICKHULL_IMPLEMENTATION
#include "quickhull.h"
#endif
#define PI 3.1415926536f
GLfloat mycolor[10][3];

GLWidget::GLWidget(QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f)
{
    eyex = 0; eyey = 0; eyez = 2+5;
    centerx = 0; centery = 0; centerz = 0;
    upx = 0; upy = 1; upz = 0;

    setMinimumSize(320,240);
    resize(640,480);
    setWindowTitle(tr("Voronoi demo"));

    F1_start = false;
    F2_start = false;
    F3_start = false;
    F4_start = false;
    F5_start = false;
    F6_start = false;

    m_xRot = 0;
    m_yRot = 0;
    m_zRot = 0;

    process_step = 0;
    for (int i = 0; i<10; i++){
        mycolor[i][0] = rand() / double(RAND_MAX);
        mycolor[i][1] = rand() / double(RAND_MAX);
        mycolor[i][2] = rand() / double(RAND_MAX);
    }
}
GLWidget::~GLWidget()
{
}
void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambient[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
    GLfloat lightpos[] = {eyex,eyey+10.0f,eyez+100.0f,1.0};
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);

}
void GLWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
    glRotatef(m_xRot/16.0+37,1.0,0.0,0.0);
    glRotatef(m_yRot/16.0+300.5,0.0,1.0,0.0);
    glRotatef(m_zRot/16.0,0.0,0.0,1.0);

    if (F1_start) // show points
        paint_points();
    if (F2_start) // show delauny
        paint_delauny();
     if (F3_start) // show voronoi vertics
         paint_voronoi_vertics();
     if (F4_start) // show voronoi convhull-cell
         paint_voronoi_cell();
     if (F5_start) // show voronoi all cells and biggest sphere
         paint_voronoi_cell_all();
     if (F6_start) // show delaunay process
         paint_delauney_process(process_step);
    Triangle TT = Triangle(Vector3(0.0f,1.0f,0.0f),Vector3(1.0f,0.0f,0.0f),
             Vector3(0.0f,0.0f,0.0f));
    glFlush();  
}
void GLWidget::resizeGL(int width, int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );
    glMatrixMode( GL_MODELVIEW );
}
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = event->x() - m_lastPos.x();
    float dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(m_xRot + 8 * dy);
        setZRotation(m_zRot + 8 * dx);
    }
    m_lastPos = event->pos();
}
void GLWidget::mouseDoubleClickEvent( QMouseEvent *event )
{
    if(windowState() &  Qt::WindowFullScreen)
        showNormal();
    else
        showFullScreen();
}
void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())  {
        case Qt::Key_F1:
            F1_start = !F1_start; // show points
            update();
            break;
        case Qt::Key_F2:
            F2_start = !F2_start; // show delauny
            update();
            break;
        case Qt::Key_F3:
            F3_start = !F3_start; // show voronoi vertics
            update();
            break;
        case Qt::Key_F4:
            F4_start = !F4_start; // show voronoi cell
            update();
            break;
        case Qt::Key_F5:
            F5_start = !F5_start; // show voronoi all cells
            update();
            break;
        case Qt::Key_F6:
            F6_start = !F6_start;
            update();
            break;
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_PageUp:
            break;
        case Qt::Key_PageDown:
            break;
        case Qt::Key_Up:
            eyez += 0.1;
            update();
            break;
        case Qt::Key_Down:
            eyez -= 0.1;
            update();
            break;
        case Qt::Key_Q:
            process_step++;
            update();
            break;
        case Qt::Key_W:
            process_step--;
            process_step = process_step<0?0:process_step;
            update();
            break;
    }
}
static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}
void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}
void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}
void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}
void GLWidget::paint_points(){
    // Setup our vertex buffer object.
    glDisable(GL_LIGHTING);
    m_cube.set_paint_delauny();
    const GLfloat* data = m_cube.constData();
    glPointSize(20.0f);
    glColor3f(0.0, 1.0, 0.0);
    glBegin( GL_POINTS );
    for (int i = 0; i < m_cube.count()/3; ++i){
        glVertex3f(  data[i*3+0],  data[i*3+1],  data[i*3+2] );

    }
    glEnd();
    glEnable(GL_LIGHTING);
}
 void GLWidget::paint_delauny(){
     // Setup our vertex buffer object.
     glDisable(GL_LIGHTING);
     m_cube.set_paint_delauny();
     const GLfloat* data = m_cube.constData();
     glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
     glColor3f(1.0, 0.0, 0.0);
     glBegin( GL_TRIANGLES );
     for (int i = 0; i < m_cube.count()/3; ++i){
         glVertex3f(  data[i*3+0],  data[i*3+1],  data[i*3+2] );
     }
     glEnd();
     glEnable(GL_LIGHTING);
 }
 void GLWidget::paint_voronoi_vertics(){
     // Setup our vertex buffer object.
     glDisable(GL_LIGHTING);
     m_cube.set_paint_voronoi_vertics();
     const GLfloat* data = m_cube.constData();
     glPointSize(30.0f);
     glColor3f(1.0, 1.0, 1.0);
     glBegin( GL_POINTS );
     for (int i = 0; i < m_cube.count()/3; ++i){
         glVertex3f(  data[i*3+0],  data[i*3+1],  data[i*3+2] );
     }
     glEnd();
     glEnable(GL_LIGHTING);
 }
void GLWidget::paint_voronoi_cell(){
    // Setup our vertex buffer object.
    m_cube.set_paint_voronoi_cell();
    const GLfloat* data = m_cube.constData();
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glBegin( GL_TRIANGLES );
    for (int i = 0; i < m_cube.count()/6/3; i++){
        for (int j = 0; j < 3; ++j){
            GLfloat norm[3] = {data[i*6*3+j*6+3], data[i*6*3+j*6+4], data[i*6*3+j*6+5]};
            glNormal3fv(norm);
            glVertex3f(data[i*6*3+j*6+0],  data[i*6*3+j*6+1],  data[i*6*3+j*6+2] );

        }
    }
    glEnd();
}
void GLWidget::paint_delauney_process(int step){
    glDisable(GL_LIGHTING);
    m_cube.paint_delauney_process(step, 0);
    if(!(m_cube.cur_data_draw_type == DeleteBigTetra ||
         m_cube.cur_data_draw_type == SetCurrentTetras ||
         m_cube.cur_data_draw_type == CreateBigTetra ||
         m_cube.cur_data_draw_type == SetCurrentPoint ||
         m_cube.cur_data_draw_type == JudgeIsInSphere ||
         m_cube.cur_data_draw_type == CreateFourNewTetraAndRemove)){
        m_cube.paint_delauney_process(step, 3);
        const GLfloat* data4 = m_cube.constData();
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glColor3f(0.0, 1.0, 1.0);
        glBegin( GL_TRIANGLES );
        for (int i = 0; i < m_cube.count()/3; ++i){
            glVertex3f(  data4[i*3+0],  data4[i*3+1],  data4[i*3+2] );
        }
        glEnd();
    }

    if(!(m_cube.cur_data_draw_type == DeleteBigTetra ||
         m_cube.cur_data_draw_type == SetCurrentTetras ||
         m_cube.cur_data_draw_type == CreateBigTetra ||
         m_cube.cur_data_draw_type == SetCurrentPoint ||
         m_cube.cur_data_draw_type == JudgeIsInSphere)){
        m_cube.paint_delauney_process(step, 2);
        const GLfloat* data3 = m_cube.constData();
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glColor3f(0.0, 0.0, 1.0);
        glBegin( GL_TRIANGLES );
        for (int i = 0; i < m_cube.count()/3; ++i){
            glVertex3f(  data3[i*3+0],  data3[i*3+1],  data3[i*3+2] );
        }
        glEnd();
    }

    if(!(m_cube.cur_data_draw_type == DeleteBigTetra ||
         m_cube.cur_data_draw_type == SetCurrentTetras ||
         m_cube.cur_data_draw_type == CreateBigTetra ||
         m_cube.cur_data_draw_type == SetCurrentPoint)){
        m_cube.paint_delauney_process(step, 1);
        const GLfloat* data2 = m_cube.constData();
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glColor3f(1.0, 0.0, 0.0);
        glBegin( GL_TRIANGLES );
        for (int i = 0; i < m_cube.count()/3; ++i){
            glVertex3f(  data2[i*3+0],  data2[i*3+1],  data2[i*3+2] );
        }
        glEnd();
    }

    if(!(m_cube.cur_data_draw_type == DeleteBigTetra ||
         m_cube.cur_data_draw_type == SetCurrentTetras ||
            m_cube.cur_data_draw_type == CreateBigTetra)){
        m_cube.paint_delauney_process(step, 4);
        const GLfloat* data11 = m_cube.constData();
        glPointSize(30.0f);
        glColor3f(1.0, 1.0, 1.0);
        glBegin( GL_POINTS );
        for (int i = 0; i < m_cube.count()/3; ++i){
            glVertex3f(  data11[i*3+0],  data11[i*3+1],  data11[i*3+2] );
        }
        glEnd();
    }
    if(!(m_cube.cur_data_draw_type == DeleteBigTetra)){
        m_cube.paint_delauney_process(step, 0);
        const GLfloat* data1 = m_cube.constData();
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glLineWidth(10.0f);
        glBegin( GL_TRIANGLES );
        for (int i = 0; i < m_cube.count()/3; ++i){
            glVertex3f(  data1[i*3+0],  data1[i*3+1],  data1[i*3+2] );
        }
        glEnd();
    }
    m_cube.paint_delauney_process(step, 5);
    const GLfloat* data1 = m_cube.constData();
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glColor3f(0.0, 1.0, 0.0);
    glBegin( GL_TRIANGLES );
    for (int i = 0; i < m_cube.count()/3; ++i){
        glVertex3f(  data1[i*3+0],  data1[i*3+1],  data1[i*3+2] );
    }
    glEnd();
    glEnable(GL_LIGHTING);

}

void GLWidget::paint_voronoi_cell_all(){
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    int cellsize = m_cube.set_paint_voronoi_cell_all(-1);

    glPushMatrix();
    glColor4f(0.0f, 0.0f, 1.0f, .8f);
    glLineWidth(10.0f);
    glTranslatef(m_cube.o.X, m_cube.o.Y, m_cube.o.Z);
    glutWireSphere(m_cube.r, 20, 20);
    glPopMatrix();

    for(int idx = 0; idx<cellsize; idx++){
        m_cube.set_paint_voronoi_cell_all(idx);
        const GLfloat* data = m_cube.constData();
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glLineWidth(10.0f);
        glBegin( GL_LINES );

        glVertex3f(2.0f, 2.0f, 2.0f);
        glVertex3f(-2.0f, 2.0f, 2.0f);

        glVertex3f(2.0f, -2.0f, 2.0f);
        glVertex3f(-2.0f, -2.0f, 2.0f);

        glVertex3f(2.0f, 2.0f, -2.0f);
        glVertex3f(-2.0f, 2.0f, -2.0f);

        glVertex3f(2.0f, -2.0f, -2.0f);
        glVertex3f(-2.0f, -2.0f, -2.0f);

        glVertex3f(2.0f, 2.0f, 2.0f);
        glVertex3f(2.0f, -2.0f, 2.0f);

        glVertex3f(-2.0f, 2.0f, 2.0f);
        glVertex3f(-2.0f, -2.0f, 2.0f);

        glVertex3f(2.0f, 2.0f, -2.0f);
        glVertex3f(2.0f, -2.0f, -2.0f);

        glVertex3f(-2.0f, 2.0f, -2.0f);
        glVertex3f(-2.0f, -2.0f, -2.0f);

        glVertex3f(2.0f, 2.0f, 2.0f);
        glVertex3f(2.0f, 2.0f, -2.0f);

        glVertex3f(-2.0f, 2.0f, 2.0f);
        glVertex3f(-2.0f, 2.0f, -2.0f);

        glVertex3f(2.0f, -2.0f, 2.0f);
        glVertex3f(2.0f, -2.0f, -2.0f);

        glVertex3f(-2.0f, -2.0f, 2.0f);
        glVertex3f(-2.0f, -2.0f, -2.0f);


        glEnd();

        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glLineWidth(10.0f);
        glBegin( GL_TRIANGLES );
        for (int i = 0; i < m_cube.count()/6/3; i++){
            for (int j = 0; j < 3; ++j){
                glVertex3f(data[i*6*3+j*6+0],  data[i*6*3+j*6+1],  data[i*6*3+j*6+2] );

            }
        }
        glEnd();

        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        glColor4f(mycolor[idx%10][0],
                  mycolor[idx%10][1],
                  mycolor[idx%10][2],0.3f);
        glBegin( GL_TRIANGLES );
        for (int i = 0; i < m_cube.count()/6/3; i++){
            for (int j = 0; j < 3; ++j){
                GLfloat norm[3] = {data[i*6*3+j*6+3], data[i*6*3+j*6+4], data[i*6*3+j*6+5]};
                glNormal3fv(norm);
                glVertex3f(data[i*6*3+j*6+0],  data[i*6*3+j*6+1],  data[i*6*3+j*6+2] );

            }
        }
        glEnd();
    }
    glEnable(GL_LIGHTING);
}
