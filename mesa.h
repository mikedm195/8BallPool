/*
 *  
 * Miguel Alberto Del Moral González
 * A01015019
 *     
 */
#pragma once 

#include <GL/glut.h>
#include <stdlib.h>

class Mesa{
    public:
        Mesa();
        void dibujar(double x,double y, double z);//Dibuja la mesa
};
Mesa::Mesa(){
    
}

void setColor(double R, double G, double B){
	GLfloat mat[] = { R/255.0, G/255.0, B/255.0, 1.0f };
	GLfloat mat_shininess[] = { 0.0f };
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//color

}
void Mesa::dibujar(double x,double y, double z){

    glPushMatrix();
		
		setColor(41.0, 121.0, 52.0);//Colorea la base de la mesa (verde)
          
        glTranslatef ( x, y, z);//traslada la extremidad
        
        glPushMatrix(); 
            glScalef ( 22, 1, 11);//Escala la extremidad
            glutSolidCube (1.0);//Dibuja
        glPopMatrix();

        setColor(100.0, 54.0, 2.0);//Colorea las paredes de la mesa (cafe)
        
        glTranslatef ( 0, .7, 0);//traslada la extremidad
    
        glPushMatrix(); 
            glTranslatef ( 0, 0, 5.5);//traslada la extremidad
            glScalef ( 22, 2.0, .5);//Escala la extremidad
            glutSolidCube (1.0);//Dibuja
        glPopMatrix();
        glPushMatrix(); 
            glTranslatef ( 0, 0, -5.5);//traslada la extremidad
            glScalef ( 22, 2.0, .5);//Escala la extremidad
            glutSolidCube (1.0);//Dibuja
        glPopMatrix();
        glPushMatrix(); 
            glTranslatef ( 11, 0, 0);//traslada la extremidad
        glScalef ( .5, 2.0, 11);//Escala la extremidad
        glutSolidCube (1.0);//Dibuja
        glPopMatrix();
        glPushMatrix(); 
            glTranslatef ( -11, 0, 0);//traslada la extremidad
            glScalef ( .5, 2.0, 11);//Escala la extremidad
            glutSolidCube (1.0);//Dibuja
        glPopMatrix();
		
		setColor(255,255,255);
    glPopMatrix();
}


