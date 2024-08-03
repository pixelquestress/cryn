// Gnat.h: interface for the CGnat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Gnat_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
#define AFX_Gnat_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>

class CGnat  
{
private:
	int x, y;
	int Speed;
	int iTicker;

public:
	CDXSprite *Sprite;
	CDXTile *Tile;
	CDXScreen *Screen;

	CGnat();
	virtual ~CGnat();

	void Load(CDXScreen *screen);
	void Unload() { SAFEDELETE(Sprite); SAFEDELETE(Tile); };
	void Draw();
	void Move(int iDirection = 0);

};

#endif // !defined(AFX_Gnat_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
