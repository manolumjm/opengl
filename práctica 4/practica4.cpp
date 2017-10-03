//**************************************************************************
// Práctica 4
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "objetos.h"
#include "modelo_ply.h"
#include "modelo_revolucion.h"
#include "grua.h"

int tipo;
char modo;
char accion;

_cubo cubo(1);
_piramide piramide(1);
modelo_ply ply;
modelo_ply ply_perfil;
modelo_revolucion revolucion;

modelo_ply ply1_lata_centro;
modelo_ply ply2_lata_tapa_superior;
modelo_ply ply3_lata_tapa_inferior;

modelo_ply ply4_peon_madera;
modelo_ply ply5_peon_negro;
modelo_ply ply6_peon_blanco;

modelo_revolucion lata_tapa_superior;
modelo_revolucion lata_tapa_inferior;
modelo_revolucion peon_negro;
modelo_revolucion peon_blanco;

// Objetos con texturas
revolucion_tex lata;
revolucion_tex peon_madera;

// Texturas
const char *  coca_tex = "text-lata-1.jpg";
textura tex(coca_tex);
const char *  wood_tex = "text-madera.jpg";
textura tex2(wood_tex);

// Movimientos grua
float cuadradoPluma=0.0;
float giroBrazo = 0.0;
float alargaPluma = 0.0;


// tamaño de los ejes
const int AXIS_SIZE = 5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width, Window_height, Front_plane, Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x = 50, UI_window_pos_y = 50, UI_window_width = 500, UI_window_height = 500;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-Window_width, Window_width, -Window_height, Window_height, Front_plane, Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -Observer_distance);
	glRotatef(Observer_angle_x, 1, 0, 0);
	glRotatef(Observer_angle_y, 0, 1, 0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	glBegin(GL_LINES);
	// eje X, color rojo
	glColor3f(1, 0, 0);
	glVertex3f(-AXIS_SIZE, 0, 0);
	glVertex3f(AXIS_SIZE, 0, 0);
	// eje Y, color verde
	glColor3f(0, 1, 0);
	glVertex3f(0, -AXIS_SIZE, 0);
	glVertex3f(0, AXIS_SIZE, 0);
	// eje Z, color azul
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -AXIS_SIZE);
	glVertex3f(0, 0, AXIS_SIZE);
	glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
	if (tipo == 1)
	{
		if (modo == 'P')
			cubo.draw_puntos(0, 0, 0, 2);
		else if (modo == 'A')
			cubo.draw_aristas(0, 1, 0, 4);
		else if (modo == 'S')
			cubo.draw_solido(1, 0, 0);
		else if (modo == 'J')
			cubo.draw_solido_ajedrez(1, 0, 0, 0, 1, 0);
		
	}
	else if (tipo == 2)
	{

		if (modo == 'P')
			piramide.draw_puntos(0, 0, 0, 2);
		else if (modo == 'A')
			piramide.draw_aristas(0, 1, 0, 4);
		else if (modo == 'S')
			piramide.draw_solido(1, 0, 0);
		else if (modo == 'J')
			piramide.draw_solido_ajedrez(1, 0, 0, 0, 1, 0);
		
	}
    else if(tipo == 3)
    {
        if (modo == 'P')
            ply.draw_puntos(0, 0, 0, 2);
        else if (modo == 'A')
            ply.draw_aristas(0, 1, 0, 4);
        else if (modo == 'S')
            ply.draw_solido(1, 0, 0);
        else if (modo == 'J')
            ply.draw_solido_ajedrez(1, 0, 0, 0, 1, 0);
       
    }
    else if(tipo == 4)
    {
        if (modo == 'P')
            revolucion.draw_puntos(0, 0, 0, 2);
        else if (modo == 'A')
            revolucion.draw_aristas(0, 1, 0, 4);
        else if (modo == 'S')
            revolucion.draw_solido(1, 0, 0);
            //revolucion.draw_solido_prueba();
        else if (modo == 'J')
            revolucion.draw_solido_ajedrez(1, 0, 0, 0, 1, 0);
        
    }
    else if(tipo == 5)
    {
        grua grua(cuadradoPluma,giroBrazo,alargaPluma);
        grua.dibujar();
    }
    else if(tipo == 6) /*NOTA: MOVER HACIA ATRÁS PARA QUE SE VE LA TEXTURA*/
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            // Dibuja la lata
            lata.draw_textura_iluminacion_plana(1,tex.imagen);
            lata_tapa_superior.iluminacion_suave();
            lata_tapa_inferior.iluminacion_suave();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.5,0.28,0.5);
            glScalef(0.2,0.2,0.2);
            // Dibuja peon madera
            peon_madera.draw_textura_iluminacion_plana(1,tex2.imagen);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.5,0.28,-0.5);
            glScalef(0.2,0.2,0.2);
            // Dibuja peon negro
            peon_negro.iluminacion_plana();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.5,0.28,0);
            glScalef(0.2,0.2,0.2);
            // Dibujar peon blanco
            peon_blanco.iluminacion_suave();
        glPopMatrix();   
    }
}

void luces()
{
    GLfloat light_position[4] = {10.0,0.0,10.0,1.0}; //al ser 0.0 es una luz en el infinito
    GLfloat light_position2[4] = {0.0,10.0,10.0,1.0}; //al ser 0.0 es una luz en el infinito
    GLfloat color_luz_2[4] = {0.7,0.7,0.7,1.0};
    GLfloat color_luz_1[4] = {0.3,0.3,0.3,0};
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glLightfv(GL_LIGHT1,GL_POSITION,light_position2);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,color_luz_2);
    glLightfv(GL_LIGHT1,GL_SPECULAR,color_luz_1);
    glDisable(GL_LIGHTING);
}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

	clear_window();
    luces();
	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1, int Alto1)
{
	change_projection();
	glViewport(0, 0, Ancho1, Alto1);
	glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1, int x, int y)
{

	if (toupper(Tecla1) == 'Q')
		exit(0);
	else if (toupper(Tecla1) == '1' || toupper(Tecla1) == '2' || toupper(Tecla1) == '3' || toupper(Tecla1) == '4' || toupper(Tecla1) == '5' || toupper(Tecla1) == '6')
		tipo = Tecla1-48;
	else if (toupper(Tecla1) == 'P' || toupper(Tecla1) == 'A' || toupper(Tecla1) == 'S' || toupper(Tecla1) == 'J')
		modo = (char)toupper(Tecla1);
	else if (toupper(Tecla1) == 'T')
		modo = (char)Tecla1;
    else if (Tecla1 == 'z' && cuadradoPluma<0.3)
        cuadradoPluma=cuadradoPluma+0.05;
    else if (Tecla1 =='Z' && cuadradoPluma>-1.5)    
        cuadradoPluma=cuadradoPluma-0.05;
    else if (Tecla1 == 'x' )
        giroBrazo=giroBrazo+0.5;
    else if (Tecla1 =='X')
        giroBrazo=giroBrazo-0.5;
    else if (Tecla1 == 'c' && alargaPluma<5)
        alargaPluma=alargaPluma+0.05;
    else if (Tecla1 =='C'&& alargaPluma>-0.55)
        alargaPluma=alargaPluma-0.05;

	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1, int x, int y)
{

	switch (Tecla1) {
	case GLUT_KEY_LEFT:Observer_angle_y--; break;
	case GLUT_KEY_RIGHT:Observer_angle_y++; break;
	case GLUT_KEY_UP:Observer_angle_x--; break;
	case GLUT_KEY_DOWN:Observer_angle_x++; break;
	case GLUT_KEY_PAGE_UP:Observer_distance *= 1.2; break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance /= 1.2; break;
	}
	glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
	// se inicalizan la ventana y los planos de corte
	Window_width = 0.5;
	Window_height = 0.5;
	Front_plane = 1;
	Back_plane = 1000;

	// se inicia la posicion del observador, en el eje z
	Observer_distance = 3 * Front_plane;
	Observer_angle_x = 0;
	Observer_angle_y = 0;

	// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1, 1, 1, 1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	//
	change_projection();
	//
	glViewport(0, 0, UI_window_width, UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
	ply.leer_ply((char*)"beethoven.ply");
	ply_perfil.leer_ply((char*)"perfil1.ply");
	revolucion.hacer_revolucion(ply_perfil.vertices,20,0, 360);

    ply1_lata_centro.leer_ply((char*)"lata-pcue.ply");
    lata.hacer_revolucion_tex(ply1_lata_centro.vertices,40);
    
    ply2_lata_tapa_superior.leer_ply((char*)"lata-psup.ply");
    lata_tapa_superior.hacer_revolucion(ply2_lata_tapa_superior.vertices,40,0,360);

    ply3_lata_tapa_inferior.leer_ply((char*)"lata-pinf.ply");
    lata_tapa_inferior.hacer_revolucion(ply3_lata_tapa_inferior.vertices,40,0,360);


    ply4_peon_madera.leer_ply((char*)"perfil1.ply");
    peon_madera.hacer_revolucion_tex(ply4_peon_madera.vertices,40);

    ply5_peon_negro.leer_ply((char*)"perfil1.ply");
    peon_negro.hacer_revolucion(ply5_peon_negro.vertices,20,0,360);

    ply6_peon_blanco.leer_ply((char*)"perfil1.ply");
    peon_blanco.hacer_revolucion(ply6_peon_blanco.vertices,20,0,360);

    //revolucion.puntos_figura4();
    //revolucion.hacer_revolucion(revolucion.vertices,20,0,360);
    // Reservamos tamaño para cubo1 
	//cubo1 = (struct solido*)malloc(sizeof(struct solido));
	// Reservamos tamaño para los 8 vertices del cubo1
	//cubo1->ver = (struct vertices*)malloc(8 * sizeof(struct vertices));
	// Reservamos tamaño para los 12 triangulos del cubo1
	//cubo1->car = (struct caras*)malloc(12 * sizeof(struct caras));

	// Reserva de color segun caras para cubo1
	//cubo1->colores = (struct color*)malloc(12* sizeof(struct color));

	// Reservamos tamaño para cubo1 
	//tetraedro = (struct solido*)malloc(sizeof(struct solido));
	// Reservamos tamaño para los 8 vertices del cubo1
	//tetraedro->ver = (struct vertices*)malloc(4 * sizeof(struct vertices));
	// Reservamos tamaño para los 12 triangulos del cubo1
	//tetraedro->car = (struct caras*)malloc(4 * sizeof(struct caras));

	//tetraedro->colores = (struct color*)malloc(4 * sizeof(struct color));

	//construir_cubo(5, cubo1);
	//construir_piramide(5, 5, tetraedro);


	// se llama a la inicialización de glut
	glutInit(&argc, argv);

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(UI_window_pos_x, UI_window_pos_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(UI_window_width, UI_window_height);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("Práctica 4");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);
	// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "tecla_normal" al evento correspondiente
	glutKeyboardFunc(normal_keys);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_keys);

	// funcion de inicialización
	initialize();

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
