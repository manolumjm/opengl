//******************************************************************************
// Práctica 5
// class to build cameras on the scene
//
//******************************************************************************

#include "camara.h"
#include <iostream>
using namespace std;

Camara::Camara()
{
    Observer_distance=4.0;
    Observer_angle_x=0.0;
    Observer_angle_y=0.0;
    x=0.0;
    y=0.0;
    z=0.0;

}   


void Camara::setVista(Vista vista)
{
    cout << vista << endl;
    vist = vista;
}


Vista Camara::getVista()
{
    return vist;
}

void Camara::setObservador()
{
    if(vist == alzado) // F1
    {
        glTranslatef(x, y, 0);
    }

    else if(vist == perfil) // F2
    {
        glRotatef(90,0,1,0);
        glTranslatef(0,y,z);
    
    }

    else if(vist == planta) // F3
    {
        glRotatef(-90,1,0,0);
        glTranslatef(x,0,z);
    
    }
    
    else if(vist == perspectiva) // F4
    {
        glTranslatef(0, 0, -Observer_distance);
        glRotatef(Observer_angle_x, 1, 0, 0);
        glRotatef(Observer_angle_y, 0, 1, 0);
    }
}



void Camara::girar(int Raton_x,int Raton_y)
{
    if(vist == alzado)
    {
        x += (GLfloat)Raton_x*0.1;
        y -= (GLfloat)Raton_y*0.1;
    }

    else if(vist == perfil)
    {
        z += (GLfloat)Raton_x*0.1;
        y -= (GLfloat)Raton_y*0.1;
    }

    else if(vist == planta)
    {
        x += (GLfloat)Raton_x*0.1;
        z -= (GLfloat)Raton_y*0.1;
    }

    else if(vist == perspectiva)
    {
        Observer_angle_x += Raton_y;  
        Observer_angle_y += Raton_x;
    }

    setObservador();
}
