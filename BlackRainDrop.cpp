// BlackRainDrop.cpp: implementation of the CBlackRainDrop class.
//
//////////////////////////////////////////////////////////////////////

#include "BlackRainDrop.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBlackRainDrop::CBlackRainDrop()
{

}

CBlackRainDrop::~CBlackRainDrop()
{

}

void CBlackRainDrop::Load(CDXScreen *screen)
{
	// Loads a random 1-3 RainDrop.
	Screen = screen;

	int r = rand() % 3; // 0 - 2
	char filename[256];

	switch (r)
	{
		case 0 : { strcpy(filename, (char*)"graphics/blackraindrop1.bmp"); break; }
		case 1 : { strcpy(filename, (char*)"graphics/blackraindrop1.bmp"); break; }
		case 2 : { strcpy(filename, (char*)"graphics/blackraindrop1.bmp"); break; }
		default : { strcpy(filename, (char*)"graphics/blackraindrop1.bmp"); break; }
	};

	Tile = new CDXTile();
    if( Tile->Create(Screen, filename, 10, 10, 0) == FALSE )
        CDXError( Screen , (char*)"could not load tiles from file BlackRainDrop file" );
    // set the top left pixel in tiles bitmap as transparent color
	Tile->SetColorKey(0);

	Sprite = new CDXSprite();
	Sprite->Create(Tile);
//	Sprite->SetAlphaValue(rand()%100);

	x = rand() % 640;
	y = 0;

	Speed = rand() % 5 + 5;
}