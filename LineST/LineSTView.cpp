
// LineSTView.cpp: CLineSTView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LineST.h"
#endif

#include "LineSTDoc.h"
#include "LineSTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLineSTView

IMPLEMENT_DYNCREATE(CLineSTView, CView)

BEGIN_MESSAGE_MAP(CLineSTView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLineSTView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CLineSTView::OnDDA)
	ON_COMMAND(ID_32772, &CLineSTView::OnMID)
	ON_COMMAND(ID_32773, &CLineSTView::OnBRES)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_CLC, &CLineSTView::OnCLC)
END_MESSAGE_MAP()

// CLineSTView 构造/析构

CLineSTView::CLineSTView() noexcept
{
	// TODO: 在此处添加构造代码

}

CLineSTView::~CLineSTView()
{
}

BOOL CLineSTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLineSTView 绘图

void CLineSTView::OnDraw(CDC* /*pDC*/)
{
	CLineSTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CLineSTView 打印


void CLineSTView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLineSTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLineSTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLineSTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CLineSTView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLineSTView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLineSTView 诊断

#ifdef _DEBUG
void CLineSTView::AssertValid() const
{
	CView::AssertValid();
}

void CLineSTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLineSTDoc* CLineSTView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLineSTDoc)));
	return (CLineSTDoc*)m_pDocument;
}
#endif //_DEBUG


// CLineSTView 消息处理程序


void CLineSTView::OnDDA()
{
	// TODO: 在此添加命令处理程序代码
	start = 0;
}


void CLineSTView::OnMID()
{
	// TODO: 在此添加命令处理程序代码
	start = 1;
}


void CLineSTView::OnBRES()
{
	// TODO: 在此添加命令处理程序代码
	start = 2;
}


void CLineSTView::DDA_line(int B_x, int B_y, int E_x, int E_y)
{
	COLORREF col = (0, 0, 0);
	CDC* pDC = GetDC();//建立一个用于图形显示的指针
	if (B_x == E_x && B_y == E_y) {
		pDC->TextOut(450, 18, _T("两点不能重合"));
		return;
	}
	float x, y, k, _k,Dx, Dy;//浮点型变量x，y，斜率，斜率倒数，x增量，y增量
	int xm, ym;//终点坐标
	Dx = E_x - B_x;
	Dy = E_y - B_y;
	x = B_x; y = B_y;
	xm = E_x; ym = E_y;

	//判断斜率绝对值同1大小，决定自增方向
	if (abs(Dx) > abs(Dy))
	{
		k = Dy / Dx;
		if (B_x > E_x) {
			x = E_x; y = E_y; xm = B_x; ym = B_y;
		}
		//开始循环画点
		for (x; x < xm; x++) {
			pDC->SetPixel(x, (int)(y + 0.5), col);
			y = y + k;
		}
	}
	else
	{
		_k = Dx / Dy;
		if (B_y > E_y) {
			x = E_x; y = E_y; xm = B_x; ym = B_y;
		}
		//开始循环画点
		for (y; y < ym; y++) {
			pDC->SetPixel((int)(x + 0.5), y, col);
			x += _k;
		}
	}
	pDC->TextOut(450, 18, _T("DDA画线法成功了！"));
}


void CLineSTView::MID_line(int B_x, int B_y, int E_x, int E_y)
{
	// TODO: 在此处添加实现代码.
	COLORREF col = (0, 255, 255);	//像素颜色
	CDC* pDC = GetDC();	// 建用于图形显示的指针

	int x = B_x, y = B_y;	//画线的起点
	
	int A, B;	//直线一般式方程系数：Ax+By+C=0
	A = B_y - E_y;
	B = E_x - B_x;

	int dx = (B >= 0 ? 1 : (B = -B, -1));
	int dy = (A <= 0 ? 1 : (A = -A, -1));

	pDC->SetPixel(x, y, col);

	int d, d1, d2;
	if (-A <= B) {	//|k|<=1
		d = 2 * A + B;
		d1 = 2 * A;
		d2 = 2 * (A + B);
		while (x != E_x) {
			if(d < 0) 
				y += dy, d += d2;
			else 
				d += d1;
			x += dx;
			pDC->SetPixel(x, y, col);
		}
	}
	else {	//|k|>1
		d = 2 * B + A;
		d1 = 2 * B;
		d2 = 2 * (A + B);
		while (y != E_y) {
			if (d < 0)
				d += d1;
			else
				x += dx, d += d2;
			y += dy;
			pDC->SetPixel(x, y, col);
		}
	}
	pDC->TextOut(450, 18, _T("中点画线法成功了！"));
}


void CLineSTView::BRES_line(int B_x, int B_y, int E_x, int E_y)
{
	// TODO: 在此处添加实现代码.
	COLORREF col = (0, 0, 255);//像素颜色
	CDC* pDC = GetDC();

	int x, y, Dx, Dy, e;
	x = B_x, y = B_y;	//画线的起点
	Dx = E_x - B_x;
	Dy = E_y - B_y;

	int dx = Dx >= 0 ? 1 : (Dx = -Dx, -1);
	int dy = Dy >= 0 ? 1 : (Dy = -Dy, -1);
	e = -Dx;

	if (Dx >= Dy) {	//|k|<=1
		while (x != E_x) {
			pDC->SetPixel(x, y, col);
			x += dx;
			e += 2 * Dy;
			if (e >= 0)
				y += dy, e -= 2 * Dx;
		}
	}
	else {	//|k|>1
		while (y != E_y) {
			pDC->SetPixel(x, y, col);
			y += dy;
			e += 2 * Dx;
			if (e >= 0)
				x += dx, e -= 2 * Dy;
		}
	}
	pDC->TextOut(450, 18, _T("Bresenham画线法成功了！"));
}



void CLineSTView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDown(nFlags, point);
	x0 = point.x;
	y0 = point.y;
}


void CLineSTView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags, point);
	x1 = point.x;
	y1 = point.y;

	switch (start) {
	case 0:
		DDA_line(x0, y0, x1, y1);
		break;
	case 1:
		MID_line(x0, y0, x1, y1);
		break;
	case 2:
		BRES_line(x0, y0, x1, y1);
		break;
	default:
		DDA_line(x0, y0, x1, y1);
		break;
	}
}




void CLineSTView::OnCLC()
{
	// TODO: 在此添加命令处理程序代码
	RedrawWindow();
}
