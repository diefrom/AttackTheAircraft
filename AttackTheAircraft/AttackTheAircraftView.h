
// AttackTheAircraftView.h : CAttackTheAircraftView 类的接口
//

#pragma once
#include "Aircraft.h"


class CAttackTheAircraftView : public CView
{
protected: // 仅从序列化创建
	CAttackTheAircraftView();
	DECLARE_DYNCREATE(CAttackTheAircraftView)

// 特性
public:
	CAttackTheAircraftDoc* GetDocument() const;

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
	virtual ~CAttackTheAircraftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	Aircraft m_data[10][10];
	int m_nKillCount;
	int m_nGoGount;

// 生成的消息映射函数
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

#ifndef _DEBUG  // AttackTheAircraftView.cpp 中的调试版本
inline CAttackTheAircraftDoc* CAttackTheAircraftView::GetDocument() const
   { return reinterpret_cast<CAttackTheAircraftDoc*>(m_pDocument); }
#endif

