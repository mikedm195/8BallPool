/*
 *  
 * Miguel Alberto Del Moral González
 * A01015019
 *     
 */
#pragma once 

#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include "glm.h"
#include "Texture.h"
#include <stdio.h>
#include <math.h>

class Bola{
	private:
		GLuint	texturas;
		Texture BallTexture;
		double x,z;
		double velX;
		double velZ;
	public:
		GLMmodel* pmodel2 = NULL;
        Bola();
		bool colision[16];
        void dibujar();//Dibuja la bola
		bool loadTextures(char * nombre);
		double getX();
		double getZ();
		void setX(double x);	
		void setZ(double z);	
		double getVelX();
		double getVelZ();
		void setVelX(double mx);	
		void setVelZ(double mz);	
};
