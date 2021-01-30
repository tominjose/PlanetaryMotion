
// PlanetaryMotionView.cpp : implementation of the CPlanetaryMotionView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PlanetaryMotion.h"
#endif

#include "PlanetaryMotionDoc.h"
#include "PlanetaryMotionView.h"
#include "CTestThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanetaryMotionView

IMPLEMENT_DYNCREATE(CPlanetaryMotionView, CView)

BEGIN_MESSAGE_MAP(CPlanetaryMotionView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlanetaryMotionView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_THREAD_START, &CPlanetaryMotionView::OnThreadStart)
	ON_COMMAND(ID_THREAD_PAUSE, &CPlanetaryMotionView::OnThreadPause)
	ON_COMMAND(ID_THREAD_RESUME, &CPlanetaryMotionView::OnThreadResume)
END_MESSAGE_MAP()

// CPlanetaryMotionView construction/destruction

CPlanetaryMotionView::CPlanetaryMotionView() noexcept
{
	angle = 0, a1 = 200, b1 = 190, a2 = 295, b2 = 240;
	t = 3.14 / 180.0;
	
	n = 0;

}

CPlanetaryMotionView::~CPlanetaryMotionView()
{
}

BOOL CPlanetaryMotionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlanetaryMotionView drawing

void CPlanetaryMotionView::OnDraw(CDC* pDC)
{
	CPlanetaryMotionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//largest orbit
	CPen redpen;
	n++;
	redpen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldpen1 = pDC->SelectObject(&redpen);
	pDC->Ellipse(10, 70, 600, 550);
	pDC->SelectObject(pOldpen1);

	//Smallest orbit
	CPen greenpen;
	greenpen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldpen2 = pDC->SelectObject(&greenpen);
	pDC->Ellipse(100, 120, 500, 500);
	pDC->SelectObject(pOldpen1);

    //Sun
	CBrush sun(RGB(255,165,0));
	CBrush* pOldpen3 = pDC->SelectObject(&sun);
	pDC->Ellipse(250, 250, 330, 330);
	pDC->SelectObject(pOldpen3);

	//Small rotation
	for (int i = 0; i < n; i++)
	{
		angle = i;
		x1 = a1 * cos(t * angle);

		y1 = b1 * sin(t * angle);

	}
	for (int i = 0; i < n  ; i++)
	{
		CBrush brushblue(RGB(192, 192, 192));
		CBrush* pOldBrush1 = pDC->SelectObject(&brushblue);
        pDC->Ellipse(300 + x1 + 20, 300 + y1 + 20, 310 + x1 - 20, 310 + y1 - 20);

		Invalidate();
		pDC->SelectObject(pOldBrush1);
	}


	for (int i = 0; i < n; i++)
	{
		angle = i;
		x2 = a2 * cos(t * angle);

		y2 = b2 * sin(t * angle);

	}
	for (int i = 0; i < n; i++)
	{
		CBrush brushblue(RGB(0, 0, 255));
		CBrush* pOldBrush = pDC->SelectObject(&brushblue);


		pDC->Ellipse(305 + x2 + 20, 310 + y2 + 20, 305 + x2 - 20, 310 + y2 - 20);

		Invalidate();
		pDC->SelectObject(pOldBrush);


	}
}


// CPlanetaryMotionView printing


void CPlanetaryMotionView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPlanetaryMotionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlanetaryMotionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlanetaryMotionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPlanetaryMotionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlanetaryMotionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPlanetaryMotionView diagnostics

#ifdef _DEBUG
void CPlanetaryMotionView::AssertValid() const
{
	CView::AssertValid();
}

void CPlanetaryMotionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlanetaryMotionDoc* CPlanetaryMotionView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlanetaryMotionDoc)));
	return (CPlanetaryMotionDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlanetaryMotionView message handlers


void CPlanetaryMotionView::OnThreadStart()
{
	pThread=AfxBeginThread(CTestThread::RunThreadFunction, this);
}


void CPlanetaryMotionView::OnThreadPause()
{
	pThread->SuspendThread();
}


void CPlanetaryMotionView::OnThreadResume()
{
	pThread->ResumeThread();
}
