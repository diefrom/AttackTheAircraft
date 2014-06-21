#pragma once

#include "resource.h"
class Aircraft
{
public:
	Aircraft(void);
	~Aircraft(void);

	//int m_nClose;
	int m_nFlag;
	int m_nOpen;
	CPoint m_ptBegin;

	void draw(CDC *cdc);
};

