#include "mesa.h"

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
void Mesa::dibujaDI(){
	//========Dibuja lado derecho de la mesa==============// 
    glPushMatrix(); 
        glTranslatef ( 5.5, 0, 6.3075);//traslada la extremidad
        glScalef ( 9, 2.0, 2);//Escala la extremidad
        glutSolidCube (1.0);//Dibuja
    glPopMatrix();
	glPushMatrix(); 
        glTranslatef ( -5.5, 0, 6.3075);//traslada la extremidad
        glScalef ( 9, 2.0, 2);//Escala la extremidad
        glutSolidCube (1.0);//Dibuja
    glPopMatrix();
	glPushMatrix(); 
        glTranslatef ( 0, 0, 7);//traslada la extremidad
        glScalef ( 26, 2.0, 2);//Escala la extremidad
        glutSolidCube (1.0);//Dibuja
    glPopMatrix();
   	//========Dibuja lado izquierdo de la mesa==============// 
    glPushMatrix(); 
        glTranslatef ( 5.5, 0, -6.3075);//traslada la extremidad
        glScalef ( 9, 2.0, 2);//Escala la extremidad
        glutSolidCube (1.0);//Dibuja
    glPopMatrix();
	glPushMatrix(); 
    	glTranslatef ( -5.5, 0, -6.3075);//traslada la extremidad
        glScalef ( 9, 2.0, 2);//Escala la extremidad
        glutSolidCube (1.0);//Dibuja
        glPopMatrix();
	glPushMatrix(); 
        glTranslatef ( 0, 0, -7);//traslada la extremidad
        glScalef ( 26, 2.0, 2);//Escala la extremidad
        glutSolidCube (1.0);//Dibuja
    glPopMatrix();	
}
void Mesa::dibujaAB(){
	//========Dibuja lado de arriba de la mesa==============// 
    glPushMatrix(); 
        glTranslatef ( 11.8075, 0, 0);//traslada la extremidad
        glScalef ( 2, 2.0, 9);//Escala la extremidad
  	    glutSolidCube (1.0);//Dibuja
    glPopMatrix();
    glPushMatrix(); 
        glTranslatef ( 12.3, 0, 0);//traslada la extremidad
	    glScalef ( 1.5, 2.0, 16);//Escala la extremidad
        glutSolidCube (1.0);//Dibuja
    glPopMatrix();
	//========Dibuja lado de abajo de la mesa==============// 
    glPushMatrix(); 
        glTranslatef ( -11.8075, 0, 0);//traslada la extremidad
	    glScalef ( 2, 2.0, 9);//Escala la extremidad
        glutSolidCube (1.0);//Dibuja
    glPopMatrix();
    glPushMatrix(); 
        glTranslatef ( -12.3, 0, 0);//traslada la extremidad
	    glScalef ( 1.5, 2.0, 16);//Escala la extremidad
        glutSolidCube (1.0);//Dibuja
    glPopMatrix();
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
        glTranslatef ( 0, .2, 0);//traslada la extremidad
		dibujaDI();//dibuja lado izquierdo y derecho
		dibujaAB();//dibuja lado abajo y arriba
		setColor(0,0,0);
        glTranslatef ( 0, .5, 0);//traslada la extremidad
		glScalef(1,.5,1);
		glPushMatrix(); //mueve y dibuja los hoyos
            glTranslatef ( -11, 0, 5.5);
            glutSolidSphere (0.615,20,20);
			glTranslatef ( 11, 0, 0);
            glutSolidSphere (0.615,20,20);
			glTranslatef ( 11, 0, 0);
            glutSolidSphere (0.615,20,20);
			glTranslatef ( 0, 0, -11);
            glutSolidSphere (0.615,20,20);
			glTranslatef ( -11, 0, 0);
            glutSolidSphere (0.615,20,20);
			glTranslatef ( -11, 0, 0);
            glutSolidSphere (0.615,20,20);
        glPopMatrix();
		setColor(255,255,255);
    glPopMatrix();
}

