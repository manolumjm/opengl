//**************************************************************************
// Práctica 5
//**************************************************************************


#include <GL/glut.h>
#include <ctype.h>
#include "objetos.h"
#include "modelo_ply.h"
#include "modelo_revolucion.h"
#include "grua.h"
#include "camara.h"


#define tam_buffer 100

int tipo;
char modo;
char accion;
int camaraActiva=0;
unsigned zoom=5;
float zoom1=5.0;
int xant,yant;
bool primeraVez=true;
vector <bool> figuraClickeada; // para saber indice de la figura clickeada y cambiar su color
int numeroFigurasClickeadas=4; // Serían 3 figuras (no 4). Recordad que empezamos desde LoadName(1) para las figuras

_cubo cubo(1);
_piramide piramide(1);
modelo_ply ply;
modelo_ply ply_perfil;
modelo_revolucion revolucion;
//grua grua;
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

// Camara
vector <Camara> camara;
Vista vi;

bool clickDerecho=false;
bool clickIzquierdo=false;
bool picking=false;

// tamaño de los ejes
const int AXIS_SIZE = 5000;

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
    if(!picking)
	   glLoadIdentity();
	
    if(camara[camaraActiva].getVista() == perspectiva) // perspectiva
    {
        
        glFrustum(-Window_width, Window_width, -Window_height, Window_height, Front_plane, Back_plane);
    }

    else // alzado, perfil y planta
    {
        glOrtho(zoom1 * -Window_width * glutGet(GLUT_WINDOW_WIDTH) / (float) UI_window_width , 
            zoom1 * Window_width * glutGet(GLUT_WINDOW_WIDTH) / (float) UI_window_width, 
            zoom1 * -Window_height * glutGet(GLUT_WINDOW_HEIGHT) / (float) UI_window_height, 
            zoom1 * Window_height * glutGet(GLUT_WINDOW_HEIGHT) / (float) UI_window_height,
            -100,100);   
    }
        

}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
    camara[camaraActiva].setObservador();
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
void draw_lata_peones()
{
    glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            lata.draw_textura_iluminacion_plana(1,tex.imagen);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.5,0.28,0.5);
            glScalef(0.2,0.2,0.2);
            // Dibujar peon madera
            peon_madera.draw_textura_iluminacion_plana(1,tex2.imagen);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.5,0.28,-0.5);
            glScalef(0.2,0.2,0.2);
            // Dibujar peon negro
            peon_negro.iluminacion_plana();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.5,0.28,0);
            glScalef(0.2,0.2,0.2);
            // Dibujar peon blanco
            peon_blanco.iluminacion_suave();
        glPopMatrix();
}

void draw_modelo_jerarquico()
{
    grua grua(cuadradoPluma,giroBrazo,alargaPluma);
    grua.dibujar(); 
}


//**************************************************************************
// Funcion para elegir el tipo de dibujado de las figuras
//***************************************************************************
template <class T>
void paint_object(T object)
{
    switch(modo)
    {
        case 'P': 
            object.draw_puntos(0, 0, 0, 2); 
            break;
        case 'A': 
            object.draw_aristas(0, 1, 0, 4); 
            break;
        case 'S': 
            object.draw_solido(1, 0, 0); 
            break;
        case 'J': 
            object.draw_solido_ajedrez(1, 0, 0, 0, 1, 0); 
            break;
    }
}

//**************************************************************************
// Funcion de dibujado según el click 
//***************************************************************************
void draw_objects_with_names()
{
    for(int i=1;i<numeroFigurasClickeadas;i++)
    {
        glPushMatrix();
        glTranslatef(0,13.0*(i-1),0.0);
        glLoadName(i);
        if(figuraClickeada[i]==true)
            ply.draw_solido(0, 1, 0);
        else 
            ply.draw_solido(1, 0, 0);
        glPopMatrix();
    }  
}

//**************************************************************************
// Funcion para elegir el tipo de objetos a dibujar
//***************************************************************************
void draw_objects()
{
    switch (tipo) 
    {
        case 1:
            paint_object(cubo); // cubo 
            break;
        case 2:
            paint_object(piramide); // pirámide
            break;
        case 3:
            paint_object(ply); // ply 
            break;
        case 4:
            paint_object(revolucion); // objeto por revolución
            break;
        case 5:
            draw_modelo_jerarquico(); // grúa
            break;
        case 6:
            draw_lata_peones(); // lata de coca cola + peones
            break;
        case 7:
            draw_objects_with_names(); // objetos con opción a click
    }
}

//**************************************************************************
// Funcion para iniciar las luces
//***************************************************************************

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
// Funcion de dibujado completo de la escena
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
    switch(Tecla1)
    {
        case '1': case '2': case '3': case '4': case '5': case '6': case '7':
            tipo = Tecla1 - '0'; break;
        case 'Q': case 'q': 
            exit(0); break;
        case 'P': case 'p': case 'A': case 'a': case 'S': case 's': case 'J': case 'j': 
            modo=(char)toupper(Tecla1); break;
        case 'z':
            if(cuadradoPluma<0.3) 
                cuadradoPluma=cuadradoPluma+0.05; 
            break;
        case 'Z':
            if(cuadradoPluma>-1.5)
                cuadradoPluma=cuadradoPluma-0.05;
            break;
        case 'x': giroBrazo=giroBrazo+0.5; break;
        case 'X': giroBrazo=giroBrazo-0.5; break;
        case 'c': 
            if(alargaPluma<5)
                alargaPluma=alargaPluma+0.05;
            break;
        case 'C':
            if(alargaPluma>-0.55)
                alargaPluma=alargaPluma-0.05;
            break;

    }

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

	switch (Tecla1) 
    {
        // Teclado adaptado para ambas proyecciones (perspectiva y ortogonal)
        case GLUT_KEY_LEFT:
            if(camaraActiva==3)
                camara[camaraActiva].Observer_angle_y--; 
            else
            {
                if(camaraActiva==0) // alzado 
                {
                    camara[camaraActiva].x-=0.1;
                }
                else if(camaraActiva==1) // perfil 
                {
                    camara[camaraActiva].z-=0.1;
                }
                else // planta
                {
                    camara[camaraActiva].x-=0.1;
                }
            }
            break;

        case GLUT_KEY_RIGHT:
            if(camaraActiva==3)
                camara[camaraActiva].Observer_angle_y++; 
            else
            {
                if(camaraActiva==0) // alzado 
                {
                    camara[camaraActiva].x+=0.1;
                }
                else if(camaraActiva==1) // perfil 
                {
                    camara[camaraActiva].z+=0.1;
                }
                else // planta
                {
                    camara[camaraActiva].x+=0.1;
                }
            }
            break;

        case GLUT_KEY_UP:
            if(camaraActiva==3)
                camara[camaraActiva].Observer_angle_x--; 
            else
            {
                if(camaraActiva==0) // alzado 
                {
                    camara[camaraActiva].y+=0.1;
                }
                else if(camaraActiva==1) // perfil 
                {
                    camara[camaraActiva].y+=0.1;
                }
                else // planta
                {
                    camara[camaraActiva].z+=0.1;
                }
            }
            break;

        case GLUT_KEY_DOWN:
            if(camaraActiva==3)
                camara[camaraActiva].Observer_angle_x++; 
            else
            {
                if(camaraActiva==0) // alzado 
                {
                    camara[camaraActiva].y-=0.1;
                }
                else if(camaraActiva==1) // perfil 
                {
                    camara[camaraActiva].y-=0.1;
                }
                else // planta
                {
                    camara[camaraActiva].z-=0.1;
                }
            }
            break;

        case GLUT_KEY_PAGE_UP: 
            if(camaraActiva==3) // perspectiva
                camara[camaraActiva].Observer_distance *= 1.2; 
            else // ortogonal
                zoom1*=1.1;   
            break;

        case GLUT_KEY_PAGE_DOWN:
            if(camaraActiva==3) // perspectiva
                camara[camaraActiva].Observer_distance /= 1.2;
            else // ortogonal
                zoom1*=0.9;
            break;


        case GLUT_KEY_F1 : cout << "Entra en F1 -> Proyección ortogonal: ALZADO" << endl;camaraActiva=0; break;
        case GLUT_KEY_F2 : cout << "Entra en F2 -> Proyección ortogonal: PERFIL" << endl;camaraActiva=1; break;
        case GLUT_KEY_F3 : cout << "Entra en F3 -> Proyección ortogonal: PLANTA" << endl;camaraActiva=2; break;
        case GLUT_KEY_F4 : cout << "Entra en F4 -> Proyección perspectiva" << endl;camaraActiva=3; break;
	}

    picking=false;
    change_projection();

	glutPostRedisplay();
}


//***************************************************************************
// Funcion de selección
//***************************************************************************

int procesar_hits(GLint hits, GLuint *names)
{
    int indiceEncontrado=-1;
    
    // mostrar contenido de la pila
    cout << "hits " << hits << endl;
    for(int i=0;i<hits;i++)
    {
        cout << "Numero:" << names[i*4] << endl;
        cout << "Min Z:" << names[i*4+1] << endl;
        cout << "Max Z:" << names[i*4+2] << endl;
        cout << "Nombre de la pila: " << names[i*4+3] << endl;
    }

    if(hits > 0) // hay algun objeto 
    {
        float z, Zmin = INFINITY;

        for(int i=0; i < hits;i++)
        {
            if(names[i*4]!=0)
            {
                z = names[i*4+1]; // Valor de z min
                if(z < Zmin)
                {
                    indiceEncontrado = names [i*4+3]; // indice del objeto (corresponde al mismo en LoadName(i))
                    Zmin = z;
                }
            }
        }
    }
    return indiceEncontrado;
}


//***************************************************************************
// Funcion de selección
//***************************************************************************
int pick (int x, int y)
{
    GLuint selectBuf[tam_buffer]={0}; // tam_buffer=100
    GLint viewport[4],hits=0;
    int indiceEncontrado;

    // Declarar buffer de selección
    glSelectBuffer(tam_buffer,selectBuf);

    // Obtener los parámetros del viewport
    glGetIntegerv (GL_VIEWPORT, viewport);

    // Pasar OpenGL a modo seleccion
    glRenderMode(GL_SELECT);
    glInitNames(); 
    glPushName(0);

    // Fijar la transformación de proyección para selección
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPickMatrix(x,(viewport[3]-y),5.0,5.0,viewport);
    // creo que va esto en vez de glFrustum
    picking=true; // para que no haga LoadIdentity()
    change_projection();
    //glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);

    // Dibujar escena
    draw_objects_with_names();

    // Pasar OpenGL a modo rener
    hits = glRenderMode(GL_RENDER);

    // Restablecer la transformación de proyección
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    picking=false;
    change_projection();
    //glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);

    // Procesar el contenido del buffer de selección
    indiceEncontrado = procesar_hits(hits, selectBuf);

    return indiceEncontrado;
}

//***************************************************************************
// Funciones para detectar el click del raton
//***************************************************************************
void clickRaton(int boton, int estado, int x, int y)
{
    int indiceEncontrado;
    if(boton == GLUT_RIGHT_BUTTON) // click derecho
    {
        clickIzquierdo=false;
        if(estado == GLUT_DOWN) // mantiene pulsado el click derecho
        {
            clickDerecho=true;
            indiceEncontrado = pick(x,y);

        }
        else // deja de pulsar el click derecho
        {
           clickDerecho=false; 
        }
    }
    else
    {
        clickDerecho=false;   
        if(boton == GLUT_LEFT_BUTTON)
        {
            
            if(estado == GLUT_DOWN)
            {
                clickIzquierdo=true;
                indiceEncontrado = pick(x,y);
                cout << "Indice encontrado = " << indiceEncontrado << endl;
                if(indiceEncontrado!=-1 && figuraClickeada[indiceEncontrado]==false) // pulsa y cambia color
                    figuraClickeada[indiceEncontrado]=true;
                else if(indiceEncontrado!=-1 && figuraClickeada[indiceEncontrado]==true) // despulsa y cambia color
                    figuraClickeada[indiceEncontrado]=false;
                draw_objects_with_names();
            }
            else
            {
               clickIzquierdo=false; 
            }
        }  
    }


    glutPostRedisplay();
}

//***************************************************************************
// Funcion para saber posicion (x,y) en la que se encuentra el raton
//***************************************************************************
void ratonMovido(int x, int y)
{

    if(clickDerecho)
    {
        // Si es la primera vez que hace click, nos podría dar x=270 e y=270, por lo que 
        // x-xant = 270 e y-yant=270. Para alzado, perfil y planta supone un problema ya que 
        // al aumentar una de sus coordenadas esa cantidad se dejaría de ver. 
        // Una vez que esa primera vez es realizada, los valores de x-ant y y-ant estan en el rango {-1,0,1}       
        if(primeraVez) 
        {
            xant = x;
            yant = y;
            primeraVez=false;
        }

        camara[camaraActiva].girar(x-xant,y-yant);
        xant=x;
        yant=y;

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
	camara[camaraActiva].Observer_distance = zoom * Front_plane;
	camara[camaraActiva].Observer_angle_x = 0;
	camara[camaraActiva].Observer_angle_y = 0;

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
    // ply
	ply.leer_ply((char*)"beethoven.ply");
	ply_perfil.leer_ply((char*)"perfil1.ply");
	revolucion.hacer_revolucion(ply_perfil.vertices,20,0, 360);

    // texturas
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

   
    // camaras
    camara.resize(4);

    vi=alzado;
    camara[0].setVista(vi);

    vi=perfil;
    camara[1].setVista(vi);

    vi=planta;
    camara[2].setVista(vi);

    vi=perspectiva;
    camara[3].setVista(vi);

    // click
    figuraClickeada.resize(numeroFigurasClickeadas);

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
	glutCreateWindow("Práctica 5");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);
	// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "tecla_normal" al evento correspondiente
	glutKeyboardFunc(normal_keys);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_keys);

    // Funciones del ratón
    glutMouseFunc(clickRaton);
    glutMotionFunc(ratonMovido);

	// funcion de inicialización
	initialize();

    // inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
