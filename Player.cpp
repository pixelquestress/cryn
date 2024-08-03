// Player.cpp: implementation of the CPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "Player.h"
#include "BattleEngine.h"
#include <time.h>
#include <fstream>
#include <fcntl.h>
#include <errno.h>
#include <io.h>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlayer::CPlayer()
{
	Speed = 1;
	Direction = 0;

	Screen = NULL;
	Input = NULL;
	Sound = NULL;

	Exp = 0;
	Gold = 0;
	HP = 65;
	MaxHP = 65;
	MaxMP = 4;
	MP = 4;
	iArmor = ARMOR_9;
	iWeapon = SHORTSWORD;
	Level = 1;

	GameSpeed = 0;

	BeorneTileX = 0;
	BeorneTileY = 0;
	AyliTileX = 0;
	AyliTileY = 0;

	bCrystalClearOn = false;
	bBonusAttackOn = false;

	srand( (unsigned)time( NULL ) );
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Move(int Direction)
{
	if (Direction == RIGHT)
	{
		// Move sprite.
		if (Sprite->m_PosX >= Screen->GetWidth() - RIGHT_PUSH &&
			Map->GetScreenMapPosX2() < Map->GetMapWidth())
		{
			// Or scroll map.
			Map->ScrollRight(Speed*2);
			Map2->ScrollRight(Speed*2);
		}

		Direction = RIGHT;
		return CCharacter::Move(Direction, Speed);
	}

	return false;
}

bool CPlayer::Move()
{
	if (Sprite == NULL)
		return false;

	isAnimated = false;

	// Check if we are in between moving.
	if (MoveStep > 0)
	{
		isAnimated = true;
		if (Direction == RIGHT)
		{
			if (Sprite->m_PosX >= Screen->GetWidth() - RIGHT_PUSH &&
				Map->GetScreenMapPosX2() < Map->GetMapWidth())
			{
				Map->ScrollRight(Speed*2);
				Map2->ScrollRight(Speed*2);
			}
		}
		else if (Direction == LEFT)
		{
			if (Sprite->m_PosX <= RIGHT_PUSH &&
				Map->GetScreenMapPosX2() > 0)
			{
				Map->ScrollLeft(Speed*2);
				Map2->ScrollLeft(Speed*2);
			}
		}
		else if (Direction == UP)
		{
			if (Sprite->m_PosY <= TOP_PUSH &&
				Map->GetScreenMapPosY2() > 0)
			{
				Map->ScrollUp(Speed*2);
				Map2->ScrollUp(Speed*2);
			}
		}
		else if (Direction == DOWN)
		{
			if (Sprite->m_PosY >= Screen->GetHeight() - TOP_PUSH &&
				Map->GetScreenMapPosY2() < Map->GetScreenHeight())
			{
				Map->ScrollDown(Speed*2);
				Map2->ScrollDown(Speed*2);
			}
		}

		return CCharacter::Draw2();
	}

	// Otherwise, allow user to move player.
	if (Input->GetKeyState(CDXKEY_LEFTARROW))
	{
		// Move sprite.
		if (Sprite->m_PosX <= RIGHT_PUSH &&
			Map->GetScreenMapPosX2() > 0)
		{
			// Or scroll map.
			Map->ScrollLeft(Speed*2);
			Map2->ScrollLeft(Speed*2);
		}

		Direction = LEFT;
		
		// If we can't move, check if we're just blocked by a follower.
		if (!CCharacter::Move(Direction, Speed))
		{
			// We could just be being blocked by a following NPC.
			// If so, push the NPC left too.
			if (isFollowingUs != NULL)
			if (isFollowingUs->GetTileX() == GetTileX() - 1)
			{
				// Yep, lets push him.
				if (!isFollowingUs->Move(LEFT))
					if (!isFollowingUs->Move(UP))
						isFollowingUs->Move(DOWN);
			}
		}

		return true;
	}
	else if (Input->GetKeyState(CDXKEY_RIGHTARROW))
	{
		// Move sprite.
		if (Sprite->m_PosX >= Screen->GetWidth() - RIGHT_PUSH &&
			Map->GetScreenMapPosX2() < Map->GetMapWidth())
		{
			// Or scroll map.
			Map->ScrollRight(Speed*2);
			Map2->ScrollRight(Speed*2);
		}

		Direction = RIGHT;
		
		// If we can't move, check if we're just blocked by a follower.
		if (!CCharacter::Move(Direction, Speed))
		{
			// We could just be being blocked by a following NPC.
			// If so, push the NPC right too.
			if (isFollowingUs != NULL)
			if (isFollowingUs->GetTileX() == GetTileX() + 1)
			{
				// Yep, lets push him.
				if (!isFollowingUs->Move(RIGHT))
					if (!isFollowingUs->Move(UP))
						isFollowingUs->Move(DOWN);
			}
		}

		return true;
	}
	else if (Input->GetKeyState(CDXKEY_UPARROW))
	{
		// Move sprite.
		if (Sprite->m_PosY <= TOP_PUSH &&
			Map->GetScreenMapPosY2() > 0)
		{
			// Or scroll map.
			Map->ScrollUp(Speed*2);
			Map2->ScrollUp(Speed*2);
		}

		Direction = UP;
		
		// If we can't move, check if we're just blocked by a follower.
		if (!CCharacter::Move(Direction, Speed))
		{
			// We could just be being blocked by a following NPC.
			// If so, push the NPC up too.
			if (isFollowingUs != NULL)
			if (isFollowingUs->GetTileY() == GetTileY() - 1)
			{
				// Yep, lets push him.
				if (!isFollowingUs->Move(UP))
					if (!isFollowingUs->Move(RIGHT))
						isFollowingUs->Move(LEFT);
			}
		}

		return true;
	}
	else if (Input->GetKeyState(CDXKEY_DOWNARROW))
	{
		// Move sprite.
		if (Sprite->m_PosY >= Screen->GetHeight() - TOP_PUSH &&
			Map->GetScreenMapPosY2() < Map->GetScreenHeight())
		{
			// Or scroll map.
			Map->ScrollDown(Speed*2);
			Map2->ScrollDown(Speed*2);
		}

		Direction = DOWN;

		// If we can't move, check if we're just blocked by a follower.
		if (!CCharacter::Move(Direction, Speed))
		{
			// We could just be being blocked by a following NPC.
			// If so, push the NPC down too.
			if (isFollowingUs != NULL)
			if (isFollowingUs->GetTileY() == GetTileY() + 1)
			{
				// Yep, lets push him.
				if (!isFollowingUs->Move(DOWN))
					if (!isFollowingUs->Move(RIGHT))
						isFollowingUs->Move(LEFT);
			}
		}

		return true;
	}

	isFinishedMove = false;

	return false;
}

int CPlayer::NextXP()
{
	// Returns XP needed to gain next level.
	int iResult = 0;

	if (Level == 1)
		return 250;
	else if (Level == 2)
		return 600;
	else if (Level == 3)
		return 1500;
	else if (Level == 4)
		return 3000;
	else if (Level == 5)
		return 5500;
	else if (Level == 6)
		return 7000;
	else if (Level == 7)
		return 9000;
	else if (Level == 8)
		return 12000;
	else if (Level == 9)
		return 15000;
	else if (Level == 10)
		return 20000;
	else if (Level == 11)
		return 30000;
	else if (Level == 12)
		return 50000;
	else if (Level == 13)
		return 75000;
	else if (Level == 14)
		return 100000;
	else
		return 0;
}

bool CPlayer::GainLevel()
{
	// Determines if player gains a level.
	bool bGainedLevel = false;

	if (Level == 1 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}
	else if (Level == 2 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}
	else if (Level == 3 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}
	else if (Level == 4 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}
	else if (Level == 5 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}
	else if (Level == 6 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}
	else if (Level == 7 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}
	else if (Level == 8 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}
	else if (Level == 9 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}
	else if (Level == 10 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}
	else if (Level == 11 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}
	else if (Level == 12 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}
	else if (Level == 13 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}
	else if (Level == 14 && Exp >= NextXP())
	{
		bGainedLevel = true;
	}

	if (bGainedLevel)
	{
		char strmsg[1000];
		int hpgain = 0, mpgain = 0;

		Level++;

		// Determine gains in HP and MP.
		hpgain = rand() % (Level * 7) + (5 + Level); // 5+Level - Level*7
		mpgain = rand() % Level + (Level); //  Level - (0-Level)

		sprintf(strmsg, (char*)"You gained a level!\nYou gain %d HP and %d MP", hpgain, mpgain);

		// Check for spell gains.
		if (Level == 2)
			strcat(strmsg, (char*)"\nYou learn the spell Crystal Clear.");
		else if (Level == 3)
			strcat(strmsg, (char*)"\nYou learn the spell Bio Flare.");
		else if (Level == 4)
		{
			strcat(strmsg, (char*)"\nYou learn the spell Light Shock.");
			strcat(strmsg, (char*)"\nYou learn the spell Mind Numb.");
		}
		else if (Level == 5)
			strcat(strmsg, (char*)"\nYou learn the spell Fire.");
		else if (Level == 6)
			strcat(strmsg, (char*)"\nYou learn the spell Lightning.");
		else if (Level == 7)
			strcat(strmsg, (char*)"\nYou learn the spell Fluxal Melt.");
		else if (Level == 8)
		{
			strcat(strmsg, (char*)"\nYou learn the spell Body Shield.");
			strcat(strmsg, (char*)"\nYou learn the spell Mind Shield.");
		}
		else if (Level == 10)
			strcat(strmsg, (char*)"\nYour spell Magic Missile evolves into Magic Explosion.");
		else if (Level == 12)
			strcat(strmsg, (char*)"\nYour spell Bio Flare evolves into Bio Field.");
		else if (Level == 14)
			strcat(strmsg, (char*)"\nYour spell Light Shock evolves into Holy Light.");

		CInfoBox MyMessage;
		MyMessage.Initialize(Screen, Input, Sound, 2);
		MyMessage.Display2(10, 335, strmsg);

		MaxHP += hpgain;
		HP = MaxHP; // regain all hitpoints
		MaxMP += mpgain;
		MP = MaxMP; // regain all magic points
	}

	return bGainedLevel;
}

void CPlayer::SaveGame()
{
	ofstream f("myplayer.dat");

	f << Exp << " ";
	f << Gold << " ";
	f << HP << " ";
	f << iArmor << " ";
	f << iWeapon << " ";
	f << Level << " ";
	f << MaxHP << " ";
	f << MaxMP << " ";
	f << MP << " ";

	// Store Area, Location, Tile position.
	f << Area << " ";
	f << StoryLocation << " ";
	f << TileX << " ";
	f << TileY << " ";
	f << Map->GetPosX() << " ";
	f << Map->GetPosY() << " ";
	f << Map2->GetPosX() << " ";
	f << Map2->GetPosY() << " ";

	f << GameSpeed << " ";
	f << (int)bCrystalClearOn << " ";
	f << (int)bBonusAttackOn << " ";

	f << BeorneTileX << " " << BeorneTileY << " ";
	f << AyliTileX << " " << AyliTileY << endl;

	f.close();
}

void CPlayer::SaveMaxHealth()
{
	// Only saves max health settings, rest stays the same.
	// Used when player dies, to restore health for next time.

	// Read old stats.
	LoadGame();
	
	// Set Max health.
	HP = MaxHP;
	MP = MaxMP;

	ofstream f("myplayer.dat");	

	// Save new health and old settings back to file.
	f << Exp << " ";
	f << Gold << " ";
	f << HP << " ";
	f << iArmor << " ";
	f << iWeapon << " ";
	f << Level << " ";
	f << MaxHP << " ";
	f << MaxMP << " ";
	f << MP << " ";

	// Store Area, Location, Tile position.
	f << Area << " ";
	f << StoryLocation << " ";
	f << TileX << " ";
	f << TileY << " ";
	f << Map->GetPosX() << " ";
	f << Map->GetPosY() << " ";
	f << Map2->GetPosX() << " ";
	f << Map2->GetPosY() << " ";
	f << GameSpeed << " ";
	f << (int)bCrystalClearOn << " ";
	f << (int)bBonusAttackOn << " ";

	f << BeorneTileX << " " << BeorneTileY << " ";
	f << AyliTileX << " " << AyliTileY << endl;

	f.close();
}

bool CPlayer::LoadGame()
{
	if (!file_exists((char*)"myplayer.dat"))
	{
		return false;
	}

	ifstream f("myplayer.dat");

	int iCrystalClearOn=0, iBonusAttackOn=0;
	MapX=0, MapY=0, Map2X=0, Map2Y=0;
	int aTileX = -1, aTileY = -1;

	f >> Exp >> Gold >> HP >> iArmor >> iWeapon >> Level >> MaxHP >> MaxMP >> MP;
	f >> Area >> StoryLocation;
	f >> aTileX >> aTileY;
	f >> MapX >> MapY;
	f >> Map2X >> Map2Y;
	f >> GameSpeed;
	f >> iCrystalClearOn;
	f >> iBonusAttackOn;
	bCrystalClearOn = (bool)iCrystalClearOn;
	bBonusAttackOn = (bool)iBonusAttackOn;

	f >> BeorneTileX;
	f >> BeorneTileY;
        if (!f.eof())
	   f >> AyliTileX;
        if (!f.eof())
	   f >> AyliTileY;

	Map->MoveTo(MapX, MapY);
	Map2->MoveTo(Map2X, Map2Y);

	if (aTileX != -1 && aTileY != -1)
	{
		// Remove old position.
		CharacterMap->CharacterMap[TileX][TileY] = 0;
		TileX = aTileX;
		TileY = aTileY;
		// Set new position.
		CharacterMap->CharacterMap[TileX][TileY] = 1;
	}

	f.close();

	return true;
}

int CPlayer::file_exists(const char* file_name)
{
	int handle = _open(file_name, O_RDONLY);
	if (handle != -1) {
		_close(handle);
		return 1;  // file exists
	}
	else {
		if (errno == ENOENT) {
			return 0;  // file does not exist
		}
		else {
			return -1;  // error occurred
		}
	}
}
