/*
 *
 *Miguel Alberto Del Moral González
 *A01015019
 *
 */
#include <GL/glut.h>
#include <stdlib.h>
#include "mesa.h"
#include "bola.h"

Mesa mesa;
Bola bola[16];
//inicializa la iluminacion
void init(void) 
{
   GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
   GLfloat mat_ambient[] = {1.0,1.0,1.0,1.0};
   GLfloat mat_shininess[] = { 0.0 };
   GLfloat light_position[] = { 0.0, 5.0, 5.0, 1.0 };

   glClearColor (0.0, 0.0, 0.0, 1.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

}

void dibujaBolas(){
    double x = -4;
    double y = -6;
    double z = 0;
    int num = 0;
    for(int i = 0;i<5;i++){
        z = (1*i)*.3075;
        for(int j = 0;j<=i;j++){
            bola[num++].dibujar(x,y,z);
            z-=.615;
        }
        x-=.615;
    }
}

//Se dibuja todo aqui
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        
        mesa.dibujar(0,-7,0);
        dibujaBolas();
        bola[15].dibujar(5,-6,0);

    glPopMatrix();
    glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
   
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -25.0);
   //glRotatef (-35.0, 0.0, 1.0, 0.0);
   glRotatef (90.0, 1.0, 0.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
        break;
        default:
        break;
   }
}

void simulacion()
{
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutIdleFunc(simulacion);
   glutMainLoop();
   return 0;
}
