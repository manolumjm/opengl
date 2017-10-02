//**************************************************************************
// Práctica 1
//**********************************************************************
#ifndef _USER_CODE
#define _USER_CODE

#include <GL/gl.h>
#include "stdlib.h"
#include <math.h>

//#include "file_ply_stl.h"


//**************************************************************************
// estructuras de datos para los modelos
//**************************************************************************

struct vertices
{
	float coord[3];
	float color_vertices[3];
};


struct caras
{
	int ind_c[3];
};

struct color
{
	float r;
	float g;
	float b;
};

struct solido
{
	int n_v;
	int n_c;
	struct vertices *ver;
	struct caras    *car;

	struct color *colores;// vector de colores
};


// Estructura para aristas aladas

/*struct arista
{
	struct vertices *verticeUno;
	struct vertices *verticeDos;
};
struct aristasAladas
{
	struct arista *aristaActual;

	struct caras *caraIzquierda;
	struct caras *caraDerecha;

	struct arista *aristaPredecesoraDerecha;
	struct arista *aristaSucesoraDerecha;

	struct arista *aristaPredecesoraIzquierda;
	struct arista *aristaSucesoraIzquierda;
};*/


//**************************************************************************
// funciones para construir modelos sólidos poligonales
//**************************************************************************


//void leer_objetos(char *file);

void construir_cubo(float tam, struct solido *cubo);
void construir_piramide(float tam, float al, struct solido *piramide);


//**************************************************************************
// funciones de visualización
//**************************************************************************

void draw_puntos(struct vertices *ver, int n_v, float r,float g,float b,int grosor);
void draw_arista_solido(struct solido *malla, float r, float g, float b, int modo, int grosor);
void draw_solido_ajedrez(struct solido *malla, float r1, float g1, float b1, float r2, float g2, float b2);
void draw_arista_solido_smooth(struct solido *malla, float r, float g, float b, int modo, int grosor);
void draw_arista_solido_color_cada_cara(struct solido *malla, float r, float g, float b, int modo, int grosor);
#endif
