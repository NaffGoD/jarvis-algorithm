﻿
// ConvexPolygonDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "ConvexPolygon.h"
#include "ConvexPolygonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CConvexPolygonDlg



CConvexPolygonDlg::CConvexPolygonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONVEXPOLYGON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConvexPolygonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConvexPolygonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	/*ON_BN_CLICKED(IDC_BUTTON1, &CConvexPolygonDlg::OnBnClickedButton1)*/
	ON_BN_CLICKED(IDC_BUTTON2, &CConvexPolygonDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CConvexPolygonDlg::OnBnClickedButton3)
	//ON_BN_CLICKED(IDC_BUTTON5, &CConvexPolygonDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// Обработчики сообщений CConvexPolygonDlg

BOOL CConvexPolygonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CConvexPolygonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CConvexPolygonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		jarvisWork.Draw(dc);

		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CConvexPolygonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//void CConvexPolygonDlg::OnBnClickedButton1()
//{
//	//Інформація
//	char information[100] = "This program builds a convex polygon and a figure inside it using the entered point coordinates";
//	MessageBoxA(NULL, (LPCSTR)(information), (LPCSTR)"Description", MB_OK);
//	Invalidate();
//}


void CConvexPolygonDlg::OnBnClickedButton2()
{
	//Ініціалізація
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	int res = _spawnlp(_P_WAIT, "C:\\Windows\\notepad.exe", "notepad.exe", "Data.txt", NULL);
	jarvisWork.ReadFile();

	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	Invalidate();
}

void CConvexPolygonDlg::OnBnClickedButton3()
{
	//Запуск алгоритмів
	try
	{
		jarvisWork.Run();
	}
	catch (int ex)
	{
		char information[100] = "Could not create convex shape, because the points lie on one straight line";
		MessageBoxA(NULL, (LPCSTR)(information), (LPCSTR)"Error", MB_OK);
		GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	/*GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);*/
	Invalidate();
}


//void CConvexPolygonDlg::OnBnClickedButton5()
//{
//	jarvisWork.FigureRun();
//	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
//	Invalidate();
//}
