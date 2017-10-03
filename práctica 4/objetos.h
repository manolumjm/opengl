//**************************************************************************
// Práctica 4 
// Class which define multiple geometric figures with different types of drawn
//**************************************************************************

#ifndef _OBJETOS_H_
#define _OBJETOS_H_

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "jpg_imagen.hpp"

using namespace std;

//const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
    vector<_vertex3f> vertices;


	_puntos3D();
    void draw_puntos(float r, float g, float b, int grosor);

    
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

    vector<_vertex3i> caras;
    vector<_color3f> color; // color para cada cara
    vector<_vertex3f> normales_caras; // normales de las caras
    vector<_vertex3f> normales_vertices; // normales de los vertices
    vector<_vertex2f> textura_coord; // coordenadas de textura

    bool b_normales_caras;
    bool b_normales_vertices;
    bool b_textura_coord; // texels
    bool mode_text;

    _vertex4f ambient;
    _vertex4f difusa;
    _vertex4f ambiente_difusa;
    _vertex4f especular;
    int brillo;
    
    GLfloat coefs_s[4] , coefs_t[4] ; // si mode_text == false, coeficientes para la coord. S idem para coordenada T


	_triangulos3D();
    void draw_aristas(float r, float g, float b, int grosor);
    void draw_solido(float r, float g, float b);
    void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
    void iluminacion_plana();
    void iluminacion_suave();
    void draw_textura(GLuint ident_textura,jpg::Imagen*& imagen);
    void draw_textura_iluminacion_plana(GLuint ident_textura,jpg::Imagen*& imagen);
    void draw_textura_iluminacion_suave(GLuint ident_textura,jpg::Imagen*& imagen);
    void calcular_normales_caras();
    void calcular_normales_vertices();
    // funcion draw para la textura (HAY QUE HACERLA)
    //draw(modo ,r1,g1,b1,r2,g2,b2,grosor,GLuint ident_textura)

   
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};


//*************************************************************************
// clase textura
//*************************************************************************

class textura: public _triangulos3D
{
public:
    textura();
    //Método para leer una imágen y poder usarla con OpenGL. Es el constructor. Le pasamos el nombre del archivo de la imagen
    textura(const char * archivoJPG);

    GLuint ident_textura; //Entero que asigna OpenGL a la textura.
    jpg::Imagen * imagen; //imagen a leer

};


//*************************************************************************
// clase revolucion textura
//*************************************************************************

class revolucion_tex: public _triangulos3D
{
public:
  revolucion_tex();
  void hacer_revolucion_tex(vector<_vertex3f> ver, int num_caras);
};

#endif





