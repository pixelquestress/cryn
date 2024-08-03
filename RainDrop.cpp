// RainDrop.cpp: implementation of the CRainDrop class.
//
//////////////////////////////////////////////////////////////////////

#include "RainDrop.h"
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRainDrop::CRainDrop()
{
	Sprite = NULL;
	Tile = NULL;
	Screen = NULL;

	x = 100;
	y = 100;
	Speed = 35;
}

CRainDrop::~CRainDrop()
{
	SAFEDELETE(Sprite);
	SAFEDELETE(Tile);
}

void CRainDrop::Load(CDXScreen *screen)
{
	// Loads a random 1-3 RainDrop.
	Screen = screen;

	int r = rand() % 3; // 0 - 2
	char filename[256];

	switch (r)
	{
		case 0 : { strcpy(filename, (char*)"graphics/raindrop1.bmp"); break; }
		case 1 : { strcpy(filename, (char*)"graphics/raindrop2.bmp"); break; }
		case 2 : { strcpy(filename, (char*)"graphics/raindrop3.bmp"); break; }
		default : { strcpy(filename, (char*)"graphics/raindrop1.bmp"); break; }
	};


	Tile = new CDXTile();
    if( Tile->Create(Screen, filename, 10, 10, 0) == FALSE )
        CDXError( Screen , (char*)"could not load tiles from file RainDrop file" );
    // set the top left pixel in tiles bitmap as transparent color
	Tile->SetColorKey(0);

	Sprite = new CDXSprite();
	Sprite->Create(Tile);
//	Sprite->SetAlphaValue(rand()%100);

	x = rand() % 640;
	y = 0;

	Speed = rand() % 10 + 10;
}

void CRainDrop::Move(int iDirection)
{
	// iDirection: -1 left, 0 straight down, 1 right
	y += Speed;

	if (iDirection == -1)
		x -= rand() % 5 + 1;
	else if (iDirection == 0)
	{}
	else if (iDirection == 1)
		x += rand() % 5 + 1;

	if (y > 480)
	{
		// Reset coordinates.
		x = rand() % 640;
		y = 0;
		Speed = rand() % 10 + 10;
	}
}

void CRainDrop::Draw()
{
	Sprite->SetPos(x, y);
	Sprite->Draw(Screen->GetBack() , 0 , 0 , CDXBLT_TRANSALPHAFAST);
}