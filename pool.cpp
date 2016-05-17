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
#define Max_Fuerza .21
Mesa mesa;
Bola bola[16];//Bolas que estan sobre la mesa
Bola score[16];//Bolas que indican cuantas faltan por meter
Text t;//Texto

int lastx, lasty;
int down = 0;
int right = 0;
int turno = 1;//turno de jugador 1 o 2
int lisas = 10;//si es 1, jugador 1 es liso, si es -1 jugador 2 es liso si es 10 aun no se sabe
bool lisaIn = false;//Saber si una lisa entro durante la jugada
bool rayadaIn = false;//Saber si una rayada entro durante la jugada
bool quietas = true;//Dice si las bolas estan quietas para cambiar de turno
int status = 0;//Para saber cuando le esta pegando le pego
double fuerza = 0;//La fuerza con la que le pega
double tempFuerza = 0;//Aumentar/decrementar la fuerza

bool colisiones[16][16];//Saber si una bola esta colisionando con otra
bool ballIn[16];//Indica cuando la bola ya entro en un hoyo
double rot = 0;//Rotacion de la camara

typedef struct velocidadesBolas{
	double velXbol1;
	double velZbol1;
	double velXbol2;
	double velZbol2;
};

void cargarBolas(){
   for(int i = 1;i<=16;i++){//Carga las texturas a las 16 bolas
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
            z-=.616;
        }
        x-=.615;
   }
   //pone la bola blanca en su lugar
   bola[15].setX(5);
   bola[15].setZ(0);
}

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
	
   t3dInit();//carga texto 3d
	
   cargarBolas();//carga las bolas

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

}

//calcula la distancia entre dos bolas
double distancia(Bola bola1,Bola bola2){
	double disX = fabs(bola1.getX() - bola2.getX());
	double disZ = fabs(bola1.getZ() - bola2.getZ());
	return sqrt(pow(disX,2)+pow(disZ,2));
}

velocidadesBolas velocidadColision(Bola bola1, Bola bola2){
	//printf("x1ini->%f\ty1ini->%f\nx2ini->%f\ty2ini->%f\n",bola1.getVelX(),bola1.getVelZ(),bola2.getVelX(),bola2.getVelZ());
	double anguloTheta, anguloPhi;
	velocidadesBolas resultado;

	anguloTheta = atan((bola1.getX() - bola2.getX()) / (bola1.getZ() - bola2.getZ()));
	anguloPhi = atan((bola1.getZ() - bola2.getZ()) / (bola1.getX() - bola2.getX()));
	//printf("T->%f\tP->%f\n",anguloTheta*180/PI,anguloPhi*180/PI);
	double matriz[2][3] = {
			{cos(anguloTheta), cos(anguloPhi), bola1.getVelX() + bola2.getVelX()},
			{sin(anguloTheta), sin(anguloPhi), bola1.getVelZ() + bola2.getVelX()}
	};

	double determinanteS = (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]); 
	double determinanteX = (matriz[0][2] * matriz[1][1]) - (matriz[1][2] * matriz[0][1]);
	double determinanteY = (matriz[0][0] * matriz[1][2]) - (matriz[1][0] * matriz[0][2]);
	
	//printf("S->%f\ŧX->%f\tY->%f\n",determinanteS,determinanteX,determinanteY);

	double x = determinanteX / determinanteS;
	double y = determinanteY / determinanteS;
	//printf("x->%f\ty->%f\n",x,y);
	resultado.velXbol1 = x * matriz[0][0];
	resultado.velZbol1 = y * matriz[1][0];
	resultado.velXbol2 = x * matriz[0][1];
	resultado.velZbol2 = y * matriz[1][1];
	if(resultado.velXbol1>.21)
		resultado.velXbol1 = .17;
	if(resultado.velZbol1>.21)
		resultado.velZbol1 = .17;
	if(resultado.velXbol2>.21)
		resultado.velXbol2 = .17;
	if(resultado.velZbol2>.21)
		resultado.velZbol2 = .17;

	//printf("x1fin->%f\ty1fin->%f\nx2fin->%f\ty2fin->%f\n\n\n",resultado.velXbol1,resultado.velZbol1,resultado.velXbol2,resultado.velZbol2);
	return resultado;
}

void velFin(Bola bola1,Bola bola2){
	double ang = asin(fabs(bola1.getZ()-bola2.getZ())/distancia(bola1,bola2));
	printf("%f\t%f\t%f\n",fabs(bola1.getZ()-bola2.getZ()),distancia(bola1,bola2),ang*(180/PI));
}

void checaColision(){
	for(int i = 0;i<15;i++){
		for(int j = i+1;j<16;j++){
			if(distancia(bola[i],bola[j]) <= .615){//si la distancia de las bolas es menor a su diametro es que esta chocando
				if(!colisiones[i][j]){
					velocidadesBolas velocidades = velocidadColision(bola[i], bola[j]);
					//printf("%d %d\n",i,j);
					//velFin(bola[i],bola[j]);
					bola[i].setVelX(velocidades.velXbol1);
					bola[i].setVelZ(velocidades.velZbol1);
					bola[j].setVelX(velocidades.velXbol2);
					bola[j].setVelZ(velocidades.velZbol2);
					//evita que se detecte una colision dos veces
					colisiones[i][j]=true;
					colisiones[j][i]=true;
				}
			}else{
				colisiones[i][j]=false;
				colisiones[j][i]=false;
			}
		}
	}
}

void colisionPared(int x){
	double d = .615;//diametro de la bola
	double r = .7075;
	//checa colisiones con las 4 paredes
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
    for(int i = 0;i<16;i++){
		if(!ballIn[i]){
			glEnable(GL_TEXTURE_2D);
			//checa si la bola entro en algun lado
			if(fabs(bola[i].getZ())>5.4||fabs(bola[i].getX())>11.4){
				ballIn[i]=true;
				if(i == 0 || i == 1 || i == 5 || i == 6 || i == 8 || i == 12 || i == 14)
					lisaIn = true;
				if(i == 2 || i == 3 || i == 7 || i == 9 || i == 10 || i == 11 || i == 13)
					rayadaIn == true;
				//le quita la velocidad a las bolas
				bola[i].setVelX(0);
				bola[i].setVelZ(0);
			}
			//checa si la bola que metieron era lisa o rayada
			if(!ballIn[i]){
		    	bola[i].dibujar();//dibuja la bola
				colisionPared(i);//checa colisiones
			}
			glDisable(GL_TEXTURE_2D);
		}
    }
}

//dibuja las bolsa para ver cuales faltan
void dibujaBolaScore(double x,double y,double z,int i){
	if(ballIn[i]==false){//si todavia no la meten
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
				glRotatef(-90,0,1,0);
				glRotatef(25,0,0,1);
				glTranslatef(x,y,z);
				score[i].dibujar();		
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

}

void dibujaScore(){
	//Dibuja las bolas lisas que faltan por meter 
	dibujaBolaScore( 4,17.5,3*lisas,0);
	dibujaBolaScore( 4,16.8,3*lisas,1);
	dibujaBolaScore( 4,16.1,3*lisas,5);
	dibujaBolaScore( 4,15.4,3*lisas,6);
	dibujaBolaScore( 4,14.7,3*lisas,8);
	dibujaBolaScore( 4,14  ,3*lisas,12);
	dibujaBolaScore( 4,13.3,3*lisas,14);
							
	//Dibuja las bolas rayadas que faltan por meter 
	dibujaBolaScore( 4,17.5,-3*lisas,2);
	dibujaBolaScore( 4,16.8,-3*lisas,3);
	dibujaBolaScore( 4,16.1,-3*lisas,7);
	dibujaBolaScore( 4,15.4,-3*lisas,9);
	dibujaBolaScore( 4,14.7,-3*lisas,10);
	dibujaBolaScore( 4,14  ,-3*lisas,11);
	dibujaBolaScore( 4,13.3,-3*lisas,13);

}	

//dibuja el taco
void dibujaTaco(){
	GLfloat mat[] = {201/255.0, 100/255.0,  50/255.0, 1.0f };
	GLfloat no[] = {255/255.0, 255/255.0, 255/255.0, 1.0f };
	//dibuja el taco cafe
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);

	glPushMatrix();
		glTranslatef (bola[15].getX(), -6,bola[15].getZ());//traslada el taco hacia la bola blanca
		glRotatef(rot,0,-1,0);//rota el taco al mismo angulo de la camara
		glTranslatef (0, 0, 3.5+fuerza*15);//mueve el taco atras de la bola blanca
		glScalef (.2,.2,4);
		glutSolidSphere(1,20,20);
	glPopMatrix();
					
	//cambia color a blanco para que no pinte toda la escena de cafe
	glMaterialfv(GL_FRONT, GL_AMBIENT, no);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, no);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no);

	glutPostRedisplay();
}

//calcula la fuerza de la bola
void calculaFuerza(){
	if(right == 1 && status == 1){
		dibujaTaco();
		if(fuerza > Max_Fuerza)
			tempFuerza = -.002;
		else if(fuerza < .01)
			tempFuerza = .002;

		fuerza += tempFuerza;
		t.setStrength(fuerza * (100/Max_Fuerza));//Se multiplica para que el valor que imprima sea de 0-100
	}
}

//Resetea las colisiones 
void resetCollisions(){
	for(int i = 0;i<16;i++)
		for(int j = 0;j<16;j++)
			colisiones[i][j]=false;
}
//cambia de turno
void cambiaTurno(){
	if(t.getTurn()==1)
		t.setTurn(2);
	else
		t.setTurn(1);
	status = 0;
	t.setStrength(0);
	resetCollisions();
}

bool continuar(){
	bool c = false;
	if(lisas == 10){//si aun no se ha metido ninguna bola
		if(lisaIn && !rayadaIn){//si se mete bola blanca
			if(t.getTurn()==1)
				lisas = 1;
			else
				lisas = -1;
		}else{
			if (!lisaIn && rayadaIn){//si se mete bola rayada
				if(t.getTurn()==1)
					lisas = -1;
				else
					lisas = 1;
			}
		}
	}else{
		if(lisas == 1){//checa si un jugador no metio alguna de las bolas que le tocaba
			if((!lisaIn && t.getTurn()==1)||(!rayadaIn && t.getTurn()==2))
				c = true;
		}else{
			if(lisas == -1)
				if((!rayadaIn && t.getTurn() == 1)||(!lisaIn && t.getTurn()==2))
					c = true;
		}
	}
	if(!lisaIn && !rayadaIn)
		c = true;
	return c;
}

//checa si metieron la bola blanca
bool checaBlanca(){
	if(ballIn[15]){
		bola[15].setX(0);	
		bola[15].setZ(0);
		ballIn[15]=false;	
		return true;
	}
	return false;
}

bool acabo(){
	bool a = false;
	int temp = t.getTurn();//checa si ya se metieron las bolas que le tocan al jugador
	if((temp == 1 && lisas == 1)||(temp=2 && lisas == -1)){
		if(ballIn[0] && ballIn[1] &&ballIn[5] &&ballIn[6] &&ballIn[8] &&ballIn[12] &&ballIn[14]){
			a = true;
		}
	}else{
		if(ballIn[2] && ballIn[3] &&ballIn[7] &&ballIn[9] &&ballIn[10] &&ballIn[11] &&ballIn[13]){
			a = true;	
		}
	}
	return a;
}

bool checaNegra(){
	if(ballIn[4]){
		if(acabo()){
			t.setWinner(t.getTurn());//si el jugador ya metio todas las bolas que le tocaban gana
		}else{
			int temp = t.getTurn();//si todavia no acababa gana el contrario
			if(temp==1)
				t.setWinner(2);
			else
				t.setWinner(1);
		}
		return false;
	}
	return true;
}

void checaTurno(){
	calculaFuerza();
	bool cambiar;
	if(right == 0 && status == 1){//asigna la fuerza a la bola blanca cuando ya le pegaron
		bola[15].setVelX(sin(rot*PI/180)*fuerza);
		bola[15].setVelZ(-cos(rot*PI/180)*fuerza);
		fuerza = 0;
		status = 2;
	}
	if(status == 2){
		quietas = true;
		for(int i = 0;i<16;i++){
			if(bola[i].getVelX() != 0 || bola[i].getVelZ() !=0){
				if(!ballIn[i])
					quietas = false;//checa si las bolas siguen en movimiento
			}
		}

		if(quietas){
			cambiar = checaNegra();//Ve si metieron la bola negra
			if(cambiar){
				cambiar = checaBlanca();//Ve si metieron la bola blanca
				if(!cambiar)
					cambiar = continuar();//checa si mete alguna de las bolas que le toca al jugador en turno
			}
			lisaIn=false;
			rayadaIn=false;
			status = 0;
			if(cambiar)
				cambiaTurno();//Cambia de turno
		}
	}
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
		//checa de quien es el turno
		checaTurno();
	glPopMatrix();
	//dibuja el score
	dibujaScore();
	//dibuja el texto 3d
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
	//gira la camara
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			lastx = x;
			down = 1;
		}
		else {
			down = 0;
		}
	}
	//para tirar
	if (button == GLUT_RIGHT_BUTTON) {
		if(status==0)
			status = 1;
		if(state == GLUT_DOWN)
			right = 1;
		else
			right = 0;
		for(int i = 0;i<16;i++){
			//bola[i].setVelX(-1*(double)rand()/(double)(RAND_MAX)*.2);
			//bola[i].setVelZ((double)rand()/(double)(RAND_MAX)*.2);
		}
	}else{
		right = 0;
	}

}
//mueve la camara
void mouse_move(int x, int y) {
    if(down) {
		rot += ((x - lastx)*0.3);
		lastx = x;
	}
}
void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 'a':
		case 'A':
			bola[15].setX(bola[15].getX()-.1);
			printf("%f\t%f\n",bola[15].getX(),bola[15].getZ());
			printf("\t%f\t%f\n",bola[15].getVelX(),bola[15].getVelZ());
			break;
		case 'd':
		case 'D':
			bola[15].setX(bola[15].getX()+.1);
			printf("%f\t%f\n",bola[15].getX(),bola[15].getZ());
			printf("\t%f\t%f\n",bola[15].getVelX(),bola[15].getVelZ());
			break;
		case 'w':
		case 'W':
			bola[15].setZ(bola[15].getZ()-.1);
			printf("%f\t%f\n",bola[15].getX(),bola[15].getZ());
			printf("\t%f\t%f\n",bola[15].getVelX(),bola[15].getVelZ());
			break;
		case 's':
		case 'S':
			bola[15].setZ(bola[15].getZ()+.1);
			printf("%f\t%f\n",bola[15].getX(),bola[15].getZ());
			printf("\t%f\t%f\n",bola[15].getVelX(),bola[15].getVelZ());
			break;
		case 'z':
			lisaIn=true;
			break;
		case 'x':
			rayadaIn=true;
			break;
		case 'c':
			ballIn[4]=true;
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
