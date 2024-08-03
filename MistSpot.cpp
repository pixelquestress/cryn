// MistSpot.cpp: implementation of the CMistSpot class.
//
//////////////////////////////////////////////////////////////////////

#include "MistSpot.h"
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMistSpot::CMistSpot()
{
	iAlpha = rand() % 100 + 100; // 255 is invisible, 0 is fully visible
	bAlphaUp = false;
	iRecursion = 0;
	bRandom = true;
	iAlphaMax = 255;
	iAlphaMin = 150;
	iFadeSpeed = 2; // speed of fading in and out
	LeftBorder = -1;
	RightBorder = -1;
	TopBorder = -1;
	BottomBorder = -1;
}

CMistSpot::~CMistSpot()
{
}

void CMistSpot::Init()
{
	SetAlphaValue(999); // indicate we want real alpha trans effect
	NumFramesPerDirection = 0;
	isAnimated = false;
	iRecursion = 0;
	MoveRandomSpot();
}

void CMistSpot::SetRandom(bool abRandom)
{
	bRandom = abRandom;
}

void CMistSpot::MoveRandomSpot()
{
	if (!bRandom)
		return;

	// Moves the most to a random tile on the map.
	if (LeftBorder > -1 && RightBorder != -1 && TopBorder > -1 && BottomBorder != -1 &&
		RightBorder < Map->GetMapWidth() && BottomBorder < Map->GetMapHeight())
	{
		// Using borders for where the spots can appear.
		SetPosTile(rand() % (RightBorder-LeftBorder) + LeftBorder, rand() % (BottomBorder-TopBorder) + TopBorder);
	}
	else
	{
		SetPosTile(rand() % Map->GetMapWidth(), rand() % Map->GetMapHeight());
	}

	StandStill();

	if (!Map->IsWalkable(GetTileX(), GetTileY()) && iRecursion++ < 100)
	{
		MoveRandomSpot();
	}
}

bool CMistSpot::Draw()
{
	Facing = 0;
	FrameIndex = 0;
	MoveStep = 0;
	FacingOld = 0;

	if (bAlphaUp)
	{
		if (iAlpha + iFadeSpeed <= iAlphaMax)
			iAlpha+=iFadeSpeed;
		else
		{
			iRecursion = 0;
			MoveRandomSpot();
			bAlphaUp = false;
		}
	}
	
	if (!bAlphaUp)
	{
		if (iAlpha - iFadeSpeed >= iAlphaMin)
			iAlpha-=iFadeSpeed;
		else
		{
			bAlphaUp = true;
		}
	}

	Sprite->SetAlphaValue(iAlpha);

	return CNPC::Draw();
}