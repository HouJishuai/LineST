
// LineSTView.h: CLineSTView 类的接口
//

#pragma once


class CLineSTView : public CView
{
protected: // 仅从序列化创建
	CLineSTView() noexcept;
	DECLARE_DYNCREATE(CLineSTView)

// 特性
public:
	CLineSTDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CLineSTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDDA();

private:
	int start = 0;
	int x0, y0, x1, y1;
public:
	afx_msg void OnMID();
	afx_msg void OnBRES();
	void DDA_line(int B_x, int B_y, int E_x, int E_y);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void MID_line(int B_x, int B_y, int E_x, int E_y);
	void BRES_line(int B_x, int B_y, int E_x, int E_y);
	afx_msg void OnCLC();
};

#ifndef _DEBUG  // LineSTView.cpp 中的调试版本
inline CLineSTDoc* CLineSTView::GetDocument() const
   { return reinterpret_cast<CLineSTDoc*>(m_pDocument); }
#endif

