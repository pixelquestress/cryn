// SnowFlake.h: interface for the CSnowFlake class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNOWFLAKE_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
#define AFX_SNOWFLAKE_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>

class CSnowFlake  
{
protected:
	int x, y;
	int Speed;
	bool bBlizzard; // Snow moving fast

public:
	CDXSprite *Sprite;
	CDXTile *Tile;
	CDXScreen *Screen;

	CSnowFlake();
	virtual ~CSnowFlake();

	void Load(CDXScreen *screen, bool bblizzard = false);
	void Draw();
	void Move(int iDirection = 0);

};

#endif // !defined(AFX_SNOWFLAKE_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
