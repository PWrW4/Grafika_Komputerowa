//#include <iostream>
//#include <GL/glut.h>
//#include <GL/gl.h>
//#include <ctime>
//
//
//
//void rysujKwadraty(float a, float x, float y, int poz, int per) //a-d³ugoœæ boku, x i y-punkty rysowania pocz¹tku dywanu, poz-g³êbokoœæ, per-perturbacje
//{
//
//	if (poz > 0)
//	{
//		float A = a / 3.0f;
//
//		rysujKwadraty(A, x, y, poz - 1, per);
//		rysujKwadraty(A, x + A, y, poz - 1, per);
//		rysujKwadraty(A, x + 2.0f *A, y, poz - 1, per);
//
//		rysujKwadraty(A, x, y - A, poz - 1, per);
//		//rysujKwadraty(A, x + A, y - A, poz-1);//œrodkowy wyrzucamy
//		rysujKwadraty(A, x + 2.0f *A, y - A, poz - 1, per);
//
//		rysujKwadraty(A, x, y - 2.0f * A, poz - 1, per);
//		rysujKwadraty(A, x + A, y - 2.0f * A, poz - 1, per);
//		rysujKwadraty(A, x + 2.0f *A, y - 2.0f * A, poz - 1, per);
//	}
//	else
//	{
//		float xr = (rand() % per) % 2;
//		float yr = (rand() % per) % 2;
//		float B = a / 2.0f;
//
//		glBegin(GL_POLYGON);
//		glColor3ub(rand() % 255, rand() % 255, rand() % 255);
//		glVertex2f(-1.0f*(B)+x + xr, -1.0f*(B)+y + yr);
//
//		xr = (rand() % per) % 2;
//		yr = (rand() % per) % 2;
//		glColor3ub(rand() % 255, rand() % 255, rand() % 255);
//		glVertex2f((B)+x + xr, -1.0f*(B)+y + yr);
//
//		xr = (rand() % per) % 2;
//		yr = (rand() % per) % 2;
//		glColor3ub(rand() % 255, rand() % 255, rand() % 255);
//		glVertex2f((B)+x + xr, (B)+y + yr);
//
//		xr = (rand() % per) % 2;
//		yr = (rand() % per) % 2;
//		glColor3ub(rand() % 255, rand() % 255, rand() % 255);
//		glVertex2f(-1.0f*(B)+x + xr, (B)+y + yr);
//		glEnd();
//	}
//}
//
//void RenderScene(void)
//{
//	float A = 180, x = A / 2, y = x;
//	int rejurecja = 3;
//	int perturbacje = 10;
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	rysujKwadraty(A, -1.0f*x, y, rejurecja, perturbacje);
//
//	glFlush();
//}
//
///*************************************************************************************/
//// Funkcja ustalaj¹ca stan renderowania
//void MyInit(void)
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	// Kolor okna wnêtrza okna - ustawiono na szary
//}
//
//void ChangeSize(GLsizei horizontal, GLsizei vertical)
//// Parametry horizontal i vertical (szerokoœæ i wysokoœæ okna) s¹
//// przekazywane do funkcji za ka¿dym razem, gdy zmieni siê rozmiar okna
//{
//	GLfloat AspectRatio;
//	// Deklaracja zmiennej AspectRatio okreœlaj¹cej proporcjê wymiarów okna
//
//	if (vertical == 0)
//		// Zabezpieczenie pzred dzieleniem przez 0
//		vertical = 1;
//	
//	glutInitWindowSize(600, 400);
//
//	glViewport(0, 0, horizontal, vertical);
//	// Ustawienie wielkoœciokna okna urz¹dzenia (Viewport)
//	// W tym przypadku od (0,0) do (horizontal, vertical)
//
//	glMatrixMode(GL_PROJECTION);
//	// Okreœlenie uk³adu wspó³rzêdnych obserwatora
//
//	glLoadIdentity();
//	// Okreœlenie przestrzeni ograniczaj¹cej
//
//	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
//	// Wyznaczenie wspó³czynnika proporcji okna
//
//	// Gdy okno na ekranie nie jest kwadratem wymagane jest
//	// okreœlenie okna obserwatora.
//	// Pozwala to zachowaæ w³aœciwe proporcje rysowanego obiektu
//	// Do okreœlenia okna obserwatora s³u¿y funkcja glOrtho(...)
//
//	if (horizontal <= vertical)
//		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
//	else
//		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);
//
//	glMatrixMode(GL_MODELVIEW);
//	// Okreœlenie uk³adu wspó³rzêdnych    
//	glLoadIdentity();
//}
//
///*************************************************************************************/
//// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli
//void main(int argc, char* argv[])
//{
//
//	srand(time(NULL));
//
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
//	// Ustawienie trybu wyœwietlania
//	// GLUT_SINGLE - pojedynczy bufor wyœwietlania
//	// GLUT_RGBA - model kolorów RGB
//
//	glutInit(&argc, argv);
//	glutCreateWindow("Dywan Sierpiñskiego");
//	// Utworzenie okna i okreœlenie treœci napisu w nag³ówku okna
//
//	glutDisplayFunc(RenderScene);
//	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹ (callback)
//	// Biblioteka GLUT bêdzie wywo³ywa³a t¹ funkcjê za ka¿dym razem, gdy
//	// trzeba bêdzie przerysowaæ okno
//
//	glutReshapeFunc(ChangeSize);
//	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹ za
//	// zmiany rozmiaru okna
//
//	MyInit();
//	// Funkcja MyInit (zdefiniowana powy¿ej) wykonuje wszelkie
//	// inicjalizacje konieczne przed przyst¹pieniem do renderowania
//
//	glutMainLoop();
//	// Funkcja uruchamia szkielet biblioteki GLUT
//}
//
//// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
//// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie
//
//// Porady dotycz¹ce rozpoczynania pracy:
////   1. U¿yj okna Eksploratora rozwi¹zañ, aby dodaæ pliki i zarz¹dzaæ nimi
////   2. U¿yj okna programu Team Explorer, aby nawi¹zaæ po³¹czenie z kontrol¹ Ÿród³a
////   3. U¿yj okna Dane wyjœciowe, aby sprawdziæ dane wyjœciowe kompilacji i inne komunikaty
////   4. U¿yj okna Lista b³êdów, aby zobaczyæ b³êdy
////   5. Wybierz pozycjê Projekt > Dodaj nowy element, aby utworzyæ nowe pliki kodu, lub wybierz pozycjê Projekt > Dodaj istniej¹cy element, aby dodaæ istniej¹ce pliku kodu do projektu
////   6. Aby w przysz³oœci ponownie otworzyæ ten projekt, przejdŸ do pozycji Plik > Otwórz > Projekt i wybierz plik sln