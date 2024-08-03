// Bat.h: interface for the CBat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Bat_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
#define AFX_Bat_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>

class CBat  
{
private:
	int x, y;
	int Speed;
	int iTicker;
	int FlyingDuration; // ticks bat will continue flying before roosting.
	bool bFlying; // true if bat is flying.
	bool bFlyingRight; // true if flying right, otherwise flying left.

public:
	CDXSprite *Sprite;
	CDXTile *Tile;
	CDXScreen *Screen;
	CDXSoundBuffer *Bat1Sound, *Bat2Sound;

	CBat();
	virtual ~CBat();

	void Load(CDXScreen *screen, CDXSound *sound);
	void Unload() { SAFEDELETE(Sprite); SAFEDELETE(Tile); };
	void Draw();
	void Move(int iDirection = 0);
	bool isFlying() { return bFlying; };
};

#endif // !defined(AFX_Bat_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
