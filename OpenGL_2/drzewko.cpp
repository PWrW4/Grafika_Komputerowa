#include <stdio.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <time.h>


int n;
double zoomFactor;
typedef float point2[2];
GLsizei horizontalSize;
GLsizei verticalSize;

void drawTree() {


	//deklaracja odwzorawan afinicznych
	float f1[6] = { -0.67, -0.02, 0.0, -0.18, 0.81, 10.0 };
	float f2[6] = { 0.4, 0.4, 0.0, -0.1, 0.4, 0.0 };
	float f3[6] = { -0.4, -0.4, 0.0, -0.1, 0.4, 0.0 };
	float f4[6] = { -0.1, 0.0, 0.0, 0.44, 0.44, -2.0 };

	point2 point, newPoint;

	//losujemy polozenie pierwszego punktu
	point[0] = rand() % 90;
	point[1] = rand() % 90;

	// Ustawienie aktualnego koloru rysowania na zielony
	glColor3f(0.0f, 1.0f, 0.0f);

	//rysujemy pierwszy punkt
	glBegin(GL_POINTS);
	glVertex2fv(point);
	glEnd();


	int rnd;

	for (int i = 0; i < n; i++) {

		//losujemy numer odwzorowania z ktorego bedziemy teraz korzystac
		rnd = rand() % 4;


		//w zaleznosci od wylosowanego odwzorowania wyliczamy nowe wspolrzedne dla nowego punktu 
		if (rnd == 0) {
			newPoint[0] = f1[0] * point[0] + f1[1] * point[1] + f1[2];
			newPoint[1] = f1[3] * point[0] + f1[4] * point[1] + f1[5];
		}
		else if (rnd == 1) {
			newPoint[0] = f2[0] * point[0] + f2[1] * point[1] + f2[2];
			newPoint[1] = f2[3] * point[0] + f2[4] * point[1] + f2[5];
		}
		else if (rnd == 2) {
			newPoint[0] = f3[0] * point[0] + f3[1] * point[1] + f3[2];
			newPoint[1] = f3[3] * point[0] + f3[4] * point[1] + f3[5];
		}
		else {
			newPoint[0] = f4[0] * point[0] + f4[1] * point[1] + f4[2];
			newPoint[1] = f4[3] * point[0] + f4[4] * point[1] + f4[5];
		}


		point[0] = newPoint[0];
		point[1] = newPoint[1];


		//rysujemy nastepny punkt
		glBegin(GL_POINTS);
		glVertex2fv(point);
		glEnd();

	}
}



// Funkcaja okre�laj�ca, co ma by� rysowane
// (zawsze wywo�ywana, gdy trzeba przerysowa� scen�)
//sluzy takze do kontroli zachowania proporcji rysowanych obiekt�w niezale�nie od rozmiar�w okna graficznego
void RenderScene(void)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio okre�laj�cej proporcj� wymiar�w okna

	if (verticalSize == 0)
		// Zabezpieczenie pzred dzieleniem przez 0
		verticalSize = 1;


	glViewport(0, 0, horizontalSize, verticalSize);
	// Ustawienie wielko�ciokna okna urz�dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontalSize, verticalSize)

	glMatrixMode(GL_PROJECTION);
	// Okre�lenie uk�adu wsp�rz�dnych obserwatora

	glLoadIdentity();
	// Okre�lenie przestrzeni ograniczaj�cej

	AspectRatio = (GLfloat)horizontalSize / (GLfloat)verticalSize;
	// Wyznaczenie wsp�czynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest
	// okre�lenie okna obserwatora.
	// Pozwala to zachowa� w�a�ciwe proporcje rysowanego obiektu
	// Do okre�lenia okna obserwatora s�u�y funkcja glOrtho(...)
	if (horizontalSize <= verticalSize)

		glOrtho(-100.0, 100, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);

	else

		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);


	glMatrixMode(GL_MODELVIEW);
	// Okre�lenie uk�adu wsp�rz�dnych     

	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym

	drawTree();
	//wywolanie rysowania dla wyzej ustawionych parametrow

	glMatrixMode(GL_PROJECTION);
	// Okre�lenie uk�adu wsp�rz�dnych obserwatora

	glLoadIdentity();


	glMatrixMode(GL_MODELVIEW);
	// Okre�lenie uk�adu wsp�rz�dnych     

	glLoadIdentity();


	drawTree();
	//wywolanie rysowania dla wyzej ustawionych parametrow

	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania
}


void MyInit(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wn�trza okna - ustawiono na szary
}


void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szeroko�� i wysoko�� okna) s�
// przekazywane do funkcji za ka�dym razem, gdy zmieni si� rozmiar okna
{
	verticalSize = vertical;
	horizontalSize = horizontal;
	//zapisujemy je wtedy do zmiennych globalnych, aby funkcja rysujaca mogla z nich skorzystac


	glutPostRedisplay();
	//i wywolujemy ponowne renderowanie
}



void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	n = 10000;
	//ustawia liczbe punktow do narysowania

	zoomFactor = 1.2;
	//ustawia startowy wspolczynnik powiekszenia; dla 1 - brak powiekszenia

	srand(time(NULL));
	//inicjalizacja dla funkcji rand


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wy�wietlania
	// GLUT_SINGLE - pojedynczy bufor wy�wietlania
	// GLUT_RGBA - model kolor�w RGB

	glutCreateWindow("Zadanie domowe 3 z lab2");
	// Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
	// Biblioteka GLUT b�dzie wywo�ywa�a t� funkcj� za ka�dym razem, gdy
	// trzeba b�dzie przerysowa� okno

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn� za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy�ej) wykonuje wszelkie 
	// inicjalizacje konieczneprzed przyst�pieniem do renderowania


	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}