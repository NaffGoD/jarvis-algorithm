
// ConvexPolygon.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CConvexPolygonApp:
// Сведения о реализации этого класса: ConvexPolygon.cpp
//

class CConvexPolygonApp : public CWinApp
{
public:
	CConvexPolygonApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CConvexPolygonApp theApp;

//////////////////////////////////////////////////////////////////////////

struct Point
{
	int x, y;
	Point() { x = y = 0; }
	bool itsVerify = false;
	bool itsFailVerify = false;
	void draw(CPaintDC& dc) { dc.Rectangle(x - 2, y - 2, x + 2, y + 2); }
};

//////////////////////////////////////////////////////////////////////////

class Line
{
	Point p1, p2;
	int A, B, C;
public:

	Line() {};

	Line(Point p1, Point p2);

	// bool itsVerify = false;

	/*Point getP1() { return p1; }
	Point getP2() { return p2; }*/

	void SetP(Point p1, Point p2);

	/*double LineLenght();*/

	/*int checkCrossed(Line l);*/

	int CheckSign(Point p);

	void draw(CPaintDC& dc);

};

class ColourLine : public Line
{
	int R, G, B;
public:
	ColourLine();

	ColourLine(Point p1, Point p2, int R, int G, int B);

	void SetColour(int R, int G, int B);

	void Draw(CPaintDC& dc);
};

//////////////////////////////////////////////////////////////////////////

class InTriangle
{
	Line l1, l2, l3;

public:

	/*Line getL1() { return l1; }
	Line getL2() { return l2; }
	Line getL3() { return l3; }*/
	InTriangle() {};

	InTriangle(Point p1, Point p2, Point p3);

	void SetPoints(Point p1, Point p2, Point p3);

	void Draw(CPaintDC& dc);
};

// Кольоровий трикутник

class TriangleColour : public InTriangle
{
	int red = 0;
	int green = 0;
	int blue = 0;

public:

	//TriangleColor(Point p1, Point p2, Point p3, int red, int green, int blue);

	void SetTriangle(Point p1, Point p2, Point p3, int red, int green, int blue);

	TriangleColour() {};

	void SetColour(int red, int green, int blue);

	void Draw(CPaintDC& dc);
};

class Jarvis
{
	ColourLine* l;
	Point* p;
	/*ColourLine* dl;*/
	/*QuadrangleColor r;
	PentagonColor pe;*/
	/*ColourLine* 
	failLine;*/
	Point* failp;
	/*ColourLine xline;*/
	ColourLine templine;
	TriangleColour t;
	/*ColourLine diaLine;*/


	int direct = 1;

	/*int Lenghtdl = 0;
	int tempLenght;*/

	int failpoints;
    /*int failLines;
	int failfirst;
	int failcurrent;*/

	int cntline;
	int cntpoint;
	int first;
	int current;

public:

	void ReadFile();
	int GetFirst();
	int Verify(int index);
	void GiveNext(int index);
	void FindLast(int index);

    int FindExtra();
	/*int FailFirst();
	int verifyFail(int index);
	void giveFail(int index);
	void findFail(int index);*/

	bool IsTriangle(Point p1, Point p2, Point p3);

	//void verifyLine();

	void Run();

	//void FigureRun();

	//void MaxDia();

	//void MinDia();

	void Draw(CPaintDC& dc);
};

extern Jarvis jarvisWork;

extern CConvexPolygonApp theApp;

//////////////////////////////////////////////////////////////////////////

