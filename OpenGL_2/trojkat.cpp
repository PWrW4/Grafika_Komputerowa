//#include <Windows.h>
//#include <GL//GL.h>
//#include <GL/glut.h>
//
//void RenderScene(void)
//{
//
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glBegin(GL_TRIANGLES);
//
//	glColor3f(1.0f, 0.0f, 0.0f); // wierzcho�ek czerwony
//	glVertex2f(0, 0.5);
//	glColor3f(0.0f, 1.0f, 0.0f); // wierzcho�ek zielony
//	glVertex2f(-0.5, 0);
//	glColor3f(0.0f, 0.0f, 1.0f); // wierzcho�ek niebieski
//	glVertex2f(0.5, 0);
//
//	glEnd();
//
//	glFlush();
//}
//
///*************************************************************************************/
//
//// Funkcja ustalaj�ca stan renderowania
//
//
//void MyInit(void)
//{
//
//	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//}
//
//
//
///*************************************************************************************/
//
//// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli
//
//
//
//void main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitWindowSize(640, 500);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
//	// Ustawienie trybu wy�wietlania
//	// GLUT_SINGLE - pojedynczy bufor wy�wietlania
//	// GLUT_RGBA - model kolor�w RGB
//
//	glutCreateWindow("Triangle");
//	// Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna
//
//
//	glutDisplayFunc(RenderScene);
//	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
//	// Biblioteka GLUT b�dzie wywo�ywa�a t� funkcj� za ka�dym razem, gdy
//	// trzeba b�dzie przerysowa� okno
//
//	MyInit();
//	// Funkcja MyInit (zdefiniowana powy�ej) wykonuje wszelkie
//	// inicjalizacje konieczne przed przyst�pieniem do renderowania
//
//	glutMainLoop();
//	// Funkcja uruchamia szkielet biblioteki GLUT
//
//}
//
///**************************************************************************************/
