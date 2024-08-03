// SnowFlake.cpp: implementation of the CSnowFlake class.
//
//////////////////////////////////////////////////////////////////////

#include "SnowFlake.h"
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnowFlake::CSnowFlake()
{
	Sprite = NULL;
	Tile = NULL;
	Screen = NULL;

	x = 100;
	y = 100;
	Speed = 35;
	bBlizzard = false;
}

CSnowFlake::~CSnowFlake()
{
	SAFEDELETE(Sprite);
	SAFEDELETE(Tile);
}

void CSnowFlake::Load(CDXScreen *screen, bool bblizzard)
{
	// Loads a random 1-3 snowflake.
	// bBlizzard represents speed of the flakes.
	Screen = screen;
	bBlizzard = bblizzard;

	int r = rand() % 3; // 0 - 2
	char filename[256];

	switch (r)
	{
		case 0 : { strcpy(filename, (char*)"graphics/snowflake1.bmp"); break; }
		case 1 : { strcpy(filename, (char*)"graphics/snowflake2.bmp"); break; }
		case 2 : { strcpy(filename, (char*)"graphics/snowflake3.bmp"); break; }
		default : { strcpy(filename, (char*)"graphics/snowflake1.bmp"); break; }
	};


	Tile = new CDXTile();
    if( Tile->Create(Screen, filename, 10, 10, 0) == FALSE )
        CDXError( Screen , (char*)"could not load tiles from file snowflake file" );
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

void CSnowFlake::Move(int iDirection)
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
		if (bBlizzard)
			Speed = rand() % 20 + 5;
		else
			Speed = rand() % 5 + 1;
	}
}

void CSnowFlake::Draw()
{
	Sprite->SetPos(x, y);
	Sprite->Draw(Screen->GetBack() , 0 , 0 , CDXBLT_TRANSALPHAFAST);
}