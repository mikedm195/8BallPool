//#include <stdafx.h>
#include <stdlib.h>
//#include <windows.h>
#include <GL/glut.h>
#include "glm.h"
#include "Texture.h"

static float ypoz = 0, zpoz = 0;

GLMmodel* pmodel2 = NULL;

// You need an integer value to store the texture index that OpenGL retures when you load a texture
// Using this index you can later refer to a specific texture
// Note that GLuint is actualy an int.
GLuint	texturas[2];
Texture	treeTexture, textura2;

bool LoadTreeTextures()
{
  // Define un arreglo de texturas
  glGenTextures(2, texturas);

  // Código para cargar la textura original que se pega al cubo
  LoadTGA(&treeTexture, "imagenPrueba.tga");
  //glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
  glBindTexture(GL_TEXTURE_2D, texturas[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, treeTexture.bpp / 8, treeTexture.width, treeTexture.height, 0, treeTexture.type, GL_UNSIGNED_BYTE, treeTexture.imageData);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  if (treeTexture.imageData)		
    free(treeTexture.imageData);

   //Código para textura 2 de cuadritos azules que se pegan al plano de fondo
   LoadTGA(&textura2, "imagenPrueba2.tga");	
   glBindTexture(GL_TEXTURE_2D, texturas[1]);
   glTexImage2D(GL_TEXTURE_2D, 0, textura2.bpp / 8, textura2.width, textura2.height, 0, textura2.type, GL_UNSIGNED_BYTE, textura2.imageData);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   if (textura2.imageData)		
     free(textura2.imageData);

   // Habilita todas las texturas.
   glEnable(GL_TEXTURE_2D);
}

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   LoadTreeTextures();
   glEnable(GL_DEPTH_TEST);
   glShadeModel (GL_SMOOTH);
}


void drawmodel(void)
{
    // Load the model just as I have shown you in the previous tutorial
	// You could replace this part with your own loader
    if (!pmodel2) {
        pmodel2 = glmReadOBJ("sphere.obj");
        if (!pmodel2) exit(0);
        glmUnitize(pmodel2);
        glmFacetNormals(pmodel2);
        glmVertexNormals(pmodel2, 90.0);
    }
	// before you draw anything you should bind the right texture
	// If you have more then one texture you will have to make sure you bind the right one
    //glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
    glBindTexture(GL_TEXTURE_2D, texturas[0]);
	// You can replace this with your drawing code
	// This calls GLM to draw the loaded model with GLM_TEXTURE on to tell it to also render texture coordinates
	// without those coordinates OpenGL will have no ideea how to map your texture to the object
    glmDraw(pmodel2, GLM_SMOOTH | GLM_TEXTURE );
}


void display(void)
{
	
     glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
     // Lets do some rotations here so you can see the textures on the cube

     glBindTexture(GL_TEXTURE_2D, texturas[1]);
     glPushMatrix();
        glScalef( 1.2f, 1.2f, 1.0f);
        glBegin(GL_QUADS);
          glTexCoord2f(0.0, 0.0); glVertex3f( 1.0f,  1.0f, 0.0f );
          glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f,  1.0f, 0.0f );
          glTexCoord2f(1.0, 1.0); glVertex3f(-1.0f, -1.0f, 0.0f );
          glTexCoord2f(1.0, 0.0); glVertex3f( 1.0f, -1.0f, 0.0f );
        glEnd();
     glPopMatrix();

     glPushMatrix();
        glRotatef(ypoz,0,1,0);
	glRotatef(zpoz,0,0,1);
	
	drawmodel();	
     glPopMatrix();

//	Sleep(5);
     glutSwapBuffers();
	
   
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
   glTranslatef(0,0,-2);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
	 // These will allow you to force some extra rotation by pressing the 'y' and 'z' key.
	  case 'y':         
		  ypoz=ypoz+5;
		  if (ypoz>360) ypoz=0;
         glutPostRedisplay();
         break;
	 case 'z':         
		 zpoz = zpoz+5;
		 if (zpoz>360) zpoz=0;
         glutPostRedisplay();
         break;
	 
   }
}

// Animate this a little bit
// Changing the rotation angle of the whole sceene from 0 to 360 and then refreshing
// the screen for a nice effect
// You can see the cube and the textures better.
void animate()
{
	ypoz+=0.5;
	if (ypoz>360) ypoz=0;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutIdleFunc(animate);
   glutMainLoop();
   return 0;
}
