//**************************************************************************
// Práctica 5
// Class to make objects by revolution
//**************************************************************************


#ifndef _MODELO_REVOLUCION_H_
#define _MODELO_REVOLUCION_H_


#include "objetos.h"
#include <vector>
#include <math.h>

class modelo_revolucion: public _triangulos3D
{

    public:
        modelo_revolucion();
        void hacer_revolucion(vector<_vertex3f> ver,int number_of_rotations,double angulo_inicial, double angulo_final);
        void puntos_figura1();
        void puntos_figura2();
        void puntos_figura3();
        void puntos_figura4();
        void puntos_figura5();
        // defensa
        void draw_solido_prueba();
        void hacer_revolucion_prueba(vector<_vertex3f> ver,int number_of_rotations,double angulo_inicial, double angulo_final);
};


#endif