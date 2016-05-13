/*
 *
 *Miguel Alberto Del Moral González
 *A01015019
 *Marcos López Mendoza
 *A01020023
 *
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "mesa.h"
#include "bola.h"
#include <string>
#include <time.h>
#include "text.h"

#define PI 3.14159265

Mesa mesa;
Bola bola[16];
Bola score[16];
Text t;
int lastx, lasty;
int down = 0;
int right = 0;

double rot = 0;

//inicializa la iluminacion
void init(void) 
{
	srand(time(NULL));
   //Luz ambiental
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
	
   t3dInit();
   //Carga las texturas a las 16 bolas
   for(int i = 1;i<=16;i++){
	   std::string nombre = "Texturas/Ball" + std::to_string(i) + ".tga";
	   char *cstr = new char[nombre.length() + 1];
	   strcpy(cstr, nombre.c_str());
	   bola[i-1].loadTextures(cstr);
	   score[i-1].loadTextures(cstr);
	   delete [] cstr;
   }
   double x = -4;
   double z = 0;
   int num = 0;
   //inicializa las bolas en su posicion correspondiente
   for(int i = 0;i<15;i++){
		score[i].setX(0);
		score[i].setZ(0);
   }
   for(int i = 0;i<5;i++){
        z = (1*i)*.3075;
        for(int j = 0;j<=i;j++){
            bola[num].setX(x);
            bola[num++].setZ(z);
            z-=.615;
        }
        x-=.615;
   }
   //pone la bola blanca en su lugar
   bola[15].setX(5);
   bola[15].setZ(0);


   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

}

double distancia(Bola bola1,Bola bola2){
	double disX = fabs(bola1.getX() - bola2.getX());
	double disZ = fabs(bola1.getZ() - bola2.getZ());
	return sqrt(pow(disX,2)+pow(disZ,2));
}

void checaColision(){
	for(int i = 0;i<15;i++){
		for(int j = i+1;j<16;j++){
			if(distancia(bola[i],bola[j]) <= .615){
				if(!bola[i].colision[j]){
					bola[i].setVelX(bola[i].getVelX()*-1);
					bola[i].setVelZ(bola[i].getVelZ()*-1);
					bola[j].setVelX(bola[j].getVelX()*-1);
					bola[j].setVelZ(bola[j].getVelZ()*-1);
					bola[i].colision[j]=true;
					bola[j].colision[i]=true;
				}
			}else{
				bola[i].colision[j]=false;
				bola[j].colision[i]=false;
			}
		}
	}
}

void colisionPared(int x){
	double d = .615;
	double r = .7075;
	if(bola[x].getX()>11-d && (bola[x].getZ()<4.5 && bola[x].getZ() > -4.5))
		bola[x].setVelX(-fabs(bola[x].getVelX()));
	if(bola[x].getX()<-11+d && (bola[x].getZ()<4.5 && bola[x].getZ() > -4.5))
		bola[x].setVelX(fabs(bola[x].getVelX()));
	if(bola[x].getZ()>5.5-d && ((bola[x].getX() < 11-r && bola[x].getX() > 1+r) || (bola[x].getX() > -11+r && bola[x].getX() < -1-r)))
		bola[x].setVelZ(-fabs(bola[x].getVelZ()));
	if(bola[x].getZ()<-5.5+d && ((bola[x].getX() < 11-r && bola[x].getX() > 1+r) || (bola[x].getX() > -11+r && bola[x].getX() < -1-r)))
		bola[x].setVelZ(fabs(bola[x].getVelZ()));

}
void dibujaBolas(){
	//Dibuja las bolas
    double x = -4;
    double z = 0;
    int num = 0;
    for(int i = 0;i<16;i++){
    	bola[i].dibujar();
		colisionPared(i);
    }
}

void dibujaBolaScore(int x,int y,int z,int i){
	glPushMatrix();
		glRotatef(-90,0,1,0);
		glTranslatef(x,y,z);
		score[i].dibujar();
	glPopMatrix();

}

void dibujaScore(){
	//Dibuja las bolas lisas que faltan por meter 
	dibujaBolaScore(-5,18,5,0);
	dibujaBolaScore(-5,17,5,1);
	dibujaBolaScore(-5,16,5,5);
	dibujaBolaScore(-5,15,5,6);
	dibujaBolaScore(-5,14,5,8);
	dibujaBolaScore(-5,13,5,12);
	dibujaBolaScore(-5,12,5,14);

	//Dibuja las bolas rayadas que faltan por meter 
	dibujaBolaScore(-5,18,-5,2);
	dibujaBolaScore(-5,17,-5,3);
	dibujaBolaScore(-5,16,-5,7);
	dibujaBolaScore(-5,15,-5,9);
	dibujaBolaScore(-5,14,-5,10);
	dibujaBolaScore(-5,13,-5,11);
	dibujaBolaScore(-5,12,-5,13);

}	

void dibujaTaco(){
	glPushMatrix();
		glTranslatef (bola[15].getX(), 0,bola[15].getZ()-15);
		glScalef (.2,.2,4);
		glRotatef(rot,0,0,1);
		glutSolidSphere(1,20,20);
	glPopMatrix();
	glutPostRedisplay();
}

//Se dibuja todo aqui
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

		gluLookAt(0.0, 0.0, 25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	    glRotated(rot, 0.0, 1.0, 0.0);

		//Checa si bolas colisionan
		checaColision();
		//Dibuja mesa
        mesa.dibujar(0,-7,0);
		//dibuja bola blanca
        bola[15].dibujar();
        //dibuja bolas
        dibujaBolas();
		//printf("%f\n",rot);
		//////////////7printf("%f\t%f\n",bola[15].getVelX(),bola[15].getVelZ());
 
	glPopMatrix();
	
	dibujaScore();
	//dibujaTaco();
	


	t.drawText();
 	
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
   glTranslatef (0.0, -10.0, -10.0);
   glRotatef (-25.0, -1.0, 0.0, 0.0);
   //glRotatef (90.0, 1.0, 0.0, 0.0);
}

void simulacion()
{
    glutPostRedisplay();
}



//Iteracción con el mouse
void mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			lastx = x;
			down = 1;
		}
		else {
			down = 0;
		}
	}
	if (button == GLUT_RIGHT_BUTTON) {
		//bola[15].setVelX(.01);
		//bola[15].setVelZ(.01);
		for(int i = 0;i<16;i++){
			bola[i].setVelX(-1*(double)rand()/(double)(RAND_MAX)*.2);
			bola[i].setVelZ((double)rand()/(double)(RAND_MAX)*.2);
		}
		if(t.getTurn()==1)
			t.setTurn(2);	
		else
			t.setTurn(1);	
			bola[15].setVelX(sin(rot*PI/180)*.21);
			bola[15].setVelZ(-cos(rot*PI/180)*.21);
			//bola[15].setVelZ(-sin(rot)*.1);
	}
}
void mouse_move(int x, int y) {
    if(down) {
		rot += (x - lastx)*0.3;
		lastx = x;
	}
}
void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 'a':
		case 'A':
			score[15].setX(score[15].getX()-.1);
			printf("%f\t%f\n",bola[15].getX(),bola[15].getZ());
			printf("\t%f\t%f\n",bola[15].getVelX(),bola[15].getVelZ());
			break;
		case 'd':
		case 'D':
			score[15].setX(score[15].getX()+.1);
			printf("%f\t%f\n",bola[15].getX(),bola[15].getZ());
			printf("\t%f\t%f\n",bola[15].getVelX(),bola[15].getVelZ());
			break;
		case 'w':
		case 'W':
			score[15].setZ(score[15].getZ()-.1);
			printf("%f\t%f\n",bola[15].getX(),bola[15].getZ());
			printf("\t%f\t%f\n",bola[15].getVelX(),bola[15].getVelZ());
			break;
		case 's':
		case 'S':
			score[15].setZ(score[15].getZ()+.1);
			printf("%f\t%f\n",bola[15].getX(),bola[15].getZ());
			printf("\t%f\t%f\n",bola[15].getVelX(),bola[15].getVelZ());
			break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
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
   glutMouseFunc(mouse);
   glutMotionFunc(mouse_move);
   glutIdleFunc(simulacion);
   glutMainLoop();
   return 0;
}
