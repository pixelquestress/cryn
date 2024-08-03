// Player.h: interface for the CPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYER_H__1BFE499E_9394_4687_A22D_F14CA187CE8F__INCLUDED_)
#define AFX_PLAYER_H__1BFE499E_9394_4687_A22D_F14CA187CE8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NPC.h"

#define RIGHT_PUSH 200
#define TOP_PUSH 125

class CPlayer : public CNPC
{
public:
	CPlayer();
	virtual ~CPlayer();

	// Overidables
	bool Move();
	bool Move(int Direction);

	void Init(CDXScreen *screen, CDXInput *input, CDXSound *sound) { Screen = screen; Input = input; Sound = sound; };
	int file_exists(const char* file_name);

	int NextXP(); // returns the XP needed to gain next level.
	bool GainLevel(); // see if player gains any level.
	void SaveGame();
	void SaveMaxHealth(); // saves only max hp & mp and old settings.
	bool LoadGame();

	long Exp;
	int Gold;
	int HP;
	int MaxHP;
	int MP;
	int MaxMP;
	int Level;
	int iWeapon;
	int iArmor;

	int Area;
	float StoryLocation;

	int GameSpeed;

	int MapX, MapY, Map2X, Map2Y; // values loaded from saved game file.

	bool bCrystalClearOn; // true if user can permanently see crystal clear.
	bool bBonusAttackOn; // true if user can do the bonus attack damage.

	int BeorneTileX, BeorneTileY;
	int AyliTileX, AyliTileY;

	CDXScreen *Screen;
	CDXInput *Input;
	CDXSound *Sound;
};

#endif // !defined(AFX_PLAYER_H__1BFE499E_9394_4687_A22D_F14CA187CE8F__INCLUDED_)
