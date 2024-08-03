// InfoBox.cpp: implementation of the CInfoBox class.
//
//////////////////////////////////////////////////////////////////////

#include "InfoBox.h"
#include "cdxmenu.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInfoBox::CInfoBox()
{
	Initialized = false;
	Screen = NULL;
	Sprite = NULL;
	Tile = NULL;
	iLineCount = 0;
}

CInfoBox::~CInfoBox()
{
	if (Sprite != NULL)
	{
		delete(Sprite);
		Sprite = NULL;
	}

	if (Tile != NULL)
	{
		delete(Tile);
		Tile = NULL;
	}

	SAFEDELETE(MsgBoxSound);
}

void CInfoBox::Initialize(CDXScreen *screen, CDXInput *input, CDXSound *sound, int Type)
{
	// Loads bitmaps into memory to be used for message box.
	// Load Message Box Bitmap ON.
	Screen = screen;
	Input = input;
	Sound = sound;

	char filename[1000];

	if (Type == 1)
	{
		strcpy(filename, (char*)"tiles/msgbox_yellow.bmp");
	}
	else if (Type == 2)
	{
		strcpy(filename, (char*)"tiles/msgbox_yellow.bmp");
	}

	Tile = new CDXTile();

	if (Tile->Create(Screen, filename, 620, 140, 0) == FALSE)
		CDXError( Screen , (char*)"could not load tiles from msgbox.bmp" );

	
	// set the top left pixel in tiles bitmap as transparent color
	Tile->SetColorKey(0);

	Sprite = new CDXSprite();
	Sprite->Create(Tile);

//	Sprite->SetPos(TileX, TileY);
	Sprite->SetShadowOffset(10,-10);
	Sprite->SetShadowValue(150);

	MsgBoxSound = new CDXSoundBuffer;
	MsgBoxSound->Load(Sound, (char*)"music/msgbox.wav", 4);

	Initialized = true;
	iLineCount = 0;
}

/*void CInfoBox::Display(int x, int y, CString strMessage, int Width, int Height)
{
	// Displays a message box at x,y.
	if (Width == 0)
	{
	int LengthValue = strMessage.GetLength();
	int NumLinesHeight = 1;
	// Default text box width standard CHARACTERS_PER_LINE width.
	int WidthValue = CHARACTERS_PER_LINE;
	
	if (SizeToText)
	{
		// Text box will have a width = to the text length.
		WidthValue = strMessage.GetLength();
	}

	if (LengthValue > CHARACTERS_PER_LINE)
	{
		// We have to break text into multiple lines.
		// Width is now the max characters per line.
		// Height is now the number of lines.
		NumLinesHeight = LengthValue / CHARACTERS_PER_LINE;
		WidthValue = CHARACTERS_PER_LINE;
	}

	if (Width == 0)
	{
		Width = (WidthValue * 7) + X_OFFSET;
	}

	if (Height == 0)
	{
		Height = (NumLinesHeight * FONT_SIZE) + Y_OFFSET;
	}
	} // Width, Height == 0

	Width = 150;
	Height = 60;

	// Draw Message Box Background.
	// Start at center, work outwards.
	// Draw vertical bars going outward.
	int SCROLL_SPEED = 10;
	int jj = (x+Width)/2, count = 0;
	int i;

	for (int j=(x+Width)/2; j<x+Width; j+=SCROLL_SPEED)
	{
		for (i=y; i<y+Height*2; i++)
		{
			// Left bar.
			Draw_Rectangle(j, i, j+1, i+1, 205, lpddsback);
			// Right bar.
			Draw_Rectangle(jj-count, i, jj-count+1, i+1, 205, lpddsback);
			// Draw rest of bars in between scroll speed amount.
			for (int s=1; s<=SCROLL_SPEED*2; s++)
			{
				// Left bar.
				Draw_Rectangle(j-s, i, j+1-s, i+1, 205, lpddsback);
				// Right bar.
				Draw_Rectangle(jj-count+s, i, jj-count+1+s, i+1, 205, lpddsback);
			} 
		}

		count+=SCROLL_SPEED;

		// Show new vertical line.
		DD_Flip();
		// sync to 30ish fps
		Wait_Clock(25);
		// Start the timing clock
		Start_Clock();
	}

/*	for (i=x; i<x+Width; i++)
		for (int j=y; j<y+Height*2; j++)
		{
			// Plot every other pixel so its transparent.
			if (i%2 == 0 && j%2 == 0)
			Draw_Rectangle(i, j, i+1, j+1, 205, lpddsback);

		}
*/
/*	CString strLine;
	bool bBreak = false; // when to break a line.
	for (int i=0; i < strMessage.GetLength(); i++)
	{
		// Break text into lines and display them.
		strLine += strMessage[i];

//		if (i % strMessage.GetLength() == CHARACTERS_PER_LINE)
		if (i > 0 && (i % CHARACTERS_PER_LINE == 0))
		{
			bBreak = true;
		}

		// Only break the line on spaces or punctuation.
		if (bBreak &&
			(strMessage[i] == ' ' || strMessage[i] == ',' || strMessage[i] == '.' ||
			strMessage[i] == '!' || strMessage[i] == '?'))
		{
			// Reached max characters per line.
			Draw_Text_GDI(strLine.GetBuffer(strLine.GetLength()), x + X_OFFSET, y + Y_OFFSET, RGB(255, 255, 255), lpddsback);
			strLine.Empty();
			y += FONT_SIZE + 7;
			bBreak = false;
		}
	}

	if (!strLine.IsEmpty())
	{
		// Print remaining text.
		Draw_Text_GDI(strLine.GetBuffer(strLine.GetLength()), x + X_OFFSET, y + Y_OFFSET, RGB(255, 255, 255), lpddsback);
		y += FONT_SIZE + 15;
	}

	DD_Wait_For_Vsync();
	DD_Flip();

	// clear the back drawing surface
	DD_Fill_Surface(lpddsback, 0);

	while (!KEY_DOWN(VK_ESCAPE));

	DD_Wait_For_Vsync();
	DD_Fill_Surface(lpddsprimary, 0);
	DD_Flip();

	return;
}
*/

void CInfoBox::Display2(int x, int y, char *strMessage, bool bSound)
{
	// Puts the text message inside the bitmap message box.
	if (!Initialized)
		return;

	// Copy Front to Temp
	DWORD w,h;
	w = Screen->GetFront()->GetWidth();
	h = Screen->GetFront()->GetHeight();

	CDXSurface *Temp = NULL;
	Temp = new CDXSurface();
	Temp->Create(Screen, w, h, CDXMEM_SYSTEMONLY);

	RECT mRect;
	mRect.left = 0;
	mRect.top = 0;
	mRect.right = w;
	mRect.bottom = h;

	// Copy front to temp buffer.
	Screen->GetFront()->DrawBlk(Temp, 0, 0, &mRect);

	// First, animate the box appearing.
	int FrameIndex = 0;
	Sprite->SetPos(x, y);
	Sprite->SetFrame(FrameIndex);
	Sprite->SetAlphaValue(65);

	if (bSound)
		MsgBoxSound->Play();

	iLineCount = 0;

	while (FrameIndex < 5)
	{
		// Copy Temp to Back
		Temp->DrawBlk(Screen->GetBack(), 0, 0, &mRect);

		Sprite->SetFrame(FrameIndex);
		Sprite->Draw(Screen->GetBack() , 0 , 0 , CDXBLT_TRANSALPHA);

		Screen->Flip();
		FrameIndex++;
		
//		Sleep(5);
	}

	x += X_OFFSET;
	y += Y_OFFSET;

	// Next, put the text in it.
	char strLine[50000] = {""};
	int ind = 0;
	bool bBreak = false; // when to break a line.
	for (int i=0; i < strlen(strMessage); i++)
	{
		// Break text into lines and display them.
		if (strMessage[i] != '\n')
			strLine[ind++] = strMessage[i];

		if (i > 0 && ( /*(i % CHARACTERS_PER_LINE == 0)*/ (iLineCount++ >= CHARACTERS_PER_LINE) ||
					   strMessage[i] == '\n'))
		{
			bBreak = true;
		}

		// Only break the line on spaces or punctuation.
		if (bBreak &&
			(strMessage[i] == ' ' || strMessage[i] == ',' || strMessage[i] == '.' ||
			strMessage[i] == '-' ||	strMessage[i] == '!' || strMessage[i] == '?' ||
			strMessage[i] == '\n'))
		{
			// Reached max characters per line.
			strLine[ind++] = '\0';
			CDXMenu menu;
			menu.TextXY(Screen->GetFront(), x, y, RGB(200, 200, 255), strLine);
			//Screen->GetFront()->TextXY(x, y, RGB(200,200,255), (LPCTSTR)strLine);
			strcpy(strLine, (char*)"");
			y += FONT_SIZE + 7;
			ind = 0;
			bBreak = false;
			iLineCount = 0;
		}
	}

	if (strlen(strLine) > 0)
	{
		// Print remaining text.
		strLine[ind++] = '\0';
		//Screen->GetFront()->TextXY(x, y, RGB(200,200,255), (LPCTSTR)strLine);
		CDXMenu menu;
		menu.TextXY(Screen->GetFront(), x, y, RGB(200, 200, 255), strLine);
		y += FONT_SIZE + 15;
	}

	Input->Update();
	Input->UpdateLastKey(true);
	while (Input->GetLastKey() != 57 && Input->GetLastKey() != 28)
	{
		Input->Update();
		Input->UpdateLastKey(true);
	}

	// Make the message box go away now.
	FrameIndex = 4;
	while (FrameIndex >= 0)
	{
		// Copy Temp to Back
		Temp->DrawBlk(Screen->GetBack(), 0, 0, &mRect);

		Sprite->SetFrame(FrameIndex);
		Sprite->Draw(Screen->GetBack() , 0 , 0 , CDXBLT_TRANSALPHA);

		Screen->Flip();
		FrameIndex--;

//		Sleep(5);
	}

	// Copy Temp to Front
	Temp->DrawBlk(Screen->GetBack(), 0, 0, &mRect);
	Screen->Flip();	 // Flip the back buffer to the front

	SAFEDELETE(Temp);

	return;
}