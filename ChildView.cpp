
// ChildView.cpp: Implementierung der CChildView-Klasse
//

#include "pch.h"
#include "framework.h"
#include "CoGra_Aufgabe1.h"
#include "ChildView.h"
#include "Vektor2.h"
#include <iostream>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_COGRA_DIAGONALE, &CChildView::OnCograDiagonale)
	ON_COMMAND(ID_COGRA_JULIAMENGE, &CChildView::OnCograJuliamenge)
	ON_COMMAND(ID_COGRA_MANDELBROT, &CChildView::OnCograMandelbrot)
//	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_VEKTOR_QUADRAT1, &CChildView::OnVektorQuadrat1)
	ON_COMMAND(ID_VEKTOR_ROTATION32777, &CChildView::OnVektorRotation)
	ON_COMMAND(ID_AUFGABE5_W32778, &CChildView::OnAufgabe5)
	ON_COMMAND(ID_AUFGABE5_FIGURZEICHNEN, &CChildView::OnAufgabe5Figurzeichnen)
	ON_COMMAND(ID_AUFGABE4_W32780, &CChildView::OnAufgabe4)
END_MESSAGE_MAP()



// CChildView-Meldungshandler

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // Gerätekontext zum Zeichnen
	
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein.
	
	// Rufen Sie nicht CWnd::OnPaint() zum Zeichnen von Nachrichten auf
}



void CChildView::OnCograDiagonale()
{
	CRect rc, rp;
	GetClientRect(&rc);
	GetParent()->GetWindowRect(rp);

	// rp := Rahmen vom Parentframe
	// rc := Rahmen vom Childframe
	// diff := Differenz der GUI
	int diffx = rp.Width() - rc.Width();
	int diffy = rp.Height() - rc.Height();

	// Addition der Differenz, damit Zeichenbereich auch wirklich 700*700
	GetParent()->SetWindowPos(NULL, 50, 50, 700 + diffx, 700 + diffy, SWP_SHOWWINDOW);

	UpdateWindow();

	CDC* pDC = GetDC();
	for (int i = 0; i < 700; i++) {
		pDC->SetPixel(i, i, RGB(255, 0, 0));
	}
}


void CChildView::OnCograJuliamenge()
{
	CRect rc, rp;
	GetClientRect(&rc);
	GetParent()->GetWindowRect(rp);

	// rp := Rahmen vom Parentframe
	// rc := Rahmen vom Childframe
	// diff := Differenz der GUI
	int diffx = rp.Width() - rc.Width();
	int diffy = rp.Height() - rc.Height();

	// Addition der Differenz, damit Zeichenbereich auch wirklich 700*700
	GetParent()->SetWindowPos(NULL, 50, 50, 700 + diffx, 700 + diffy, SWP_SHOWWINDOW);

	UpdateWindow();


	xdmin = -1.6; xddelta = 3.2;
	ydmin = -1.6; yddelta = 3.2;

	JuliaMalen();
}

void CChildView::OnCograMandelbrot()
{
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.


	CRect rc, rp;
	GetClientRect(&rc);
	GetParent()->GetWindowRect(rp);

	int diffx = rp.Width() - rc.Width();
	int diffy = rp.Height() - rc.Height();

	GetParent()->SetWindowPos(NULL, 50, 50, 700 + diffx, 700 + diffy, SWP_SHOWWINDOW);

	UpdateWindow();


	xdmin = -2.0; xddelta = 2.5;
	ydmin = -1.25; yddelta = 2.5;

	MandelbrotMalen();
}

bool julia = false;
bool mandelbrot = false;

void CChildView::JuliaMalen() {
	julia = true;
	mandelbrot = false;
	CDC* pDC = GetDC();
	int xp, xpmin = 0, xpdelta = 700;
	int yp, ypmin = 0, ypdelta = 700;

	double xd, yd;
	for (xp = 0; xp < 700; xp++) {
		for (yp = 0; yp < 700; yp++) {
			xd = xdmin + xp * xddelta / xpdelta;
			yd = ydmin + yp * yddelta / ypdelta;

			double a_alt = xd;
			double b_alt = yd;
			double a_neu, b_neu;
			double ab2;
			int n;
			for (n = 1; n < 1024; n++) {
				a_neu = (a_alt * a_alt) - (b_alt * b_alt) - 0.75;
				b_neu = 2 * a_alt * b_alt + 0.06;
				a_alt = a_neu;
				b_alt = b_neu;
				ab2 = (a_alt * a_alt) + (b_alt * b_alt);

				if (ab2 > 4)
					break;
			}
			if (ab2 > 4) {
				pDC->SetPixel(xp, yp, RGB(n%255, n%512, (int)ab2));
			}
			else {
				pDC->SetPixel(xp, yp, RGB(0, 0, 0));
			}
		}
	}
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
}

void CChildView::MandelbrotMalen() {
	julia = false;
	mandelbrot = true;
	CDC* pDC = GetDC();
	int xp, xpmin = 0, xpdelta = 700;
	int yp, ypmin = 0, ypdelta = 700;

	double xd, yd;
	for (xp = 0; xp < 700; xp++) {
		for (yp = 0; yp < 700; yp++) {
			xd = xdmin + xp * xddelta / xpdelta;
			yd = ydmin + yp * yddelta / ypdelta;

			double a_alt = xd;
			double b_alt = yd;
			double a_neu, b_neu;
			double ab2;
			int n;
			for (n = 1; n < 1024; n++) {
				a_neu = (a_alt * a_alt) - (b_alt * b_alt) + xd;
				b_neu = 2 * a_alt * b_alt + yd;
				a_alt = a_neu;
				b_alt = b_neu;
				ab2 = (a_alt * a_alt) + (b_alt * b_alt);

				if (ab2 > 4)
					break;
			}
			if ((a_alt * a_alt) + (b_alt * b_alt) > 4) {
				pDC->SetPixel(xp, yp, RGB(n % 255, n % 512, (int)ab2));
			}
			else {
				pDC->SetPixel(xp, yp, RGB(0, 0, 0));
			}
		}
	}
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein, und/oder benutzen Sie den Standard.
	double xd = xdmin + point.x * xddelta / 700;
	double yd = ydmin + point.y * yddelta / 700;

	xddelta = xddelta / 2;
	yddelta = yddelta / 2;

	xdmin = xd - xddelta / 2;
	ydmin = yd - yddelta / 2;

	if (julia == true) {
		JuliaMalen();
	}
	else if (mandelbrot == true) {
		MandelbrotMalen();
	}

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein, und/oder benutzen Sie den Standard.
	double xd = xdmin + point.x * xddelta / 700;
	double yd = ydmin + point.y * yddelta / 700;

	xddelta = xddelta * 2;
	yddelta = yddelta * 2;

	xdmin = xd - xddelta / 2;
	ydmin = yd - yddelta / 2;

	if (julia == true) {
		JuliaMalen();
	}
	else if (mandelbrot == true) {
		MandelbrotMalen();
	}

	CWnd::OnRButtonUp(nFlags, point);
}



void CChildView::OnVektorQuadrat1()
{
	Vektor2 Quadrat[4];
	Quadrat[0] = Vektor2(50, 50);
	Quadrat[1] = Vektor2(150, 50);
	Quadrat[2] = Vektor2(150, 150);
	Quadrat[3] = Vektor2(50, 150);

	CDC* pDC = GetDC();

	Matrix2 MT;
	MT.setTrans(10, 0);

	CRect rect;
	GetClientRect(&rect);
	
	for (int anim = 0; anim < 50; anim++) {
		pDC->FillSolidRect(rect, RGB(255, 255, 0));
		//Quadrat verschieben
		for (int i = 0; i < 4; i++) {
			Quadrat[i] = MT * Quadrat[i];
		}
		pDC->MoveTo(Quadrat[3].vek[0], Quadrat[3].vek[1]);
		//Quadrat malen
		for (int i = 0; i < 4; i++) {
			pDC->LineTo(Quadrat[i].vek[0], Quadrat[i].vek[1]);
		}
		Sleep(1000);
	}
}

void CChildView::OnVektorRotation()
{

	//Definition des Quadrats
	Vektor2 Quadrat[4];
	Quadrat[0] = Vektor2(-50, -50);
	Quadrat[1] = Vektor2(50, -50);
	Quadrat[2] = Vektor2(50, 50);
	Quadrat[3] = Vektor2(-50, 50);
	
	CDC* pDC = GetDC();

	//Ermittlung der Fenstergröße
	CRect rc;
	GetClientRect(&rc);
	int height = rc.right;
	int width = rc.bottom;

	CBrush FrameBrush(RGB(255, 255, 255));

	Matrix2 RotMat;
	RotMat.setRot(0.05235987755983);

	//Koordinatenursprung auf die Mitte des Fensters setzen
	pDC->SetViewportOrg(height/2, width/2);
	
	for (int j = 0; j < 1200; j++){
		pDC->SetViewportOrg(height/2, width/2);
		for (int i = 0; i < 4; i++) {
			Quadrat[i] = RotMat * Quadrat[i];
		}
		pDC->MoveTo(0, 0);
		pDC->MoveTo(Quadrat[0].vek[0], Quadrat[0].vek[1]);
		//Quadrat malen
		for (int i = 0; i < 4; i++) {
			pDC->LineTo(Quadrat[i].vek[0], Quadrat[i].vek[1]);
		}
		pDC->LineTo(Quadrat[0].vek[0], Quadrat[0].vek[1]);
		pDC->SetViewportOrg(0, 0);
		Sleep(1);
		pDC->FillRect(rc, &FrameBrush);
	}
}

// Achtung!!!
// Funktionsdefinitionen auch in Header-Datei übernehmen

void CChildView::GLInit(int Breite, int Hoehe, int Modus)
{
	static HDC         hdc;
	static HGLRC       hglrc;
	int         iPixelFormat;
	HWND hwnd = GetSafeHwnd();


	static PIXELFORMATDESCRIPTOR pfd =	//pfd legt das Aussehen der Szene fest
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,						//Versionsnummer
		PFD_DRAW_TO_WINDOW |	//pfd muss Windows unterstützen
		PFD_SUPPORT_OPENGL |	//pfd muss OpenGL unterstützen
		PFD_DOUBLEBUFFER ,		//Doppelpuffer wird unterstützt
		PFD_TYPE_RGBA,			//RGBA-Farbformat auswählen
		32,						//Bit-Farbtiefe
		0, 0, 0, 0, 0, 0,		//Farbbits werden ignoriert
		0,						//kein Alphapuffer
		0,						//Schiebebit ignoriert
		0,						//kein Ansammlungspuffer
		0, 0, 0, 0,				//Ansammlungsbits werden ignoriert
		16,						//16bit Z-Puffer (Tiefenpuffer)
		16,						//Masken-Puffer
		0,						//keinen Hilfs-Puffer
		PFD_MAIN_PLANE,			//Festlegung der Zeichenebene (Hauptebene)
		0,						//reserviert
		0, 0, 0					//Ebenenmasken werden ignoriert 
	};
	CDC* pDC = GetDC();
	CRect gesamt, client;
	GetWindowRect(&gesamt);
	GetClientRect(&client);
	int diff_x = gesamt.Width() - client.Width();
	int diff_y = gesamt.Height() - client.Height();
	m_height = Hoehe;
	m_width = Breite;

	switch (Modus)
	{
	case 1:  // Modus 1 -> Initialisierung

		// ---------- Fenstergröße
		GetParent()->SetWindowPos(&wndTop,
			50, 50, m_height + diff_x, m_width + diff_y, 0);
		//		GetParent()->ShowWindow(SW_NORMAL);
		GetParent()->RedrawWindow();
		// ------ Device Context
		hdc = pDC->GetSafeHdc();

		// ------ Pixelformat einstellen (OpenGL-fähig)
		iPixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, iPixelFormat, &pfd);

		// ----  Rendering-Context erstellen und zuweisen
		hglrc = wglCreateContext(hdc);
		if (hglrc == NULL) { SetWindowText(CString("Fehler beim RC !")); Sleep(2000); }
		wglMakeCurrent(hdc, hglrc);
		break;

	case 0:  // Modus 0 -> Beenden
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hglrc);

		ReleaseDC(pDC);
		break;
	}
	return;

}

void CChildView::Bunter_Einheitswuerfel()
{
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);          // grün bei z = -0.5
	glNormal3f(0, 0, -1);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);

	glColor3f(1, 0, 0);        // rot bei z = 0.5
	glNormal3f(0, 0, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	glColor3f(1, 0.75, 0.25);  // orange bei y = -0.5
	glNormal3f(0, -1, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	glColor3f(0, 0, 1);          // blau bei y = 0.5
	glNormal3f(0, 1, 0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);

	glColor3f(1, 0, 1);          // lila bei x =  0.5
	glNormal3f(-1, 0, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	glColor3f(1, 1, 0);          // gelb bei x = -0.5
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
}

void CChildView::Achsenkreuz(float l)
{
	GLfloat Pfeil = (float)0.05;

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(-l, 0, 0);  // Achsen
	glVertex3f(l, 0, 0);

	glVertex3f(0, -l, 0);
	glVertex3f(0, l, 0);

	glVertex3f(0, 0, -l);
	glVertex3f(0, 0, l);

	glVertex3f(l, 0, 0);  // Pfeile
	glVertex3f(l - Pfeil, Pfeil, 0);

	glVertex3f(l, 0, 0);
	glVertex3f(l - Pfeil, -Pfeil, 0);

	glVertex3f(0, l, 0);  // Pfeile
	glVertex3f(0, l - Pfeil, Pfeil);

	glVertex3f(0, l, 0);
	glVertex3f(0, l - Pfeil, -Pfeil);

	glVertex3f(0, 0, l);  // Pfeile
	glVertex3f(Pfeil, 0, l - Pfeil);

	glVertex3f(0, 0, l);
	glVertex3f(-Pfeil, 0, l - Pfeil);
	glEnd();
}


void CChildView::OnAufgabe4()
{
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
	
	CDC* pDC = GetDC();

	CRect rc;
	GetClientRect(&rc);
	double height = rc.Height()/2;
	double width = rc.Width()/2;

	int groeße = 50;

	Matrix3 RotCube = Matrix3();
	Matrix3 TransCube, TransCubeReverse;
	Vektor3 Würfel[8];

	Würfel[0] = Vektor3(width - groeße, height - groeße, 0);
	Würfel[1] = Vektor3(width + groeße, height - groeße, 0);
	Würfel[2] = Vektor3(width + groeße, height + groeße, 0);
	Würfel[3] = Vektor3(width - groeße, height + groeße, 0);
	Würfel[4] = Vektor3(width - groeße, height - groeße, groeße * 2);
	Würfel[5] = Vektor3(width + groeße, height - groeße, groeße * 2);
	Würfel[6] = Vektor3(width + groeße, height + groeße, groeße * 2);
	Würfel[7] = Vektor3(width - groeße, height + groeße, groeße * 2);

	//pDC->SetViewportOrg(height/2, width/2);

	for (int anim = 0; anim < 90000; anim++) {
		pDC->FillSolidRect(0, 0, rc.Width()*2, rc.Height()*2, RGB(255, 255, 255));

		Sleep(10);

		// Rotieren
		TransCube.setTransCube(-width, -height);
		
		RotCube.setRotCubeX(0.05);
		
		TransCubeReverse.setTransCube(width, height);
		
		for (int i = 0; i < 8; i++) {
			Würfel[i] = TransCube * Würfel[i]; // Verschieben Ursprung
			Würfel[i] = RotCube * Würfel[i]; // Rotieren im Ursprung
			Würfel[i] = TransCubeReverse * Würfel[i]; // Verschieben undo
		}
		
		RotCube.setRotCubeY(0.05);
		
		for (int i = 0; i < 8; i++) {
			Würfel[i] = TransCube * Würfel[i]; // Verschieben Ursprung
			Würfel[i] = RotCube * Würfel[i]; // Rotieren im Ursprung
			Würfel[i] = TransCubeReverse * Würfel[i]; // Verschieben undo
		}
		RotCube.setRotCubeZ(0.05);
		
		for (int i = 0; i < 8; i++) {
			Würfel[i] = TransCube * Würfel[i]; // Verschieben Ursprung
			Würfel[i] = RotCube * Würfel[i]; // Rotieren im Ursprung
			Würfel[i] = TransCubeReverse * Würfel[i]; // Verschieben undo
		}
		
		// hinten
		pDC->MoveTo(Würfel[3].vek[0], Würfel[3].vek[1]);
		for (int i = 0; i < 4; i++) {
			pDC->LineTo(Würfel[i].vek[0], Würfel[i].vek[1]);
		}
		// vorne
		pDC->MoveTo(Würfel[7].vek[0], Würfel[7].vek[1]); // vek[0] -> x-Koordinate | vek[1] -> y-Koordinate
		for (int i = 4; i < 8; i++) {
			pDC->LineTo(Würfel[i].vek[0], Würfel[i].vek[1]);
		}

		for (int i = 0; i < 4; i++) {
			pDC->MoveTo(Würfel[i].vek[0], Würfel[i].vek[1]);
			pDC->LineTo(Würfel[i + 4].vek[0], Würfel[i + 4].vek[1]);
		}
		pDC->BitBlt(0, 0, width, height, pDC, 0, 0, SRCCOPY);

		// Animation abbrechen, wenn Esc gedrückt
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
	}


	/*
	//To-do: Viereck in der Mitte zeichnen
	pDC->MoveTo(0, 0);
	pDC->MoveTo(Würfel[0].vek[0], Würfel[0].vek[1]);


	//To-do: Würfel mit entsprechender Matrix multiplizieren
	pDC->SetViewportOrg(height / 2, width / 2);
	for (int i = 0; i < 8; i++) {
		Würfel[i] = RotCube * Würfel[i];
	}
	pDC->MoveTo(0, 0);
	pDC->MoveTo(Würfel[0].vek[0], Würfel[0].vek[1]);
	//Quadrat malen
	for (int i = 0; i < 4; i++) {
		pDC->LineTo(Würfel[i].vek[0], Würfel[i].vek[1]);
	}

	pDC->LineTo(0, 0);
	pDC->SetViewportOrg(50, 50);
	
	for (int i = 0; i < 4;i++) {
		pDC->MoveTo(Würfel[i].vek[0], Würfel[i].vek[1]);
		pDC->LineTo(Würfel[i + 4].vek[0], Würfel[i + 4].vek[1]);
	}
	pDC->LineTo(Würfel[4].vek[0], Würfel[4].vek[1]);*/
}

void CChildView::OnAufgabe5()
{
	GLInit(700, 700, 1);
	glClearColor(0.5, 0.5, 0.5, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(-1, 1, -1, 1, 1.5, 6);
	glFrustum(-1, 1, -1, 1, 1.5, 6);
	gluLookAt(1.0, 1.0, 3.0,	//Augpunkt
		0.0, 0.0, 0.0,	//Zielpunkt
		0.0, 1.0, 0.0);	//Up-Vektor

	for (int anim = 0; anim < 900; anim++) {

		glEnable(GL_DEPTH_TEST);	// Tiefe hinzufügen
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW); // Transformationen organisieren

		glLoadIdentity();
		Achsenkreuz(1.2);
		double rotationsspeed = 30;

		//großer Würfel in der Mitte
		//glRotated(-30.0, 1.0, 0, 0);
		//glRotated(45.0, 0.0, 1.0, 0);
		Bunter_Einheitswuerfel();
		
		//kleiner Würfel an der rechten Seite
		glLoadIdentity();
		glTranslated(0.75, 0, 0);
		glScaled(0.5, 0.5, 0.5);
		glRotated(anim, 1.0, 0.0, 0.0);
		Bunter_Einheitswuerfel();

		//kleiner Würfel an der oberen Seite
		glLoadIdentity();
		glTranslated(0, 0.75, 0);
		glScaled(0.5, 0.5, 0.5);
		glRotated(anim, 0.0, 1.0, 0.0);
		Bunter_Einheitswuerfel();

		//kleiner Würfel an der vorderen Seite
		glLoadIdentity();
		glTranslated(0, 0, 0.75);
		glScaled(0.5, 0.5, 0.5);
		glRotated(anim, 0.0, 0.0, 1.0);
		Bunter_Einheitswuerfel();

		//kleiner Würfel an der linken Seite
		glLoadIdentity();
		glTranslated(-0.75, 0, 0.0);
		glScaled(0.5, 0.5, 0.5);
		glRotated(anim, 1.0, 0.0, 0.0);
		Bunter_Einheitswuerfel();
		
		//kleiner Würfel an der unteren Seite
		glLoadIdentity();
		glTranslated(0, -0.75, 0.0);
		glScaled(0.5, 0.5, 0.5);
		glRotated(anim, 0.0, 1.0, 0.0);
		Bunter_Einheitswuerfel();
		
		//kleiner Würfel an der hinteren Seite
		glLoadIdentity();
		glTranslated(0, 0, -0.75);
		glScaled(0.5, 0.5, 0.5);
		glRotated(rotationsspeed, 0.0, 0.0, 1.0);
		Bunter_Einheitswuerfel();

		SwapBuffers(wglGetCurrentDC());

		//GLInit(0, 0, 0);
		Sleep(10);

		if (GetAsyncKeyState(VK_ESCAPE))
			break;
		// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
	}
}

void CChildView::OnAufgabe5Figurzeichnen()
{
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
	GLInit(900, 900, 1);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-1, 1, -1, 1, 1.5, 6);
	gluLookAt(1.0, 1.0, 3.0,	//Augpunkt
		0.0, 0.0, 0.0,	//Zielpunkt
		0.0, 1.0, 0.0);	//Up-Vektor

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLUquadricObj* pquadric = gluNewQuadric();
	gluQuadricDrawStyle(pquadric, GLU_FILL);


	//eine simple Scheibe
	/*glPushMatrix();
	glTranslated(0, 1, 0);
	glRotated(90, 1.0, 0, 0);
	float matrix0[10] = { 0.05375, 0.05, 0.06625, 0.18275, 0.17, 0.22525, 0.332741, 0.328634, 0.346435, 0.3 };
	material(matrix0);
	glColor3d(0.0, 1.0, 0.0);
	gluDisk(pquadric, 0.3, 0.8, 20, 5);
	glPopMatrix();*/


	//die untere Kugel
	glPushMatrix();
	glTranslated(-0.5, 0, 0);
	float matrix[10] = {0.05375, 0.05, 0.06625, 0.18275, 0.17, 0.22525, 0.332741, 0.328634, 0.346435, 0.6};
	material(matrix);
	gluSphere(pquadric, 0.27, 20, 20);
	glPopMatrix();


	//Kugel auf dem linken Zylinder
	glPushMatrix();
	glTranslated(-0.5, 1, 0);
	glColor3d(1.0, 0.0, 0.0);
	float matrix2[10] = {0.135, 0.2225, 0.1575, 0.54, 0.89, 0.63, 0.316228, 0.316228, 0.316228, 0.1 };
	material(matrix2);
	gluSphere(pquadric, 0.27, 20, 20);
	glPopMatrix();

	
	//Zylinder auf der linken Seite
	glPushMatrix();
	glTranslated(-0.5, 1, 0);
	glRotated(90, 1.0, 0, 0);
	float matrix3[10] = { 0.25, 0.20725, 0.20725, 1, 0.829, 0.829, 0.296648, 0.296648, 0.296648, 0.088 };
	material(matrix3);
	gluCylinder(pquadric, 0.275, 0.275, 1, 20, 10);
	glPopMatrix();

	//Zylinder, welcher die beiden oberen Kugeln verbindet
	glPushMatrix();
	glTranslated(-0.5, 1, 0);
	glRotated(90, 0, 1, 0);
	float matrix4[10] = { 0.1, 0.18725, 0.1745, 0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1 };
	material(matrix4);
	gluCylinder(pquadric, 0.275, 0.275, 1, 20, 10);
	glPopMatrix();

	//Kugel auf dem rechten Zylinder
	glPushMatrix();
	glTranslated(0.5, 1, 0);
	glColor3d(1.0, 0.0, 0.0);
	float matrix5[10] = { 0.135, 0.2225, 0.1575, 0.54, 0.89, 0.63, 0.316228, 0.316228, 0.316228, 0.1 };
	material(matrix5);
	gluSphere(pquadric, 0.27, 20, 20);
	glPopMatrix();


	//Zylinder auf der rechten Seite
	glPushMatrix();
	glTranslated(0.5, 1, 0);
	glRotated(90, 1.0, 0, 0);
	float matrix6[10] = { 0.25, 0.20725, 0.20725, 1, 0.829, 0.829, 0.296648, 0.296648, 0.296648, 0.088 };
	material(matrix6);
	gluCylinder(pquadric, 0.275, 0.275, 1, 20, 10);
	glPopMatrix();


	//die untere Kugel auf der rechten Seite
	glPushMatrix();
	glTranslated(0.5, 0, 0);
	float matrix7[10] = { 0.05375, 0.05, 0.06625, 0.18275, 0.17, 0.22525, 0.332741, 0.328634, 0.346435, 0.6 };
	material(matrix7);
	gluSphere(pquadric, 0.27, 20, 20);
	glPopMatrix();



	//Idee: Zeichnen von einem Penis

	SwapBuffers(wglGetCurrentDC()); //statt glFlush();

	//GLInit(0, 0, 0);
}

void CChildView::material(float matR[10]) {
	//GLfloat Ambient[4] = { matR, matG, matB, 1 };
	GLfloat Ambient[4] = { matR[0], matR[1], matR[2], 1 };
	//GLfloat Diffuse[4] = { matR, matG, matB, 1 };
	GLfloat Diffuse[4] = { matR[3], matR[4], matR[5], 1 };
	//GLfloat Specular[4] = { matR, matG, matB, 1 };
	GLfloat Specular[4] = { matR[6], matR[7], matR[8], 1 };

	//GLfloat shininess = 64;
	GLfloat shininess = matR[9] * 128;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}