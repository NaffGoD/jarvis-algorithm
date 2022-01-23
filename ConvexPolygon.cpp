
// ConvexPolygon.cpp: определяет поведение классов для приложения.
//

#include "pch.h"
#include "framework.h"
#include "ConvexPolygon.h"
#include "ConvexPolygonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CConvexPolygonApp

BEGIN_MESSAGE_MAP(CConvexPolygonApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Создание CConvexPolygonApp

CConvexPolygonApp::CConvexPolygonApp()
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CConvexPolygonApp

CConvexPolygonApp theApp;


// Инициализация CConvexPolygonApp

BOOL CConvexPolygonApp::InitInstance()
{
	// InitCommonControlsEx() требуется для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Создать диспетчер оболочки, в случае, если диалоговое окно содержит
	// представление дерева оболочки или какие-либо его элементы управления.
	CShellManager *pShellManager = new CShellManager;

	// Активация визуального диспетчера "Классический Windows" для включения элементов управления MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующих
	// конкретных процедур инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));

	CConvexPolygonDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "ОК"
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "Отмена"
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Предупреждение. Не удалось создать диалоговое окно, поэтому работа приложения неожиданно завершена.\n");
		TRACE(traceAppMsg, 0, "Предупреждение. При использовании элементов управления MFC для диалогового окна невозможно #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Удалить диспетчер оболочки, созданный выше.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Поскольку диалоговое окно закрыто, возвратите значение FALSE, чтобы можно было выйти из
	//  приложения вместо запуска генератора сообщений приложения.
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////

//int Line::checkCrossed(Line l)
//{
//	if (checkSign(l.getP1()) * checkSign(l.getP2()) < 0 && l.checkSign(p1) * l.checkSign(p2) < 0)
//		return 1;
//	return 0;
//};

void TriangleColour::SetColour(int red, int green, int blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
};

void TriangleColour::Draw(CPaintDC& dc)
{
	CPen Pen(PS_SOLID, 1, RGB(red, green, blue));

	//CPen redPen(PS_SOLID, 1, RGB(red, green, blue));

	CPen* TakenPen = dc.SelectObject(&Pen);

	InTriangle::Draw(dc);
};

// Конструктори 

void TriangleColour::SetTriangle(Point p1, Point p2, Point p3, int red, int green, int blue)
{
	SetPoints(p1, p2, p3);
	SetColour(red, green, blue);
}

void InTriangle::SetPoints(Point p1, Point p2, Point p3)
{
	l1.SetP(p1, p2);
	l2.SetP(p2, p3);
	l3.SetP(p3, p1);
}

InTriangle::InTriangle(Point p1, Point p2, Point p3)
{
	l1.SetP(p1, p2);
	l2.SetP(p2, p3);
	l3.SetP(p3, p1);
};

void InTriangle::Draw(CPaintDC& dc)
{
	l1.draw(dc);
	l2.draw(dc);
	l3.draw(dc);
};

Line::Line(Point p1, Point p2)
{
	this->p1 = p1;
	this->p2 = p2;

	A = 0;
	B = 0;
	C = 0;
};

void Line::SetP(Point p1, Point p2)
{
	this->p1 = p1;
	this->p2 = p2;

	A = p2.y - p1.y;
	B = p1.x - p2.x;
	C = p1.y * (p2.x - p1.x) - p1.x * (p2.y - p1.y);
}

//double Line::LineLenght()
//{
//	double dx = p1.x - p2.x;
//	double dy = p1.y - p2.y;
//	return sqrt((dx * dx) + (dy * dy));
//}

void Line::draw(CPaintDC& dc)
{
	dc.MoveTo(p1.x, p1.y);
	dc.Rectangle(p1.x - 2, p1.y - 2, p1.x + 2, p1.y + 2);
	dc.LineTo(p2.x, p2.y);
	dc.Rectangle(p2.x - 2, p2.y - 2, p2.x + 2, p2.y + 2);
}

int operator ^ (ColourLine templine, Point p)
{
	return templine.CheckSign(p);
}

int operator ^ (Point p, ColourLine templine)
{
	return templine.CheckSign(p);
}

int Line::CheckSign(Point p)
{
	int eq = A * p.x + B * p.y + C;
	if (eq > 0)
		return 1;
	if (eq == 0)
		return 0;
	return -1;
}

//////////////////////////////////////////////////////////////////////////

ColourLine::ColourLine(Point p1, Point p2, int R, int G, int B) :Line(p1, p2)
{
	SetColour(R, G, B);
};

ColourLine::ColourLine() :Line() {};

void ColourLine::SetColour(int R, int G, int B)
{
	this->R = R;
	this->G = G;
	this->B = B;
}

void ColourLine::Draw(CPaintDC& dc)
{
	CPen Pen(PS_SOLID, 1, RGB(this->R, this->G, this->B));
	dc.SelectObject(&Pen);
	Line::draw(dc);
}

//////////////////////////////////////////////////////////////////////////

void Jarvis::ReadFile()
{
	cntpoint = 0, cntline = 0;
	char str[100];
	int c;
	FILE* f;

	errno_t err = fopen_s(&f, "Data.txt", "r");

	while ((c = getc(f)) != EOF)
		if (c == '=')
			cntpoint++;
	rewind(f);
	cntpoint /= 2;

	p = new Point[cntpoint];
	failp = new Point[cntpoint];
	l = new ColourLine[cntpoint];
	
	fgets(str, 100, f);
	for (int i = 0; i < cntpoint; i++)
	{
		fscanf_s(f, "%s%s%2s%d%s%2s%d%s\n",
			str, _countof(str),
			str, _countof(str),
			str, _countof(str),
			&p[i].x, str, _countof(str),
			str, _countof(str),
			&p[i].y, str, _countof(str));
	}
	fclose(f);
}

int Jarvis::GetFirst()
{
	first = 0;
	int min = p[0].x;
	for (int i = 0; i < cntpoint; i++)
	{
			if (p[i].itsVerify == false)
			{

				if (p[i].x < min )
				{
					first = i;
					min = p[i].x;
				}
			}
	}
	return first;
}

int Jarvis::Verify(int index)
{
	if (p[index].itsVerify )
		return 0;

	templine.SetP(p[current], p[index]);

	for (int i = 0; i < cntpoint; i++)

		if (i != current && i != index)
		{
			if ((p[i] ^ templine) == 0)
				throw 99;

			if ((templine^p[i]) != direct)
				return -1;
		}
	return 1;
}

void Jarvis::GiveNext(int index)
{
	l[cntline++].SetP(p[current], p[index]);
	current = index;
	p[current].itsVerify = true;
}

void Jarvis::FindLast(int index)
{
		p[first].itsVerify = false;

		if (jarvisWork.Verify(first) == 1)

			l[cntline++].SetP(p[current], p[first]);

		templine.SetP(p[current], p[current]);

		p[first].itsVerify = true;
}

//////////////////////////////////////////////////////////////////////////

int Jarvis::FindExtra()
{
	failpoints = 0;
	/*failLine = new ColourLine[cntpoint];*/
	for (int i = 0; i < cntpoint; i++)
	{
		if (p[i].itsVerify == false)
		{
			failp[failpoints++] = p[i];
		}
	}
	return failpoints;
 }

//int Jarvis::FailFirst()
//{
//	failfirst = 0;
//	int min = failp[0].x;
//	for (int i = 1; i < failPoint; i++)
//	{
//		if (failp[i].itsVerify==false)
//		{
//			if (failp[i].itsFailVerify == false)
//			{
//				if (failp[i].x < min)
//				{
//					failfirst = i;
//					min = failp[i].x;
//				}
//			}
//		}
//	}
//	return failfirst;
//}
//
//int Jarvis::verifyFail(int index)
//{
//	if (failp[index].itsFailVerify||failp[index].itsVerify)
//		return 0;
//	/*if (p[index].itsVerify == false && p[index].itsFailVerify == false)
//		second == index;*/
//	templine.SetP(failp[current], failp[index]);
//	/*tempLenght = templine.LineLenght();
//	if (tempLenght > Lenghtdl)
//	{
//		Lenghtdl = tempLenght;
//		diaLine = templine;
//	}*/
//	for (int i = 0; i < failPoint; i++)
//		if (i != current && i != index)
//			if ((templine^failp[i]) != direct)
//				return -1;
//	return 1;
//}
//
//void Jarvis::giveFail(int index)
//{
//	l[cntline++].SetP(failp[current], failp[index]);
//	current = index;
//	failp[current].itsVerify = false;
//	failp[current].itsFailVerify = true;
//}
//
//void Jarvis::findFail(int index)
//{
//	failp[first].itsFailVerify = false;
//
//	if (jarvisWork.verifyFail(first) == 1)
//
//		l[cntline++].SetP(failp[current], failp[first]);
//
//	templine.SetP(failp[current], failp[current]);
//
//	failp[first].itsFailVerify = true;
//}

bool Jarvis::IsTriangle(Point p1,Point p2,Point p3)
{
  return (p3.x * (p2.y - p1.y) - p3.y * (p2.x - p1.x) == p1.x * p2.y - p2.x * p1.y);
}

//bool Jarvis::isPointsOnLine(Point p1, Point p2, Point p3)
//{
//	return (p3.x * (p2.y - p1.y) - p3.y * (p2.x - p1.x) == p1.x * p2.y - p2.x * p1.y);
//}

//////////////////////////////////////////////////////////////////////////

//void Jarvis::verifyLine()
//{
//	for (int i = 0; i < cntpoint; i++)
//	{
//		if (p[i].itsVerify )
//		{
//			for (int j = 0; j < cntpoint; j++)
//			{
//				if (p[j].itsVerify )
//				{
//
//						xline.setP(p[i], p[j]);
//						tempLenght = xline.LineLenght();
//
//						if (tempLenght > Lenghtdl)
//						{
//							Lenghtdl = tempLenght;
//							diaLine = xline;
//						}
//					
//				}
//			}
//		}
//	}
//}

void Jarvis::Run()
{
	first = GetFirst();
	p[first].itsVerify = true;
	current = first;

	bool flagcontinue = false;

	//Рішення задачі;
	do
	{
		flagcontinue = false;
		for (int i = 0; i < cntpoint; i++)
		{
			if (Verify(i) == 1)
			{
				GiveNext(i);
				flagcontinue = true;
				break;
			}
		}
	} while (flagcontinue);
	FindLast(current);

	if (FindExtra() == 3 && IsTriangle(failp[0], failp[1], failp[2]) == 0)
	{
		t.SetTriangle(failp[0], failp[1], failp[2], 0, 255, 0);
	}

	////////////////////////////////////////////

	/*int trycnt = 0;
	do
	{
		for (int j = 0; j < count; j++)
		{
			if (p[j].itsVerify != true)
			{
				lx.setP(p[current], p[j]);
				for (int k = 0; k < count; k++)
				{
					if (k != current && k != j)
					{
						if (lx.checkSign(p[k]) == -1)
						{
							j++;
							trycnt = 0;
							break;
						}
						trycnt++;
					}
				}
				if (trycnt<count == false)
				{
					l[cntline].setP(p[current], p[j]);
					p[j].itsVerify;
					current = j;
					cntline++;
					break;
				}
			}
		}
	} while (current != first);*/
};

//Для внутрішньої фігури

//void Jarvis::FigureRun()
//{
//
//	/*current = 0;
//	first = 0;
//	if (findExtra() == 3 && isTriangle(failp[0], failp[1], failp[2]) == 0)
//	{
//		first = FailFirst();
//		failp[first].itsFailVerify = true;
//		current = first;
//
//		bool flagcontinue = false;
//
//		do
//		{
//			flagcontinue = false;
//			for (int i = 0; i < failPoint; i++)
//			{
//				if (verifyFail(i) == 1)
//				{
//					giveFail(i);
//					flagcontinue = true;
//					break;
//				}
//			}
//		} while (flagcontinue);
//		findFail(current);
//	}*/
//}

void Jarvis::Draw(CPaintDC& dc)
{
	//Рисування 

	for (int i = 0; i < cntpoint; i++)
		p[i].draw(dc);

		for (int i = 0; i < cntline; i++)
		{
			l[i].SetColour(0, 0, 255);
			l[i].Draw(dc);
		}

		if(FindExtra()==3)
		t.Draw(dc);

		/*diaLine.setColor(255, 0, 0);
		diaLine.draw(dc);*/
}

Jarvis jarvisWork;

//////////////////////////////////////////////////////////////////////////


