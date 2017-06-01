#include "Application.h"

Application::Application(){
    eyeX = 0;
    eyeZ = 0;
    radius = 5;
    relativeX = 0;
    wireframe = false;
    turnSpeed = 0.5f;
    zoomSpeed = 0.05f;
}

Application::~Application(){

}

void Application::Init(){
    glEnable(GL_DEPTH_TEST);
    cube.Init();
}

void Application::Mouse(int button,int state,int x,int y){
    switch(button){
        case GLUT_LEFT_BUTTON: 
            printf("[Mouse] GLUT_LEFT_BUTTON\n");
            break;
        case GLUT_MIDDLE_BUTTON: 
            printf("[Mouse] GLUT_MIDDLE_BUTTON\n");
            break;
        case GLUT_RIGHT_BUTTON: 
            printf("[Mouse] GLUT_RIGHT_BUTTON\n");
            break;
        case GLUT_WHEEL_UP: 
            printf("[Mouse] GLUT_WHEEL_UP\n");
            radius = std::max(radius-zoomSpeed,1.0f);
            break;
        case GLUT_WHEEL_DOWN: 
            printf("[Mouse] GLUT_WHEEL_DOWN\n");
            radius += zoomSpeed;
            break;
        default: 
            break;
    }
}


void Application::Zoom(int direction){
    radius += direction*zoomSpeed;
    printf("zoom: %d\n", direction);
}

void Application::Input(unsigned char key, int x, int y){
    if(key == 119){
        wireframe = (!wireframe);
    }else if(key == 27){
        glutExit();
    }
}

void Application::Draw(){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //wireframe mode
    if(wireframe){
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }else{
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
    
    //modify object model view matrice to rotate with eyeX and eyeZ values
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, 3, eyeZ, 0, 0, 0, 0, 1, 0);
    
    cube.Draw();

    glutSwapBuffers();
}

void Application::Update(double deltaTime){
    relativeX += (((float)deltaTime*turnSpeed))*M_PI;
    
    eyeX = radius*sin(relativeX);
    eyeZ = radius*cos(relativeX);

    cube.Update(deltaTime);

    glutPostRedisplay();
}