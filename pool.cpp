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
#include "mesa.h"
#include "bola.h"

Mesa mesa;
Bola bola[16];

#define	stripeImageWidth 32
GLubyte stripeImage[4*stripeImageWidth];

#ifdef GL_VERSION_1_1
static GLuint texName;
#endif

void makeStripeImage(void)
{
   int j;

   for (j = 0; j < stripeImageWidth; j++) {
      stripeImage[4*j] = (GLubyte) ((j<=4) ? 255 : 0);
      stripeImage[4*j+1] = (GLubyte) ((j>4) ? 255 : 0);
      stripeImage[4*j+2] = (GLubyte) 0;
      stripeImage[4*j+3] = (GLubyte) 255;
   }
}

/*  planes for texture coordinate generation  */
static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};
static GLfloat slanted[] = {1.0, 1.0, 1.0, 0.0};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;

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



   /* #ifdef GL_VERSION_1_1
       glGenTextures(1, &texName);
       glBindTexture(GL_TEXTURE_1D, texName);
    #endif*/




       glEnable(GL_TEXTURE_GEN_S);
          glEnable(GL_TEXTURE_1D);
          glEnable(GL_CULL_FACE);
             glEnable(GL_AUTO_NORMAL);
             glEnable(GL_NORMALIZE);
             //glFrontFace(GL_CW);
             //glCullFace(GL_BACK);
             //glMaterialf (GL_FRONT, GL_SHININESS, 64.0);
}

void dibujaBolas(){
    double x = -4;
    double y = -6;
    double z = 0;
    int num = 0;
    for(int i = 0;i<5;i++){
        z = (1*i)*.3075;
        for(int j = 0;j<=i;j++){
        makeStripeImage();
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
               glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
               glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            #ifdef GL_VERSION_1_1
               glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, stripeImageWidth, 0,
                            GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
            #else
               glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0,
                            GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
            #endif

            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                   currentCoeff = xequalzero;
                   currentGenMode = GL_OBJECT_LINEAR;
                   currentPlane = GL_OBJECT_PLANE;
                   glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
                   glTexGenfv(GL_S, currentPlane, currentCoeff);
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
        bola[15].dibujar(5,-6,0);
        dibujaBolas();


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
   glRotatef (-35.0, 0.0, 1.0, 0.0);
   //glRotatef (90.0, 1.0, 0.0, 0.0);
}

void simulacion()
{
    glutPostRedisplay();
}

int lastx, lasty;
int down = 0;
int right = 0;

void motion(int x, int y)
{
	if (down) {
		glRotatef(lastx - x, 0, 1, 0);
		lastx = x;
		glutPostRedisplay();
	}
/*
	if ( right)
        {
          _angulo += ( x - _startx ) / 2.0f;

          if ( _fz > 1.0 && _fz < 54.0  )
            _fz += ( (y - _starty) * 0.1 );
          else if ( _fz <= 1.0  )
            _fz = 1.1f;
          else if ( _fz >= 54.0  )
            _fz = 53.9f;

          if ( _fx > 7.0 && _fx < 60.0  )
            _fx += ( (y - _starty) * 0.1 );
          else if ( _fx <= 7.0  )
            _fx = 7.1f;
          else if ( _fx >= 60.0  )
            _fx = 59.9f;

          _startx = x;
          _starty = y;
          glutPostRedisplay();
        }

        if ( _mover )
        {
          _moverX -= ( (x - _startx) * 0.05 );

          _startx = x;
          _starty = y;
          glutPostRedisplay();
        }*/
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
	/*
	if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
        {
          right = 1;
          lastx = x;
          lasty = y;
        }
        if ( button == GLUT_RIGHT_BUTTON && state == GLUT_UP )
        {
          right = 0;
        }

        if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN )
        {
          down = 1;
          lastx = x;
          lasty = y;

        }
        if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_UP )
        {
          down = 0;
        }*/
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      /*case 'e':
      case 'E':
         currentGenMode = GL_EYE_LINEAR;
         currentPlane = GL_EYE_PLANE;
         glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
         glTexGenfv(GL_S, currentPlane, currentCoeff);
         glutPostRedisplay();
         break;
      case 'o':
      case 'O':
         currentGenMode = GL_OBJECT_LINEAR;
         currentPlane = GL_OBJECT_PLANE;
         glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
         glTexGenfv(GL_S, currentPlane, currentCoeff);
         glutPostRedisplay();
         break;
      case 's':
      case 'S':
         currentCoeff = slanted;
         glTexGenfv(GL_S, currentPlane, currentCoeff);
         glutPostRedisplay();
         break;
      case 'x':
      case 'X':
         currentCoeff = xequalzero;
         glTexGenfv(GL_S, currentPlane, currentCoeff);
         glutPostRedisplay();
         break;
      case 27:
         exit(0);
         break;*/
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
   glutMotionFunc(motion);
   glutIdleFunc(simulacion);
   glutMainLoop();
   return 0;
}
