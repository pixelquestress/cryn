// Branch.cpp: implementation of the CBranch class.
//
//////////////////////////////////////////////////////////////////////

#include "Branch.h"
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBranch::CBranch()
{
	Sprite = NULL;
	Tile = NULL;
	Screen = NULL;

	x = rand() % 600 + 1;
	y = rand() % 400 + 1;
	Speed = 3;
	iTicker = 0;
}

CBranch::~CBranch()
{
	SAFEDELETE(Sprite);
	SAFEDELETE(Tile);
}

void CBranch::Load(CDXScreen *screen)
{
	// Loads a random 1-3 Branch.
	Screen = screen;

	char filename[256];
	strcpy(filename, (char*)"graphics/treebranch.bmp");

	Tile = new CDXTile();
    if( Tile->Create(Screen, filename, 60, 60, 0) == FALSE )
        CDXError( Screen , (char*)"could not load tiles from file Branch file" );
    // set the top left pixel in tiles bitmap as transparent color
	Tile->SetColorKey(0);

	Sprite = new CDXSprite();
	Sprite->Create(Tile);
	Sprite->SetAlphaValue(150);
	Sprite->SetShadowOffset(15, -15);
	Sprite->SetShadowValue(150);
	Sprite->SetFrame(0);
	Sprite->SetScale(8);

	x = 400;
	y = rand() % 280;

	Speed = 1; // max speed
	iTicker = 0;
}

void CBranch::Move(int iDirection)
{
	if (y >= 450)
	{
		y = 0;
	}

	if (x >= 620)
	{
		x = 0;
	}

	if (x <= 0)
	{
		x = 619;
	}

	if (y <= 0)
	{
		y = 449;
	}

	if (iDirection == LEFT)
	{
		x -= Speed;
	}
	else if (iDirection == RIGHT)
	{
		x += Speed;
	}
	else if (iDirection == UP)
	{
		y -= Speed;
	}
	else if (iDirection == DOWN)
	{
		y += Speed;
	}
}

void CBranch::Draw()
{
	Sprite->SetPos(x, y);
	Sprite->Draw(Screen->GetBack() , 0 , 0 , CDXBLT_TRANSALPHA | CDXBLT_TRANSSCALED);
}