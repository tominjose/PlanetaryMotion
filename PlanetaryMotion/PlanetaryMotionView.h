
// PlanetaryMotionView.h : interface of the CPlanetaryMotionView class
//
#include "PlanetaryMotionDoc.h"
#pragma once


class CPlanetaryMotionView : public CView
{
protected: // create from serialization only
	CPlanetaryMotionView() noexcept;
	DECLARE_DYNCREATE(CPlanetaryMotionView)
	CWinThread *pThread;
// Attributes
public:
	 CPlanetaryMotionDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPlanetaryMotionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnThreadStart();
	afx_msg void OnThreadPause();
	afx_msg void OnThreadResume();
	int x1, y1, x2,y2, angle, a1, b1, a2, b2;
	float t;
	long n;
};

#ifndef _DEBUG  // debug version in PlanetaryMotionView.cpp
inline CPlanetaryMotionDoc* CPlanetaryMotionView::GetDocument() const
   { return reinterpret_cast<CPlanetaryMotionDoc*>(m_pDocument); }
#endif

