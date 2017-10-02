//**************************************************************************
// Práctica 2
// Class to make objects by revolution
//**************************************************************************

#include "modelo_revolucion.h"

modelo_revolucion::modelo_revolucion()
{
    
}

/**
  * Método de dibujado por revolución de objetos a partir de puntos iniciales.
  * @param ver Vector de vertices que contiene los puntos iniciales y a partir de los cuales se
  * formará el objeto.
  * @param numer_of_rotations numero de rotaciones que se realizarán para la revolución.
  * @param angulo_inicial Ángulo inicial a partir del cual se formará la figura por revolución.
  * @param angulo_final Ángulo final a partir del cual se formará la figura por revolución.
*/
void modelo_revolucion::hacer_revolucion(vector<_vertex3f> ver,int number_of_rotations,double angulo_inicial, double angulo_final)
{
    vector<_vertex3f> vertices_revolucion;
    vector<_vertex3f> tapas;
    vector<_vertex3i> caras_revolucion;
    _vertex3f nuevo;
    _vertex3i nueva;
    int number_of_vertex, number_of_faces, angulo_rotacion,vertices_para_revolucion,tam_inicial, vertice_inicial, vertice_final;
    int tapa = 0;
    double angulo; 
    bool tapa_arriba = false;
    bool tapa_abajo = false;
    int con_grados = 0;

    _color3f lado1; lado1.r=1; lado1.g=0; lado1.b=0;
    _color3f lado2; lado2.r=0; lado2.g=1; lado2.b=0;
    _color3f tapa1; tapa1.r=1; tapa1.g=1;  tapa1.b=0;
    _color3f tapa2; tapa2.r=0; tapa2.g=1;  tapa2.b=1;
    
    

    /* Vemos si necesita tapa*/
    if (ver[0].x == 0) // primero 
    {
        tapa++;
        tapa_abajo = true;
    }

    if (ver[ver.size() - 1].x == 0) //ultimo
    {
        tapa++;
        tapa_arriba = true;
    }

    // Metemos vertices iniciales en vertices_revolucion y vertices de tapas en TAPAS
    for (int i = 0; i < ver.size(); i++)
    {
        if (tapa_abajo && i == 0)
            tapas.push_back(ver[i]);
        else if (tapa_arriba && i == ver.size() - 1)
            tapas.push_back(ver[i]);
        else
            vertices_revolucion.push_back(ver[i]);
        
    }

    // Tapas que tendremos
    tapa = tapas.size(); 

    // Vértices de partida sin contar los de la tapa
    tam_inicial = vertices_revolucion.size(); 

    // Si la figura no es completa, debemos hacer una modificacion ( 2 vertices mas para tener una cara que no cierra la figura)
    if (angulo_inicial != 0 || angulo_final != 360)
        con_grados=tam_inicial;
    
    // Vertices que se obtendran al rotar (LOS VERTICES TAPA NO ROTAN)
    vertices_para_revolucion = tam_inicial*number_of_rotations; 


    /********************************************/
    /* PARTE DE VERTICES */
    /********************************************/

    // Cálculo del ángulo total que haremos desde el angulo_inicial a angulo_final a radianes
    angulo = (((angulo_final - angulo_inicial)*M_PI)/180)/number_of_rotations;
    
    // Cálculo de angulo_inicial a radianes
    angulo_inicial = ((angulo_inicial*M_PI)/180);

    // Rotación de los ángulos iniciales dependiendo de angulo_inicial
    for (int i = 0; i < vertices_revolucion.size(); i++)
    {
        nuevo.x = cos(angulo_inicial)* vertices_revolucion[i].x + sin(angulo_inicial)* vertices_revolucion[i].z;  //x
        nuevo.y = vertices_revolucion[i].y;                                                                              //y
        nuevo.z = -sin(angulo_inicial)* vertices_revolucion[i].x + cos(angulo_inicial)* vertices_revolucion[i].z; //z

        vertices_revolucion[i].x = nuevo.x;
        vertices_revolucion[i].y = nuevo.y;
        vertices_revolucion[i].z = nuevo.z;
    }


    // Vértices por revolución (sin tapas)
    for (int i = 0; i < vertices_para_revolucion - tam_inicial + con_grados; i++) 
    {
        // Rotamos sobre Y el ultimo elemento
        nuevo.x = cos(angulo)* vertices_revolucion[i].x + sin(angulo)* vertices_revolucion[i].z;  //x
        nuevo.y = vertices_revolucion[i].y;                                                              //y
        nuevo.z = -sin(angulo)* vertices_revolucion[i].x + cos(angulo)* vertices_revolucion[i].z; //z
        
        vertices_revolucion.push_back(nuevo);
    }


    /********************************************/
    /* PARTE DE CARAS */
    /********************************************/

    vertice_inicial = vertices_para_revolucion;
    vertice_final = vertice_inicial + tam_inicial;

    int contador=0;
    // Caras por revolucion (sin tapas)
    for (int num = 0; num < number_of_rotations; num++)
    {
        vertice_inicial = num*(tam_inicial);
        vertice_final = vertice_inicial + tam_inicial;

        for (int i = vertice_inicial + 1, k = vertice_final + 1; i < vertice_final; i++, k++)
        {

            nueva._0 = i - 1;
            nueva._1 = (k - 1) % (vertices_para_revolucion+con_grados);
            nueva._2 = k % (vertices_para_revolucion+con_grados);
            
            //color.push_back(lado1);
            caras_revolucion.push_back(nueva);

            nueva._0 = i - 1;
            nueva._1 = k % (vertices_para_revolucion+con_grados);
            nueva._2 = i;

            //color.push_back(lado2);
            caras_revolucion.push_back(nueva); 

            if(contador%2==0)
            {
                color.push_back(lado1);
                color.push_back(lado1);
            }
            else
            {
                color.push_back(lado2);
                color.push_back(lado2);
            }
            contador++;
        }
    }

    /* Añadimos tapa de abajo*/
    if (tapa_abajo)
    {
        vertices_revolucion.push_back(tapas[0]);
        for (int i = 0; i < number_of_rotations; i++)
        {
            vertice_inicial = i*tam_inicial;
            vertice_final = vertice_inicial + tam_inicial;

            nueva._0 = vertices_revolucion.size() - 1;
            nueva._1 = vertice_final % (vertices_para_revolucion+con_grados);
            nueva._2 = vertice_inicial;

            color.push_back(tapa1);
            caras_revolucion.push_back(nueva);
        }
    }

    /* Añadimos tapa de arriba*/
    if (tapa_arriba)
    {
        vertices_revolucion.push_back(tapas[tapas.size()-1]);
        for (int i = 0; i < number_of_rotations; i++)
        {
            vertice_inicial = (i+1)*tam_inicial-1;
            vertice_final = vertice_inicial + tam_inicial;

            nueva._0 = vertices_revolucion.size() - 1;
            nueva._1 = vertice_inicial;
            nueva._2 = vertice_final % (vertices_para_revolucion+con_grados);
            
            color.push_back(tapa2);
            caras_revolucion.push_back(nueva);
        }
    }
    
    /********************************************/
    /* CREACIÓN DE LA FIGURA */
    /********************************************/

    /* Ahora sabemos el numero de vértices y de caras*/
    number_of_vertex = vertices_revolucion.size();
    number_of_faces = caras_revolucion.size();

    /* Borramos vértices iniciales, para despues reservar tamaño para la figura entera*/
    //delete malla.ver;

    
    /* Reserva de memoria para vértices y caras*/
    vertices.resize(number_of_vertex);
    caras.resize(number_of_faces);
    
    
    /* Asignamos vertices en la figura (malla)*/
    for (int i = 0; i < number_of_vertex; i++)
    {
        vertices[i].x = vertices_revolucion[i].x;
        vertices[i].y = vertices_revolucion[i].y;
        vertices[i].z = vertices_revolucion[i].z;
    }

    /* Asignamos caras a la figura (malla)*/
    for (int i = 0; i < number_of_faces; i++)
    {
        caras[i]._0 = caras_revolucion[i]._0;
        caras[i]._1 = caras_revolucion[i]._1;
        caras[i]._2 = caras_revolucion[i]._2;
    }

}

void modelo_revolucion::puntos_figura1()
{
    //vertices.clear();
    vertices.resize(2);

    vertices[0].x = 1;
    vertices[0].y = -1;
    vertices[0].z = 0;
    vertices[1].x = 1;
    vertices[1].y = 1;
    vertices[1].z = 0;
}
void modelo_revolucion::puntos_figura2()
{
    vertices.clear();
    vertices.resize(3);

    vertices[0].x = 0;
    vertices[0].y = -1;
    vertices[0].z = 0;
    vertices[1].x = 1;
    vertices[1].y = -1;
    vertices[1].z = 0;
    vertices[2].x = 2;
    vertices[2].y = 2;
    vertices[2].z = 0;
}

void modelo_revolucion::puntos_figura3()
{
    vertices.clear();
    vertices.resize(3);

    vertices[0].x = 2;
    vertices[0].y = -2;
    vertices[0].z = 0;
    vertices[1].x = 1;
    vertices[1].y = 1;
    vertices[1].z = 0;
    vertices[2].x = 0;
    vertices[2].y = 1;
    vertices[2].z = 0;
}
void modelo_revolucion::puntos_figura4()
{
    vertices.clear();
    vertices.resize(4);
    
    vertices[0].x = 0;
    vertices[0].y = -1;
    vertices[0].z = 0;
    vertices[1].x = 1;
    vertices[1].y = -1;
    vertices[1].z = 0;
    vertices[2].x = 1;
    vertices[2].y = 1;
    vertices[2].z = 0;
    vertices[3].x = 0;
    vertices[3].y = 1;
    vertices[3].z = 0;
}
void modelo_revolucion::puntos_figura5()
{
    vertices.clear();
    vertices.resize(3);
   
    vertices[0].x = 0;
    vertices[0].y = -1;
    vertices[0].z = 0;
    vertices[1].x = 1;
    vertices[1].y = -1;
    vertices[1].z = 0;
    vertices[2].x = 0;
    vertices[2].y = 1;
    vertices[2].z = 0;
}


void modelo_revolucion::hacer_revolucion_prueba(vector<_vertex3f> ver,int number_of_rotations,double angulo_inicial, double angulo_final)
{
    vector<_vertex3f> vertices_revolucion;
    vector<_vertex3f> tapas;
    vector<_vertex3i> caras_revolucion;
    _vertex3f nuevo;
    _vertex3i nueva;
    int number_of_vertex, number_of_faces, angulo_rotacion,vertices_para_revolucion,tam_inicial, vertice_inicial, vertice_final;
    int tapa = 0;
    double angulo; 
    bool tapa_arriba = false;
    bool tapa_abajo = false;
    int con_grados = 0;
    

    /* Vemos si necesita tapa*/
    if (ver[0].x == 0) // primero 
    {
        tapa++;
        tapa_abajo = true;
    }

    if (ver[ver.size() - 1].x == 0) //ultimo
    {
        tapa++;
        tapa_arriba = true;
    }

    // Metemos vertices iniciales en vertices_revolucion y vertices de tapas en TAPAS
    for (int i = 0; i < ver.size(); i++)
    {
        if (tapa_abajo && i == 0)
            tapas.push_back(ver[i]);
        else if (tapa_arriba && i == ver.size() - 1)
            tapas.push_back(ver[i]);
        else
            vertices_revolucion.push_back(ver[i]);
        
    }

    // Tapas que tendremos
    tapa = tapas.size(); 

    // Vértices de partida sin contar los de la tapa
    tam_inicial = vertices_revolucion.size(); 

    // Si la figura no es completa, debemos hacer una modificacion ( 2 vertices mas para tener una cara que no cierra la figura)
    if (angulo_inicial != 0 || angulo_final != 360)
        con_grados=tam_inicial;
    
    // Vertices que se obtendran al rotar (LOS VERTICES TAPA NO ROTAN)
    vertices_para_revolucion = tam_inicial*number_of_rotations; 


    /********************************************/
    /* PARTE DE VERTICES */
    /********************************************/

    // Cálculo del ángulo total que haremos desde el angulo_inicial a angulo_final a radianes
    angulo = (((angulo_final - angulo_inicial)*M_PI)/180)/number_of_rotations;
    
    // Cálculo de angulo_inicial a radianes
    angulo_inicial = ((angulo_inicial*M_PI)/180);

    // Rotación de los ángulos iniciales dependiendo de angulo_inicial
    for (int i = 0; i < vertices_revolucion.size(); i++)
    {
        nuevo.x = cos(angulo_inicial)* vertices_revolucion[i].x + sin(angulo_inicial)* vertices_revolucion[i].z;  //x
        nuevo.y = vertices_revolucion[i].y;                                                                              //y
        nuevo.z = -sin(angulo_inicial)* vertices_revolucion[i].x + cos(angulo_inicial)* vertices_revolucion[i].z; //z

        vertices_revolucion[i].x = nuevo.x;
        vertices_revolucion[i].y = nuevo.y;
        vertices_revolucion[i].z = nuevo.z;
    }


    // Vértices por revolución (sin tapas)
    for (int i = 0; i < vertices_para_revolucion - tam_inicial + con_grados; i++) 
    {
        // Rotamos sobre Y el ultimo elemento
        nuevo.x = cos(angulo)* vertices_revolucion[i].x + sin(angulo)* vertices_revolucion[i].z;  //x
        nuevo.y = vertices_revolucion[i].y;                                                              //y
        nuevo.z = -sin(angulo)* vertices_revolucion[i].x + cos(angulo)* vertices_revolucion[i].z; //z
        
        vertices_revolucion.push_back(nuevo);
    }


    /********************************************/
    /* PARTE DE CARAS */
    /********************************************/

    vertice_inicial = vertices_para_revolucion;
    vertice_final = vertice_inicial + tam_inicial;

    
    // Caras por revolucion (sin tapas)
    for (int num = 0; num < number_of_rotations; num++)
    {
        vertice_inicial = num*(tam_inicial);
        vertice_final = vertice_inicial + tam_inicial;

        for (int i = vertice_inicial + 1, k = vertice_final + 1; i < vertice_final; i++, k++)
        {
            nueva._0 = i - 1;
            nueva._1 = (k - 1) % (vertices_para_revolucion+con_grados);
            nueva._2 = k % (vertices_para_revolucion+con_grados);
            
            
            
            caras_revolucion.push_back(nueva);

            nueva._0 = i - 1;
            nueva._1 = k % (vertices_para_revolucion+con_grados);
            nueva._2 = i;

            caras_revolucion.push_back(nueva);      
        }
    }

    /* Añadimos tapa de abajo*/
    if (tapa_abajo)
    {
        vertices_revolucion.push_back(tapas[0]);
        for (int i = 0; i < number_of_rotations; i++)
        {
            vertice_inicial = i*tam_inicial;
            vertice_final = vertice_inicial + tam_inicial;

            nueva._0 = vertices_revolucion.size() - 1;
            nueva._1 = vertice_final % (vertices_para_revolucion+con_grados);
            nueva._2 = vertice_inicial;

            caras_revolucion.push_back(nueva);
        }
    }

    /* Añadimos tapa de arriba*/
    if (tapa_arriba)
    {
        vertices_revolucion.push_back(tapas[tapas.size()-1]);
        for (int i = 0; i < number_of_rotations; i++)
        {
            vertice_inicial = (i+1)*tam_inicial-1;
            vertice_final = vertice_inicial + tam_inicial;

            nueva._0 = vertices_revolucion.size() - 1;
            nueva._1 = vertice_inicial;
            nueva._2 = vertice_final % (vertices_para_revolucion+con_grados);
        
            caras_revolucion.push_back(nueva);
        }
    }
    
    /********************************************/
    /* CREACIÓN DE LA FIGURA */
    /********************************************/

    /* Ahora sabemos el numero de vértices y de caras*/
    number_of_vertex = vertices_revolucion.size();
    number_of_faces = caras_revolucion.size();

    /* Borramos vértices iniciales, para despues reservar tamaño para la figura entera*/
    //delete malla.ver;

    
    /* Reserva de memoria para vértices y caras*/
    vertices.resize(number_of_vertex);
    caras.resize(number_of_faces);
    
    
    /* Asignamos vertices en la figura (malla)*/
    for (int i = 0; i < number_of_vertex; i++)
    {
        vertices[i].x = vertices_revolucion[i].x;
        vertices[i].y = vertices_revolucion[i].y;
        vertices[i].z = vertices_revolucion[i].z;
    }

    /* Asignamos caras a la figura (malla)*/
    for (int i = 0; i < number_of_faces; i++)
    {
        caras[i]._0 = caras_revolucion[i]._0;
        caras[i]._1 = caras_revolucion[i]._1;
        caras[i]._2 = caras_revolucion[i]._2;
    }

}

void modelo_revolucion::draw_solido_prueba()
{
    int n=caras.size();

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    //glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);
    for(int i=0;i<n;i++)
    {
        /********************Color para cada cara *************************************************/
        glColor3f(color[i].r,color[i].g,color[i].b);

        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);   
    }
    glEnd();
}
