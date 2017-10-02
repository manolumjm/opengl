//**************************************************************************
// Práctica 1
//**********************************************************************

#include "user_code.h"




void construir_cubo(float tam, struct solido *cubo)
{
	// Dividimos a la mitad el tamaño, para que las coordenadas sean 
	// las adecuadas
	tam=tam/2;

	// Un cubo tiene 8 vertices y 12 caras
	cubo->n_v=8;
	cubo->n_c=12;

	/********* Inicio Colores para vértices ***********************/

	cubo->ver[0].color_vertices[0]=0.1;
	cubo->ver[0].color_vertices[1]=0.2;
	cubo->ver[0].color_vertices[2]=0.3;

	cubo->ver[1].color_vertices[0]=0.3;
	cubo->ver[1].color_vertices[1]=0.2;
	cubo->ver[1].color_vertices[2]=0.1;

	cubo->ver[2].color_vertices[0]=0.2;
	cubo->ver[2].color_vertices[1]=0.3;
	cubo->ver[2].color_vertices[2]=0.2;

	cubo->ver[3].color_vertices[0]=0.3;
	cubo->ver[3].color_vertices[1]=0.4;
	cubo->ver[3].color_vertices[2]=0.5;

	cubo->ver[4].color_vertices[0]=0.5;
	cubo->ver[4].color_vertices[1]=0.4;
	cubo->ver[4].color_vertices[2]=0.3;

	cubo->ver[5].color_vertices[0]=0.4;
	cubo->ver[5].color_vertices[1]=0.3;
	cubo->ver[5].color_vertices[2]=0.5;

	cubo->ver[6].color_vertices[0]=0.6;
	cubo->ver[6].color_vertices[1]=0.7;
	cubo->ver[6].color_vertices[2]=0.8;

	cubo->ver[7].color_vertices[0]=0.8;
	cubo->ver[7].color_vertices[1]=0.7;
	cubo->ver[7].color_vertices[2]=0.6;

	/********* Fin Colores para vértices ***********************/

	 /************ Inicio Colores caras fijo ***********************/
	cubo->colores[0].r=0.1;
	cubo->colores[0].g=0.1;
	cubo->colores[0].b=0.1;

	cubo->colores[1].r=0.2;
	cubo->colores[1].g=0.2;
	cubo->colores[1].b=0.2;

	cubo->colores[2].r=0.3;
	cubo->colores[2].g=0.3;
	cubo->colores[2].b=0.3;

	cubo->colores[3].r=0.4;
	cubo->colores[3].g=0.4;
	cubo->colores[3].b=0.4;

	cubo->colores[4].r=0.5;
	cubo->colores[4].g=0.5;
	cubo->colores[4].b=0.5;

	cubo->colores[5].r=0.6;
	cubo->colores[5].g=0.6;
	cubo->colores[5].b=0.6;

	cubo->colores[6].r=0.7;
	cubo->colores[6].g=0.7;
	cubo->colores[6].b=0.7;

	cubo->colores[7].r=0.8;
	cubo->colores[7].g=0.8;
	cubo->colores[7].b=0.8;

	cubo->colores[8].r=0.9;
	cubo->colores[8].g=0.9;
	cubo->colores[8].b=0.9;

	cubo->colores[9].r=0.15;
	cubo->colores[9].g=0.15;
	cubo->colores[9].b=0.15;

	cubo->colores[10].r=0.25;
	cubo->colores[10].g=0.25;
	cubo->colores[10].b=0.25;

	cubo->colores[11].r=0.35;
	cubo->colores[11].g=0.35;
	cubo->colores[11].b=0.35;
	 /************ Fin Colores caras fijo ***********************/

	// metemos coordenadas
	cubo->ver[0].coord[0]=-tam;
	cubo->ver[0].coord[1]=-tam; //0
	cubo->ver[0].coord[2]=tam;

	cubo->ver[1].coord[0]=tam;
	cubo->ver[1].coord[1]=-tam; //1
	cubo->ver[1].coord[2]=tam;

	cubo->ver[2].coord[0]=tam;
	cubo->ver[2].coord[1]=tam;  //2
	cubo->ver[2].coord[2]=tam;

	cubo->ver[3].coord[0]=-tam;
	cubo->ver[3].coord[1]=tam;  //3
	cubo->ver[3].coord[2]=tam;

	cubo->ver[4].coord[0]=-tam;
	cubo->ver[4].coord[1]=-tam;  //4
	cubo->ver[4].coord[2]=-tam;

	cubo->ver[5].coord[0]=tam;
	cubo->ver[5].coord[1]=-tam;  //5
	cubo->ver[5].coord[2]=-tam;

	cubo->ver[6].coord[0]=tam;
	cubo->ver[6].coord[1]=tam;   //6
	cubo->ver[6].coord[2]=-tam;

	cubo->ver[7].coord[0]=-tam;
	cubo->ver[7].coord[1]=tam;   //7
	cubo->ver[7].coord[2]=-tam;

	// Metemos caras (debe ser por triangulos)

	// cara 0,1,3
	cubo->car[0].ind_c[0]=0; 
	cubo->car[0].ind_c[1]=1;
	cubo->car[0].ind_c[2]=3;

	// cara 1,2,3
	cubo->car[1].ind_c[0]=1; 
	cubo->car[1].ind_c[1]=2;
	cubo->car[1].ind_c[2]=3;

	// cara 1,5,2
	cubo->car[2].ind_c[0]=1; 
	cubo->car[2].ind_c[1]=5;
	cubo->car[2].ind_c[2]=2;

	// cara 5,6,2
	cubo->car[3].ind_c[0]=5; 
	cubo->car[3].ind_c[1]=6;
	cubo->car[3].ind_c[2]=2;

	// cara 5,4,6
	cubo->car[4].ind_c[0]=5; 
	cubo->car[4].ind_c[1]=4;
	cubo->car[4].ind_c[2]=6;

	// cara 4,7,6
	cubo->car[5].ind_c[0]=4; 
	cubo->car[5].ind_c[1]=7;
	cubo->car[5].ind_c[2]=6;
	// cara 4,0,7
	cubo->car[6].ind_c[0]=4; 
	cubo->car[6].ind_c[1]=0;
	cubo->car[6].ind_c[2]=7;

	// cara 0,3,7
	cubo->car[7].ind_c[0]=0; 
	cubo->car[7].ind_c[1]=3;
	cubo->car[7].ind_c[2]=7;
	// cara 3,2,6
	cubo->car[8].ind_c[0]=3; 
	cubo->car[8].ind_c[1]=2;
	cubo->car[8].ind_c[2]=6;
	// cara 3,6,7
	cubo->car[9].ind_c[0]=3; 
	cubo->car[9].ind_c[1]=6;
	cubo->car[9].ind_c[2]=7;
	// cara 4,1,0
	cubo->car[10].ind_c[0]=4; 
	cubo->car[10].ind_c[1]=1;
	cubo->car[10].ind_c[2]=0;
	// cara 4,5,1
	cubo->car[11].ind_c[0]=4; 
	cubo->car[11].ind_c[1]=5;
	cubo->car[11].ind_c[2]=1;

}
void construir_piramide(float tam, float al, struct solido *piramide)
{
	// Dividimos a la mitad el tamaño, para que las coordenadas sean 
	// las adecuadas
	tam=tam/2;

	// Un tetraedro tiene 4 vertices y 4 caras
	piramide->n_v=4;
	piramide->n_c=4;

	/*************** Inicio colores vertices *********************/

	piramide->ver[0].color_vertices[0]=1;
	piramide->ver[0].color_vertices[1]=0;
	piramide->ver[0].color_vertices[2]=0;

	piramide->ver[1].color_vertices[0]=0;
	piramide->ver[1].color_vertices[1]=1;
	piramide->ver[1].color_vertices[2]=0;

	piramide->ver[2].color_vertices[0]=0;
	piramide->ver[2].color_vertices[1]=0;
	piramide->ver[2].color_vertices[2]=1;

	piramide->ver[3].color_vertices[0]=1;
	piramide->ver[3].color_vertices[1]=1;
	piramide->ver[3].color_vertices[2]=0;

	/*************** Inicio colores vertices *********************/

   /************ Inicio Colores caras fijo ***********************/
	piramide->colores[0].r=0.1;
	piramide->colores[0].g=0.1;
	piramide->colores[0].b=0.1;

	piramide->colores[1].r=0.2;
	piramide->colores[1].g=0.2;
	piramide->colores[1].b=0.2;

	piramide->colores[2].r=0.3;
	piramide->colores[2].g=0.3;
	piramide->colores[2].b=0.3;

	piramide->colores[3].r=0.4;
	piramide->colores[3].g=0.4;
	piramide->colores[3].b=0.4;
	/************ Fin Colores caras fijo ***********************/

	// metemos coordenadas
	piramide->ver[0].coord[0]=-tam;
	piramide->ver[0].coord[1]=-tam; //0
	piramide->ver[0].coord[2]=tam;

	piramide->ver[1].coord[0]=tam;
	piramide->ver[1].coord[1]=-tam; //1
	piramide->ver[1].coord[2]=tam;

	piramide->ver[2].coord[0]=0;
	piramide->ver[2].coord[1]=-tam;  //2
	piramide->ver[2].coord[2]=-tam;

	piramide->ver[3].coord[0]=0;
	piramide->ver[3].coord[1]=al-tam;  //3
	piramide->ver[3].coord[2]=0;

	// caras


	piramide->car[0].ind_c[0]=0; 
	piramide->car[0].ind_c[1]=1;
	piramide->car[0].ind_c[2]=2;

	// cara 1,2,3
	piramide->car[1].ind_c[0]=0; 
	piramide->car[1].ind_c[1]=2;
	piramide->car[1].ind_c[2]=3;

	// cara 1,5,2
	piramide->car[2].ind_c[0]=0; 
	piramide->car[2].ind_c[1]=3;
	piramide->car[2].ind_c[2]=1;

	// cara 5,6,2
	piramide->car[3].ind_c[0]=1; 
	piramide->car[3].ind_c[1]=3;
	piramide->car[3].ind_c[2]=2;



}

//**************************************************************************
// funciones de visualización
//**************************************************************************

void draw_puntos_color_diferente(struct vertices *ver, int n_v, float r,float g,float b,int grosor)
{
	int i;
	glPointSize(grosor);
	glBegin(GL_POINTS);
		for(i=0;i<n_v;i++)
		{
			
			glColor3f(ver[i].color_vertices[0],ver[i].color_vertices[1],ver[i].color_vertices[2]);
			glVertex3f(ver[i].coord[0],ver[i].coord[1],ver[i].coord[2]);
		}
	glEnd();
}

void draw_puntos(struct vertices *ver, int n_v, float r,float g,float b,int grosor)
{
    int i;
    glColor3f(r,g,b);
    glPointSize(grosor);
    glBegin(GL_POINTS);
        for(i=0;i<n_v;i++)
        {
        
            glVertex3f(ver[i].coord[0],ver[i].coord[1],ver[i].coord[2]);
        }
    glEnd();
}

void draw_arista_solido(struct solido *malla, float r, float g, float b, int modo, int grosor)
{
	int i,n;
	n=malla->n_c;


	if(modo==GL_LINE)
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	else if(modo=GL_FILL)
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);

	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for(i=0;i<n;i++)
	{
		glVertex3fv(malla->ver[malla->car[i].ind_c[0]].coord);
		glVertex3fv(malla->ver[malla->car[i].ind_c[1]].coord);
		glVertex3fv(malla->ver[malla->car[i].ind_c[2]].coord);

    }
	glEnd();
}

void draw_arista_solido_color_cada_cara(struct solido *malla, float r, float g, float b, int modo, int grosor)
{
    int i,n;
    n=malla->n_c;

    if(modo==GL_LINE)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else if(modo=GL_FILL)
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    else
        glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);

    glBegin(GL_TRIANGLES);

    for(i=0;i<n;i++)
    {
        /********************Color para cada cara *************************************************/
        glColor3f(malla->colores[i].r,malla->colores[i].g,malla->colores[i].b);
        /********************Fin Color para cada cara ************************************************/
        glVertex3fv(malla->ver[malla->car[i].ind_c[0]].coord);
        glVertex3fv(malla->ver[malla->car[i].ind_c[1]].coord);
        glVertex3fv(malla->ver[malla->car[i].ind_c[2]].coord);
    }
    glEnd();
}


void draw_arista_solido_smooth(struct solido *malla, float r, float g, float b, int modo, int grosor)
{
	int i,n;
	n=malla->n_c;


	if(modo==GL_LINE)
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	else if(modo=GL_FILL)
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);

	
	glBegin(GL_TRIANGLES);

	glShadeModel(GL_SMOOTH);

	for(i=0;i<n;i++)
	{
		/******* modo smooth **************/
		glColor3f(1,0,0);
		glVertex3fv(malla->ver[malla->car[i].ind_c[0]].coord);
		glColor3f(0,1,0);
		glVertex3fv(malla->ver[malla->car[i].ind_c[1]].coord);
		glColor3f(0,0,1);
		glVertex3fv(malla->ver[malla->car[i].ind_c[2]].coord);
		
	}
	glEnd();

	//glShadeModel(GL_FLAT);
	
}
void draw_solido_ajedrez(struct solido *malla, float r1, float g1, float b1, float r2, float g2, float b2)
{
	int num_caras,i;
	num_caras=malla->n_c;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glBegin(GL_TRIANGLES);
	for(i=0;i<num_caras;i++)
	{
		if(i%2==0)
			glColor3f(r1,g1,g1);
		else
			glColor3f(r2,g2,g2);

		glVertex3fv(malla->ver[malla->car[i].ind_c[0]].coord);
		glVertex3fv(malla->ver[malla->car[i].ind_c[1]].coord);
		glVertex3fv(malla->ver[malla->car[i].ind_c[2]].coord);
	}
	glEnd();
}
