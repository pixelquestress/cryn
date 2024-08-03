// Bat.cpp: implementation of the CBat class.
//
//////////////////////////////////////////////////////////////////////

#include "Bat.h"
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBat::CBat()
{
	Sprite = NULL;
	Tile = NULL;
	Screen = NULL;
	Bat1Sound = 0;
	Bat2Sound = 0;

	x = rand() % 600 + 1;
	y = rand() % 400 + 1;
	Speed = 3;
	iTicker = 0;
	FlyingDuration = 0;
	bFlyingRight = false;
	bFlying = false;
}

CBat::~CBat()
{
	SAFEDELETE(Sprite);
	SAFEDELETE(Tile);
	SAFEDELETE(Bat1Sound);
	SAFEDELETE(Bat2Sound);
}

void CBat::Load(CDXScreen *screen, CDXSound *sound)
{
	// Loads a random 1-3 Bat.
	Screen = screen;

	char filename[256];
	strcpy(filename, (char*)"graphics/bat.bmp");

	Tile = new CDXTile();
    if( Tile->Create(Screen, filename, 40, 40, 0) == FALSE )
        CDXError( Screen , (char*)"could not load tiles from file bat file" );
    // set the top left pixel in tiles bitmap as transparent color
	Tile->SetColorKey(0);

	Sprite = new CDXSprite();
	Sprite->Create(Tile);
	Sprite->SetAlphaValue(150);
	Sprite->SetShadowOffset(15, -15);
	Sprite->SetShadowValue(150);
	Sprite->SetFrame(1);

	Bat1Sound = new CDXSoundBuffer;
	Bat1Sound->Load(sound, (char*)"music/bat1.wav", 4);
	Bat2Sound = new CDXSoundBuffer;
	Bat2Sound->Load(sound, (char*)"music/bat2.wav", 4);

	x = rand() % 600 + 1;
	y = rand() % 400 + 1;
	FlyingDuration = 0;
	bFlyingRight = false;
	bFlying = false;
	Speed = rand() % 4 + 1; // speed = 1 .. 4
	iTicker = 0;
}

void CBat::Move(int iDirection)
{
	if (!bFlying)
	{
		// Bat is roosting, so check if it's time to fly.
		if (FlyingDuration++ > 50)
		{
			// About time to fly, check random shot to take off.
			int r = rand() % 500;
			if (r == 11 || r == 7)
			{
				// Take off little bat.
				FlyingDuration = rand() % 101 + 50; // fly for 50 - 150 ticks.
				bFlyingRight = rand() % 2;
				bFlying = true;

				if (r == 11)
					Bat1Sound->Play();
				else
					Bat2Sound->Play();
			}
		}
	}
	else if (bFlying)
	{
		// Bat is flying, see if he's tired out and wants to stop.
		if (FlyingDuration-- < 1)
		{
			// It's time to roost.
			FlyingDuration = 0;// - (rand() % 101 + 50); // roost for 50 .. 150 + 100 ticks.
			bFlying = false;
		}
		else
		{
			// Fly bat fly.
			int r = rand() % 10;
			if (r < 5)
				y += rand() % Speed + 1;
			else
				y -= rand() % Speed + 1;

			if (bFlyingRight)
				x += Speed;
			else
				x -= Speed;

			if (x >= 640 || x < 0 || y >= 480 || y < 0)
			{
				// Reset coordinates.
				x = rand() % 600 + 1;
				y = rand() % 400 + 1;
				FlyingDuration = 0;
				bFlyingRight = false;
				bFlying = false;
				Speed = rand() % 4 + 1;
			}
		}
	}
}

void CBat::Draw()
{
	if (!bFlying)
	{
		// Roosting.
		Sprite->SetFrame(1);
	}
	else
	{
		// Flying.
		int iFrame = Sprite->GetFrame();
		if (iFrame++ >= 5)
			iFrame = 2;
	
		Sprite->SetFrame(iFrame);
	}

	Sprite->SetPos(x, y);
	Sprite->Draw(Screen->GetBack() , 0 , 0 , CDXBLT_TRANSALPHA);
}