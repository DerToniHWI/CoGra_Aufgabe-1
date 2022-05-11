
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


void CChildView::OnAufgabe5()
{
	GLInit(700, 700, 1);
	glClearColor(0.5, 0.5, 0.5, 0.0);

	glOrtho(-1, 1, -1, 1, 1.5, 6);
	gluLookAt(1.0, 1.0, 3.0,	//Augpunkt
			  0.0, 0.0, 0.0,	//Zielpunkt
			  0.0, 1.0, 0.0);	//Up-Vektor
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);


	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Achsenkreuz(1.2);

	//großer Einheitswürfel in der Mitte
	//glRotated(-30.0, 1.0, 0, 0);
	//glRotated(45.0, 0.0, 1.0, 0);
	Bunter_Einheitswuerfel();

	//kleiner Würfel an der rechten Seite
	glTranslated(0.75, 0, 0);
	glScaled(0.5, 0.5, 0.5);
	Bunter_Einheitswuerfel();

	//kleiner Würfel an der oberen Seite
	glTranslated(0, 1.3, 0);
	glScaled(0.5, 0.5, 0.5);
	Bunter_Einheitswuerfel();

	SwapBuffers(wglGetCurrentDC());

	GLInit(0, 0, 0);
	//Bunter_Einheitswuerfel();
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
}
