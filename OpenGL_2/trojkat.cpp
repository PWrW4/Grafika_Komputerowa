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
//	glColor3f(1.0f, 0.0f, 0.0f); // wierzcho³ek czerwony
//	glVertex2f(0, 0.5);
//	glColor3f(0.0f, 1.0f, 0.0f); // wierzcho³ek zielony
//	glVertex2f(-0.5, 0);
//	glColor3f(0.0f, 0.0f, 1.0f); // wierzcho³ek niebieski
//	glVertex2f(0.5, 0);
//
//	glEnd();
//
//	glFlush();
//}
//
///*************************************************************************************/
//
//// Funkcja ustalaj¹ca stan renderowania
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
//// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli
//
//
//
//void main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitWindowSize(640, 500);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
//	// Ustawienie trybu wyœwietlania
//	// GLUT_SINGLE - pojedynczy bufor wyœwietlania
//	// GLUT_RGBA - model kolorów RGB
//
//	glutCreateWindow("Triangle");
//	// Utworzenie okna i okreœlenie treœci napisu w nag³ówku okna
//
//
//	glutDisplayFunc(RenderScene);
//	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹ (callback)
//	// Biblioteka GLUT bêdzie wywo³ywa³a t¹ funkcjê za ka¿dym razem, gdy
//	// trzeba bêdzie przerysowaæ okno
//
//	MyInit();
//	// Funkcja MyInit (zdefiniowana powy¿ej) wykonuje wszelkie
//	// inicjalizacje konieczne przed przyst¹pieniem do renderowania
//
//	glutMainLoop();
//	// Funkcja uruchamia szkielet biblioteki GLUT
//
//}
//
///**************************************************************************************/
