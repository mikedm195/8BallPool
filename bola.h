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
		double moveX;
		double moveZ;
	public:
		GLMmodel* pmodel2 = NULL;
        Bola();
        void dibujar();//Dibuja la bola
		bool loadTextures(char * nombre);
		double getX();
		double getZ();
		void setX(double x);	
		void setZ(double z);	
		double getMoveX();
		double getMoveZ();
		void setMoveX(double mx);	
		void setMoveZ(double mz);	
};
