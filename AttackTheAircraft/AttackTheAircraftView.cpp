
// AttackTheAircraftView.cpp : CAttackTheAircraftView 类的实现
//

#include "stdafx.h"
#include <mmsystem.h>
#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "AttackTheAircraft.h"
#endif

#include "AttackTheAircraftDoc.h"
#include "AttackTheAircraftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

#define GOCOUNT 30
#define KILLCOUNT 5

// CAttackTheAircraftView

IMPLEMENT_DYNCREATE(CAttackTheAircraftView, CView)

BEGIN_MESSAGE_MAP(CAttackTheAircraftView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CAttackTheAircraftView 构造/析构

CAttackTheAircraftView::CAttackTheAircraftView()
	:m_nGoGount(0), m_nKillCount(0)
{
	// TODO: 在此处添加构造代码

}

CAttackTheAircraftView::~CAttackTheAircraftView()
{
}

BOOL CAttackTheAircraftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CAttackTheAircraftView 绘制

void CAttackTheAircraftView::OnDraw(CDC* pDC)
{
	CAttackTheAircraftDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	for (int i = 0;i < 10;i++)
	{
		for (int j = 0;j < 10;j++)
		{
			m_data[i][j].draw(pDC);
		}
	}

	CString goCount;
	CString skillCount;
	goCount.Format(_T("步数：%d/%d"),m_nGoGount, GOCOUNT);
	skillCount.Format(_T("飞机：%d/%d"),m_nKillCount, KILLCOUNT);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(goCount, &CRect(CPoint(10, GRIDWIDTH*10),CSize(90, 40)),DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	pDC->DrawText(skillCount, &CRect(CPoint(GRIDWIDTH*10 - 90, GRIDWIDTH*10),CSize(70, 40)),DT_CENTER | DT_SINGLELINE | DT_VCENTER);


}


// CAttackTheAircraftView 打印

BOOL CAttackTheAircraftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CAttackTheAircraftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CAttackTheAircraftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CAttackTheAircraftView 诊断

#ifdef _DEBUG
void CAttackTheAircraftView::AssertValid() const
{
	CView::AssertValid();
}

void CAttackTheAircraftView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAttackTheAircraftDoc* CAttackTheAircraftView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAttackTheAircraftDoc)));
	return (CAttackTheAircraftDoc*)m_pDocument;
}
#endif //_DEBUG


// CAttackTheAircraftView 消息处理程序


void CAttackTheAircraftView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	//srand((unsigned)time(NULL));

	// TODO: 在此添加专用代码和/或调用基类
	InitAircraft();
	PlaySound((LPCTSTR)IDR_WAV_BK, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
}


int CAttackTheAircraftView::InitAircraft(void)
{
	int airCount = 0; 
	srand((unsigned)time(NULL));
	int nTyepA = 0;

	m_nGoGount = 0;
	m_nKillCount = 0;
	InvalidateRect(&CRect(CPoint(10, GRIDWIDTH*10),CSize(GRIDWIDTH*10+12, 40)));


	//绘制每一个grid
	CPoint ptTmp;
	for (int i = 0; i< 10; i++)
	{
		for (int j = 0;j < 10; j++)
		{
			ptTmp.x = j * GRIDWIDTH;
			ptTmp.y = i * GRIDWIDTH;
			m_data[i][j].m_ptBegin = ptTmp;
			m_data[i][j].m_nFlag = CLOSE;
			m_data[i][j].m_nOpen = EMPTY;
		}
	}

	int nStart = rand() %3;
	for (int i = nStart;i < 8;i++)
	{
		bool isexit = false;
		for (int j = 0; j < 8;j++)
		{
			nTyepA = rand() % 4;
			if (i == 7 && (nTyepA == TOP || nTyepA == BOTTOM))
			{
				continue;
			}
			if (j == 7 && (nTyepA == LEFT || nTyepA == RIGHT))
			{
				continue;
			}
			if (DiscoverAircraft(i, j, nTyepA))
			{
				airCount++;
			}
			if (airCount == KILLCOUNT)
			{
				isexit = true;
				break;
			}
		}
		if (isexit)
		{
			break;
		}
	}



	return 0;
}


bool CAttackTheAircraftView::DiscoverAircraft(int i, int j, int nTypeA)
{
	bool isAircraft = false;
	switch(nTypeA)
	{
	case TOP:
		if (IsTop(i, j))
		{
			AirTop(i, j);
			isAircraft = true;
		}		
		break;
	case BOTTOM:
		if (IsBottom(i, j))
		{
			AirBottom(i, j);
			isAircraft = true;
		}		
		break;
	case LEFT:
		if (IsLeft(i, j))
		{
			AirLeft(i, j);
			isAircraft = true;
		}		
		break;
	case RIGHT:
		if (IsRight(i, j))
		{
			AirRight(i, j);
			isAircraft = true;
		}	
		break;
	}
	return isAircraft;
}




bool CAttackTheAircraftView::IsTop(int i, int j)
{
	if ((m_data[i+1][j].m_nOpen != EMPTY) || (m_data[i+3][j].m_nOpen != EMPTY))
	{
		return false;
	}

	for (int k = i; k < i+4 ; k++)
	{
		if (m_data[k][j+1].m_nOpen != EMPTY)
		{
			return false;
		}
	}

	if ((m_data[i+1][j+2].m_nOpen != EMPTY) || (m_data[i+3][j+2].m_nOpen != EMPTY))
	{
		return false;
	}
	return true;
}


bool CAttackTheAircraftView::IsLeft(int i, int j)
{
	if ((m_data[i][j+1].m_nOpen != EMPTY) || (m_data[i][j+3].m_nOpen != EMPTY))
	{
		return false;
	}

	for (int k = j; k < j+4 ; k++)
	{
		if (m_data[i+1][k].m_nOpen != EMPTY)
		{
			return false;
		}
	}

	if ((m_data[i+2][j+1].m_nOpen != EMPTY) || (m_data[i+2][j+3].m_nOpen != EMPTY))
	{
		return false;
	}
	return true;
}

bool CAttackTheAircraftView::IsBottom(int i, int j)
{
	if ((m_data[i][j].m_nOpen != EMPTY) || (m_data[i+2][j].m_nOpen != EMPTY))
	{
		return false;
	}

	for (int k = i; k < i+4 ; k++)
	{
		if (m_data[k][j+1].m_nOpen != EMPTY)
		{
			return false;
		}
	}

	if ((m_data[i][j+2].m_nOpen != EMPTY) || (m_data[i+2][j+2].m_nOpen != EMPTY))
	{
		return false;
	}
	return true;
}


bool CAttackTheAircraftView::IsRight(int i, int j)
{
	if ((m_data[i][j].m_nOpen != EMPTY) || (m_data[i][j+2].m_nOpen != EMPTY))
	{
		return false;
	}

	for (int k = j; k < j+4 ; k++)
	{
		if (m_data[i+1][k].m_nOpen != EMPTY)
		{
			return false;
		}
	}

	if ((m_data[i+2][j].m_nOpen != EMPTY) || (m_data[i+2][j+2].m_nOpen != EMPTY))
	{
		return false;
	}
	return true;
}

int CAttackTheAircraftView::AirTop(int i, int j)
{
	m_data[i+1][j].m_nOpen = AT;
	m_data[i+3][j].m_nOpen = AT;
	for (int k = i+1; k < i+4 ; k++)
	{
		m_data[k][j+1].m_nOpen = AT;
	}
	m_data[i+1][j+2].m_nOpen = AT; 
	m_data[i+3][j+2].m_nOpen = AT;

	m_data[i][j+1].m_nOpen = KILL;
	return 0;
}

int CAttackTheAircraftView::AirLeft(int i, int j)
{
	m_data[i][j+1].m_nOpen = AT;
	m_data[i][j+3].m_nOpen = AT;
	for (int k = j+1; k < j+4 ; k++)
	{
		m_data[i+1][k].m_nOpen = AT;
	}
	m_data[i+2][j+1].m_nOpen = AT; 
	m_data[i+2][j+3].m_nOpen = AT;

	m_data[i+1][j].m_nOpen = KILL;
	return 0;
}


int CAttackTheAircraftView::AirBottom(int i, int j)
{
	m_data[i][j].m_nOpen = AT;
	m_data[i+2][j].m_nOpen = AT;
	for (int k = i; k < i+3 ; k++)
	{
		m_data[k][j+1].m_nOpen = AT;
	}
	m_data[i][j+2].m_nOpen = AT;
	m_data[i+2][j+2].m_nOpen = AT;

	m_data[i+3][j+1].m_nOpen = KILL;

	return 0;
}

int CAttackTheAircraftView::AirRight(int i, int j)
{
	m_data[i][j].m_nOpen = AT;
	m_data[i][j+2].m_nOpen = AT;
	for (int k = j; k < j+3 ; k++)
	{
		m_data[i+1][k].m_nOpen = AT;
	}
	m_data[i+2][j].m_nOpen = AT;
	m_data[i+2][j+2].m_nOpen = AT;

	m_data[i+1][j+3].m_nOpen = KILL;

	return 0;
}


void CAttackTheAircraftView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	CDC * cdc = GetDC();
	int x, y;
	y = point.x / GRIDWIDTH;
	x = point.y / GRIDWIDTH;

	//PlayMusic(x, y);

	m_nGoGount++;
	InvalidateRect(&CRect(CPoint(10, GRIDWIDTH*10),CSize(90, 40)));
	if (m_data[x][y].m_nOpen == KILL && m_data[x][y].m_nFlag == CLOSE)
	{
		m_nKillCount++;
		InvalidateRect(&CRect(CPoint(GRIDWIDTH*10 - 90, GRIDWIDTH*10),CSize(70, 40)));
	}


	m_data[x][y].m_nFlag = OPEN;
	m_data[x][y].draw(cdc);


	


	if (m_nKillCount == KILLCOUNT)
	{
		if (AfxMessageBox(_T("You Win!\n Play Again?"), MB_YESNO) == IDYES)
		{
			InitAircraft();
			Invalidate(FALSE);
		}else
		{
			AfxGetMainWnd()->PostMessage(WM_CLOSE, 0, 0);
		}
	}

	if (m_nGoGount == GOCOUNT)
	{
		if (AfxMessageBox(_T("You Lose!\n Play Again?"), MB_YESNO) == IDYES)
		{
			InitAircraft();
			Invalidate(FALSE);
		}else
		{
			AfxGetMainWnd()->PostMessage(WM_CLOSE, 0, 0);
		}
	}

	CView::OnLButtonDown(nFlags, point);
}


void CAttackTheAircraftView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC * cdc = GetDC();
	int x, y;
	y = point.x / GRIDWIDTH;
	x = point.y / GRIDWIDTH;
	if ( m_data[x][y].m_nFlag != OPEN)
	{
		m_data[x][y].m_nFlag == FLAG ? m_data[x][y].m_nFlag = CLOSE : m_data[x][y].m_nFlag = FLAG;
	}

	InvalidateRect(&CRect(m_data[x][y].m_ptBegin,CSize(GRIDWIDTH, GRIDWIDTH)), FALSE);

	CView::OnRButtonDown(nFlags, point);
}


int CAttackTheAircraftView::PlayMusic(int x, int y)
{
	if (m_data[x][y].m_nOpen == EMPTY && m_data[x][y].m_nFlag == CLOSE)
	{
		PlaySound((LPCTSTR)IDR_WAV_EMPTY, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_NOSTOP);
	}

	if (m_data[x][y].m_nOpen == AT && m_data[x][y].m_nFlag == CLOSE)
	{
		PlaySound((LPCTSTR)IDR_WAV_AT, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_NOSTOP);
	}

	if (m_data[x][y].m_nOpen == KILL && m_data[x][y].m_nFlag == CLOSE)
	{
		PlaySound((LPCTSTR)IDR_WAV_KILL, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_NOSTOP);
	}

	return 0;
}
