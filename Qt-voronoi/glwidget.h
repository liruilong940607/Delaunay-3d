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
    bool F6_start;
    void paint_points();
    void paint_delauny();
    void paint_voronoi_vertics();
    void paint_voronoi_cell();
    void paint_voronoi_cell_all();
    void paint_delauney_process(int step);

     int m_xRot;
     int m_yRot;
     int m_zRot;
     QPoint m_lastPos;

     int process_step;

};  

#endif
