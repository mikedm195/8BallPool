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
		int strength=0;
		void drawTurn();
		void drawWinner();
		void drawPlayers();
		void drawStrength();

	public:
								    
		Text();
		void setTurn(int x);
		int getTurn();
		void setWinner(int w);
		int getWinner();
		void drawText();
		void setStrength(int strength);														    																    
};

