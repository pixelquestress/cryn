// InfoBox.h: interface for the CInfoBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFOBOX_H__E1617AA0_E111_11D0_983D_AA78BD133344__INCLUDED_)
#define AFX_INFOBOX_H__E1617AA0_E111_11D0_983D_AA78BD133344__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>

#define X_OFFSET 60
#define Y_OFFSET 25
#define CHARACTERS_PER_LINE 72
#define FONT_SIZE 13

class CInfoBox  
{
private:
	CDXScreen *Screen;
	CDXSprite *Sprite;
	CDXTile *Tile;
	CDXInput *Input;
	CDXSound *Sound;
	CDXSoundBuffer *MsgBoxSound;

	bool Initialized;
	int iLineCount;

public:
	CInfoBox();
	CInfoBox(CDXScreen *screen, CDXInput *input, CDXSound *sound, int Type = 1) { Initialize(screen, input, sound, Type); };

	virtual ~CInfoBox();

	// Loads bitmaps needed into memory.
	// Must be called before Display2().
	void Initialize(CDXScreen *screen, CDXInput *input, CDXSound *sound, int Type = 1);

	// Displays the message box at (x,y)
	void Display2(int x, int y, char *strMessage, bool bSound = true);
	void Display2(char *strMessage, bool bSound = true) { iLineCount = 0; Display2(10, 335, strMessage, bSound); };
};

#endif // !defined(AFX_INFOBOX_H__E1617AA0_E111_11D0_983D_AA78BD133344__INCLUDED_)
