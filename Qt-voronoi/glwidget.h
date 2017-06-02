#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>  
#include <QtOpenGL/QtOpenGL>  
// ubuntu
//#include <GL/glu.h>
// mac
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include "cube.h"
class GLWidget : public QGLWidget  
{  
    Q_OBJECT  
public:  
    GLWidget(QWidget *parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);  
    ~GLWidget();  

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
  
protected:  
    void initializeGL();  
    void paintGL();  
    void resizeGL(int width, int height);  
    void mouseDoubleClickEvent( QMouseEvent *event );  
    void keyPressEvent(QKeyEvent *e);  
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:  
    GLfloat eyex; GLfloat eyey; GLfloat eyez;
    GLfloat centerx; GLfloat centery; GLfloat centerz;
    GLfloat upx; GLfloat upy; GLfloat upz;

    Cube m_cube;
    // control
    bool F1_start;
    bool F2_start;
    bool F3_start;
    bool F4_start;
    bool F5_start;
    void paint_points();
    void paint_delauny();
    void paint_voronoi_vertics();
    void paint_voronoi_cell();
    // void paint_voronoi_cell_all();

     int m_xRot;
     int m_yRot;
     int m_zRot;
     QPoint m_lastPos;

};  



// #include <QOpenGLWidget>
// #include <QOpenGLFunctions>
// #include <QOpenGLVertexArrayObject>
// #include <QOpenGLBuffer>
// #include <QMatrix4x4>
// #include "logo.h"
// #include "cube.h"
// QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

// class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
// {
//     Q_OBJECT

// public:
//     GLWidget(QWidget *parent = 0);
//     ~GLWidget();

//     QSize minimumSizeHint() const Q_DECL_OVERRIDE;
//     QSize sizeHint() const Q_DECL_OVERRIDE;

// public slots:
//     void setXRotation(int angle);
//     void setYRotation(int angle);
//     void setZRotation(int angle);
//     void cleanup();

// signals:
//     void xRotationChanged(int angle);
//     void yRotationChanged(int angle);
//     void zRotationChanged(int angle);

// protected:
//     void initializeGL() Q_DECL_OVERRIDE;
//     void paintGL() Q_DECL_OVERRIDE;
//     void resizeGL(int width, int height) Q_DECL_OVERRIDE;
//     void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//     void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//     void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
// private:
//     void setupVertexAttribs();

//     bool m_core;
//     int m_xRot;
//     int m_yRot;
//     int m_zRot;
//     QPoint m_lastPos;
//     Logo m_logo; //TODO
//     Cube m_cube;
//     QOpenGLVertexArrayObject m_vao;
//     QOpenGLBuffer m_logoVbo;
//     QOpenGLBuffer m_cubeVbo;
//     QOpenGLShaderProgram *m_program;
//     int m_projMatrixLoc;
//     int m_mvMatrixLoc;
//     int m_normalMatrixLoc;
//     int m_lightPosLoc;
//     QMatrix4x4 m_proj;
//     QMatrix4x4 m_camera;
//     QMatrix4x4 m_world;
//     bool m_transparent;

//     // control
//     bool wireframe;
//     bool F1_start;
//     bool F2_start;
//     bool F3_start;
//     bool F4_start;
//     bool F5_start;
//     void paint_points();
//     void paint_delauny();
//     void paint_voronoi_vertics();
//     void paint_voronoi_cell();
//     void paint_voronoi_cell_all();

// };

#endif
