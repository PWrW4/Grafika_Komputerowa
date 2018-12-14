#define _CRT_SECURE_NO_DEPRECATE
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>
#include <math.h>
using namespace std;
typedef float point3[3];


static GLfloat viewer[] = { 0.0, 0.0, 10.0 };
// inicjalizacja po³o¿enia obserwatora

static GLfloat thetaArr[] = { 0.0, 0.0, 0.0 }; // trzy k¹ty obrotu
static GLfloat theta = 0.0;   // k¹t obrotu obiektu
static GLfloat alfa = 0.0;
static GLfloat pix2angle;     // przelicznik pikseli na stopnie

static GLint status = 0;       // stan klawiszy myszy
							   // 0 - nie naciœniêto ¿adnego klawisza
							   // 1 - naciœniêty zostaæ lewy klawisz
							   // 2 - wcisniety prawy klawisz

static int x_pos_old = 0;       // poprzednia pozycja kursora myszy
static int y_pos_old = 0;
static int scroll_old = 0;
static int delta_x = 0;        // ró¿nica pomiêdzy pozycj¹ bie¿¹c¹
static int delta_y = 0;
static int delta_scroll = 0;

const int n = 80;


double tabTekstury[n][n][2];

bool mode1 = true;


void RenderScene(void);

// i poprzedni¹ kursora myszy

/*************************************************************************************/

void spinEgg()
{

	thetaArr[0] -= 0.5;
	if (thetaArr[0] > 360.0) thetaArr[0] -= 360.0;

	thetaArr[1] -= 0.5;
	if (thetaArr[1] > 360.0) thetaArr[1] -= 360.0;

	thetaArr[2] -= 0.5;
	if (thetaArr[2] > 360.0) thetaArr[2] -= 360.0;

	glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
}



/*************************************************************************************/
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

			tabTekstury[i][j][0]=u;
			tabTekstury[i][j][1]=v;

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
			if (i<n/2)
			{
				glBegin(GL_TRIANGLES);
				glNormal3fv(vektorNorm[i][j + 1]);
				glTexCoord2f(tabTekstury[i][j + 1][0], tabTekstury[i][j + 1][1]);
				glVertex3fv(vectors3d[i][j + 1]);

				glNormal3fv(vektorNorm[i + 1][j]);
				glTexCoord2f(tabTekstury[i + 1][j][0], tabTekstury[i + 1][j][1]);
				glVertex3fv(vectors3d[i + 1][j]);

				glNormal3fv(vektorNorm[i + 1][j + 1]);
				glTexCoord2f(tabTekstury[i + 1][j + 1][0], tabTekstury[i + 1][j + 1][1]);
				glVertex3fv(vectors3d[i + 1][j + 1]);
				glEnd();


				glBegin(GL_TRIANGLES);
				glNormal3fv(vektorNorm[i][j]);
				glTexCoord2f(tabTekstury[i][j][0], tabTekstury[i][j][1]);
				glVertex3fv(vectors3d[i][j]);

				glNormal3fv(vektorNorm[i + 1][j]);
				glTexCoord2f(tabTekstury[i + 1][j][0], tabTekstury[i + 1][j][1]);
				glVertex3fv(vectors3d[i + 1][j]);

				glNormal3fv(vektorNorm[i][j + 1]);
				glTexCoord2f(tabTekstury[i][j + 1][0], tabTekstury[i][j + 1][1]);
				glVertex3fv(vectors3d[i][j + 1]);
				glEnd();
			}
			else
			{
			glBegin(GL_TRIANGLES);
			glNormal3fv(vektorNorm[i + 1][j + 1]);
			glTexCoord2f(tabTekstury[i + 1][j + 1][0], tabTekstury[i + 1][j + 1][1]);
			glVertex3fv(vectors3d[i + 1][j + 1]);



			glNormal3fv(vektorNorm[i + 1][j]);
			glTexCoord2f(tabTekstury[i+1][j][0], tabTekstury[i+1][j][1]);
			glVertex3fv(vectors3d[i + 1][j]);

			glNormal3fv(vektorNorm[i][j + 1]);
			glTexCoord2f(tabTekstury[i][j + 1][0], tabTekstury[i][j + 1][1]);
			glVertex3fv(vectors3d[i][j + 1]);

			glEnd();


			glBegin(GL_TRIANGLES);
			glNormal3fv(vektorNorm[i][j + 1]);
			glTexCoord2f(tabTekstury[i][j + 1][0], tabTekstury[i][j + 1][1]);
			glVertex3fv(vectors3d[i][j + 1]);
					   
			glNormal3fv(vektorNorm[i + 1][j]);
			glTexCoord2f(tabTekstury[i+1][j][0], tabTekstury[i+1][j][1]);
			glVertex3fv(vectors3d[i + 1][j]);

			glNormal3fv(vektorNorm[i][j]);
			glTexCoord2f(tabTekstury[i][j][0], tabTekstury[i][j][1]);
			glVertex3fv(vectors3d[i][j]);

			glEnd();
			}


			

		}
	}
}
void Mouse(int btn, int state, int x, int y)
{


	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;        // przypisanie aktualnie odczytanej pozycji kursora
		y_pos_old = y;
		// jako pozycji poprzedniej
		status = 1;          // wciêniêty zosta³ lewy klawisz myszy
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		scroll_old = y;
		// jako pozycji poprzedniej
		status = 2;          // wciêniêty zosta³ prawy klawisz myszy
	}
	else
		status = 0;          // nie zosta³ wciêniêty ¿aden klawisz
}



void keys(unsigned char key, int x, int y)
{
	if (key == '1') mode1 = !mode1;

	RenderScene(); // przerysowanie obrazu sceny
}
/*************************************************************************************/

// Funkcja "monitoruje" po³o¿enie kursora myszy i ustawia wartoœci odpowiednich
// zmiennych globalnych

void Motion(GLsizei x, GLsizei y)
{
	if (status == 1) {
		delta_x = x - x_pos_old;     // obliczenie ró¿nicy po³o¿enia kursora myszy
		delta_y = y - y_pos_old;
		x_pos_old = x;            // podstawienie bie¿¹cego po³o¿enia jako poprzednie
		y_pos_old = y;
	}
	else if (status == 2) {
		delta_scroll = y - scroll_old;
		scroll_old = y;
	}
	glutPostRedisplay();     // przerysowanie obrazu sceny
}

/*************************************************************************************/


// Funkcja rysuj¹ca osie uk³adu wspó?rz?dnych



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

// Funkcja okreœlaj¹ca co ma byæ rysowane (zawsze wywo³ywana, gdy trzeba
// przerysowaæ scenê)



void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glLoadIdentity();
	// Czyszczenie macierzy bie??cej
	float scroll = delta_scroll * pix2angle*0.07;
	if (status == 2 && ((viewer[2] <= 6 && scroll > 0) || (scroll < 0 && viewer[2] >= 20) || (viewer[2] > 6 && viewer[2] < 20))) {

		viewer[2] += scroll;
	}
	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	// Zdefiniowanie po³o¿enia obserwatora


	if (status == 1)                     // jeœli lewy klawisz myszy wciêniêty
	{
		theta += delta_x * pix2angle;    // modyfikacja k¹ta obrotu o kat proporcjonalny
		alfa += delta_y * pix2angle;

	}

	glRotatef(thetaArr[0], 1.0, 0.0, 0.0);

	glRotatef(thetaArr[1], 0.0, 1.0, 0.0);

	glRotatef(thetaArr[2], 0.0, 0.0, 1.0);
	glRotatef(theta, 0.0, 1.0, 0.0);  //obrót obiektu o nowy k¹t
	glRotatef(alfa, 1.0, 0.0, 0.0);  //obrót obiektu o nowy k¹t



	glColor3f(1.0f, 23.0f, 1.0f);
	// Ustawienie koloru rysowania na bia³y

	Egg();
	// Narysowanie czajnika

	Axes();

	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania

	glutSwapBuffers();



}
/*************************************************************************************/

// Funkcja ustalaj¹ca stan renderowania

/*************************************************************************************/
 // Funkcja wczytuje dane obrazu zapisanego w formacie TGA w pliku o nazwie
 // FileName, alokuje pamiêæ i zwraca wskaŸnik (pBits) do bufora w którym
 // umieszczone s¹ dane.
 // Ponadto udostêpnia szerokoœæ (ImWidth), wysokoœæ (ImHeight) obrazu
 // tekstury oraz dane opisuj¹ce format obrazu wed³ug specyfikacji OpenGL
 // (ImComponents) i (ImFormat).
 // Jest to bardzo uproszczona wersja funkcji wczytuj¹cej dane z pliku TGA.
 // Dzia³a tylko dla obrazów wykorzystuj¹cych 8, 24, or 32 bitowy kolor.
 // Nie obs³uguje plików w formacie TGA kodowanych z kompresj¹ RLE.
/*************************************************************************************/


GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat)
{

	/*************************************************************************************/

	// Struktura dla nag³ówka pliku  TGA


#pragma pack(1)           
	typedef struct
	{
		GLbyte    idlength;
		GLbyte    colormaptype;
		GLbyte    datatypecode;
		unsigned short    colormapstart;
		unsigned short    colormaplength;
		unsigned char     colormapdepth;
		unsigned short    x_orgin;
		unsigned short    y_orgin;
		unsigned short    width;
		unsigned short    height;
		GLbyte    bitsperpixel;
		GLbyte    descriptor;
	}TGAHEADER;
#pragma pack(8)

	FILE *pFile;
	TGAHEADER tgaHeader;
	unsigned long lImageSize;
	short sDepth;
	GLbyte    *pbitsperpixel = NULL;


	/*************************************************************************************/

	// Wartoœci domyœlne zwracane w przypadku b³êdu

	*ImWidth = 0;
	*ImHeight = 0;
	*ImFormat = GL_BGR_EXT;
	*ImComponents = GL_RGB8;

	pFile = fopen(FileName, "rb");
	if (pFile == NULL)
		return NULL;

	/*************************************************************************************/
	// Przeczytanie nag³ówka pliku 


	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);


	/*************************************************************************************/

	// Odczytanie szerokoœci, wysokoœci i g³êbi obrazu

	*ImWidth = tgaHeader.width;
	*ImHeight = tgaHeader.height;
	sDepth = tgaHeader.bitsperpixel / 8;


	/*************************************************************************************/
	// Sprawdzenie, czy g³êbia spe³nia za³o¿one warunki (8, 24, lub 32 bity)

	if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
		return NULL;

	/*************************************************************************************/

	// Obliczenie rozmiaru bufora w pamiêci


	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;


	/*************************************************************************************/

	// Alokacja pamiêci dla danych obrazu


	pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));

	if (pbitsperpixel == NULL)
		return NULL;

	if (fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
	{
		free(pbitsperpixel);
		return NULL;
	}


	/*************************************************************************************/

	// Ustawienie formatu OpenGL


	switch (sDepth)

	{

	case 3:

		*ImFormat = GL_BGR_EXT;

		*ImComponents = GL_RGB8;

		break;

	case 4:

		*ImFormat = GL_BGRA_EXT;

		*ImComponents = GL_RGBA8;

		break;

	case 1:

		*ImFormat = GL_LUMINANCE;

		*ImComponents = GL_LUMINANCE8;

		break;

	};



	fclose(pFile);



	return pbitsperpixel;

}

/*************************************************************************************/

void MyInit(void)
{

	/*************************************************************************************/

// Zmienne dla obrazu tekstury



	GLbyte *pBytes;
	GLint ImWidth, ImHeight, ImComponents;
	GLenum ImFormat;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLfloat mat_ambient[] = { 1.0,1.0, 1.0, 1 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess = { 20.0 };
	GLfloat light_position[] = { 0.0, 0.0, 30.0, 1.0 };
	GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
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

	glShadeModel(GL_SMOOTH); // w³aczenie ³agodnego cieniowania
	glEnable(GL_LIGHTING);   // w³aczenie systemu oœwietlenia sceny
	glEnable(GL_LIGHT0);     // w³¹czenie Ÿród³a o numerze 0
	glEnable(GL_DEPTH_TEST); // w³¹czenie mechanizmu z-bufora

	/*************************************************************************************/

// Teksturowanie bêdzie prowadzone tyko po jednej stronie œciany

	glEnable(GL_CULL_FACE);

	/*************************************************************************************/

	//  Przeczytanie obrazu tekstury z pliku o nazwie tekstura.tga

	pBytes = LoadTGAImage("N1_t.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);

	/*************************************************************************************/

   // Zdefiniowanie tekstury 2-D

	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);

	/*************************************************************************************/

	// Zwolnienie pamiêci

	free(pBytes);

	/*************************************************************************************/

	// W³¹czenie mechanizmu teksturowania

	glEnable(GL_TEXTURE_2D);

	/*************************************************************************************/

	// Ustalenie trybu teksturowania

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	/*************************************************************************************/

	// Okreœlenie sposobu nak³adania tekstur

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	pix2angle = 360.0 / (float)horizontal;

	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej
	cout << vertical << " horizontal " << horizontal << endl;

	GLdouble aspect = (GLdouble)horizontal / vertical;

	gluPerspective(70, (float)aspect, 1.0, 30.0);
	// Ustawienie parametrów dla rzutu perspektywicznego


	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœci okna okna widoku (viewport) w zale¿noœci
	// relacji pomiêdzy wysokoœci¹ i szerokoœci¹ okna

	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu 

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej

}

/*************************************************************************************/

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli



void main(void)
{
	char *myargv[1];
	int myargc = 1;
	myargv[0] = _strdup("Myappname");
	glutInit(&myargc, myargv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(1000, 1000);

	glutCreateWindow("Oœwietlenie jajka");

	//glutIdleFunc(spinEgg);

	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹
	// (callback function).  Bêdzie ona wywo³ywana za ka¿dym razem
	// gdy zajdzie potrzeba przerysowania okna


	glutMouseFunc(Mouse);

	glutKeyboardFunc(keys);

	glutMotionFunc(Motion);

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹
	// za zmiany rozmiaru okna                      


	MyInit();
	// Funkcja MyInit() (zdefiniowana powy¿ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst¹pieniem do renderowania

	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania niewidocznych elementów sceny

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}
