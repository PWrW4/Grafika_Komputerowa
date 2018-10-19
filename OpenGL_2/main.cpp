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
//	glColor3f(1.0f, 0.0f, 0.0f); // wierzchołek czerwony
//	glVertex2f(0, 0.5);
//	glColor3f(0.0f, 1.0f, 0.0f); // wierzchołek zielony
//	glVertex2f(-0.5, 0);
//	glColor3f(0.0f, 0.0f, 1.0f); // wierzchołek niebieski
//	glVertex2f(0.5, 0);
//
//	glEnd();
//
//	glFlush();
//}
//
///*************************************************************************************/
//
//// Funkcja ustalająca stan renderowania
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
//// Główny punkt wejścia programu. Program działa w trybie konsoli
//
//
//
//void main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitWindowSize(640, 500);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
//	// Ustawienie trybu wyświetlania
//	// GLUT_SINGLE - pojedynczy bufor wyświetlania
//	// GLUT_RGBA - model kolorów RGB
//
//	glutCreateWindow("Triangle");
//	// Utworzenie okna i określenie treści napisu w nagłówku okna
//
//
//	glutDisplayFunc(RenderScene);
//	// Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
//	// Biblioteka GLUT będzie wywoływała tą funkcję za każdym razem, gdy
//	// trzeba będzie przerysować okno
//
//	MyInit();
//	// Funkcja MyInit (zdefiniowana powyżej) wykonuje wszelkie
//	// inicjalizacje konieczne przed przystąpieniem do renderowania
//
//	glutMainLoop();
//	// Funkcja uruchamia szkielet biblioteki GLUT
//
//}
//
///**************************************************************************************/
