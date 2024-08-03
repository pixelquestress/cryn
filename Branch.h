// Branch.h: interface for the CBranch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Branch_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
#define AFX_Branch_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>
#include "BattleEngine.h"

class CBranch  
{
private:
	int x, y;
	int Speed;
	int iTicker;

public:
	CDXSprite *Sprite;
	CDXTile *Tile;
	CDXScreen *Screen;

	CBranch();
	virtual ~CBranch();

	void SetSpeed(int s) { Speed = s; };
	void Load(CDXScreen *screen);
	void Draw();
	void Move(int iDirection = DOWN);

};

#endif // !defined(AFX_Branch_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
