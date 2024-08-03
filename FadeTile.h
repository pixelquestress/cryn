// FadeTile.h: interface for the CFadeTile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FADETILE_H__27352E55_FD50_41D1_9FA0_90356D4C04CF__INCLUDED_)
#define AFX_FADETILE_H__27352E55_FD50_41D1_9FA0_90356D4C04CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>
extern unsigned short RGB565(int r, int g, int b);

class CFadeTile  
{
private:
	int PixelX, PixelY;
	int RGBShade;
	int iShade;
	CDXScreen *Screen;
	COLORREF TileBuffer[40][40];

public:
	CFadeTile();
	virtual ~CFadeTile();

	void SetPos(int x, int y) { PixelX = x; PixelY = y; };
	void SetShade(int aiShade) { RGBShade = aiShade; iShade = aiShade; };
	void SetScreen(CDXScreen *aScreen) { Screen = aScreen; };
	void CopyTile(int x, int y, int bShade=0, int iShadeLevel=19);
	void DrawTile();
//	void Draw();
};

#endif // !defined(AFX_FADETILE_H__27352E55_FD50_41D1_9FA0_90356D4C04CF__INCLUDED_)
