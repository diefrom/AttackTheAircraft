
// AttackTheAircraftView.h : CAttackTheAircraftView ��Ľӿ�
//

#pragma once
#include "Aircraft.h"


class CAttackTheAircraftView : public CView
{
protected: // �������л�����
	CAttackTheAircraftView();
	DECLARE_DYNCREATE(CAttackTheAircraftView)

// ����
public:
	CAttackTheAircraftDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CAttackTheAircraftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	Aircraft m_data[10][10];
	int m_nKillCount;
	int m_nGoGount;

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	int InitAircraft(void);
	bool DiscoverAircraft(int i, int j, int nTypeA);
	bool IsTop(int i, int j);
	bool IsLeft(int i, int j);
	bool IsBottom(int i, int j);
	bool IsRight(int i, int j);
	int AirTop(int i, int j);
	int AirLeft(int i, int j);
	int AirBottom(int i, int j);
	int AirRight(int i, int j);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	int PlayMusic(int x, int y);
};

#ifndef _DEBUG  // AttackTheAircraftView.cpp �еĵ��԰汾
inline CAttackTheAircraftDoc* CAttackTheAircraftView::GetDocument() const
   { return reinterpret_cast<CAttackTheAircraftDoc*>(m_pDocument); }
#endif

