#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <ctime>
#include <Windows.h>



void drawPoint(float x, float y, float size)
{
	glPointSize(size);
	glBegin(GL_POINTS);	
	glVertex2f(x, y);
	glEnd();
}

void RenderScene(void)
{
	int n = 10000;
	glClear(GL_COLOR_BUFFER_BIT);

	float x = 10.0f;
	float y = 10.0f;



	for (int i = 0;i<100;i++)
	{
		drawPoint(x, y, 1.0f);
		x++;
	}

	glFlush();
}


void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor okna wn�trza okna - ustawiono na szary
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szeroko�� i wysoko�� okna) s�
// przekazywane do funkcji za ka�dym razem, gdy zmieni si� rozmiar okna
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio okre�laj�cej proporcj� wymiar�w okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0
		vertical = 1;
	
	glutInitWindowSize(600, 400);

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna urz�dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Okre�lenie uk�adu wsp�rz�dnych obserwatora

	glLoadIdentity();
	// Okre�lenie przestrzeni ograniczaj�cej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest
	// okre�lenie okna obserwatora.
	// Pozwala to zachowa� w�a�ciwe proporcje rysowanego obiektu
	// Do okre�lenia okna obserwatora s�u�y funkcja glOrtho(...)

	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okre�lenie uk�adu wsp�rz�dnych    
	glLoadIdentity();
}


void main(int argc, char* argv[])
{

	srand(time(NULL));

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wy�wietlania
	// GLUT_SINGLE - pojedynczy bufor wy�wietlania
	// GLUT_RGBA - model kolor�w RGB

	glutInit(&argc, argv);
	glutCreateWindow("Dywan Sierpi�skiego");
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
	// inicjalizacje konieczne przed przyst�pieniem do renderowania

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie
//
//// Porady dotycz�ce rozpoczynania pracy:
//   1. U�yj okna Eksploratora rozwi�za�, aby doda� pliki i zarz�dza� nimi
//   2. U�yj okna programu Team Explorer, aby nawi�za� po��czenie z kontrol� �r�d�a
//   3. U�yj okna Dane wyj�ciowe, aby sprawdzi� dane wyj�ciowe kompilacji i inne komunikaty
//   4. U�yj okna Lista b��d�w, aby zobaczy� b��dy
//   5. Wybierz pozycj� Projekt > Dodaj nowy element, aby utworzy� nowe pliki kodu, lub wybierz pozycj� Projekt > Dodaj istniej�cy element, aby doda� istniej�ce pliku kodu do projektu
//   6. Aby w przysz�o�ci ponownie otworzy� ten projekt, przejd� do pozycji Plik > Otw�rz > Projekt i wybierz plik sln