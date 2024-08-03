// Menu.h: interface for the CMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENU_H__66506D53_BF83_4D06_B445_D3E388CC523A__INCLUDED_)
#define AFX_MENU_H__66506D53_BF83_4D06_B445_D3E388CC523A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>
#include "cdxmenu.h"

#define TITLE_COLOR			RGB(100,255,255)
#define MENU_COLOR_ON		RGB(255,255,0)
#define MENU_COLOR_OFF		RGB(255,255,255)
#define MENU_COLOR			RGB(0, 0, 255)

class CMenu
{
protected:
	CDXScreen *Screen;
	CDXInput *Input;
	CDXMenu MyMenu;
	CDXSurface *Temp;
	CDXSound *Sound;
	CDXSoundBuffer *ClickSound;
	CDXTile *BackTile;
	CDXSprite *BackSprite;

	char strTitle[10000];

	int x, y;
	int Width, Height; // dimensions of menu window.

public:
	CMenu();
	virtual ~CMenu();

	void SetSpacing(int x) { MyMenu.SetSpacing(x); };
	void SetSurface(CDXSurface *surface) { MyMenu.SetSurface(surface); };
	void SetPos(int ax, int ay) { x = ax; y = ay; };
	void SetTitle(char *strtitle);
	void AddItem(char *item, bool bSelectable = true);

	void Load(CDXScreen *screen, CDXInput *input, CDXSound *sound, char *strtitle, int ax = 200, int ay = 200);
	void Draw(bool bInit = true);  // draw with a black rectangle background.
	void Draw2(bool bRect = false); // draw with no black rectangle.
	int Popup();
	int Popup2(); // uses draw2() function.

	void Down() { if (Sound != NULL) ClickSound->Play(); MyMenu.Down(); };
	void Up() { if (Sound != NULL) ClickSound->Play(); MyMenu.Up(); };
	int Enter() { return MyMenu.Enter(); };
};

#endif // !defined(AFX_MENU_H__66506D53_BF83_4D06_B445_D3E388CC523A__INCLUDED_)
