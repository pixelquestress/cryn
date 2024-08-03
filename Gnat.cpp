// Gnat.cpp: implementation of the CGnat class.
//
//////////////////////////////////////////////////////////////////////

#include "Gnat.h"
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGnat::CGnat()
{
	Sprite = NULL;
	Tile = NULL;
	Screen = NULL;

	x = rand() % 600 + 1;
	y = rand() % 400 + 1;
	Speed = 3;
	iTicker = 0;
}

CGnat::~CGnat()
{
	SAFEDELETE(Sprite);
	SAFEDELETE(Tile);
}

void CGnat::Load(CDXScreen *screen)
{
	// Loads a random 1-3 Gnat.
	Screen = screen;

	char filename[256];
	strcpy(filename, (char*)"graphics/gnats.bmp");

	Tile = new CDXTile();
    if( Tile->Create(Screen, filename, 40, 40, 0) == FALSE )
        CDXError( Screen , (char*)"could not load tiles from file Gnat file" );
    // set the top left pixel in tiles bitmap as transparent color
	Tile->SetColorKey(0);

	Sprite = new CDXSprite();
	Sprite->Create(Tile);
	Sprite->SetAlphaValue(150);
	Sprite->SetShadowOffset(15, -15);
	Sprite->SetShadowValue(150);
	Sprite->SetFrame(1);

	x = 0;
	y = rand() % 280;

	Speed = 3; // max speed
	iTicker = 0;
}

void CGnat::Move(int iDirection)
{
	int r = rand() % Speed;
	x += r;

	r = rand() % 3;
	if (r == 2)
	{
		r = rand() % Speed;
		y += r;
	}

/*	if (iDirection == -1)
		x -= rand() % 5 + 1;
	else if (iDirection == 0)
	{}
	else if (iDirection == 1)
		x += rand() % 5 + 1;
*/
	if (x >= 640 || y >= 480)
	{
		// Reset coordinates.
		x = 0;
		y = rand() % 280;
	}
}

void CGnat::Draw()
{
	if (iTicker++ > 30)
	{
		int iFrame = Sprite->GetFrame();
		if (iFrame++ >= 4)
			iFrame = 1;

		Sprite->SetFrame(iFrame);
		iTicker = 0;
	}

	Sprite->SetPos(x, y);
	Sprite->Draw(Screen->GetBack() , 0 , 0 , CDXBLT_TRANSALPHA);
}