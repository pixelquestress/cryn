// Cloud.cpp: implementation of the CCloud class.
//
//////////////////////////////////////////////////////////////////////

#include "Cloud.h"
#include <time.h>
#include "BattleEngine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCloud::CCloud()
{
	Width = 79; // assume 80 width tile map
	iTickSpeed = 40;//rand() % 21 + 40; // speed cloud moves 40-60 ticks
	iTicker = iTickSpeed;
}

CCloud::~CCloud()
{
}

void CCloud::Move(int iDirection)
{
	if (iTicker++ >= iTickSpeed)
	{
		iTicker = 0;

		if (MoveStep == 0)
			CCharacter::Move(MOVE_LEFT, 1);
	}

	if (GetTileX() == 0)
	{
		// Reset cloud, it moved off the screen.
		SetPosTile(Width, rand() % 40);
	}
}
