//**************************************************************************
// Práctica 4 
// Class which define multiple geometric figures with different types of drawn
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
    ambiente_difusa._0 = 0;
    ambiente_difusa._1 = 0;
    ambiente_difusa._2 = 1.0;
    ambiente_difusa._3 = 1;

    brillo = 12;

    especular._0 = 1.0;
    especular._1 = 0.5;
    especular._2 = 0.7;
    especular._3 = 1.0;

    mode_text = true;
    b_textura_coord = false;
    for(int i = 0; i< 4;i++)
    {
        coefs_s[i]=0.0;
        coefs_t[i]=0.0;
    }

    coefs_t[1] = 1.0;
    coefs_s[0] = 1.0;
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

void _triangulos3D::calcular_normales_caras()
{
    normales_caras.resize(caras.size());

    for(int i=0;i<caras.size();i++)
    {
        _vertex3f
            a1=vertices[caras[i]._1]-vertices[caras[i]._0],
            a2=vertices[caras[i]._2]-vertices[caras[i]._0],
            n=a1.cross_product(a2);

        //modulo
        float m=sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
        //normalización
        normales_caras[i]= _vertex3f(n.x/m,n.y/m,n.z/m);
    }

    b_normales_caras = true; //ponemos a true que hemos calculado las normales de las caras
    

}
void _triangulos3D::calcular_normales_vertices()
{
    int i,j;
    if(b_normales_vertices == false)
    {
        if(b_normales_caras==false) calcular_normales_caras(); //Si no hemos calculado las normales de las caras hay que hacerlo

        normales_vertices.resize(vertices.size());
        for(i=0;i<vertices.size();i++)
        {
            normales_vertices[i].x = 0.0;
            normales_vertices[i].y = 0.0;
            normales_vertices[i].z = 0.0;
        }
        for(i=0;i<caras.size();++i)
        {
        //se suma la normal de la cara a las normales de los tres vértices de la cara.
            normales_vertices[caras[i]._0]+=normales_caras[i];
            normales_vertices[caras[i]._1]+=normales_caras[i];
            normales_vertices[caras[i]._2]+=normales_caras[i];
        }
        //Normalización
        for(i=0;i<vertices.size();i++)
        {
            normales_vertices[i].normalize(); //normalizamos
        }
        b_normales_vertices=true; //ponemos a true que hemos calculado las normales de los vértices
    }
}


void _triangulos3D::iluminacion_plana()
{
    int i;
    GLfloat ambient_component[4]={1,1,1,1};

    GLfloat ambiental[4]={0.5,0.5,0.5,1};
    GLfloat difusa[4]={0.0,0.0,0.0,1};
    GLfloat especular[4]={0.2,0.2,0.2,1};
    int brillar=150;

    // La iluminacion plana utiliza la normal de los vertices
    if(b_normales_caras==false) calcular_normales_caras();

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);

    // Establecer el modo de sombras para iluminacion plana (GL_FLAT)
    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    //Hay que añadir más luces
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);

    //Atributos de la luz
    //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
    //glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
    //glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

    //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiental);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillar);


    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);

    //Vamos dibujando
    for(i=0;i<caras.size();++i)
    {
        // Se uso la 1 normal de una cara por cada 3 vertices (1 Normal_cara y 3 vertices)
        glNormal3fv((GLfloat *) &normales_caras[i]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
    glEnd();

    glDisable(GL_LIGHTING); //deshabilitamos las luces    

}


void _triangulos3D::iluminacion_suave()
{
    int i;
    GLfloat ambient_component[4]={1,1,1,1};

    GLfloat ambiental[4]={0.5,0.5,0.5,1};
    GLfloat difusa[4]={1.0,1.0,1.0,1};
    GLfloat especular[4]={0.2,0.2,0.2,1};
    int brillar=150;
    // La iluminacion suave utiliza la normal de los vertices
    if(b_normales_vertices==false) calcular_normales_vertices();

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
    // Establecer el modo de sombras para iluminacion suave (GL_SMOOTH)
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    //Hay que añadir más luces
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);

    //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
    //glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
    //glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);


    //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiental);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillar);


    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);

    //Vamos dibujando
    for(i=0;i<caras.size();++i)
    {
        // Se usan 1 normal de vértices para cada vértice (3 normales_vertices y 3 vertices)
        glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
    glEnd();

    glDisable(GL_LIGHTING); //deshabilitamos las luces
}


void _triangulos3D::draw_textura(GLuint ident_textura,jpg::Imagen*& imagen)
{
    //Carga la imagen
    glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());
    //activación de la textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ident_textura); //vínculo con la tectura
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);



    //vamos a realizar la generación automática de texturas
    if(mode_text)
    {
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
        glTexGenfv(GL_S,GL_EYE_PLANE,coefs_s);
        glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
        glTexGenfv(GL_T,GL_EYE_PLANE,coefs_t);
    }

    glColor3f(1.0,1.0,1.0); //máscara blanca
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);

    

    //Vamos dibujando
    for(int i =0; i<caras.size();++i)
    {
        if (b_textura_coord)
        {
            glTexCoord2f(textura_coord[caras[i]._0].s,textura_coord[caras[i]._0].t);
        }

        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    
        if (b_textura_coord)
        {
            glTexCoord2f(textura_coord[caras[i]._1].s,textura_coord[caras[i]._1].t);
        }

        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

        if (b_textura_coord)
        {
            glTexCoord2f(textura_coord[caras[i]._2].s,textura_coord[caras[i]._2].t);
        }

        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T); 
}


void _triangulos3D::draw_textura_iluminacion_plana(GLuint ident_textura,jpg::Imagen*& imagen)
{
    
    //Carga la imagen
    glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());
    GLfloat material_blanco[4]={1,1,1,1}; //Para que no se quede negra del todo

    if(b_normales_caras == false) calcular_normales_caras();


    GLfloat ambiental[4]={0.1,0.1,0.1,1};
    GLfloat difusa[4]={0.6,0.6,0.6,1};
    GLfloat especular[4]={0.2,0.2,0.2,1};
    int brillar=150;
    //activamos la iluminación
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);

    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);

    //Hay que añadir más luces
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiental);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&material_blanco);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillar);

    
    //activamos la textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ident_textura); //vínculo con la tectura
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);


    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);

    for(int i =0; i<caras.size();++i)
    {
        glNormal3fv((GLfloat *) &normales_caras[i]);
        if (b_textura_coord)
        {
            glTexCoord2f(textura_coord[caras[i]._0].s,textura_coord[caras[i]._0].t);
        }

        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        if (b_textura_coord)
        {
            glTexCoord2f(textura_coord[caras[i]._1].s,textura_coord[caras[i]._1].t);
        }

        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

        if (b_textura_coord)
        {
            glTexCoord2f(textura_coord[caras[i]._2].s,textura_coord[caras[i]._2].t);
        }

        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_LIGHTING);
}


void _triangulos3D::draw_textura_iluminacion_suave(GLuint ident_textura,jpg::Imagen*& imagen)
{
    //Carga la imagen
    glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());
    GLfloat material_blanco[4]={1,1,1,1}; //para que no se quede negra del todo

    if(b_normales_vertices==false) calcular_normales_vertices();

    // Luces
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material_blanco); //para que no quede del todo negra, si no que queda con sombra
    //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

    //activamos la textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ident_textura); //vínculo con la tectura
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    if(mode_text)
    {
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
        glTexGenfv(GL_S,GL_EYE_PLANE,coefs_s);
        glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
        glTexGenfv(GL_T,GL_EYE_PLANE,coefs_t);
    }

    glColor3f(1.0,1.0,1.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);

    for(int i =0; i<caras.size();++i)
    {
        if (b_textura_coord) //solo se utiliza para la revolución, que es cuando asignamos manualmente las coordenadas
        {
            glTexCoord2f(textura_coord[caras[i]._0].s,textura_coord[caras[i]._0].t);
        }

        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);

        if (b_textura_coord)
        {
            glTexCoord2f(textura_coord[caras[i]._1].s,textura_coord[caras[i]._1].t);
        }

        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

        if (b_textura_coord)
        {
            glTexCoord2f(textura_coord[caras[i]._2].s,textura_coord[caras[i]._2].t);
        }

        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_LIGHTING);
}




/**********************
FIN CLASE TRIANGULOS3D
***********************/




//*************************************************************************
// INICIO CLASE TEXTURA
//*************************************************************************
textura::textura(const char *archivoJPG)
{
    this->imagen = new jpg::Imagen(archivoJPG);

}

textura::textura()
{}


//*************************************************************************
// FIN CLASE TEXTURA
//*************************************************************************


//*************************************************************************
// INICIO CLASE REVOLUCION_TEXT
//*************************************************************************



revolucion_tex::revolucion_tex()
{

}

void revolucion_tex::hacer_revolucion_tex(vector<_vertex3f> ver, int num_caras)
{
    int i,j;
    _vertex3f vertices_aux;
    _vertex3i caras_aux;
    _vertex2f tex_aux;
    float alfa = 2*3.1416/num_caras;
    float alfa_aux = 2*3.1416/num_caras;
    vector <float> distancias;
    float distancia_total=0.0;
    b_textura_coord=true;
    int num_aux;

    //calculo las distancias para las coordenadas de la textura

    num_aux = ver.size();

    for(i=0; i<num_aux-1;++i)
    {
        distancias.push_back(distancia_total);
        distancia_total += sqrt((ver[i].x-ver[i+1].x)*(ver[i].x-ver[i+1].x)+
                            (ver[i].y-ver[i+1].y)*(ver[i].y-ver[i+1].y)+
                            (ver[i].z-ver[i+1].z)*(ver[i].z-ver[i+1].z));
    }

    //Normalizamos las distancias
    for(i=0;i<num_aux-1;++i)
    {
        distancias[i] = 1.0-distancias[i]/distancia_total;
    }

    distancias[0] = 1.0; //primera instancia
    distancias.push_back(0.0); //última instancia

    //tratamiento de los vértices

    for(j=0;j<num_caras+1;++j)
    {
        tex_aux.s=j/(1.0*num_caras);

        for(i=0;i<num_aux;i++)
        {
            vertices_aux.x =  ver[i].x * cos(alfa);
            vertices_aux.z =  -ver[i].x * sin(alfa);
            vertices_aux.y  = ver[i].y;
            vertices.push_back(vertices_aux);

            tex_aux.t=distancias[i];
            textura_coord.push_back(tex_aux);
        }

        alfa += alfa_aux;
    } 

    //asignación manual de coordenadas de textura

    mode_text = false;
    b_textura_coord=true;

    // tratamiento de las caras

    for(j=0;j<num_caras;j++)
    {
        for(i=0;i<num_aux-1;i++)
        {
            caras_aux._0=i+(j+1)*num_aux;
            caras_aux._1=i+1+(j+1)*num_aux;
            caras_aux._2=i+1+j*num_aux;

            caras.push_back(caras_aux);

            caras_aux._0=i+1+j*num_aux;
            caras_aux._1=i+j*num_aux;
            caras_aux._2=i+(j+1)*num_aux;

            caras.push_back(caras_aux);
        }
    }
}

//*************************************************************************
// FIN CLASE REVOLUCION_TEXT
//*************************************************************************




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

