#include <stdio.h>
#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <gl/GL.h>
#include <cmath>

//*********************************************************************************
//	Pocetna tocka Lx[1], Ly[1] Krajnja tocke Lx[2], Ly[2] linije.
//	Ix - stanje (zadana 1 ili 2 tocka)
//*********************************************************************************

GLdouble Lx[2], Ly[2];
GLint Ix;

double os[3];
double bivsiVektorSmjera[3];
double vektorSmjera[3];
int brSegment;
double segmenti[100][3];
int brVrh = 0;
int brPol = 0;
int iv = 0;
int ip = 0;
std::string polje[100000];
int brPolja = 0;
double a[300], b[300], c[300], d[300];
double* vrhX;
double* vrhY;
double* vrhZ;
double* pol1;
double* pol2;
double* pol3;
std::string tocke[1000];
double* tockeX;
double* tockeY;
double* tockeZ;
int brojTocaka = 0;
double cosinus;


//*********************************************************************************
//	Pokazivac na glavni prozor i pocetna velicina.
//*********************************************************************************

GLuint window;
GLuint width = 300, height = 300;

//*********************************************************************************
//	Function Prototypes.
//*********************************************************************************

void myDisplay();
void myReshape(int width, int height);
void myLine(GLint xa, GLint ya, GLint za, GLint xb, GLint yb, GLint zb);
void drawKrivulja();


//*********************************************************************************
//	Glavni program.
//*********************************************************************************

int main(int argc, char** argv)
{
	std::string myline;
	std::ifstream myfile("teddy.txt");
	if (myfile.is_open()) {
		while (myfile) {
			std::getline(myfile, myline);
			polje[brPolja] = myline;
			brPolja++;
			if (myline.substr(0, 1) == "v") {
				brVrh++;
			}
			if (myline.substr(0, 1) == "f") {
				brPol++;
			}
		}
	}
	vrhX = new double[brVrh];
	vrhY = new double[brVrh];
	vrhZ = new double[brVrh];
	pol1 = new double[brPol];
	pol2 = new double[brPol];
	pol3 = new double[brPol];
	

	for (int i = 0; i < brPolja; i++) {
		myline = polje[i];
			if (myline.substr(0, 1) == "v") {
				std::string help = myline.substr(2, myline.length() - 2);
				int x = help.find(' ');
				std::string help2 = help.substr(0, x);
				double heelp = atof(help2.c_str());
				vrhX[iv] = heelp;
				help = help.substr(x +1, help.length());
				x = help.find(' ');
				help2 = help.substr(0, x);
				heelp = atof(help2.c_str());
				help = help.substr(x + 1, help.length());
				vrhY[iv] = heelp;
				heelp = atof(help.c_str());
				vrhZ[iv] = heelp;
				iv++;

			}
			if (myline.substr(0, 1) == "f") {
				std::string help = myline.substr(2, myline.length() - 2);
				int x = help.find(' ');
				std::string help2 = help.substr(0, x);
				double heelp = atof(help2.c_str());
				pol1[ip] = heelp;
				help = help.substr(x + 1, help.length());
				x = help.find(' ');
				help2 = help.substr(0, x);
				heelp = atof(help2.c_str());
				help = help.substr(x + 1, help.length());
				pol2[ip] = heelp;
				heelp = atof(help.c_str());
				pol3[ip] = heelp;
				ip++;
			}
	}

	//uèitavanje toèaka aproksimacijske uniformne kubne B-splajn krivulje
	std::string myline2;
	std::ifstream myfile2("tocke.txt");
	if (myfile2.is_open()) {
		while (myfile2) {
			std::getline(myfile2, myline2);
			tocke[brojTocaka] = myline2;
			brojTocaka++;
		}
	}

	tockeX = new double[brojTocaka];
	tockeY = new double[brojTocaka];
	tockeZ = new double[brojTocaka];

	for (int i = 0; i < brojTocaka; i++) {
		std::string help = tocke[i];
		int x = help.find(' ');
		std::string help2 = help.substr(0, x);
		double heelp = atof(help2.c_str());
		tockeX[i] = heelp;
		help = help.substr(x + 1, help.length());
		x = help.find(' ');
		help2 = help.substr(0, x);
		heelp = atof(help2.c_str());
		help = help.substr(x + 1, help.length());
		tockeY[i] = heelp;
		heelp = atof(help.c_str());
		tockeZ[i] = heelp;
	}

	brSegment = brojTocaka - 3;
	bivsiVektorSmjera[0] = 0.0;
	bivsiVektorSmjera[1] = 0.0;
	bivsiVektorSmjera[2] = 1.0;

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutInit(&argc, argv);

	window = glutCreateWindow("Glut OpenGL Linija");
	
	


	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}


//*********************************************************************************
//	Osvjezavanje prikaza. (nakon preklapanja prozora) 
//*********************************************************************************

void myDisplay()
{	
	glTranslated(100, 100, 0);
	glScaled(0.5, 0.5, 0);
	
	//printf("Pozvan myDisplay()\n");
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //  boja pozadine //brisanje nakon svake iscrtane linije

	drawKrivulja();

	//Sleep(2000);
	for (int i = 0; i < brSegment; i++) {

		for (double t = 0; t < 1; t = t + 0.01) {
			//Sleep(10);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			drawKrivulja();
			
			double matricaT2[4] = { (1.0 / 6.0) * t * t * t, (1.0 / 6.0) * t * t, (1.0 / 6.0) * t, (1.0 / 6.0) };
			double koefMatrica[4][4] = { {-1,3,-3,1}, {3,-6,3,0},{-3,0,3,0},{1,4,1,0 } };
			double rslt2[4];
			for (int j = 0; j < 4; j++) {
				rslt2[j] = 0;

				for (int l = 0; l < 4; l++) {
					rslt2[j] += matricaT2[l] * koefMatrica[l][j];
				}

			}


			double matricaTocaka2[4][3] = { {tockeX[i], tockeY[i], tockeZ[i]}, {tockeX[i + 1], tockeY[i + 1], tockeZ[i + 1]}, {tockeX[i + 2], tockeY[i + 2], tockeZ[i + 2]}, {tockeX[i + 3], tockeY[i + 3], tockeZ[i + 3]} };
			double segment[3];
			for (int j = 0; j < 3; j++) {
				segment[j] = 0;

				for (int l = 0; l < 4; l++) {
					segment[j] += rslt2[l] * matricaTocaka2[l][j];
				}
			}

			double matricaT[3];
			matricaT[0] = 0.5 * pow(t, 2.0);
			matricaT[1] = 0.5 * t;
			matricaT[2] = 0.5;
			double matricaKoef[3][4] = { {-1, 3, -3, 1}, {2, -4, 2, 0}, {-1,0,1,0} };
			double rslt[4];
			for (int j = 0; j < 4; j++) {
				rslt[j] = 0;

				for (int l = 0; l < 3; l++) {
					rslt[j] += matricaT[l] * matricaKoef[l][j];
				}

			}
			double matricaTocaka[4][3] = { {tockeX[i], tockeY[i], tockeZ[i]}, {tockeX[i + 1], tockeY[i + 1], tockeZ[i + 1]}, {tockeX[i + 2], tockeY[i + 2], tockeZ[i + 2]}, {tockeX[i + 3], tockeY[i + 3], tockeZ[i + 3]} };
			for (int j = 0; j < 3; j++) {
				vektorSmjera[j] = 0;

				for (int l = 0; l < 4; l++) {
					vektorSmjera[j] += rslt[l] * matricaTocaka[l][j];
				}
			}


			os[0] = bivsiVektorSmjera[1] * vektorSmjera[2] - vektorSmjera[1] * bivsiVektorSmjera[2];
			os[1] = -1 * (bivsiVektorSmjera[0] * vektorSmjera[2] - vektorSmjera[0] * bivsiVektorSmjera[2]);
			os[2] = bivsiVektorSmjera[0] * vektorSmjera[1] - vektorSmjera[0] * bivsiVektorSmjera[1];
			
			glColor3b(1.0, 0, 0);
			

			glColor3b(0, 0, 1);
			double cos = (bivsiVektorSmjera[0] * vektorSmjera[0] + bivsiVektorSmjera[1] * vektorSmjera[1] + bivsiVektorSmjera[2] * vektorSmjera[2]);
			double norm1 = sqrt(pow(bivsiVektorSmjera[0], 2) + pow(bivsiVektorSmjera[1], 2) + pow(bivsiVektorSmjera[2], 2));
			double norm2 = sqrt(pow(vektorSmjera[0], 2) + pow(vektorSmjera[1], 2) + pow(vektorSmjera[2], 2));
			cosinus = cos / (norm1 * norm2);

			for (int i = 0; i < brPol; i++) {
				int prvi = pol1[i] - 1;
				int drugi = pol2[i] - 1;
				int treci = pol3[i] - 1;
				//std::cout << "\nBR POL:  " << brPol << "PRVI:  " << prvi;

				double matricaF[3] = { vrhX[prvi], vrhY[prvi], vrhZ[prvi]};
				double matricaTrans[3][3] = { {1, 0, 0}, {0, 1, 0}, {-os[0], -os[1], -os[2]} };
				double rslt[3];
				for (int j = 0; j < 3; j++) {
					rslt[j] = 0;

					for (int l = 0; l < 3; l++) {
						rslt[j] += matricaF[l] * matricaTrans[l][j];
					}

				}

				double rot[3][3] = { {cosinus, -sin(acos(cosinus)), 0}, {sin(acos(cosinus)), cosinus, 0}, {0,0,1} };
				double rslt1[3];
				for (int j = 0; j < 3; j++) {
					rslt1[j] = 0;

					for (int l = 0; l < 3; l++) {
						rslt1[j] += rslt[l] * rot[l][j];
					}

				}
				double matricaTraans[3][3] = { {1, 0, 0}, {0, 1, 0}, {os[0], os[1], os[2] } };
				double rslt7[3];
				for (int j = 0; j < 3; j++) {
					rslt7[j] = 0;

					for (int l = 0; l < 3; l++) {
						rslt7[j] += rslt1[l] * matricaTraans[l][j];
					}

				}

				double vrhPrvi[3] = { rslt7[0], rslt7[1], rslt7[2] };

				double matricaF1[3] = { vrhX[drugi], vrhY[drugi], vrhZ[drugi] };
				double matricaTrans1[3][3] = { {1, 0, 0}, {0, 1, 0}, {-os[0], -os[1], -os[2]} };
				double rslt13[3];
				for (int j = 0; j < 3; j++) {
					rslt13[j] = 0;

					for (int l = 0; l < 3; l++) {
						rslt13[j] += matricaF1[l] * matricaTrans1[l][j];
					}

				}

				double rot1[3][3] = { {cosinus, -sin(acos(cosinus)), 0}, {sin(acos(cosinus)), cosinus, 0}, {0,0,1} };
				double rslt11[3];
				for (int j = 0; j < 3; j++) {
					rslt11[j] = 0;

					for (int l = 0; l < 3; l++) {
						rslt11[j] += rslt13[l] * rot1[l][j];
					}

				}
				double matricaTrans2[3][3] = { {1, 0, 0}, {0, 1, 0}, {os[0], os[1], os[2]}};
				double rslt2[3];
				for (int j = 0; j < 3; j++) {
					rslt2[j] = 0;

					for (int l = 0; l < 3; l++) {
						rslt2[j] += rslt11[l] * matricaTrans2[l][j];
					}

				}

				double vrhDrugi[3] = { rslt2[0], rslt2[1], rslt2[2] };

				double matricaF0[3] = { vrhX[treci], vrhY[treci], vrhZ[treci] };
				double matricaTrans0[3][3] = { {1, 0, 0}, {0, 1, 0}, {-os[0], -os[1], -os[2]} };
				double rslt0[3];
				for (int j = 0; j < 3; j++) {
					rslt0[j] = 0;

					for (int l = 0; l < 3; l++) {
						rslt0[j] += matricaF0[l] * matricaTrans0[l][j];
					}

				}

				
				double rot0[3][3] = { {cosinus, -sin(acos(cosinus)), 0}, {sin(acos(cosinus)), cosinus, 0}, {0,0,1} };
				double rslt10[3];
				for (int j = 0; j < 3; j++) {
					rslt10[j] = 0;

					for (int l = 0; l < 3; l++) {
						rslt10[j] += rslt0[l] * rot0[l][j];
					}

				}
				double matricaTranss0[3][3] = { {1, 0, 0}, {0, 1, 0}, {os[0], os[1], os[2]}};
				double rsltt0[3];
				for (int j = 0; j < 3; j++) {
					rsltt0[j] = 0;

					for (int l = 0; l < 3; l++) {
						rsltt0[j] += rslt10[l] * matricaTranss0[l][j];
					}

				}

				double vrhTreci[3] = { rsltt0[0], rsltt0[1], rsltt0[2] };
				glColor3f(0, 0, 1);
				myLine(vrhPrvi[0]+(segment[0] * 5), vrhPrvi[1]+(segment[1] * 5), vrhPrvi[2] + (segment[2] * 5), vrhDrugi[0] + (segment[0] * 5), vrhDrugi[1] + (segment[1] * 5), vrhDrugi[2] + (segment[2] * 5));
				myLine(vrhPrvi[0] + (segment[0] * 5), vrhPrvi[1] + (segment[1] * 5), vrhPrvi[2] + (segment[2] * 5), vrhTreci[0] + (segment[0] * 5), vrhTreci[1] + (segment[1] * 5), vrhTreci[2] + (segment[2] * 5));
				myLine(vrhDrugi[0] + (segment[0] * 5), vrhDrugi[1] + (segment[1] * 5), vrhDrugi[2] + (segment[2] * 5), vrhTreci[0] + (segment[0] * 5), vrhTreci[1] + (segment[1] * 5), vrhTreci[2] + (segment[2] * 5));
				glColor3f(1, 0, 0);
				myLine(segment[0] * 5, segment[1] * 5, segment[2] * 5, (segment[0] * 5 + vektorSmjera[0]) * 5, (segment[1] * 5 + vektorSmjera[1]) * 5, segment[2] * 5);
			}
			//glRotatef(acos(cosinus), os[0], os[1], os[2]);
			glColor3b(1, 0, 0);
			//std::cout << "\n VS: " << vektorSmjera[0] << "  " << vektorSmjera[1] << "  " << vektorSmjera[2];
			glBegin(GL_LINE);
			{
				glVertex3f(segment[0] * 5, segment[1] * 5, segment[2] * 5);
				glVertex3f((segment[0] * 5 + vektorSmjera[0])*5, (segment[1] * 5 + vektorSmjera[1])*5, segment[2] * 5);
				//std::cout << "0: " << segment[0] << "1:" << segment[1] << "2: " << segment[2] <<"\n";
			}
			glEnd();
			glutSwapBuffers();
		}
		
	}
	//glFlush();
}

//*********************************************************************************
//	Promjena velicine prozora.
//*********************************************************************************

void drawKrivulja() {
	for (int i = 0; i < brSegment; i++) {
		for (double t = 0; t < 1; t = t + 0.01) {
			double matricaT2[4] = { (1.0 / 6.0) * t * t * t, (1.0 / 6.0) * t * t, (1.0 / 6.0) * t, (1.0 / 6.0) };
			double koefMatrica[4][4] = { {-1,3,-3,1}, {3,-6,3,0},{-3,0,3,0},{1,4,1,0 } };
			double rslt2[4];
			for (int j = 0; j < 4; j++) {
				rslt2[j] = 0;

				for (int l = 0; l < 4; l++) {
					rslt2[j] += matricaT2[l] * koefMatrica[l][j];
				}

			}


			double matricaTocaka2[4][3] = { {tockeX[i], tockeY[i], tockeZ[i]}, {tockeX[i + 1], tockeY[i + 1], tockeZ[i + 1]}, {tockeX[i + 2], tockeY[i + 2], tockeZ[i + 2]}, {tockeX[i + 3], tockeY[i + 3], tockeZ[i + 3]} };
			double segment[3];
			for (int j = 0; j < 3; j++) {
				segment[j] = 0;

				for (int l = 0; l < 4; l++) {
					segment[j] += rslt2[l] * matricaTocaka2[l][j];
				}
			}
			//std::cout << "Segment: " << i + 1 << std::endl;
			//std::cout << segment[0] << " " << segment[1] << " " << segment[2] << std::endl;
			glPointSize(1.0);
			glColor3b(1.0, 0.0, 0.0);

			glBegin(GL_POINTS);
			{
				glVertex3f(segment[0] * 5, segment[1] * 5, segment[2] * 5);
				//std::cout << "0: " << segment[0] << "1:" << segment[1] << "2: " << segment[2] <<"\n";
			}
			glEnd();


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
	glColor3f(0.0f, 0.0f, 1.0f);		//	postavi boju linije
}

//*********************************************************************************
//	Crtaj moju liniju.
//*********************************************************************************

void myLine(GLint xa, GLint ya, GLint za, GLint xb, GLint yb, GLint zb)
{
	
	glBegin(GL_LINES);
	{
		glVertex3f(xa, ya, za);
		glVertex3f(xb, yb, zb);
	}
	glEnd();
}



//*********************************************************************************
//	Mis.
//*********************************************************************************




//*********************************************************************************
//	Tastatura tipke - r, g, b, k - mijenjaju boju.
//*********************************************************************************



