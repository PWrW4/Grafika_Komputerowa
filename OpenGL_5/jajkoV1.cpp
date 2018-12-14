#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>
#include <math.h>
using namespace std;
typedef float point3[3];


static GLfloat viewer[] = { 0.0, 0.0, 10.0 };
// inicjalizacja położenia obserwatora

static GLfloat thetaArr[] = { 0.0, 0.0, 0.0 }; // trzy kąty obrotu
static GLfloat theta = 0.0;   // kąt obrotu obiektu
static GLfloat alfa = 0.0;
static GLfloat pix2angle;     // przelicznik pikseli na stopnie

static GLint status = 0;       // stan klawiszy myszy
							   // 0 - nie naciśnięto żadnego klawisza
							   // 1 - naciśnięty zostać lewy klawisz
							   // 2 - wcisniety prawy klawisz

static int x_pos_old = 0;       // poprzednia pozycja kursora myszy
static int y_pos_old = 0;
static int scroll_old = 0;
static int delta_x = 0;        // różnica pomiędzy pozycją bieżącą
static int delta_y = 0;
static int delta_scroll = 0;

// i poprzednią kursora myszy

/*************************************************************************************/

void spinEgg()
{

	thetaArr[0] -= 0.5;
	if (thetaArr[0] > 360.0) thetaArr[0] -= 360.0;

	thetaArr[1] -= 0.5;
	if (thetaArr[1] > 360.0) thetaArr[1] -= 360.0;

	thetaArr[2] -= 0.5;
	if (thetaArr[2] > 360.0) thetaArr[2] -= 360.0;

	glutPostRedisplay(); //odświeżenie zawartości aktualnego okna
}


/*************************************************************************************/
static int n = 80;
void Egg() {
	point3 **vectors3d = new point3*[n];
	point3 **vektorNorm = new point3*[n];
	for (int i = 0; i < n; i++) {
		vectors3d[i] = new point3[n];
		vektorNorm[i] = new point3[n];
	}


	double odstep = 1 / (double)(n - 1);
	double ***punkty2D = new double**[n];
	for (int i = 0; i < n; i++) {
		punkty2D[i] = new double*[n];
		for (int j = 0; j < n; j++) {
			punkty2D[i][j] = new double[2];
			punkty2D[i][j][0] = i * odstep;
			punkty2D[i][j][1] = j * odstep;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			double u = punkty2D[i][j][0];
			double v = punkty2D[i][j][1];
			vectors3d[i][j][0] = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u)*cos(3.14 *v);
			vectors3d[i][j][1] = 160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2) - 5;
			vectors3d[i][j][2] = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u)*sin(3.14 *v);

			float ux, uz, uy, vz, vy, vx, length;

			// obliczenie wartosci wektorow normalnych
			ux = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45)*cos(3.14*v);
			uy = (640 * pow(u, 3) - 960 * pow(u, 2) + 320 * u);
			uz = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45)*sin(3.14*v);

			vx = 3.14*(90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u)*sin(3.14*v);
			vy = 0;
			vz = -3.14*(90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u)*cos(3.14*v);

			vektorNorm[i][j][0] = uy * vz - uz * vy;
			vektorNorm[i][j][1] = uz * vx - ux * vz;
			vektorNorm[i][j][2] = ux * vy - uy * vx;

			length = sqrt(vektorNorm[i][j][0] * vektorNorm[i][j][0] + vektorNorm[i][j][1] * vektorNorm[i][j][1] + vektorNorm[i][j][2] * vektorNorm[i][j][2]);
			if (i == 0 || i == n)
			{
				vektorNorm[i][j][0] = 0;
				vektorNorm[i][j][1] = -1;
				vektorNorm[i][j][2] = 0;
			}
			else if (i < n / 2)
			{
				vektorNorm[i][j][0] = (uy*vz - uz * vy) / length;
				vektorNorm[i][j][1] = (uz*vx - ux * vz) / length;
				vektorNorm[i][j][2] = (ux*vy - uy * vx) / length;
			}
			else if (i > n / 2)
			{
				vektorNorm[i][j][0] = -1 * (uy*vz - uz * vy) / length;
				vektorNorm[i][j][1] = -1 * (uz*vx - ux * vz) / length;
				vektorNorm[i][j][2] = -1 * (ux*vy - uy * vx) / length;
			}
			else
			{
				vektorNorm[i][j][0] = 0;
				vektorNorm[i][j][1] = 1;
				vektorNorm[i][j][2] = 0;
			}


		}
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {

			glColor3f(255.0f, 255.0f, 255.0f);
			glBegin(GL_TRIANGLES);
			glNormal3fv(vektorNorm[i][j + 1]);
			glVertex3fv(vectors3d[i][j + 1]);

			glNormal3fv(vektorNorm[i + 1][j]);
			glVertex3fv(vectors3d[i + 1][j]);

			glNormal3fv(vektorNorm[i + 1][j + 1]);
			glVertex3fv(vectors3d[i + 1][j + 1]);
			glEnd();


			glBegin(GL_TRIANGLES);
			glNormal3fv(vektorNorm[i][j]);
			glVertex3fv(vectors3d[i][j]);

			glNormal3fv(vektorNorm[i + 1][j]);
			glVertex3fv(vectors3d[i + 1][j]);

			glNormal3fv(vektorNorm[i][j + 1]);
			glVertex3fv(vectors3d[i][j + 1]);
			glEnd();

		}
	}
}

// Funkcja "bada" stan myszy i ustawia wartości odpowiednich zmiennych globalnych

void Mouse(int btn, int state, int x, int y)
{


	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;        // przypisanie aktualnie odczytanej pozycji kursora
		y_pos_old = y;
		// jako pozycji poprzedniej
		status = 1;          // wcięnięty został lewy klawisz myszy
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		scroll_old = y;
		// jako pozycji poprzedniej
		status = 2;          // wcięnięty został prawy klawisz myszy
	}
	else
		status = 0;          // nie został wcięnięty żaden klawisz
}

/*************************************************************************************/

// Funkcja "monitoruje" położenie kursora myszy i ustawia wartości odpowiednich
// zmiennych globalnych

void Motion(GLsizei x, GLsizei y)
{
	if (status == 1) {
		delta_x = x - x_pos_old;     // obliczenie różnicy położenia kursora myszy
		delta_y = y - y_pos_old;
		x_pos_old = x;            // podstawienie bieżącego położenia jako poprzednie
		y_pos_old = y;
	}
	else if (status == 2) {
		delta_scroll = y - scroll_old;
		scroll_old = y;
	}
	glutPostRedisplay();     // przerysowanie obrazu sceny
}

/*************************************************************************************/


// Funkcja rysująca osie układu wspó?rz?dnych



void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz?tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0, 5.0, 0.0 };
	// pocz?tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0, 5.0 };
	//  pocz?tek i koniec obrazu osi y

	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x

	glVertex3fv(x_min);
	glVertex3fv(x_max);

	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y

	glVertex3fv(y_min);
	glVertex3fv(y_max);

	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z

	glVertex3fv(z_min);
	glVertex3fv(z_max);

	glEnd();

}

/*************************************************************************************/

// Funkcja określająca co ma być rysowane (zawsze wywoływana, gdy trzeba
// przerysować scenę)



void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszczącym

	glLoadIdentity();
	// Czyszczenie macierzy bie??cej
	float scroll = delta_scroll * pix2angle*0.07;
	if (status == 2 && ((viewer[2] <= 6 && scroll > 0) || (scroll < 0 && viewer[2] >= 20) || (viewer[2] > 6 && viewer[2] < 20))) {

		viewer[2] += scroll;
	}
	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	// Zdefiniowanie położenia obserwatora


	if (status == 1)                     // jeśli lewy klawisz myszy wcięnięty
	{
		theta += delta_x * pix2angle;    // modyfikacja kąta obrotu o kat proporcjonalny
		alfa += delta_y * pix2angle;

	}

	glRotatef(thetaArr[0], 1.0, 0.0, 0.0);

	glRotatef(thetaArr[1], 0.0, 1.0, 0.0);

	glRotatef(thetaArr[2], 0.0, 0.0, 1.0);
	glRotatef(theta, 0.0, 1.0, 0.0);  //obrót obiektu o nowy kąt
	glRotatef(alfa, 1.0, 0.0, 0.0);  //obrót obiektu o nowy kąt



	glColor3f(1.0f, 23.0f, 1.0f);
	// Ustawienie koloru rysowania na biały

	Egg();
	// Narysowanie czajnika

	glFlush();
	// Przekazanie poleceń rysujących do wykonania

	glutSwapBuffers();



}
/*************************************************************************************/

// Funkcja ustalająca stan renderowania



void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLfloat mat_ambient[] = { 1.0,1.0, 1.0, 1 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess = { 20.0 };
	GLfloat light_position[] = { 0.0, 0.0, 30.0, 1.0 };
	GLfloat light_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat att_constant = { 1.0 };
	GLfloat att_linear = { (GLfloat) 0.05 };
	GLfloat att_quadratic = { (GLfloat) 0.001 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	glShadeModel(GL_SMOOTH); // właczenie łagodnego cieniowania
	glEnable(GL_LIGHTING);   // właczenie systemu oświetlenia sceny
	glEnable(GL_LIGHT0);     // włączenie źródła o numerze 0
	glEnable(GL_DEPTH_TEST); // włączenie mechanizmu z-bufora
}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) są
// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	pix2angle = 360.0 / (float)horizontal;

	glMatrixMode(GL_PROJECTION);
	// Przełączenie macierzy bieżącej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bieżącej
	cout << vertical << " horizontal " << horizontal << endl;

	GLdouble aspect = (GLdouble)horizontal / vertical;

	gluPerspective(70, (float)aspect, 1.0, 30.0);
	// Ustawienie parametrów dla rzutu perspektywicznego


	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkości okna okna widoku (viewport) w zależności
	// relacji pomiędzy wysokością i szerokością okna

	glMatrixMode(GL_MODELVIEW);
	// Przełączenie macierzy bieżącej na macierz widoku modelu 

	glLoadIdentity();
	// Czyszczenie macierzy bieżącej

}

/*************************************************************************************/

// Główny punkt wejścia programu. Program działa w trybie konsoli



void main(void)
{
	char *myargv[1];
	int myargc = 1;
	myargv[0] = _strdup("Myappname");
	glutInit(&myargc, myargv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(1000, 1000);

	glutCreateWindow("Oświetlenie jajka");

	//glutIdleFunc(spinEgg);

	glutDisplayFunc(RenderScene);
	// Określenie, że funkcja RenderScene będzie funkcją zwrotną
	// (callback function).  Będzie ona wywoływana za każdym razem
	// gdy zajdzie potrzeba przerysowania okna


	glutMouseFunc(Mouse);

	glutMotionFunc(Motion);

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
	// za zmiany rozmiaru okna                      


	MyInit();
	// Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przystąpieniem do renderowania

	glEnable(GL_DEPTH_TEST);
	// Włączenie mechanizmu usuwania niewidocznych elementów sceny

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}
