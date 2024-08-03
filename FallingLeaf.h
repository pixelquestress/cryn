// FallingLeaf.h: interface for the CFallingLeaf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FallingLeaf_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
#define AFX_FallingLeaf_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>

class CFallingLeaf  
{
private:
	int x, y;
	int Speed;
	int iTicker, iTicker2;
	float zoom;
	int initial_x;
	int life_count;
	int life_time;
	bool bAnimRight;
	bool bLeft;
	int iRotateSpeed; // speed at which leaf rotates
	bool bZoomer; // zoomer or alphavalued leaf?

public:
	CDXSprite *Sprite;
	CDXTile *Tile;
	CDXScreen *Screen;

	CFallingLeaf();
	virtual ~CFallingLeaf();

	void Load(CDXScreen *screen);
	void Unload() { SAFEDELETE(Sprite); SAFEDELETE(Tile); };
	void Draw();
	void Move(int iDirection = 0);

};

#endif // !defined(AFX_FallingLeaf_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
