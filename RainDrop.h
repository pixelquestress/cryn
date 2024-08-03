// RainDrop.h: interface for the CRainDrop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RainDrop_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
#define AFX_RainDrop_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>

class CRainDrop  
{
protected:
	int x, y;
	int Speed;
//	bool bBlizzard; // Snow moving fast

public:
	CDXSprite *Sprite;
	CDXTile *Tile;
	CDXScreen *Screen;

	CRainDrop();
	virtual ~CRainDrop();

	void Load(CDXScreen *screen);
	void Draw();
	void Move(int iDirection = 0);
	void HardRain() { if (Speed < 20) Speed += 10; };
	void SoftRain() { if (Speed >= 20) Speed -= 10; };

};

#endif // !defined(AFX_RainDrop_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
