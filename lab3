#include <stdio.h>
#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <gl/GL.h>
#include <cmath>
#include <conio.h>
#include <windows.h>
#include <random>


GLdouble Lx[2], Ly[2];
GLint Ix;
int snakeSize;
int snakeX[50][50];
int snakeY[50][50];
int snakeNewX[50][50];
int snakeNewY[50][50];
GLint positionX;
GLint positionY;
GLint positionX2;
GLint positionY2;
GLint foodX;
GLint foodY;
int direction; // 0 - doli, 1 - gori, 2- livo, 3 - desno



GLuint window;
GLuint width = 500, height = 500;
int eaten = 1;
int exiting = 0;


void myDisplay();
void myReshape(int width, int height);
void myKeyboard(unsigned char theKey, int mouseX, int mouseY);
void myLine(GLint xa, GLint ya, GLint xb, GLint yb);
void createSnake();
void moveSnake();
void myDsplay();
void createFood();





int main(int argc, char** argv)
{
	direction = 0;
	snakeSize = 1;
	positionX = 390;
	positionY = 495;
	positionX2 = 405;
	positionY2 = 510;
	snakeX[0][0] = positionX;
	snakeX[0][1] = positionX2;
	snakeY[0][0] = positionY;
	snakeY[0][1] = positionY2;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutInit(&argc, argv);
	window = glutCreateWindow("Glut OpenGL Linija");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutMainLoop();
	return 0;
}




void createSnake() {
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(200, 450);
	int len, i, len2;
	char stringic[] = { 'R', 'e', 'z', 'u', 'l', 't', 'a', 't', ' ', ':', ' ', '\0'};
	std::string tmp = std::to_string(snakeSize);
	char const* ispis = tmp.c_str();
	len = (int)strlen(stringic);
	len2 = (int)strlen(ispis);
	for (i = 0; i < len + len2; i++) {
		if(i < len)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stringic[i]);
		else glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ispis[i - len]);
	}
	
	

	for (int i = 0; i < snakeSize; i++) {
		positionX = snakeX[i][0];
		positionX2 = snakeX[i][1];
		positionY = snakeY[i][0];
		positionY2 = snakeY[i][1];
		if (i % 2 == 0) {
			glColor3f(0.0, 0.0, 0.0);
		}
		else {
			glColor3f(0.0, 1.0, 0.0);
		}
		glBegin(GL_POLYGON);

		glVertex2f(positionX, positionY);

		glVertex2f(positionX2, positionY);

		glVertex2f(positionX2, positionY2);

		glVertex2f(positionX, positionY2);

		glEnd();

		for (int i = 1; i < snakeSize; i++) {
			if (snakeX[0][0] == snakeX[i][0] && snakeY[0][0] == snakeY[i][0]) {
			
				glColor3f(0.0, 0.0, 0.0);
				
				
				glBegin(GL_POLYGON);

				glVertex2f(0, 0);

				glVertex2f(500, 0);

				glVertex2f(500, 500);

				glVertex2f(0, 500);

				glEnd();

				glColor3f(0.0, 1.0, 0.0);
				glRasterPos2f(200, 250);
				int len, i, len2;
				char stringic[] = { 'G', 'a', 'm', 'e', ' ', 'o', 'v', 'e', 'r', ' ', ':', '(',  '\0' };
				len = (int)strlen(stringic);
				for (i = 0; i < len; i++) {
					
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stringic[i]);
					exiting = 1;
					
				}
			}
		}

	}
	

}

void createFood() {
	if (eaten == 1) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(0, 470);
		foodX = distr(gen);
		foodY = distr(gen);
		while (foodX % 15 != 0) {
			foodX = foodX + 1;
		}
		while (foodY % 15 != 0) {
			foodY = foodY + 1;
		}
		eaten = 0;
	}

	if (foodX % 4 == 0) {
		glColor3f(1.0, 0.0, 0.0);
		}
	else if (foodX % 4 == 1) {
		glColor3f(1.0, 0.5, 0.0);
	}
	else if (foodX % 4 == 2) {
		glColor3f(0.0, 0.0, 1.0);
	}
	else if (foodX % 4 == 3) {
		glColor3f(1.0, 0.0, 1.0);
	}
		glBegin(GL_POLYGON);
		{
			glVertex2f(foodX, foodY);

			glVertex2f(foodX + 15, foodY);

			glVertex2f(foodX + 15, foodY + 15);

			glVertex2f(foodX, foodY + 15);
		}
		
		glColor3f(0.0, 0.0, 0.0);
		glEnd();
		//glColor3b(0, 0, 0);

	

}

void moveSnake() {
	
	
		
		if (snakeX[0][0] == foodX && snakeY[0][0] == foodY) {
			eaten = 1;
			if (direction == 0) {
				snakeX[snakeSize][0] = snakeX[snakeSize - 1][0];
				snakeY[snakeSize][0] = snakeY[snakeSize - 1][0] + 15;
				snakeX[snakeSize][1] = snakeX[snakeSize - 1][1];
				snakeY[snakeSize][1] = snakeY[snakeSize - 1][1] + 15;

				snakeSize++;

			}
			if (direction == 1) {
				snakeX[snakeSize][0] = snakeX[snakeSize - 1][0];
				snakeY[snakeSize][0] = snakeY[snakeSize - 1][0] - 15;
				snakeX[snakeSize][1] = snakeX[snakeSize - 1][1];
				snakeY[snakeSize][1] = snakeY[snakeSize - 1][1] - 15;

				snakeSize++;

			}
			if (direction == 2) {
				snakeX[snakeSize][0] = snakeX[snakeSize - 1][0] - 15;
				snakeY[snakeSize][0] = snakeY[snakeSize - 1][0];
				snakeX[snakeSize][1] = snakeX[snakeSize - 1][1] - 15;
				snakeY[snakeSize][1] = snakeY[snakeSize - 1][1];

				snakeSize++;

			}
			if (direction == 3) {
				snakeX[snakeSize][0] = snakeX[snakeSize - 1][0] + 15;
				snakeY[snakeSize][0] = snakeY[snakeSize - 1][0];
				snakeX[snakeSize][1] = snakeX[snakeSize - 1][1] + 15;
				snakeY[snakeSize][1] = snakeY[snakeSize - 1][1] ;

				snakeSize++;

			}
		}
		createFood();
	
	if (direction == 0) {
		snakeNewX[0][0] = snakeX[0][0];
		snakeNewX[0][1] = snakeX[0][1];
		snakeNewY[0][0] = snakeY[0][0] - 15;
		snakeNewY[0][1] = snakeY[0][1] - 15;
		for (int i = 0; i < snakeSize - 1; i++) {
			snakeNewX[i + 1][0] = snakeX[i][0];
			snakeNewX[i + 1][1] = snakeX[i][1];
			snakeNewY[i + 1][0] = snakeY[i][0];
			snakeNewY[i + 1][1] = snakeY[i][1];
		}
		for (int i = 0; i < snakeSize; i++) {
			snakeX[i][0] = snakeNewX[i][0];
			snakeX[i][1] = snakeNewX[i][1];
			snakeY[i][0] = snakeNewY[i][0];
			snakeY[i][1] = snakeNewY[i][1];
		}
	}
	if (direction == 1) {
		snakeNewX[0][0] = snakeX[0][0];
		snakeNewX[0][1] = snakeX[0][1];
		snakeNewY[0][0] = snakeY[0][0] + 15;
		snakeNewY[0][1] = snakeY[0][1] + 15;
		for (int i = 0; i < snakeSize - 1; i++) {
			snakeNewX[i + 1][0] = snakeX[i][0];
			snakeNewX[i + 1][1] = snakeX[i][1];
			snakeNewY[i + 1][0] = snakeY[i][0];
			snakeNewY[i + 1][1] = snakeY[i][1];
		}
		for (int i = 0; i < snakeSize; i++) {
			snakeX[i][0] = snakeNewX[i][0];
			snakeX[i][1] = snakeNewX[i][1];
			snakeY[i][0] = snakeNewY[i][0];
			snakeY[i][1] = snakeNewY[i][1];
		}
	}
	else if (direction == 2) {
		snakeNewX[0][0] = snakeX[0][0] - 15;
		snakeNewX[0][1] = snakeX[0][1] - 15;
		snakeNewY[0][0] = snakeY[0][0];
		snakeNewY[0][1] = snakeY[0][1];
		for (int i = 0; i < snakeSize-1; i++) {
			snakeNewX[i + 1][0] = snakeX[i][0];
			snakeNewX[i + 1][1] = snakeX[i][1];
			snakeNewY[i + 1][0] = snakeY[i][0];
			snakeNewY[i + 1][1] = snakeY[i][1];
		}
		for (int i = 0; i < snakeSize; i++) {
			snakeX[i][0] = snakeNewX[i][0];
			snakeX[i][1] = snakeNewX[i][1];
			snakeY[i][0] = snakeNewY[i][0];
			snakeY[i][1] = snakeNewY[i][1];
		}
	}
	else if (direction == 3) {
		snakeNewX[0][0] = snakeX[0][0] + 15;
		snakeNewX[0][1] = snakeX[0][1] + 15;
		snakeNewY[0][0] = snakeY[0][0];
		snakeNewY[0][1] = snakeY[0][1];
		for (int i = 0; i < snakeSize-1; i++) {
			snakeNewX[i + 1][0] = snakeX[i][0];
			snakeNewX[i + 1][1] = snakeX[i][1];
			snakeNewY[i + 1][0] = snakeY[i][0];
			snakeNewY[i + 1][1] = snakeY[i][1];
		}
		for (int i = 0; i < snakeSize; i++) {
			snakeX[i][0] = snakeNewX[i][0];
			snakeX[i][1] = snakeNewX[i][1];
			snakeY[i][0] = snakeNewY[i][0];
			snakeY[i][1] = snakeNewY[i][1];
		}
	}
	createSnake();
	
}

void myDisplay()
{
	//printf("Pozvan myDisplay()\n");
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //  boja pozadine
    //brisanje nakon svake iscrtane linije
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glFlush();
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
	//printf("Pozvan myDisplay()\n");
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //  boja pozadine
	//brisanje nakon svake iscrtane linije
	char c;

	
	
	while (exiting ==0) {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		switch (theKey) {

		case 's':
			

				direction = 0;
				Sleep(150);

				moveSnake();
				glutSwapBuffers();
				if (GetAsyncKeyState(0x41))
				{
					theKey = 'a';
					
				}
				if (GetAsyncKeyState(0x44))
				{
					theKey = 'd';

				}
				
				
				break;

		case 'w':


			direction = 1;
			Sleep(150);

			moveSnake();
			glutSwapBuffers();
			
			if (GetAsyncKeyState(0x41))
			{
				theKey = 'a';

			}
			if (GetAsyncKeyState(0x53))
			{
				theKey = 's';

			}
			if (GetAsyncKeyState(0x44))
			{
				theKey = 'd';

			}


			break;
			
		case 'd':


			direction = 3;
			Sleep(150);

			moveSnake();
			glutSwapBuffers();
			
			
			if (GetAsyncKeyState(0x57))
			{
				theKey = 'w';

			}
			if (GetAsyncKeyState(0x53))
			{
				theKey = 's';

			}

			break;
		case 'a':
			
				
				direction = 2;
				Sleep(150);
				moveSnake();
				glutSwapBuffers();
				if (GetAsyncKeyState(0x53))
				{
					theKey = 's';
					
				}
				if (GetAsyncKeyState(0x57))
				{
					theKey = 'w';

				}
				
				
				break;
			
		}



		}




		
	}
		


void myReshape(int w, int h)
{
	//printf("Pozvan myReshape()\n");
	width = w; height = h;               //promjena sirine i visine prozora
	Ix = 0;								//	indeks tocke 0-prva 1-druga tocka
	glViewport(0, 0, width, height);	//  otvor u prozoru

	glMatrixMode(GL_PROJECTION);		//	matrica projekcije
	glLoadIdentity();					//	jedinicna matrica
	gluOrtho2D(0, width, 0, height); 	//	okomita projekcija
	glMatrixMode(GL_MODELVIEW);			//	matrica pogleda
	glLoadIdentity();					//	jedinicna matrica

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // boja pozadine
	glClear(GL_COLOR_BUFFER_BIT);		//	brisanje pozadine
	glPointSize(1.0);					//	postavi velicinu tocke za liniju
	glColor3f(0.0f, 0.0f, 0.0f);		//	postavi boju linije
}
