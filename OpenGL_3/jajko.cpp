#include <iostream>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <ctime>


typedef float point3[3];

struct point2
{
	float u;
	float v;
};

struct clors
{
	float R;
	float G;
	float B;
};

//static GLfloat theta[] = { 0.0, 0.0, 0.0 }; // trzy kąty obrotu

static GLfloat theta = 0.0;   // kąt obrotu obiektu
static GLfloat pix2angle;     // przelicznik pikseli na stopnie

static GLint status = 0;       // stan klawiszy myszy
							   // 0 - nie naciśnięto żadnego klawisza
							   // 1 - naciśnięty zostać lewy klawisz

static int x_pos_old = 0;       // poprzednia pozycja kursora myszy

static int delta_x = 0;        // różnica pomiędzy pozycją bieżącą
									  // i poprzednią kursora myszy


const double MOJE_PI = 3.14159265359;
int model = 2;
const int N = 15;
clors colors[N][N];

//równania do krzywej Beziera
double x(double u, double v)
{
	return (-90.0 * u*u*u*u*u + 225 * u*u*u*u - 270 * u*u*u + 180 * u*u - 45 * u)*cos(MOJE_PI*v);
}

double y(double u, double v)
{
	return (160 * u*u*u*u - 320 * u*u*u + 160 * u*u);
}

double z(double u, double v)
{
	return (-90.0 * u*u*u*u*u + 225 * u*u*u*u - 270 * u*u*u + 180 * u*u - 45 * u)*sin(MOJE_PI*v);
}

void Egg()
{

	point3 tab3D[N][N];//przestrzeń 3D
	point2 KwJed[N][N];
	//double u = 0, v = 0;
	double webLevel = 1.0f / N;

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			KwJed[i][j].u = (1.0f / (N-1)) * i;
			KwJed[i][j].v = (1.0f / (N-1)) * j;
		}
	}

	glTranslated(0, -5, 0);//przesunięcie w dół jajka
	glRotated(0, 1.0, 0.0, 0.0);//obrócenie o -30 stopni wokół osi
	glColor3f(255.0f, 255.0f, 0.0f);//żółte punkty

	if (model == 1)
	{
		glBegin(GL_POINTS);
		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				glVertex3f(x(KwJed[i][j].u, KwJed[i][j].v), y(KwJed[i][j].u, KwJed[i][j].v), z(KwJed[i][j].u, KwJed[i][j].v));
			}
		}
		glEnd();
	}
	else if (model == 2)
	{
		glBegin(GL_LINES);
		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				if (i - 1 >= 0)
					glVertex3f(z(KwJed[i - 1][j].u, KwJed[i][j].v), y(KwJed[i - 1][j].u, KwJed[i][j].v), x(KwJed[i - 1][j].u, KwJed[i][j].v));
				else
					glVertex3f(z(KwJed[N - 1][j].u, KwJed[i][j].v), y(KwJed[N - 1][j].u, KwJed[i][j].v), x(KwJed[N - 1][j].u, KwJed[i][j].v));
				glVertex3f(z(KwJed[i][j].u, KwJed[i][j].v), y(KwJed[i][j].u, KwJed[i][j].v), x(KwJed[i][j].u, KwJed[i][j].v));

				if (i - 1 >= 0)
					glVertex3f(z(KwJed[i - 1][j].u, KwJed[i][j].v), y(KwJed[i - 1][j].u, KwJed[i][j].v), x(KwJed[i - 1][j].u, KwJed[i][j].v));
				else
					glVertex3f(z(KwJed[N - 1][j].u, KwJed[i][j].v), y(KwJed[N - 1][j].u, KwJed[i][j].v), x(KwJed[N - 1][j].u, KwJed[i][j].v));
				if (j - 1 >= 0)
					glVertex3f(z(KwJed[i][j].u, KwJed[i][j - 1].v), y(KwJed[i][j].u, KwJed[i][j - 1].v), x(KwJed[i][j].u, KwJed[i][j - 1].v));
				else
					glVertex3f(z(KwJed[i][N - 1].u, KwJed[i][j].v), y(KwJed[i][N - 1].u, KwJed[i][j - 1].v), x(KwJed[i][j].u, KwJed[i][j].v));

				if (j - 1 >= 0)
					glVertex3f(z(KwJed[i][j].u, KwJed[i][j - 1].v), y(KwJed[i][j].u, KwJed[i][j - 1].v), x(KwJed[i][j].u, KwJed[i][j - 1].v));
				else
					glVertex3f(z(KwJed[i][j].u, KwJed[i][0].v), y(KwJed[i][j].u, KwJed[i][0].v), x(KwJed[i][j].u, KwJed[i][0].v));

				glVertex3f(z(KwJed[i][j].u, KwJed[i][j].v), y(KwJed[i][j].u, KwJed[i][j].v), x(KwJed[i][j].u, KwJed[i][j].v));
			
			}
		}
		glEnd();
	}
	else if (model == 3)
	{

		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{		

				glBegin(GL_TRIANGLES);
				if(i<N-1 && j<N-1)
				{
//					if (i==0 && j!=0)
//					{
//						glColor3f(colors[i][N-1].R, colors[i][N-1].G, colors[i][N-1].B);
//						glVertex3f(x(KwJed[i][j].u, KwJed[i][j].v), y(KwJed[i][j].u, KwJed[i][j].v), z(KwJed[i][j].u, KwJed[i][j].v));
//						glColor3f(colors[i + 1][N-1].R, colors[i + 1][N-1].G, colors[i + 1][N-1].B);
//						glVertex3f(x(KwJed[i + 1][N-1].u, KwJed[i + 1][N-1].v), y(KwJed[i + 1][N-1].u, KwJed[i + 1][N-1].v), z(KwJed[i + 1][N-1].u, KwJed[i + 1][N-1].v));
//						glColor3f(colors[i + 1][j + 1].R, colors[i + 1][j + 1].G, colors[i + 1][j + 1].B);
//						glVertex3f(x(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), y(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), z(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v));
//
//						glColor3f(colors[i][N-1].R, colors[i][N-1].G, colors[i][N-1].B);
//						glVertex3f(x(KwJed[i][j].u, KwJed[i][j].v), y(KwJed[i][j].u, KwJed[i][j].v), z(KwJed[i][j].u, KwJed[i][j].v));
//						glColor3f(colors[i][j + 1].R, colors[i][j + 1].G, colors[i][j + 1].B);
//						glVertex3f(x(KwJed[i][j + 1].u, KwJed[i][j + 1].v), y(KwJed[i][j + 1].u, KwJed[i][j + 1].v), z(KwJed[i][j + 1].u, KwJed[i][j + 1].v));
//						glColor3f(colors[i + 1][j + 1].R, colors[i + 1][j + 1].G, colors[i + 1][j + 1].B);
//						glVertex3f(x(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), y(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), z(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v));
//
//
//					}
//					else
//					{
//						if (i != 0 && j == 0)
//						{
//							glColor3f(colors[N-1][j].R, colors[N-1][j].G, colors[N-1][j].B);
//							glVertex3f(x(KwJed[i][j].u, KwJed[i][j].v), y(KwJed[i][j].u, KwJed[i][j].v), z(KwJed[i][j].u, KwJed[i][j].v));
//							glColor3f(colors[i + 1][j].R, colors[i + 1][j].G, colors[i + 1][j].B);
//							glVertex3f(x(KwJed[i + 1][j].u, KwJed[i + 1][j].v), y(KwJed[i + 1][j].u, KwJed[i + 1][j].v), z(KwJed[i + 1][j].u, KwJed[i + 1][j].v));
//							glColor3f(colors[i + 1][j + 1].R, colors[i + 1][j + 1].G, colors[i + 1][j + 1].B);
//							glVertex3f(x(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), y(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), z(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v));
//
//							glColor3f(colors[N-1][j].R, colors[N-1][j].G, colors[N-1][j].B);
//							glVertex3f(x(KwJed[i][j].u, KwJed[i][j].v), y(KwJed[i][j].u, KwJed[i][j].v), z(KwJed[i][j].u, KwJed[i][j].v));
//							glColor3f(colors[N-1][j + 1].R, colors[N-1][j + 1].G, colors[N-1][j + 1].B);
//							glVertex3f(x(KwJed[N-1][j + 1].u, KwJed[N-1][j + 1].v), y(KwJed[N-1][j + 1].u, KwJed[N-1][j + 1].v), z(KwJed[N-1][j + 1].u, KwJed[N-1][j + 1].v));
//							glColor3f(colors[i + 1][j + 1].R, colors[i + 1][j + 1].G, colors[i + 1][j + 1].B);
//							glVertex3f(x(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), y(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), z(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v));
//
//						}
//						else
//						{
//							if (i==0 && j==0)
//							{
//								glColor3f(colors[i][j].R, colors[i][j].G, colors[i][j].B);
//								glVertex3f(x(KwJed[i][j].u, KwJed[i][j].v), y(KwJed[i][j].u, KwJed[i][j].v), z(KwJed[i][j].u, KwJed[i][j].v));
//								glColor3f(colors[i + 1][j].R, colors[i + 1][j].G, colors[i + 1][j].B);
//								glVertex3f(x(KwJed[i + 1][j].u, KwJed[i + 1][j].v), y(KwJed[i + 1][j].u, KwJed[i + 1][j].v), z(KwJed[i + 1][j].u, KwJed[i + 1][j].v));
//								glColor3f(colors[i + 1][j + 1].R, colors[i + 1][j + 1].G, colors[i + 1][j + 1].B);
//								glVertex3f(x(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), y(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), z(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v));
//
//								glColor3f(colors[i][j].R, colors[i][j].G, colors[i][j].B);
//								glVertex3f(x(KwJed[i][j].u, KwJed[i][j].v), y(KwJed[i][j].u, KwJed[i][j].v), z(KwJed[i][j].u, KwJed[i][j].v));
//								glColor3f(colors[i][j + 1].R, colors[i][j + 1].G, colors[i][j + 1].B);
//								glVertex3f(x(KwJed[i][j + 1].u, KwJed[i][j + 1].v), y(KwJed[i][j + 1].u, KwJed[i][j + 1].v), z(KwJed[i][j + 1].u, KwJed[i][j + 1].v));
//								glColor3f(colors[i + 1][j + 1].R, colors[i + 1][j + 1].G, colors[i + 1][j + 1].B);
//								glVertex3f(x(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), y(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), z(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v));
//
//							}
//							else
//							{
//								glColor3f(colors[i][j].R, colors[i][j].G, colors[i][j].B);
//								glVertex3f(x(KwJed[i][j].u, KwJed[i][j].v), y(KwJed[i][j].u, KwJed[i][j].v), z(KwJed[i][j].u, KwJed[i][j].v));
//								glColor3f(colors[i + 1][j].R, colors[i + 1][j].G, colors[i + 1][j].B);
//								glVertex3f(x(KwJed[i + 1][j].u, KwJed[i + 1][j].v), y(KwJed[i + 1][j].u, KwJed[i + 1][j].v), z(KwJed[i + 1][j].u, KwJed[i + 1][j].v));
//								glColor3f(colors[i + 1][j + 1].R, colors[i + 1][j + 1].G, colors[i + 1][j + 1].B);
//								glVertex3f(x(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), y(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), z(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v));
//
//								glColor3f(colors[i][j].R, colors[i][j].G, colors[i][j].B);
//								glVertex3f(x(KwJed[i][j].u, KwJed[i][j].v), y(KwJed[i][j].u, KwJed[i][j].v), z(KwJed[i][j].u, KwJed[i][j].v));
//								glColor3f(colors[i][j + 1].R, colors[i][j + 1].G, colors[i][j + 1].B);
//								glVertex3f(x(KwJed[i][j + 1].u, KwJed[i][j + 1].v), y(KwJed[i][j + 1].u, KwJed[i][j + 1].v), z(KwJed[i][j + 1].u, KwJed[i][j + 1].v));
//								glColor3f(colors[i + 1][j + 1].R, colors[i + 1][j + 1].G, colors[i + 1][j + 1].B);
//								glVertex3f(x(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), y(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), z(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v));
//
//							}
//						}
//					}
					glColor3f(colors[i][j].R, colors[i][j].G, colors[i][j].B);
					glVertex3f(x(KwJed[i][j].u, KwJed[i][j].v), y(KwJed[i][j].u, KwJed[i][j].v), z(KwJed[i][j].u, KwJed[i][j].v));
					glColor3f(colors[i + 1][j].R, colors[i + 1][j].G, colors[i + 1][j].B);
					glVertex3f(x(KwJed[i + 1][j].u, KwJed[i + 1][j].v), y(KwJed[i + 1][j].u, KwJed[i + 1][j].v), z(KwJed[i + 1][j].u, KwJed[i + 1][j].v));
					glColor3f(colors[i + 1][j + 1].R, colors[i + 1][j + 1].G, colors[i + 1][j + 1].B);
					glVertex3f(x(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), y(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), z(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v));

					glColor3f(colors[i][j].R, colors[i][j].G, colors[i][j].B);
					glVertex3f(x(KwJed[i][j].u, KwJed[i][j].v), y(KwJed[i][j].u, KwJed[i][j].v), z(KwJed[i][j].u, KwJed[i][j].v));
					glColor3f(colors[i][j + 1].R, colors[i][j + 1].G, colors[i][j + 1].B);
					glVertex3f(x(KwJed[i][j + 1].u, KwJed[i][j + 1].v), y(KwJed[i][j + 1].u, KwJed[i][j + 1].v), z(KwJed[i][j + 1].u, KwJed[i][j + 1].v));
					glColor3f(colors[i + 1][j + 1].R, colors[i + 1][j + 1].G, colors[i + 1][j + 1].B);
					glVertex3f(x(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), y(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v), z(KwJed[i + 1][j + 1].u, KwJed[i + 1][j + 1].v));

									   					 					
				}
				
				glEnd();
			}
		}
	}
}

/*************************************************************************************/
// Funkcja rysująca osie układu współrzędnych
void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// początek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// początek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	//  początek i koniec obrazu osi y

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
// Funkcja określająca co ma być rysowane (zawsze wywoływana gdy trzeba
// przerysować scenę)
void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszczącym

	glLoadIdentity();
	// Czyszczenie macierzy bieżącej

	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wyżej

	if (status == 1)                     // jeśli lewy klawisz myszy wcięnięty
	{
		theta += delta_x * pix2angle;    // modyfikacja kąta obrotu o kat proporcjonalny
	}                                  // do różnicy położeń kursora myszy

	glRotatef(theta, 0.0, 1.0, 0.0);  //obrót obiektu o nowy kąt


//	glRotatef(theta[0], 0.1, 0.0, 0.0);
//
//	glRotatef(theta[1], 0.0, 0.1, 0.0);
//
//	glRotatef(theta[2], 0.0, 0.0, 0.5);

	Egg(); //rysowanie jajka

	glFlush();
	// Przekazanie poleceń rysujących do wykonania

	glutSwapBuffers();
	
}
/*************************************************************************************/
// Funkcja ustalająca stan renderowania
void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszcący (wypełnienia okna) ustawiono na czarny

}
/*************************************************************************************/
// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) są
// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.
void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	pix2angle = 360.0 / (float)horizontal;  // przeliczenie pikseli na stopnie
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  określającej proporcję
	// wymiarów okna 

	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0

		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkościokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  

	glMatrixMode(GL_PROJECTION);
	// Przełączenie macierzy bieżącej na macierz projekcji 

	glLoadIdentity();
	// Czyszcznie macierzy bieżącej            

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie współczynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest określenie tak zwanej
	// przestrzeni ograniczającej pozwalającej zachować właściwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczjącej służy funkcja
	// glOrtho(...)            

	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);

	else

		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);

	glMatrixMode(GL_MODELVIEW);
	// Przełączenie macierzy bieżącej na macierz widoku modelu                                    

	glLoadIdentity();
	// Czyszcenie macierzy bieżącej

}



//void spinEgg()
//{
//
//	theta[0] -= 0.005;
//	if (theta[0] > 360.0) theta[0] -= 360.0;
//
//	theta[1] -= 0.005;
//	if (theta[1] > 360.0) theta[1] -= 360.0;
//
//	theta[2] -= 0.005;
//	if (theta[2] > 360.0) theta[2] -= 360.0;
//
//	glutPostRedisplay(); //odświeżenie zawartości aktualnego okna
//}



/*************************************************************************************/
// Funkcja "bada" stan myszy i ustawia wartości odpowiednich zmiennych globalnych

void Mouse(int btn, int state, int x, int y)
{


	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;        // przypisanie aktualnie odczytanej pozycji kursora
							 // jako pozycji poprzedniej
		status = 1;          // wcięnięty został lewy klawisz myszy
	}
	else

		status = 0;          // nie został wcięnięty żaden klawisz
}

/*************************************************************************************/
// Funkcja "monitoruje" położenie kursora myszy i ustawia wartości odpowiednich
// zmiennych globalnych

void Motion(GLsizei x, GLsizei y)
{

	delta_x = x - x_pos_old;     // obliczenie różnicy położenia kursora myszy

	x_pos_old = x;            // podstawienie bieżącego położenia jako poprzednie

	glutPostRedisplay();     // przerysowanie obrazu sceny
}


void keys(unsigned char key, int x, int y)
{
	if (key == '1')
	{
		std::cout << "1\n";
		model = 1;
	}
	if (key == '2')
	{
		std::cout << "2\n";
		model = 2;
	}
	if (key == '3')
	{
		std::cout << "3\n";
		model = 3;
	}
	RenderScene(); // przerysowanie obrazu sceny
}

/*************************************************************************************/
// Główny punkt wejścia programu. Program działa w trybie konsoli
void main(int argc, char* argv[])
{
	srand(time(NULL));
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			colors[i][j].R = (float)(rand() % 100) / 100.0f;
			colors[i][j].G = (float)(rand() % 100) / 100.0f;
			colors[i][j].B = (float)(rand() % 100) / 100.0f;

			//std::cout << "R: " << colors[i][j].R << ", G: " << colors[i][j].G << ", B: " << colors[i][j].B << "\n";
		}
	}


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300);

	glutInit(&argc, argv);
	glutCreateWindow("Jajko");
	glutKeyboardFunc(keys);

	glutDisplayFunc(RenderScene);
	// Określenie, że funkcja RenderScene będzie funkcją zwrotną
	// (callback function).  Bedzie ona wywoływana za każdym razem
	// gdy zajdzie potrzba przeryswania okna 

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
	// zazmiany rozmiaru okna      

	//glutIdleFunc(spinEgg);

	glutMouseFunc(Mouse);
	// Ustala funkcję zwrotną odpowiedzialną za badanie stanu myszy

	glutMotionFunc(Motion);
	// Ustala funkcję zwrotną odpowiedzialną za badanie ruchu myszy

	MyInit();
	// Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przystąpieniem do renderowania 

	glEnable(GL_DEPTH_TEST);
	// Włączenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}

/*************************************************************************************/