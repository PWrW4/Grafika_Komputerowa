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

const double MOJE_PI = 3.14159265359;
int model = 2;
const int N = 20;
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
	point2 kwadratJednostkowy[N][N];
	//double u = 0, v = 0;
	double webLevel = 1.0f / N;

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			kwadratJednostkowy[i][j].u = (1.0f / N) * i;
			kwadratJednostkowy[i][j].v = (1.0f / N) * j;

			//std::cout << "u: " << kwadratJednostkowy[i][j].u << ", v: " << kwadratJednostkowy[i][j].v << "\n";
		}
		//std::cout << "\n";
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
				//std::cout << "u: " << kwadratJednostkowy[i][j].u << ", v: " << kwadratJednostkowy[i][j].v << "\n";
				//glVertex2f(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v); //punkty płaszczyzny dziedziny parametrycznej
				glVertex3f(x(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v), y(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v), z(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v));
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
					glVertex3f(z(kwadratJednostkowy[i - 1][j].u, kwadratJednostkowy[i][j].v), y(kwadratJednostkowy[i - 1][j].u, kwadratJednostkowy[i][j].v), x(kwadratJednostkowy[i - 1][j].u, kwadratJednostkowy[i][j].v));
				else
					glVertex3f(z(kwadratJednostkowy[N - 1][j].u, kwadratJednostkowy[i][j].v), y(kwadratJednostkowy[N - 1][j].u, kwadratJednostkowy[i][j].v), x(kwadratJednostkowy[N - 1][j].u, kwadratJednostkowy[i][j].v));
				glVertex3f(z(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v), y(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v), x(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v));

				if (i - 1 >= 0)
					glVertex3f(z(kwadratJednostkowy[i - 1][j].u, kwadratJednostkowy[i][j].v), y(kwadratJednostkowy[i - 1][j].u, kwadratJednostkowy[i][j].v), x(kwadratJednostkowy[i - 1][j].u, kwadratJednostkowy[i][j].v));
				else
					glVertex3f(z(kwadratJednostkowy[N - 1][j].u, kwadratJednostkowy[i][j].v), y(kwadratJednostkowy[N - 1][j].u, kwadratJednostkowy[i][j].v), x(kwadratJednostkowy[N - 1][j].u, kwadratJednostkowy[i][j].v));
				if (j - 1 >= 0)
					glVertex3f(z(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j - 1].v), y(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j - 1].v), x(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j - 1].v));
				else
					glVertex3f(z(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][N - 1].v), y(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][N - 1].v), x(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][N - 1].v));

				if (j - 1 >= 0)
					glVertex3f(z(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j - 1].v), y(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j - 1].v), x(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j - 1].v));
				else
					glVertex3f(z(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][N - 1].v), y(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][N - 1].v), x(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][N - 1].v));

				glVertex3f(z(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v), y(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v), x(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v));
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
				glColor3f(colors[i][j].R, colors[i][j].G, colors[i][j].B);

				glBegin(GL_TRIANGLES);
				glVertex3f(x(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v), y(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v), z(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v));
				glVertex3f(x(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v), y(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v), z(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v));
				glVertex3f(x(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v), y(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v), z(kwadratJednostkowy[i][j].u, kwadratJednostkowy[i][j].v));
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

	Egg(); //rysowanie jajka

	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wyżej

	glFlush();
	// Przekazanie poleceń rysujących do wykonania

	glutSwapBuffers();
	//

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


void keys(unsigned char key, int x, int y)
{
	if (key == '1')
	{
		std::cout << "p\n";
		model = 1;
	}
	if (key == '2')
	{
		std::cout << "w\n";
		model = 2;
	}
	if (key == '3')
	{
		std::cout << "s\n";
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

	MyInit();
	// Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przystąpieniem do renderowania 

	glEnable(GL_DEPTH_TEST);
	// Włączenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}

/*************************************************************************************/