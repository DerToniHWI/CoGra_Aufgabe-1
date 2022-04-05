
// ChildView.cpp: Implementierung der CChildView-Klasse
//

#include "pch.h"
#include "framework.h"
#include "CoGra_Aufgabe1.h"
#include "ChildView.h"

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

	/*
	int x = 1;
	GetParent()->SetWindowPos(NULL, 50, 50, 700, 700, SWP_SHOWWINDOW);

	UpdateWindow();

	CDC* pDC = GetDC();
	for (int i = 0; i < 700; i++) {
		pDC->SetPixel(i, i, RGB(255, 0, 0));
	}
	*/
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
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

