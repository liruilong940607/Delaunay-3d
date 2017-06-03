#include "glwidget.h"

#define PI 3.1415926536f

GLWidget::GLWidget(QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f)
{
    eyex = 0; eyey = 0; eyez = 2+10;
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
}
GLWidget::~GLWidget()
{
}
void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
//    static GLfloat lightpos[4] =
//    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
    GLfloat ambient[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
    GLfloat lightpos[] = {eyex,eyey+10.0f,eyez+100.0f,1.0};
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);

}
void GLWidget::paintGL()
{
    qDebug()<<"----------paintGL---------";
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
     if (F4_start) // show voronoi cell
         paint_voronoi_cell();
    // if (F5_start) // show voronoi all cells
    //     paint_voronoi_cell_all();
     if (F6_start)
         paint_delauney_process(process_step);
    Triangle TT = Triangle(Vector3(0.0f,1.0f,0.0f),Vector3(1.0f,0.0f,0.0f),
             Vector3(0.0f,0.0f,0.0f));
    printf("center: %f %f %f %f\n",TT.o.X,TT.o.Y,TT.o.Z,TT.r);
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
        case Qt::Key_Q:
            F1_start = !F1_start; // show points
            update();
            break;
        case Qt::Key_W:
            F2_start = !F2_start; // show delauny
            update();
            break;
        case Qt::Key_E:
            F3_start = !F3_start; // show voronoi vertics
            update();
            break;
        case Qt::Key_R:
            F4_start = !F4_start; // show voronoi cell
            update();
            break;
        case Qt::Key_T:
            F5_start = !F5_start; // show voronoi all cells
            update();
            break;
        case Qt::Key_A:
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
        case Qt::Key_Right:
            process_step++;
            update();
            break;
        case Qt::Key_Left:
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
    glPointSize(9.0f);
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
     glPointSize(14.0f);
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
        printf("SetCurrentPoint \n");
        m_cube.paint_delauney_process(step, 4);
        const GLfloat* data11 = m_cube.constData();
        glPointSize(14.0f);
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
        glColor3f(0.0, 1.0, 0.0);
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


// #include "glwidget.h"
// #include <QMouseEvent>
// #include <QOpenGLShaderProgram>
// #include <QCoreApplication>
// #include <math.h>

// GLWidget::GLWidget(QWidget *parent)
//     : QOpenGLWidget(parent),
//       m_xRot(0),
//       m_yRot(0),
//       m_zRot(0),
//       m_program(0)
// {
//     m_core = QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"));
//     // --transparent causes the clear color to be transparent. Therefore, on systems that
//     // support it, the widget will become transparent apart from the logo.
//     m_transparent = QCoreApplication::arguments().contains(QStringLiteral("--transparent"));
//     if (m_transparent) {
//         QSurfaceFormat fmt = format();
//         fmt.setAlphaBufferSize(8);
//         setFormat(fmt);
//     }
//     wireframe = false;
//     F1_start = false;
//     F2_start = false;
//     F3_start = false;
//     F4_start = false;
//     F5_start = false;
// }

// GLWidget::~GLWidget()
// {
//     cleanup();
// }

// QSize GLWidget::minimumSizeHint() const
// {
//     return QSize(50, 50);
// }

// QSize GLWidget::sizeHint() const
// {
//     return QSize(400, 400);
// }

// static void qNormalizeAngle(int &angle)
// {
//     while (angle < 0)
//         angle += 360 * 16;
//     while (angle > 360 * 16)
//         angle -= 360 * 16;
// }

// void GLWidget::setXRotation(int angle)
// {
//     qNormalizeAngle(angle);
//     if (angle != m_xRot) {
//         m_xRot = angle;
//         emit xRotationChanged(angle);
//         update();
//     }
// }

// void GLWidget::setYRotation(int angle)
// {
//     qNormalizeAngle(angle);
//     if (angle != m_yRot) {
//         m_yRot = angle;
//         emit yRotationChanged(angle);
//         update();
//     }
// }

// void GLWidget::setZRotation(int angle)
// {
//     qNormalizeAngle(angle);
//     if (angle != m_zRot) {
//         m_zRot = angle;
//         emit zRotationChanged(angle);
//         update();
//     }
// }

// void GLWidget::cleanup()
// {
//     makeCurrent();
//     m_cubeVbo.destroy();
//     delete m_program;
//     m_program = 0;
//     doneCurrent();
// }

// static const char *vertexShaderSourceCore =
//     "#version 150\n"
//     "in vec4 vertex;\n"
//     "in vec3 normal;\n"
//     "out vec3 vert;\n"
//     "out vec3 vertNormal;\n"
//     "uniform mat4 projMatrix;\n"
//     "uniform mat4 mvMatrix;\n"
//     "uniform mat3 normalMatrix;\n"
//     "void main() {\n"
//     "   vert = vertex.xyz;\n"
//     "   vertNormal = normalMatrix * normal;\n"
//     "   gl_Position = projMatrix * mvMatrix * vertex;\n"
//     "}\n";

// static const char *fragmentShaderSourceCore =
//     "#version 150\n"
//     "in highp vec3 vert;\n"
//     "in highp vec3 vertNormal;\n"
//     "out highp vec4 fragColor;\n"
//     "uniform highp vec3 lightPos;\n"
//     "void main() {\n"
//     "   highp vec3 L = normalize(lightPos - vert);\n"
//     "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
//     "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
//     "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
//     "   fragColor = vec4(col, 1.0);\n"
//     "}\n";

// static const char *vertexShaderSource =
//     "attribute vec4 vertex;\n"
//     "attribute vec3 normal;\n"
//     "varying vec3 vert;\n"
//     "varying vec3 vertNormal;\n"
//     "uniform mat4 projMatrix;\n"
//     "uniform mat4 mvMatrix;\n"
//     "uniform mat3 normalMatrix;\n"
//     "void main() {\n"
//     "   vert = vertex.xyz;\n"
//     "   vertNormal = normalMatrix * normal;\n"
//     "   gl_Position = projMatrix * mvMatrix * vertex;\n"
//     "}\n";

// static const char *fragmentShaderSource =
//     "varying highp vec3 vert;\n"
//     "varying highp vec3 vertNormal;\n"
//     "uniform highp vec3 lightPos;\n"
//     "void main() {\n"
//     "   highp vec3 L = normalize(lightPos - vert);\n"
//     "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
//     "   highp vec3 color = vec3(0.88, 1.0, 0.0);\n"
//     "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
//     "   gl_FragColor = vec4(col, 1.0);\n"
//     "}\n";

// void GLWidget::initializeGL()
// {
//     // In this example the widget's corresponding top-level window can change
//     // several times during the widget's lifetime. Whenever this happens, the
//     // QOpenGLWidget's associated context is destroyed and a new one is created.
//     // Therefore we have to be prepared to clean up the resources on the
//     // aboutToBeDestroyed() signal, instead of the destructor. The emission of
//     // the signal will be followed by an invocation of initializeGL() where we
//     // can recreate all resources.
//     connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

//     initializeOpenGLFunctions();
//     glClearColor(0, 0, 0, m_transparent ? 0 : 1);

//     m_program = new QOpenGLShaderProgram;
//     m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, m_core ? vertexShaderSourceCore : vertexShaderSource);
//     m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, m_core ? fragmentShaderSourceCore : fragmentShaderSource);
//     //m_program->bindAttributeLocation("vertex", 0);
//     //m_program->bindAttributeLocation("normal", 1);
//     //m_program->link();

//     m_program->bind();
//     m_projMatrixLoc = m_program->uniformLocation("projMatrix");
//     m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
//     m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
//     m_lightPosLoc = m_program->uniformLocation("lightPos");

//     // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
//     // implementations this is optional and support may not be present
//     // at all. Nonetheless the below code works in all cases and makes
//     // sure there is a VAO when one is needed.
//     m_vao.create();
//     QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

//     m_cubeVbo.create();

//     // Our camera never changes in this example.
//     m_camera.setToIdentity();
//     m_camera.translate(0, 0, -1);

//     // Light position is fixed.
//     m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

//     m_program->release();
// }

// void GLWidget::setupVertexAttribs()
// {

// }

// void GLWidget::paintGL()
// {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glEnable(GL_DEPTH_TEST);
//     glEnable(GL_CULL_FACE);

//     m_world.setToIdentity();
//     m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
//     m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
//     m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

//     QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
//     m_program->bind();
//     m_program->setUniformValue(m_projMatrixLoc, m_proj);
//     m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
//     QMatrix3x3 normalMatrix = m_world.normalMatrix();
//     m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);

//     if (F1_start) // show points
//         paint_points();
//     if (F2_start) // show delauny
//         paint_delauny();
//     if (F3_start) // show voronoi vertics
//         paint_voronoi_vertics();
//     if (F4_start) // show voronoi cell
//         paint_voronoi_cell();
//     if (F5_start) // show voronoi all cells
//         paint_voronoi_cell_all();

//     m_program->release();
// }
// void GLWidget::paint_points(){
//     // Setup our vertex buffer object.
//     m_cube.set_paint_delauny();
//     m_cubeVbo.bind();
//     m_cubeVbo.allocate(m_cube.constData(), m_cube.count() * sizeof(GLfloat));

//     // Store the vertex attribute bindings for the program.
//     m_cubeVbo.bind();
//     QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
//     f->glEnableVertexAttribArray(0);
//     f->glEnableVertexAttribArray(1);
//     f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
//     f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
//     m_cubeVbo.release();

//     glPointSize(9.0f);
//     glDrawArrays(GL_POINTS, 0, m_cube.count());
//     f->glDisableVertexAttribArray(0);
//     f->glDisableVertexAttribArray(1);
// }
// const GLfloat gColors[] = {
//     1.0f,0.0f,0.0f, 1.0f,
//     0.0f,1.0f,0.0f, 1.0f,
//     0.0f,0.0f,1.0f, 1.0f,
// };
// void GLWidget::paint_delauny(){
//     // Setup our vertex buffer object.
//     m_cube.set_paint_delauny();
//     m_cubeVbo.bind();
//     m_cubeVbo.allocate(m_cube.constData(), m_cube.count() * sizeof(GLfloat));

//     // Store the vertex attribute bindings for the program.
//     m_cubeVbo.bind();
//     QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
//     f->glEnableVertexAttribArray(0);
//     f->glEnableVertexAttribArray(1);
//     f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
//     f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
//     m_cubeVbo.release();

//     glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
//     glDrawArrays(GL_TRIANGLES, 0, m_cube.vertexCount());
//     f->glDisableVertexAttribArray(0);
//     f->glDisableVertexAttribArray(1);
// }
// void GLWidget::paint_voronoi_vertics(){

// }
// void GLWidget::paint_voronoi_cell(){
//     // Setup our vertex buffer object.
//     m_cube.set_paint_voronoi_cell();
//     m_cubeVbo.bind();
//     m_cubeVbo.allocate(m_cube.constData(), m_cube.count() * sizeof(GLfloat));

//     // Store the vertex attribute bindings for the program.
//     m_cubeVbo.bind();
//     QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
//     f->glEnableVertexAttribArray(0);
//     f->glEnableVertexAttribArray(1);
//     f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
//     f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
//     m_cubeVbo.release();

//     glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
//     glDrawArrays(GL_TRIANGLES, 0, m_cube.vertexCount());
//     f->glDisableVertexAttribArray(0);
//     f->glDisableVertexAttribArray(1);
// }
// void GLWidget::paint_voronoi_cell_all(){}

// void GLWidget::resizeGL(int w, int h)
// {
//     m_proj.setToIdentity();
//     m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
// }

// void GLWidget::mousePressEvent(QMouseEvent *event)
// {
//     m_lastPos = event->pos();
// }

// void GLWidget::mouseMoveEvent(QMouseEvent *event)
// {
//     int dx = event->x() - m_lastPos.x();
//     int dy = event->y() - m_lastPos.y();

//     if (event->buttons() & Qt::LeftButton) {
//         setXRotation(m_xRot + 8 * dy);
//         setYRotation(m_yRot + 8 * dx);
//     } else if (event->buttons() & Qt::RightButton) {
//         setXRotation(m_xRot + 8 * dy);
//         setZRotation(m_zRot + 8 * dx);
//     }
//     m_lastPos = event->pos();
// }

// void GLWidget::keyPressEvent(QKeyEvent *event){
//     switch (event->key())  {
//         case Qt::Key_F1:
//             F1_start = !F1_start; // show points
//             update();
//             break;
//         case Qt::Key_F2:
//             F2_start = !F2_start; // show delauny
//             update();
//             break;
//         case Qt::Key_F3:
//             F3_start = !F3_start; // show voronoi vertics
//             update();
//             break;
//         case Qt::Key_F4:
//             F4_start = !F4_start; // show voronoi cell
//             update();
//             break;
//         case Qt::Key_F5:
//             F5_start = !F5_start; // show voronoi all cells
//             update();
//             break;
//         case Qt::Key_Escape:
//             close();
//             break;
//         case Qt::Key_W:
//             wireframe = (!wireframe);
//             printf("key\n");
//             update();
//             break;
//         case Qt::Key_PageUp:
//             break;
//         case Qt::Key_PageDown:
//             break;
//         case Qt::Key_Up:
//             break;
//         case Qt::Key_Down:
//             break;
//         case Qt::Key_Right:
//             break;
//         case Qt::Key_Left:
//             break;
//     }
// }
