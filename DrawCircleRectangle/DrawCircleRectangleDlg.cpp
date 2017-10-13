
// DrawCircleRectangleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawCircleRectangle.h"
#include "DrawCircleRectangleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <stack>
using namespace std;//����ջ

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDrawCircleRectangleDlg �Ի���



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


// CDrawCircleRectangleDlg ��Ϣ�������

BOOL CDrawCircleRectangleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDrawCircleRectangleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	GetWindowRect(hWnd, &rect);   //�õ��ļ����������Ļ���ϽǵĴ��ھ�������

	POINT pt = { rect.left,rect.top };
	long lWidth = rect.right - rect.left;
	long lHeight = rect.bottom - rect.top;
	
	//�е��㷨��Բ
	//int x0 = 250, y0 = 120, r = 100, color = RGB(0, 0, 255), x, y, d;  //����Բ�ģ�x0,y0�����뾶Ϊr
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

	////Bresenham�㷨��Բ
	//int x0 = 100, y0 = 150, x, y, r = 80, color = 0;
	//float e, d;
	//e = 3 - 2 * r; x = 0; y = r;  //eΪ�б�ʽ
	//while (x <= y)
	//{
	//	if (e<0)   //��ѡ��ǰ���ص����ҷ���Ϊ��һ����
	//	{
	//		e = e + 4 * x + 6; x++;
	//	}
	//	else   //��ѡ��ǰ���ص����·���Ϊ��һ����
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


	//Bresenham�㷨��Բ
	int x0 = 100, y0 = 150, x, y, r = 80, color = 0;
	float e, d;

	POINT temp = { 0,0 };
	stack <POINT>stk;//ջ������ת˳��

	e = 3 - 2 * r; x = 0; y = r;  //eΪ�б�ʽ��1
	while (x <= y)
	{
		if (e<0)   //��ѡ��ǰ���ص����ҷ���Ϊ��һ����
		{
			e = e + 4 * x + 6; x++;
		}
		else   //��ѡ��ǰ���ص����·���Ϊ��һ����
		{
			e = e + 4 * (x - y) + 10; x++; y--;
		}

		::SetPixel(hdc, y + x0, -x + y0, color);
		Sleep(10);
	}

	e = 3 - 2 * r; x = 0; y = r;  //eΪ�б�ʽ��2
	while (x <= y)
	{
		if (e<0)   //��ѡ��ǰ���ص����ҷ���Ϊ��һ����
		{
			e = e + 4 * x + 6; x++;
		}
		else   //��ѡ��ǰ���ص����·���Ϊ��һ����
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

	e = 3 - 2 * r; x = 0; y = r;  //eΪ�б�ʽ��3
	while (x <= y)
	{
		if (e<0)   //��ѡ��ǰ���ص����ҷ���Ϊ��һ����
		{
			e = e + 4 * x + 6; x++;
		}
		else   //��ѡ��ǰ���ص����·���Ϊ��һ����
		{
			e = e + 4 * (x - y) + 10; x++; y--;
		}
		::SetPixel(hdc, -x + x0, -y + y0, color);
		Sleep(10);
	}

	e = 3 - 2 * r; x = 0; y = r;  //eΪ�б�ʽ��4
	while (x <= y)
	{
		if (e<0)   //��ѡ��ǰ���ص����ҷ���Ϊ��һ����
		{
			e = e + 4 * x + 6; x++;
		}
		else   //��ѡ��ǰ���ص����·���Ϊ��һ����
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

	e = 3 - 2 * r; x = 0; y = r;  //eΪ�б�ʽ,5
	while (x <= y)
	{
		if (e<0)   //��ѡ��ǰ���ص����ҷ���Ϊ��һ����
		{
			e = e + 4 * x + 6; x++;
		}
		else   //��ѡ��ǰ���ص����·���Ϊ��һ����
		{
			e = e + 4 * (x - y) + 10; x++; y--;
		}
		::SetPixel(hdc, -y + x0, x + y0, color);
		Sleep(10);
	}
	e = 3 - 2 * r; x = 0; y = r;  //eΪ�б�ʽ,6
	while (x <= y)
	{
		if (e<0)   //��ѡ��ǰ���ص����ҷ���Ϊ��һ����
		{
			e = e + 4 * x + 6; x++;
		}
		else   //��ѡ��ǰ���ص����·���Ϊ��һ����
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

	e = 3 - 2 * r; x = 0; y = r;  //eΪ�б�ʽ,7
	while (x <= y)
	{
		if (e<0)   //��ѡ��ǰ���ص����ҷ���Ϊ��һ����
		{
			e = e + 4 * x + 6; x++;
		}
		else   //��ѡ��ǰ���ص����·���Ϊ��һ����
		{
			e = e + 4 * (x - y) + 10; x++; y--;
		}
		::SetPixel(hdc, x + x0, y + y0, color);
		Sleep(10);
	}
	e = 3 - 2 * r; x = 0; y = r;  //eΪ�б�ʽ,8
	while (x <= y)
	{
		if (e<0)   //��ѡ��ǰ���ص����ҷ���Ϊ��һ����
		{
			e = e + 4 * x + 6; x++;
		}
		else   //��ѡ��ǰ���ص����·���Ϊ��һ����
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
	GetWindowRect(hWnd, &rect);   //�õ��ļ����������Ļ���ϽǵĴ��ھ�������

	POINT pt = { rect.left,rect.top };
	long lWidth = rect.right - rect.left;
	long lHeight = rect.bottom - rect.top;

	//������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HANDLE hThread1 = CreateThread(NULL, 0, DrawCircle, NULL, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, DrawRectangle, NULL, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);

}
