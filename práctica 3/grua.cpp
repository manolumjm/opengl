//******************************************************************************
// Práctica 3
// class to build crane as hierarchical model
//
//******************************************************************************

#include "grua.h"


grua::grua(float cuadradoPluma, float giroBrazo,float alargaPluma)
{
    cuboBase = _cubo(1);
    base = modelo_revolucion();
    
    pluma = modelo_revolucion();
    //brazo = _cubo(1);

    MovYCuboPluma=cuadradoPluma;
    //MaxMovCuadradoPluma=0.3;
    //MinMovCuadradoPluma=-1.5;

    MovGiroBrazo = giroBrazo;

    MovPluma = alargaPluma;

    betoven.leer_ply((char*)"beethoven.ply");
    
}

void grua::crearBase()
{
    glPushMatrix();

        glScalef(1.5,0.1,1);
        glTranslatef(0,0.5,0);
        cuboBase.draw_solido(1, 0, 0);

    glPopMatrix();
}

void grua::crearCilindroBase()
{
    glPushMatrix();

        glScalef(0.4,1.5,0.4);
        glTranslatef(0,1.05,0);
        base.puntos_figura4();
        base.hacer_revolucion(base.vertices,20,0,360);
        base.draw_solido(1, 1, 0);
    glPopMatrix();
}

void grua::crearBrazo()
{
    glPushMatrix();

        glScalef(4,0.5,1);
        glTranslatef(0.3,6.2,0);
        cuboBase.draw_solido(1, 0, 0);
       
    glPopMatrix();
}


void grua::crearCuadradoPluma()
{
    //MovYCuboPluma = MovYCuboPluma+MovCuadradoPluma;

    glPushMatrix();

        glScalef(0.5,0.5,0.5);
        glTranslatef(5,6,0);
        cuboBase.draw_solido(0,1,1);

    glPopMatrix();
}

void grua::crearPluma()
{
    glPushMatrix();

        glScalef(0.1,0.25,0.1);
        glTranslatef(25,10.5,0);
        pluma.puntos_figura4();
        pluma.hacer_revolucion(pluma.vertices,20,0,360);
        pluma.draw_solido(1, 0, 1);

    glPopMatrix();
}

void grua::crearPluma2()
{
    glPushMatrix();

        glScalef(0.1,0.25,0.1);
        glTranslatef(25,8,0);
        pluma.puntos_figura4();
        pluma.hacer_revolucion(pluma.vertices,20,0,360);
        pluma.draw_solido(1, 0, 1);

    glPopMatrix();
}

void grua:: crearPly()
{
    glScalef(0.05,0.05,0.05);
    glTranslatef(50,50.5,0);
    betoven.draw_solido(0, 1, 0.5);
}


void grua::dibujar()
{
    glPushMatrix();
        
            glPushMatrix();

                // Giro en Z del brazo
                glRotatef(MovGiroBrazo,0,1,0);
                crearBrazo();

                glPushMatrix();

                    // Translacion (Y) de Cuadradopluma
                    glTranslatef(MovYCuboPluma,0,0);
                    crearCuadradoPluma();

                    glPushMatrix();

                        // escalado y translacion 
                        glTranslatef(0,0-MovPluma*2.8,0); 
                        glScalef(1,1+MovPluma,1);
                        crearPluma();
                    
                    glPopMatrix();

                glPopMatrix();

            glPopMatrix();

        crearCilindroBase();
        crearBase();
        
    glPopMatrix();  
}


void grua::dibujar2()
{
    glPushMatrix();
        
            glPushMatrix();

                // Giro en Z del brazo
                glRotatef(MovGiroBrazo,0,1,0);
                crearBrazo();

                glPushMatrix();

                    //if(MovYCuboPluma>MinMovCuadradoPluma && MovYCuboPluma<MaxMovCuadradoPluma)
                    glTranslatef(MovYCuboPluma,0,0);

                    crearCuadradoPluma();

                    glPushMatrix();

                        // escalado y translacion
                        //MovPluma 
                        
                        glTranslatef(0,0-MovPluma*2.8,0); 

                        glPushMatrix();

                            glScalef(1,1+MovPluma,1);
                            crearPly();

                        glPopMatrix();

                        glTranslatef(0,0+MovPluma*2.22,0);
                        crearPluma2();

                    glPopMatrix();

                    

                glPopMatrix();

            glPopMatrix();


        crearCilindroBase();
        crearBase();
        

    glPopMatrix();  
}




