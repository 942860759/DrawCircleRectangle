
// DrawCircleRectangleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawCircleRectangle.h"
#include "DrawCircleRectangleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <stack>
using namespace std;//调用栈

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDrawCircleRectangleDlg 对话框



CDrawCircleRectangleDlg::CDrawCircleRectangleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRAWCIRCLERECTANGLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawCircleRectangleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrawCircleRectangleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDrawCircleRectangleDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDrawCircleRectangleDlg 消息处理程序

BOOL CDrawCircleRectangleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDrawCircleRectangleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDrawCircleRectangleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDrawCircleRectangleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


DWORD WINAPI DrawCircle(LPVOID lpParamter)
{
	HWND hWnd = GetForegroundWindow();
	HDC hdc;
	hdc = ::GetDC(hWnd);

	RECT rect;
	GetWindowRect(hWnd, &rect);   //得到的既是相对于屏幕左上角的窗口矩形区域

	POINT pt = { rect.left,rect.top };
	long lWidth = rect.right - rect.left;
	long lHeight = rect.bottom - rect.top;
	
	//中点算法画圆
	//int x0 = 250, y0 = 120, r = 100, color = RGB(0, 0, 255), x, y, d;  //定义圆心（x0,y0），半径为r
	//x = 0; y = r; d = 1 - r;
	//::SetPixel(hdc, x, y, color);
	//while (x <= y)
	//{
	//	if (d<0)
	//		d += 2 * x + 3;
	//	else
	//	{
	//		d += 2 * (x - y) + 5; y--;
	//	}
	//	x++;
	//	::SetPixel(hdc, x + x0, y + y0, color);
	//	::SetPixel(hdc, -x + x0, y + y0, color);
	//	::SetPixel(hdc, -x + x0, -y + y0, color);
	//	::SetPixel(hdc, x + x0, -y + y0, color);
	//	::SetPixel(hdc, y + x0, x + y0, color);
	//	::SetPixel(hdc, -y + x0, x + y0, color);
	//	::SetPixel(hdc, -y + x0, -x + y0, color);
	//	::SetPixel(hdc, y + x0, -x + y0, color);
	//	Sleep(100);
	//}

	////Bresenham算法画圆
	//int x0 = 100, y0 = 150, x, y, r = 80, color = 0;
	//float e, d;
	//e = 3 - 2 * r; x = 0; y = r;  //e为判别式
	//while (x <= y)
	//{
	//	if (e<0)   //即选择当前像素的正右方作为下一像素
	//	{
	//		e = e + 4 * x + 6; x++;
	//	}
	//	else   //即选择当前像素的右下方作为下一像素
	//	{
	//		e = e + 4 * (x - y) + 10; x++; y--;
	//	}

	//	::SetPixel(hdc, x + x0, y + y0, color);
	//	::SetPixel(hdc, -x + x0, y + y0, color);
	//	::SetPixel(hdc, -x + x0, -y + y0, color);
	//	::SetPixel(hdc, x + x0, -y + y0, color);
	//	::SetPixel(hdc, y + x0, x + y0, color);
	//	::SetPixel(hdc, -y + x0, x + y0, color);
	//	::SetPixel(hdc, -y + x0, -x + y0, color);
	//	::SetPixel(hdc, y + x0, -x + y0, color);
	//	
	//}


	//Bresenham算法画圆
	int x0 = 100, y0 = 150, x, y, r = 80, color = 0;
	float e, d;

	POINT temp = { 0,0 };
	stack <POINT>stk;//栈用来反转顺序

	e = 3 - 2 * r; x = 0; y = r;  //e为判别式，1
	while (x <= y)
	{
		if (e<0)   //即选择当前像素的正右方作为下一像素
		{
			e = e + 4 * x + 6; x++;
		}
		else   //即选择当前像素的右下方作为下一像素
		{
			e = e + 4 * (x - y) + 10; x++; y--;
		}

		::SetPixel(hdc, y + x0, -x + y0, color);
		Sleep(10);
	}

	e = 3 - 2 * r; x = 0; y = r;  //e为判别式，2
	while (x <= y)
	{
		if (e<0)   //即选择当前像素的正右方作为下一像素
		{
			e = e + 4 * x + 6; x++;
		}
		else   //即选择当前像素的右下方作为下一像素
		{
			e = e + 4 * (x - y) + 10; x++; y--;
		}

		temp.x = x + x0;
		temp.y = -y + y0;
		stk.push(temp);
		/*::SetPixel(hdc, x + x0, -y + y0, color);
		Sleep(10);*/
	}
	while (!stk.empty())
	{
		::SetPixel(hdc, stk.top().x, stk.top().y, color);
		Sleep(10);
		stk.pop();
	}

	e = 3 - 2 * r; x = 0; y = r;  //e为判别式，3
	while (x <= y)
	{
		if (e<0)   //即选择当前像素的正右方作为下一像素
		{
			e = e + 4 * x + 6; x++;
		}
		else   //即选择当前像素的右下方作为下一像素
		{
			e = e + 4 * (x - y) + 10; x++; y--;
		}
		::SetPixel(hdc, -x + x0, -y + y0, color);
		Sleep(10);
	}

	e = 3 - 2 * r; x = 0; y = r;  //e为判别式，4
	while (x <= y)
	{
		if (e<0)   //即选择当前像素的正右方作为下一像素
		{
			e = e + 4 * x + 6; x++;
		}
		else   //即选择当前像素的右下方作为下一像素
		{
			e = e + 4 * (x - y) + 10; x++; y--;
		}

		temp.x = -y + x0;
		temp.y = -x + y0;
		stk.push(temp);
		/*::SetPixel(hdc, -y + x0, -x + y0, color);
		Sleep(10);*/
	}
	while (!stk.empty())
	{
		::SetPixel(hdc, stk.top().x, stk.top().y, color);
		Sleep(10);
		stk.pop();
	}

	e = 3 - 2 * r; x = 0; y = r;  //e为判别式,5
	while (x <= y)
	{
		if (e<0)   //即选择当前像素的正右方作为下一像素
		{
			e = e + 4 * x + 6; x++;
		}
		else   //即选择当前像素的右下方作为下一像素
		{
			e = e + 4 * (x - y) + 10; x++; y--;
		}
		::SetPixel(hdc, -y + x0, x + y0, color);
		Sleep(10);
	}
	e = 3 - 2 * r; x = 0; y = r;  //e为判别式,6
	while (x <= y)
	{
		if (e<0)   //即选择当前像素的正右方作为下一像素
		{
			e = e + 4 * x + 6; x++;
		}
		else   //即选择当前像素的右下方作为下一像素
		{
			e = e + 4 * (x - y) + 10; x++; y--;
		}
		temp.x = -x + x0;
		temp.y = y + y0;
		stk.push(temp);
		/*::SetPixel(hdc, -x + x0, y + y0, color);
		Sleep(10);*/
	}
	while (!stk.empty())
	{
		::SetPixel(hdc, stk.top().x, stk.top().y, color);
		Sleep(10);
		stk.pop();
	}

	e = 3 - 2 * r; x = 0; y = r;  //e为判别式,7
	while (x <= y)
	{
		if (e<0)   //即选择当前像素的正右方作为下一像素
		{
			e = e + 4 * x + 6; x++;
		}
		else   //即选择当前像素的右下方作为下一像素
		{
			e = e + 4 * (x - y) + 10; x++; y--;
		}
		::SetPixel(hdc, x + x0, y + y0, color);
		Sleep(10);
	}
	e = 3 - 2 * r; x = 0; y = r;  //e为判别式,8
	while (x <= y)
	{
		if (e<0)   //即选择当前像素的正右方作为下一像素
		{
			e = e + 4 * x + 6; x++;
		}
		else   //即选择当前像素的右下方作为下一像素
		{
			e = e + 4 * (x - y) + 10; x++; y--;
		}
		temp.x = y + x0;
		temp.y = x + y0;
		stk.push(temp);
		/*::SetPixel(hdc, y + x0, x + y0, color);
		Sleep(10);*/
	}
	while (!stk.empty())
	{
		::SetPixel(hdc, stk.top().x, stk.top().y, color);
		Sleep(10);
		stk.pop();
	}
	
	::ReleaseDC(hWnd, hdc);


	return 0L;
}

DWORD WINAPI DrawRectangle(LPVOID lpParamter)
{
	HWND hWnd = GetForegroundWindow();
	HDC hdc;
	hdc = ::GetDC(hWnd);

	RECT rect;
	GetWindowRect(hWnd, &rect);   //得到的既是相对于屏幕左上角的窗口矩形区域

	POINT pt = { rect.left,rect.top };
	long lWidth = rect.right - rect.left;
	long lHeight = rect.bottom - rect.top;

	//画矩形
	int x0 = 440, y0 = 70, width = 160, height = 160, color = 0;

	for (int i = 0; i < width; i++) {
		::SetPixel(hdc, x0-i, y0, color);
		Sleep(7);
	}
	for (int i = 0; i < height; i++) {
		::SetPixel(hdc, x0 - width, y0 + i, color);
		Sleep(7);
	}
	for (int i = 0; i < width; i++) {
		::SetPixel(hdc, x0 - width+i, y0 + height, color);
		Sleep(7);
	}
	for (int i = 0; i < height; i++) {
		::SetPixel(hdc, x0 , y0 + height-i, color);
		Sleep(7);
	}

	::ReleaseDC(hWnd, hdc);

	return 0L;
}

void CDrawCircleRectangleDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	HANDLE hThread1 = CreateThread(NULL, 0, DrawCircle, NULL, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, DrawRectangle, NULL, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);

}
