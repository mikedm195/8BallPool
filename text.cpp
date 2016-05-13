#include "text.h"

Text::Text()
{
	turn = 1;
    winner = 0; 
}
void Text::setTurn(int t)
{
    turn = t;
}
int Text::getTurn()
{
    return turn;
}

void Text::setWinner(int w)
{
    winner = w;
}
int Text::getWinner()
{
    return winner;
}
void Text::drawTurn()
{
    std::string sturn = "Player " + std::to_string(turn) + " turn";

    
    glPushMatrix();
	    //glScalef(.3, .3, 1);
	    glTranslatef(0, 13, -5.0f);
    	t3dDraw3D(sturn, 0, 0, 0.2f);
    glPopMatrix();
    
}
void Text::drawWinner()
{
    std::string win = "Player " + std::to_string(winner) + " wins";
    
    //Draw the strings along the sides of a square
    glPushMatrix();
	    //glScalef(.3, .3, 1);
	    glTranslatef(0, 10, -5.0f);
	    t3dDraw3D(win, 0, 0, 0.2f);
    glPopMatrix();


}

void Text::drawText()
{
    //glTranslatef(0.0f, 0.0f, -8.0f);
    
    GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    
    GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat lightPos0[] = {-0.5f, 0.5f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    
    drawTurn();
	if(winner != 0)
	    drawWinner();
    
}

