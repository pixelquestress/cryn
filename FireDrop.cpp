// FireDrop.cpp: implementation of the CFireDrop class.
//
//////////////////////////////////////////////////////////////////////

#include "FireDrop.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFireDrop::CFireDrop()
{

}

CFireDrop::~CFireDrop()
{

}

void CFireDrop::Load(CDXScreen *screen, bool bblizzard)
{
	// Loads a random 1-3 fire drop.
	// bBlizzard represents speed of the flakes.
	Screen = screen;
	bBlizzard = bblizzard;

	int r = rand() % 3; // 0 - 2
	char filename[256];

	switch (r)
	{
		case 0 : { strcpy(filename, (char*)"graphics/firedrop1.bmp"); break; }
		case 1 : { strcpy(filename, (char*)"graphics/firedrop2.bmp"); break; }
		case 2 : { strcpy(filename, (char*)"graphics/firedrop3.bmp"); break; }
		default : { strcpy(filename, (char*)"graphics/firedrop1.bmp"); break; }
	};


	Tile = new CDXTile();
    if( Tile->Create(Screen, filename, 20, 20, 0) == FALSE )
        CDXError( Screen , (char*)"could not load tiles from file firedrop file" );
    // set the top left pixel in tiles bitmap as transparent color
	Tile->SetColorKey(0);

	Sprite = new CDXSprite();
	Sprite->Create(Tile);

	x = rand() % 640;
	y = 0;

	if (bBlizzard)
		Speed = rand() % 20 + 5;
	else
		Speed = rand() % 5 + 1;
}
