#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "text3d.h"

class Text
{
	private:
		int turn;
		int winner;
		void drawTurn();
		void drawWinner();

	public:
								    
		Text();
		void setTurn(int x);
		int getTurn();
		void setWinner(int w);
		int getWinner();
		void drawText();
																    																    
};

