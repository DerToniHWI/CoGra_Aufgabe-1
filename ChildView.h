
// ChildView.h: Schnittstelle der CChildView-Klasse
//


#pragma once


// CChildView-Fenster

class CChildView : public CWnd
{
// Konstruktion
public:
	CChildView();

// Attribute
public:

// Vorgänge
public:
	double xdmin;
	double xddelta;
	double ydmin;
	double yddelta;
	int m_height;
	int m_width;

// Überschreibungen
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void JuliaMalen();
	void MandelbrotMalen();

// Implementierung
public:
	virtual ~CChildView();

	// Generierte Funktionen für die Meldungstabellen
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCograDiagonale();
	afx_msg void OnCograJuliamenge();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCograMandelbrot();
	afx_msg void OnVektorQuadrat1();
	afx_msg void OnVektorRotation();
	void CChildView::GLInit(int Breite, int Hoehe, int Modus);
	void CChildView::Bunter_Einheitswuerfel();
	void CChildView::Achsenkreuz(float l);
	afx_msg void OnAufgabe5();
};

