#include "bola.h"

Bola::Bola(){
	moveX=0;
	moveZ=0;
}

double Bola::getX(){
	return x;
}
double Bola::getZ(){
	return z;
}
void Bola::setX(double x){
	this->x = x;
}
void Bola::setZ(double z){
	this->z = z;
}

double Bola::getMoveX(){
	return moveX;
}
double Bola::getMoveZ(){
	return moveX;
}
void Bola::setMoveX(double mx){
	this->moveX = mx;
}
void Bola::setMoveZ(double mz){
	this->moveZ = mz;
}

void Bola::dibujar(){
	double r = .3075*2;	
	glPushMatrix();
		x+=moveX;
		z+=moveZ;
		if(x>11-r)
			moveX = -fabs(moveX);
		if(x<-11+r)
			moveX = fabs(moveX);
		if(z>5.5-r)
			moveZ = -fabs(moveZ);
		if(z<-5.5+r)
			moveZ = fabs(moveZ);

		glTranslatef ( x, -6, z);//traslada la bola
																			        
		glScalef ( .3075, .3075, .3075);//Escala la bola

		if (!pmodel2) {
			pmodel2 = glmReadOBJ("Texturas/sphere.obj");
			if (!pmodel2) exit(0);
			glmUnitize(pmodel2);
			glmFacetNormals(pmodel2);
			glmVertexNormals(pmodel2, 90.0);
		}
		
		glBindTexture(GL_TEXTURE_2D, BallTexture.texID);
	
		glmDraw(pmodel2, GLM_SMOOTH | GLM_TEXTURE );

		if(moveX>0)
			moveX-=.0001;
		else
			moveX+=.0001;
		if(moveZ>0)
			moveZ-=.0001;
		else
			moveZ+=.0001;

	glPopMatrix();
}

bool Bola::loadTextures(char * nombre)
{
  
   if(LoadTGA(&BallTexture, nombre)){
  	  glGenTextures(1, &BallTexture.texID);
	  glBindTexture(GL_TEXTURE_2D, BallTexture.texID);
  	  glTexImage2D(GL_TEXTURE_2D, 0, BallTexture.bpp / 8, BallTexture.width, BallTexture.height, 0, BallTexture.type, GL_UNSIGNED_BYTE, BallTexture.imageData);
   	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   	  glEnable(GL_TEXTURE_2D);

   	  if (BallTexture.imageData)		
  	 	free(BallTexture.imageData);
	  return true;	  
   }else{
	  return false;
   }

}

