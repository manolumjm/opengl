//******************************************************************************
// Práctica 3
// class to build crane as hierarchical model
//
//******************************************************************************

#ifndef _GRUA_H_
#define _GRUA_H_

#include "modelo_revolucion.h"
#include "modelo_ply.h"
#include "objetos.h"


class grua: public _triangulos3D
{
private:

    modelo_revolucion base;
    //modelo_revolucion brazo;
    modelo_revolucion pluma;
    _cubo cuboBase;
    _cubo brazo;
    _cubo cuboPluma;

    float MovYCuboPluma;
    

    float MovGiroBrazo;
   
    modelo_ply betoven;
    float MovPluma;

public:
    grua(float cuadradoPluma, float giroBrazo, float alargaPluma);
    void crearBase();
    void crearCilindroBase();
    void crearBrazo();
    void crearCuadradoPluma();
    void crearPluma();
    void dibujar();
    void crearPly();
    void crearPluma2();
    void dibujar2();

};

#endif