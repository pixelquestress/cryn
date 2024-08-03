// FallingLeaf.cpp: implementation of the CFallingLeaf class.
//
//////////////////////////////////////////////////////////////////////

#include "FallingLeaf.h"
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFallingLeaf::CFallingLeaf()
{
	Sprite = NULL;
	Tile = NULL;
	Screen = NULL;

	x = rand() % 600 + 1;
	y = rand() % 400 + 1;
	Speed = 3;
	iTicker = 0;
	zoom = 10;
}

CFallingLeaf::~CFallingLeaf()
{
	SAFEDELETE(Sprite);
	SAFEDELETE(Tile);
}

void CFallingLeaf::Load(CDXScreen *screen)
{
	// Loads a random 1-3 FallingLeaf.
	Screen = screen;

	char filename[256];
	strcpy(filename, (char*)"graphics/falling_leaf.bmp");

	Tile = new CDXTile();
    if( Tile->Create(Screen, filename, 40, 40, 0) == FALSE )
        CDXError( Screen , (char*)"could not load tiles from file FallingLeaf file" );
    // set the top left pixel in tiles bitmap as transparent color
	Tile->SetColorKey(0);

	Sprite = new CDXSprite();
	Sprite->Create(Tile);
	Sprite->SetAlphaValue(rand() % 156 + 100);
	Sprite->SetShadowOffset(15, -15);
	Sprite->SetShadowValue(75);
	Sprite->SetFrame(1);

	x = rand() % 600;
	y = rand() % 400;

	Speed = 1; // max speed
	iTicker = 0;
	zoom = 3;
	initial_x = x;
	life_count = 0; // life until leaf is dead
	life_time = rand() % 301 + 500; // each leaf will display for 500 - 850 ticks
	bAnimRight = true;
	bLeft = true;
	iRotateSpeed = rand() % 5 + 1;
	bZoomer = rand() % 2;
}

void CFallingLeaf::Move(int iDirection)
{
	if (iTicker2++ > 5)
		iTicker2 = 0;

	// Zoom out as it falls.
	int r = rand() % 20;
	if (iTicker == 0 && zoom > 0)
		zoom -= 0.1;

	// Move slightly down.
	y++;

	// Move left and right.
	if (bLeft && x > initial_x - 50)
	{
		x -= Speed;
	}
	else if (x <= initial_x - 50)
	{
		bLeft = false;
		Speed = 1;
	}

	if (!bLeft && x < initial_x + 50)
	{
		x += Speed;
	}
	else if (x >= initial_x + 50)
	{
		bLeft = true;
		Speed = 1;
	}

	if (Speed < 6 && r == 5)
		Speed++;

	// Leaf dies, reset it.
	if (y >= 480)
	{
		x = rand() % 600;
		y = rand() % 400;
		
		Speed = 1; // max speed
		iTicker = 0;
		zoom = 3;
		initial_x = x;
		life_count = 0; // life until leaf is dead
		life_time = rand() % 301 + 500; // each leaf will display for 50 - 150 ticks
		Sprite->SetAlphaValue(rand() % 156 + 100);
		iRotateSpeed = rand() % 5 + 1;
		bZoomer = rand() % 2;
	}
}

void CFallingLeaf::Draw()
{
	if (iTicker++ > iRotateSpeed)
	{
		int iFrame = Sprite->GetFrame();
		if (bAnimRight)
		{
			// Rotating right.
			if (++iFrame >= 6)
			{
				bAnimRight = false;
			}
		}
		else
		{
			// Rotating left.
			if (--iFrame <= 1)
			{
				bAnimRight = true;
			}
		}

		Sprite->SetFrame(iFrame);
		iTicker = 0;
	}

	Sprite->SetPos(x, y);
	Sprite->SetScale(zoom);
	if (bZoomer)
		Sprite->Draw(Screen->GetBack() , 0 , 0 , CDXBLT_TRANSALPHA);
	else
		Sprite->Draw(Screen->GetBack() , 0 , 0 , CDXBLT_TRANSSCALED);
}