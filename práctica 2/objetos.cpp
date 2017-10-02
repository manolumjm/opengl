//**************************************************************************
// Práctica 2
// Class to define generic objects
//**************************************************************************


#include "objetos.h"
/*************
iNICIO CLASE PUNTOS 3D
*****************/

_puntos3D::_puntos3D()
{

}

void _puntos3D::draw_puntos(float r,float g,float b, int grosor)
{
    glColor3f(r,g,b);
    glPointSize(grosor);
    glBegin(GL_POINTS);
        for(int i=0;i<vertices.size();i++)
        {
            
            //glColor3f(ver[i].color_vertices[0],ver[i].color_vertices[1],ver[i].color_vertices[2]);
            //glVertex3f(ver[i].coord[0],ver[i].coord[1],ver[i].coord[2]);
            
            glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
        }
    glEnd();
}


/**********************
FIN CLASE PUNTOS 3D
*****************/


/**********************
INICIO CLASE TRIANGULOS3D
*****************/

_triangulos3D::_triangulos3D()
{

}
void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
    int n=caras.size();

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);
    for(int i=0;i<n;i++)
    {
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);

    }
    glEnd();
}

void _triangulos3D::draw_solido(float r, float g, float b)
{
    int n=caras.size();

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);
    for(int i=0;i<n;i++)
    {
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);

    }
    glEnd();
}

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
    int num_caras=caras.size();

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    for(int i=0;i<num_caras;i++)
    {
        if(i%2==0)
            glColor3f(r1,g1,g1);
        else
            glColor3f(r2,g2,g2);

        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
    glEnd();
}

/**********************
FIN CLASE TRIANGULOS3D
***********************/


//*************************************************************************
// INICIO clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
    tam = tam/2;

    vertices.resize(8);
    caras.resize(12);

    // Vertices
    vertices[0].x = -tam; vertices[0].y = -tam; vertices[0].z = tam;
    vertices[1].x = tam; vertices[1].y = -tam; vertices[1].z = tam;
    vertices[2].x = tam; vertices[2].y = tam; vertices[2].z = tam;
    vertices[3].x = -tam; vertices[3].y = tam; vertices[3].z = tam;
    vertices[4].x = -tam; vertices[4].y = -tam; vertices[4].z = -tam;
    vertices[5].x = tam; vertices[5].y = -tam; vertices[5].z = -tam;
    vertices[6].x = tam; vertices[6].y = tam; vertices[6].z = -tam;
    vertices[7].x = -tam; vertices[7].y = tam; vertices[7].z = -tam;

    // Caras

    caras[0]._0 = 0; caras[0]._1 = 1; caras[0]._2 = 3;
    caras[1]._0 = 1; caras[1]._1 = 2; caras[1]._2 = 3;
    caras[2]._0 = 1; caras[2]._1 = 5; caras[2]._2 = 2;
    caras[3]._0 = 5; caras[3]._1 = 6; caras[3]._2 = 2;
    caras[4]._0 = 5; caras[4]._1 = 4; caras[4]._2 = 6;
    caras[5]._0 = 4; caras[5]._1 = 7; caras[5]._2 = 6;
    caras[6]._0 = 4; caras[6]._1 = 0; caras[6]._2 = 7;
    caras[7]._0 = 0; caras[7]._1 = 3; caras[7]._2 = 7;
    caras[8]._0 = 3; caras[8]._1 = 2; caras[8]._2 = 6;
    caras[9]._0 = 3; caras[9]._1 = 6; caras[9]._2 = 7;
    caras[10]._0 = 4; caras[10]._1 = 1; caras[10]._2 = 0;
    caras[11]._0 = 4; caras[11]._1 = 5; caras[11]._2 = 1;

}

//*************************************************************************
// FIN clase cubo
//*************************************************************************


//*************************************************************************
// INICIO clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{
    tam = tam/2;
    
    vertices.resize(4);
    caras.resize(4);

    // Vertices
    vertices[0].x = -tam; vertices[0].y = -tam;   vertices[0].z = tam;
    vertices[1].x = tam;  vertices[1].y = -tam;   vertices[1].z = tam;
    vertices[2].x = 0;    vertices[2].y = -tam;   vertices[2].z = -tam;
    vertices[3].x = 0;    vertices[3].y = al-tam; vertices[3].z = 0;
    
    // Caras

    caras[0]._0 = 0; caras[0]._1 = 1; caras[0]._2 = 2;
    caras[1]._0 = 0; caras[1]._1 = 2; caras[1]._2 = 3;
    caras[2]._0 = 0; caras[2]._1 = 3; caras[2]._2 = 1;
    caras[3]._0 = 1; caras[3]._1 = 3; caras[3]._2 = 2;
}

//*************************************************************************
// FIN clase piramide
//*************************************************************************
