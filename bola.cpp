#include "bola.h"

Bola::Bola(){
	velX=0.0;
	velZ=0.0;
	int i = 0;
	for(;i<16;i++)
		colision[i]=false;
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

double Bola::getVelX(){
	return velX;
}
double Bola::getVelZ(){
	return velZ;
}
void Bola::setVelX(double mx){
	this->velX = mx;
}
void Bola::setVelZ(double mz){
	this->velZ = mz;
}

void Bola::desacelera(){
	double desAcc = .0008;

	if(velX != 0 || velZ != 0){
		if(fabs(velX)>fabs(velZ)){
			velZ-=velZ*desAcc/fabs(velX);
			if(velX>0)
				velX-=desAcc;
			else
				velX+=desAcc;
		}else{
			velX-=velX*desAcc/fabs(velZ);
			if(velZ>0)
				velZ-=desAcc;
			else
				velZ+=desAcc;
		}
		if(fabs(velX)<desAcc)
			velX=0;
		if(fabs(velZ)<desAcc)
			velZ=0;
	}
}

void Bola::dibujar(){
	double r = .3075;

	glPushMatrix();
		x+=velX;
		z+=velZ;
		
		glTranslatef ( x, -6, z);//traslada la bola
																			        
		glScalef ( r, r, r);//Escala la bola

		if (!pmodel2) {
			pmodel2 = glmReadOBJ("Texturas/sphere.obj");
			if (!pmodel2) exit(0);
			glmUnitize(pmodel2);
			glmFacetNormals(pmodel2);
			glmVertexNormals(pmodel2, 90.0);
		}
		
		glBindTexture(GL_TEXTURE_2D, BallTexture.texID);
	
		glmDraw(pmodel2, GLM_SMOOTH | GLM_TEXTURE );
		
		desacelera();
		
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

