// NPC.cpp: implementation of the CNPC class.
//
//////////////////////////////////////////////////////////////////////

#include "NPC.h"
#include <fstream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNPC::CNPC()
{
	Ticker = 0;
	Speed = 1;
	Alive = true;
//	MoveStep = STEPS_TO_MOVE;
	TimeToMove = 30;
	Direction = RIGHT;
	NPCFollow = NULL;
	isFollowingUs = NULL;

	// Default position 5,3
	SetPosTile(rand()%20 + 1, rand()%15 + 1);
}

CNPC::~CNPC()
{

}

void CNPC::SetArea(int a, int b, int c, int d)
{
	// Sets area fish can roam.
	TileLeftBorder = a;
	TileUpBorder = b;
	TileRightBorder = c;
	TileDownBorder = d;
}

bool CNPC::GetTicker()
{
	// counter for every other tic.
	Ticker++;

	if (Ticker > 5)
	{
		Ticker = 0;
		return true;
	}

	return false;
}

bool CNPC::Move(int aDirection)
{
	if (!Alive)
		return false;

	Direction = aDirection;
	return CCharacter::Move(Direction, Speed);
}

bool CNPC::Move()
{
   // Move character in a random direction.
   // Get random number 1-TimeToMove, if it equals TimeToMove then
   // let the player move in a random direction.
   if (!Alive)
	   return false;

	isAnimated = false;

	if (MoveStep > 0)
	{
		// Moving between tiles.
		isAnimated = true;
		return CCharacter::Draw2();
	}
	
	if (NPCFollow != NULL)
	{
		// Move towards another NPC.
		if (GetTileX() < NPCFollow->GetTileX())
			Direction = RIGHT;
		else if (GetTileX() > NPCFollow->GetTileX())
			Direction = LEFT;
		else if (GetTileY() < NPCFollow->GetTileY())
			Direction = DOWN;
		else if (GetTileY() > NPCFollow->GetTileY())
			Direction = UP;
		
		if (!CCharacter::Move(Direction, Speed))
		{
			// We're blocked, try to move around it.
			if (Direction == RIGHT || Direction == LEFT)
			{
				// Can't move right, so try up or down.
				if (GetTileY() < NPCFollow->GetTileY())
					Direction = DOWN;
				else if (GetTileY() > NPCFollow->GetTileY())
					Direction = UP;
			}
			else if (Direction == UP || Direction == DOWN)
			{
				// Can't move up or down, so try left or right.
				if (GetTileX() < NPCFollow->GetTileX())
					Direction = RIGHT;
				else if (GetTileX() > NPCFollow->GetTileX())
					Direction = LEFT;
			}
			
			if (!CCharacter::Move(Direction, Speed))
			{
				// Ok, problem. We are losing the leader because we're stuck in a corner.
				// Let's think here.
			}
		}
	}
	else
	{
		// Only move if we are not currently walking towards a tile.
		int r = rand() % (TimeToMove+1); // 0 - TimeToMove
		if (r == TimeToMove)
		{
			r = rand() % 4 + 1; // 1 - 4
			switch (r) 
			{
			case 1 : Direction = LEFT; break;
			case 2 : Direction = RIGHT; break;
			case 3 : Direction = UP; break;
			case 4 : Direction = DOWN; break;
			};
			
			CCharacter::Move(Direction, Speed);
		}
	}
/*	if (!CCharacter::Move(Direction, Speed))
	{
		MoveStep = 0;
		// If it can't move in first choice direction, try any direction.
		/*         for (int i=1; i < 5; i++)
		{
		switch (i) 
		{
		case 1 : Direction = LEFT; break;
		case 2 : Direction = RIGHT; break;
		case 3 : Direction = UP; break;
		case 4 : Direction = DOWN; break;
		};
		bool result = false;
		//if (Direction != r)
		//{
		// Try a new direction.
		result = CCharacter::Move(Direction, Speed);
		//}
		
		  if (result == true)
		  { 
		  // The new direction worked, we moved, so we're done.
		  //Direction = i;
		  return true;
		  }
		  else
		  {
		  }
		  }
		  
			// If we get here, we could not move. Must be stuck in a hole?
		return false;*/
/*	}
	else
	{
		// We were able to move first time.
		return true;
	}
*/
	return false;
}

bool CNPC::Draw()
{
	if (!Alive)
		return false;

	int ret =  CCharacter::Draw2();

	// Only draw NPC extras like bubbles if NPC is on screen.
	if (ret)
	{
	}

	return ret;
}

void CNPC::Die()
{
	// This fish has been killed.
	Alive = false;
	CharacterMap->CharacterMap[GetTileX()][GetTileY()] = 0;
	// Show die animation.
}

void CNPC::Revive()
{
	Alive = true;
	CharacterMap->CharacterMap[GetTileX()][GetTileY()] = 1;
}

bool CNPC::Talk(int PlayerTileX, int PlayerTileY)
{
	if (isAlive() && ((abs(GetTileX() - PlayerTileX) == 1 &&
		GetTileY() == PlayerTileY) || 
		(abs(GetTileY() - PlayerTileY) == 1 &&
		GetTileX() == PlayerTileX)))
	{
		Speak();
		return true;
	}

	return false;
}

bool CNPC::CheckTalk(int PlayerTileX, int PlayerTileY)
{
	if (isAlive() && ((abs(GetTileX() - PlayerTileX) == 1 &&
		GetTileY() == PlayerTileY) || 
		(abs(GetTileY() - PlayerTileY) == 1 &&
		GetTileX() == PlayerTileX)))
	{
		return true;
	}

	return false;
}