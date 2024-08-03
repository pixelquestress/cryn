// Menu.cpp: implementation of the CMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "Menu.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
unsigned short RGB565(int r, int g, int b)
{
    // Remove least significant bits
    r >>= 3; // 8-bit to 5-bit
    g >>= 2; // 8-bit to 6-bit
    b >>= 3; // 8-bit to 5-bit
    // Now arrange
    r <<= 11;
    g <<= 5;
    unsigned short c = r + g + b;

    return c;
}

CMenu::CMenu()
{
	x = 200;
	y = 200;
	Width = 200;
	Height = 200;
	Temp = NULL;
	ClickSound = 0;
	BackSprite = NULL;
	BackTile = NULL;
}

CMenu::~CMenu()
{
	SAFEDELETE(Temp);
	SAFEDELETE(ClickSound);
	SAFEDELETE(BackSprite);
	SAFEDELETE(BackTile);
}

void CMenu::SetTitle(char *strtitle)
{
	if (strlen(strtitle) < 10000)
	{
		strcpy(strTitle, strtitle);
		MyMenu.SetTitle(strTitle, TITLE_COLOR);
	}
}

void CMenu::Load(CDXScreen *screen, CDXInput *input, CDXSound *sound, char *strtitle, int ax, int ay)
{
	Screen = screen;
	Input = input;
	Sound = sound;

	if (Sound != NULL)
	{
		ClickSound = new CDXSoundBuffer;
		ClickSound->Load(Sound, (char*)"music/click.wav", 4);
	}

	SetTitle(strtitle);

//	MyMenu.Create(Screen->GetFront(), 30);
	MyMenu.Create(Screen->GetBack(), 30);
	MyMenu.SetTitle(strTitle, TITLE_COLOR);
	MyMenu.SetWrap(true);

	Width = (strlen(strtitle) + 10) * 7;
	Height = 30;

	x = ax;
	y = ay;

	BackTile = new CDXTile();
	BackSprite = new CDXSprite();
	if (BackTile->Create(Screen, (char*)"graphics/menu_background.bmp", 100, 100, 0) == FALSE )
		CDXError( Screen , (char*)"could not load tiles from file bat file" );
	// set the top left pixel in tiles bitmap as transparent color
	BackTile->SetColorKey(0);
	BackSprite->Create(BackTile);
//	BackSprite->SetAlphaValue(150);*/
}

void CMenu::AddItem(char *item, bool bSelectable)
{
	int index = MyMenu.AddItem(item, MENU_COLOR_ON, MENU_COLOR_OFF);
	MyMenu.EnableItem(index, bSelectable);

	// Adjust width of menu window.
	if (strlen(item) > (Width - 10))
	{
		Width = (strlen(item) + 10) * 7;
	}

	Height += 30;
}

void CMenu::Draw(bool bInit/*=true*/)
{
	DWORD w,h;
	w = Screen->GetFront()->GetWidth();
	h = Screen->GetFront()->GetHeight();
	
	RECT mRect;
	mRect.left = 0;
	mRect.top = 0;
	mRect.right = w;
	mRect.bottom = h;
	static int px = x-2, py = y, direction = 1; // 1=down, 2 = right, 3 = up, 4 = left

	if (bInit)
	{
		// Copy Front to Temp
		if (Temp != NULL)
			SAFEDELETE(Temp);

		Temp = new CDXSurface();
		Temp->Create(Screen, w, h, CDXMEM_SYSTEMONLY);
		Temp->ChangeFont("Impact", 0, 18);
		
		// Copy front to temp buffer.
		Screen->GetFront()->DrawBlk(Temp, 0, 0, &mRect);

		px = x - 2;
		py = y;
		direction = 1;
	}

	if (bInit)
	{
		if (Temp != NULL)
		{
			// Copy Temp to Back for drawing.
			Temp->DrawBlk(Screen->GetBack(), 0, 0, &mRect);
		}

		// Draw background of menu alpha-blended.
	/*	CDXSurface BlackTemp;
		RECT MyRect;
		MyRect.top = 0;
		MyRect.left = 0;
		MyRect.right = Width;
		MyRect.bottom = Height;
		BlackTemp.Create(Screen, Width, Height, CDXMEM_SYSTEMONLY);
		BlackTemp.Fill(RGB565(10,10,10));
		BlackTemp.DrawBlkAlpha(Screen->GetBack(), x, y, &MyRect, 10);
		/*for (int ax=x; ax < x + Width; ax++)
			for (int ay=y; ay < y + Height; ay++)
			{
				Screen->GetBack()->PutAAPixel(ax, ay, RGB565(0,0,10), 250);
			}*/
	}

	//if (BackSprite != NULL) BackSprite->Draw(Screen->GetBack() , x, y, CDXBLT_TRANSALPHAFAST);
//	Screen->GetBack()->FillRect(x, y, x + Width, y + Height, MENU_COLOR);
	BackSprite->SetPos(x, y);
	BackSprite->SetStretchWidth(Width);
	BackSprite->SetStretchHeight(Height);
	BackSprite->Draw(Screen->GetBack(), 0, 0, CDXBLT_BLKSTRETCHED);

	Screen->GetBack()->AALine(x-1, y, x-1, y + Height, RGB(20, 0, 0));
	Screen->GetBack()->AALine(x-2, y, x-2, y + Height, RGB(40, 0, 0));
	Screen->GetBack()->AALine(x-3, y, x-3, y + Height, RGB(60, 0, 0));
	Screen->GetBack()->AALine(x-4, y, x-4, y + Height, RGB(80, 0, 0));

	Screen->GetBack()->AALine(x, y-1, x + Width, y-1, RGB(20, 0, 0));
	Screen->GetBack()->AALine(x, y-2, x + Width, y-2, RGB(40, 0, 0));
	Screen->GetBack()->AALine(x, y-3, x + Width, y-3, RGB(60, 0, 0));
	Screen->GetBack()->AALine(x, y-4, x + Width, y-4, RGB(80, 0, 0));

	Screen->GetBack()->AALine(x + Width, y, x + Width, y + Height, RGB(20, 0, 0));
	Screen->GetBack()->AALine(x + Width+1, y, x + Width+1, y + Height, RGB(40, 0, 0));
	Screen->GetBack()->AALine(x + Width+2, y, x + Width+2, y + Height, RGB(60, 0, 0));
	Screen->GetBack()->AALine(x + Width+3, y, x + Width+3, y + Height, RGB(80, 0, 0));

	Screen->GetBack()->AALine(x, y + Height, x + Width, y + Height, RGB(20, 0, 0));
	Screen->GetBack()->AALine(x, y + Height+1, x + Width, y + Height+1, RGB(40, 0, 0));
	Screen->GetBack()->AALine(x, y + Height+2, x + Width, y + Height+2, RGB(60, 0, 0));
	Screen->GetBack()->AALine(x, y + Height+3, x + Width, y + Height+3, RGB(80, 0, 0));

/*	Screen->GetBack()->PutPixel(px, py, RGB(3, 3, 3));
	switch (direction)
	{
		case 1 : 
			py+=5; 
			if (py >= y + Height) direction++; 
			else
			{
				Screen->GetBack()->PutPixel(px, py-1, RGB(5, 5, 5));
				Screen->GetBack()->PutPixel(px, py-4, RGB(6, 6, 6));
				Screen->GetBack()->PutPixel(px, py-7, RGB(7, 7, 7));
			}
			break;
		case 2 : 
			px+=5; 
			if (px > x + Width) direction++;
			else
			{
				Screen->GetBack()->PutPixel(px-1, py, RGB(5, 5, 5));
				Screen->GetBack()->PutPixel(px-4, py, RGB(6, 6, 6));
				Screen->GetBack()->PutPixel(px-7, py, RGB(7, 7, 7));
			}
			break;
		case 3 : 
			py-=5; 
			if (py <= y) direction++; 
			else
			{
				Screen->GetBack()->PutPixel(px, py+1, RGB(5, 5, 5));
				Screen->GetBack()->PutPixel(px, py+4, RGB(6, 6, 6));
				Screen->GetBack()->PutPixel(px, py+7, RGB(7, 7, 7));
			}
			break;
		case 4 : 
			px-=5; 
			if (px < x-1) direction = 1; 
			else
			{
				Screen->GetBack()->PutPixel(px+1, py, RGB(5, 5, 5));
				Screen->GetBack()->PutPixel(px+4, py, RGB(6, 6, 6));
				Screen->GetBack()->PutPixel(px+7, py, RGB(7, 7, 7));
			}
			break;
	};
*/
	MyMenu.Draw(x + 10, y + 10);

	// Draw it on front.
	Screen->Flip();
}

void CMenu::Draw2(bool bRect)
{
	// Draw with no black rectangle.
	if (bRect)
	{
		MyMenu.GetSurface()->FillRect(x-10, y-10, x + Width/2, y + Height/2 + 10, RGB(1,1,1));
	}

	MyMenu.Draw(x, y);
}

int CMenu::Popup()
{
	// Shows the menu, waits for input, returns result.
	Draw();

	int MenuResult = -1;
	while (MenuResult == -1)
	{
		Draw(false);

		Input->Update();
		Input->UpdateLastKey(true);

		// Inside Menu
		if (Input->GetLastKey() == 208)
		{
			Down();
		}
		else if (Input->GetLastKey() == 200)
		{
			Up();
		}
		else if (Input->GetLastKey() == 28 || Input->GetLastKey() == 57)
		{
			MenuResult = MyMenu.Enter();
			return MenuResult;
		}
	}

	return MenuResult;
}

int CMenu::Popup2()
{
	// Shows the menu, waits for input, returns result.
	// Uses Draw2() function, no black rectangle.
	Draw2();

	int MenuResult = -1;
	while (MenuResult == -1)
	{
		Input->Update();
		Input->UpdateLastKey(true);

		// Inside Menu
		if (Input->GetLastKey() == 208)
		{
			MyMenu.Down();
			Draw2();
		}
		else if (Input->GetLastKey() == 200)
		{
			MyMenu.Up();
			Draw2();
		}
		else if (Input->GetLastKey() == 28 || Input->GetLastKey() == 57)
		{
			MenuResult = MyMenu.Enter();
			return MenuResult;
		}
	}

	return MenuResult;
}
