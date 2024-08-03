// NPC.h: interface for the CNPC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPC_H__57BF05C0_9B60_11D5_9853_444553546170__INCLUDED_)
#define AFX_NPC_H__57BF05C0_9B60_11D5_9853_444553546170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Character.h"

class CNPC : public CCharacter
{
protected:
	int /*MoveStep,*/ TimeToMove;
	int Ticker;
	bool Alive;
	CNPC *NPCFollow; // another NPC we are following.
	CNPC *isFollowingUs; // another NPC is following us.

public:
	void Speak(int x = 10, int y = 335) { if (isAlive()) CCharacter::Speak(x, y); };

public:
	int Speed;

	CNPC();
	virtual ~CNPC();
	
	bool isAlive() { return Alive; };

	// Overidables
	bool Move();
	bool Move(int aDirection);
	bool Draw();
	void SetArea(int a, int b, int c, int d);
	bool Talk(int PlayerTileX, int PlayerTileY); // verifies adjacent to player then calls Speak();
	bool CheckTalk(int PlayerTileX, int PlayerTileY); // verifies adjacent to player;
	void Follow(CNPC *Who) { NPCFollow = Who; if (Who != NULL) Who->isFollowingUs = this; };
	void UnFollow(CNPC *Who) { NPCFollow = NULL; if (Who != NULL) Who->isFollowingUs = NULL; };
	void Die();
	void Revive();
	void StandStill() { SetArea(GetTileX(), GetTileY(), GetTileX(), GetTileY()); };

	bool GetTicker();
};

#endif // !defined(AFX_NPC_H__57BF05C0_9B60_11D5_9853_444553546170__INCLUDED_)
