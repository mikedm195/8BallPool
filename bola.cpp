#include "bola.h"

Bola::Bola(){
		    
}

void Bola::dibujar(double x,double y, double z){
	
	glPushMatrix();
		glTranslatef ( x, y, z);//traslada la extremidad
																			        
		glScalef ( .3075, .3075, .3075);//Escala la extremidad

		if (!pmodel2) {
			pmodel2 = glmReadOBJ("Texturas/sphere.obj");
			if (!pmodel2) exit(0);
			glmUnitize(pmodel2);
			glmFacetNormals(pmodel2);
			glmVertexNormals(pmodel2, 90.0);
		}
		// before you draw anything you should bind the right texture
		// If you have more then one texture you will have to make sure you bind the right one
		//glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
		glBindTexture(GL_TEXTURE_2D, BallTexture.texID);
		// You can replace this with your drawing code
		// This calls GLM to draw the loaded model with GLM_TEXTURE on to tell it to also render texture coordinates
		// without those coordinates OpenGL will have no ideea how to map your texture to the object
		glmDraw(pmodel2, GLM_SMOOTH | GLM_TEXTURE );
/*
		glTranslatef ( x, y, z);//traslada la extremidad
																			        
		glPushMatrix(); 
			glScalef ( .3075, .3075, .3075);//Escala la extremidad
			glutSolidSphere (1.0,20,20);//Dibuja
		glPopMatrix();
*/
	//
	glPopMatrix();
}

bool Bola::loadTextures(char * nombre)
{
  
   LoadTGA(&BallTexture, nombre);
   glGenTextures(1, &BallTexture.texID);
   //glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
   glBindTexture(GL_TEXTURE_2D, BallTexture.texID);
   glTexImage2D(GL_TEXTURE_2D, 0, BallTexture.bpp / 8, BallTexture.width, BallTexture.height, 0, BallTexture.type, GL_UNSIGNED_BYTE, BallTexture.imageData);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

   if (BallTexture.imageData)		
  	 free(BallTexture.imageData);

 
   // Habilita todas las texturas.
   glEnable(GL_TEXTURE_2D);

}

