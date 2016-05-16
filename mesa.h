/*
 *  
 * Miguel Alberto Del Moral González
 * A01015019
 *     
 */
#pragma once 

#include <GL/glut.h>
#include <stdlib.h>

class Mesa{
	private:
		void dibujaDI();
		void dibujaAB();
    public:
        Mesa();
        void dibujar(double x,double y, double z);//Dibuja la mesa
};

