//******************************************************************************
// Práctica 5
// class to build cameras on the scene
//
//******************************************************************************

#ifndef _CAMARA_
#define _CAMARA_

#include <GL/glut.h>


enum Vista {alzado=0, perfil=1, planta=2, perspectiva=3};

class Camara
{
private:

    Vista vist;
public:

    // Variables cámara perspectiva
    GLfloat Observer_distance, Observer_angle_x,Observer_angle_y;

    //Variables cámara ortográfica (representan x,y,z)
    GLfloat x,y,z;

    Camara();
    void setVista(Vista vist);
    Vista getVista();
    void setObservador();
    void girar(int Raton_x,int Raton_y);

};

#endif