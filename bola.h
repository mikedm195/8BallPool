/*
 *  
 * Miguel Alberto Del Moral González
 * A01015019
 *     
 */
#pragma once 

#include <GL/glut.h>
#include <stdlib.h>

class Bola{
    public:
        Bola();
        void dibujar(double x,double y, double z);//Dibuja la mesa
};
Bola::Bola(){
    
}


void Bola::dibujar(double x,double y, double z){

    glPushMatrix(); 
        GLfloat matB[] = { 255.0/255.0, 255.0/255.0, 255.0/255.0, 1.0f };
        GLfloat matC[] = { 100.0/255.0, 54.0/255.0, 2.0/255.0, 1.0f };
        GLfloat mat_shininess[] = { 0.0f };

        glMaterialfv(GL_FRONT, GL_AMBIENT, matB);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, matB);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matB);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//color

        glTranslatef ( x, y, z);//traslada la extremidad
        
        glPushMatrix(); 
            glScalef ( .3075, .3075, .3075);//Escala la extremidad
            glutSolidSphere (1.0,20,20);//Dibuja
        glPopMatrix();

    glPopMatrix();
}


