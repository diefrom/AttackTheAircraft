#include "StdAfx.h"
#include "Aircraft.h"



Aircraft::Aircraft(void)
	:m_nOpen(EMPTY), m_nFlag(CLOSE)
{
}


Aircraft::~Aircraft(void)
{
}

void Aircraft::draw(CDC *cdc)
{
	static HBITMAP hBmpClose = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_CLOSE));
	static HBITMAP hBmpFlag = LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BMP_FLAG));
	static HBITMAP hBmpEmpty = LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BMP_EMPTY));
	static HBITMAP hBmpAt = LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BMP_AT));
	static HBITMAP hBmpKill = LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BMP_KILL));

	HBITMAP hBmp;

	switch(m_nFlag)
	{
	case CLOSE:
		hBmp = hBmpClose;
		break;
	case FLAG:
		hBmp = hBmpFlag;
		break;
	case OPEN:
		switch(m_nOpen)
		{
		case EMPTY:
			hBmp = hBmpEmpty;
			break;
		case AT:
			hBmp = hBmpAt;
			break;
		case KILL:
			hBmp = hBmpKill;
			break;
		}
	}

	BITMAP bitMap;
	GetObject(hBmp, sizeof(bitMap), &bitMap);
	CDC  pdc;
	bool b = pdc.CreateCompatibleDC(cdc);
	pdc.SelectObject(hBmp);
	cdc->StretchBlt(m_ptBegin.x, m_ptBegin.y, GRIDWIDTH, GRIDWIDTH, &pdc, 0, 0, bitMap.bmWidth, bitMap.bmHeight, SRCCOPY);


}
