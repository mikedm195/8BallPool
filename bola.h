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
class Bola{
	private:
		GLuint	texturas;
		Texture BallTexture;
	public:
		GLMmodel* pmodel2 = NULL;
        Bola();
        void dibujar(double x,double y, double z);//Dibuja la bola
		bool loadTextures(char * nombrem);
		
};
