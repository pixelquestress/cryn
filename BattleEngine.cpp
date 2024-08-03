// BattleEngine.cpp: implementation of the CBattleEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "BattleEngine.h"
#include <fstream>
#include <time.h>

DWORD RGB2(int r, int g, int b)
{
	return RGB(r, b, g);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBattleEngine::CBattleEngine()
{
	Init();
}

CBattleEngine::~CBattleEngine()
{
	SAFEDELETE(SmallSurface);
	SAFEDELETE(SmallSurface2);
	SAFEDELETE(SmallSurfaceFade);
	SAFEDELETE(Background);
	SAFEDELETE(BattleLayerBack);
	SAFEDELETE(BattleFront);
	SAFEDELETE(FrameSprite);
	SAFEDELETE(FrameTile);
	SAFEDELETE(HandSprite);
	SAFEDELETE(HandTile);
	SAFEDELETE(SpellSprite);
	SAFEDELETE(SpellTile);
	SAFEDELETE(MonsterSpellSprite);
	SAFEDELETE(MonsterSpellTile);
	SAFEDELETE(MagicMissileSound);
	SAFEDELETE(SlashSound);
	SAFEDELETE(Fire1Sound);
	SAFEDELETE(Fire2Sound);
	SAFEDELETE(LightningSound);
	SAFEDELETE(FluxalMeltSound);
	SAFEDELETE(BioFlareSound);
	SAFEDELETE(LightShockSound);
	SAFEDELETE(CrystalClearSound);
	SAFEDELETE(DarknessSound);
	SAFEDELETE(SuckedSound);
	SAFEDELETE(CureSound);
	SAFEDELETE(MindNumbSound);
	SAFEDELETE(DesecrateSound);

	for (int i=0; i<NumMonsters; i++)
	{
		SAFEDELETE(Monsters[i].Sprite);
		SAFEDELETE(Monsters[i].Tile);
	}

	for (int i=0; i<NumPlayers; i++)
	{
		SAFEDELETE(Players[i].Sprite);
		SAFEDELETE(Players[i].Tile);
	}
}

void CBattleEngine::Init()
{
	// Resets all variables.
	SAFEDELETE(SmallSurface);
	SAFEDELETE(SmallSurface2);
	SAFEDELETE(SmallSurfaceFade);
	SAFEDELETE(Background);
	SAFEDELETE(BattleLayerBack);
	SAFEDELETE(BattleFront);
	SAFEDELETE(FrameSprite);
	SAFEDELETE(FrameTile);
	SAFEDELETE(HandSprite);
	SAFEDELETE(HandTile);
	SAFEDELETE(SpellSprite);
	SAFEDELETE(SpellTile);
	SAFEDELETE(MonsterSpellSprite);
	SAFEDELETE(MonsterSpellTile);
	SAFEDELETE(MagicMissileSound);
	SAFEDELETE(SlashSound);
	SAFEDELETE(Fire1Sound);
	SAFEDELETE(Fire2Sound);
	SAFEDELETE(LightningSound);
	SAFEDELETE(FluxalMeltSound);
	SAFEDELETE(BioFlareSound);
	SAFEDELETE(LightShockSound);
	SAFEDELETE(CrystalClearSound);
	SAFEDELETE(DarknessSound);
	SAFEDELETE(SuckedSound);
	SAFEDELETE(CureSound);
	SAFEDELETE(MindNumbSound);
	SAFEDELETE(DesecrateSound);

	for (int i=0; i<NumMonsters; i++)
	{
		SAFEDELETE(Monsters[i].Sprite);
		SAFEDELETE(Monsters[i].Tile);
	}

	for (int i=0; i<NumPlayers; i++)
	{
		SAFEDELETE(Players[i].Sprite);
		SAFEDELETE(Players[i].Tile);
	}

	Screen = NULL;
	Input = NULL;
	Sound = NULL;
	DesecrateSound = NULL;

	iTemp = -1;
	Exp = 0;
	Gold = 0;
	SmallSurface = 0;
	SmallSurface2 = 0;
	SmallSurfaceFade = 0;
	Background = 0;
	BattleLayerBack = 0;
	BattleFront = 0;
	FrameTile = 0;
	FrameSprite = 0;
	HandTile = NULL;
	HandSprite = NULL;
	SpellTile = NULL;
	SpellSprite = NULL;
	MonsterSpellTile = NULL;
	MonsterSpellSprite = NULL;

	HandTarget = 0;
	NumMonsters = 0;
	NumPlayers = 0;
	Phase = COMMAND;
	MonsterAttackCounter = 0;
	PlayerAttackCounter = 0;
	Attacking = true;
	Spell = NO_SPELL;
	MonsterSpell = NO_SPELL;
	SpellStart = true;
	MonsterSpellStart = true;
	AttackDamage = 0;
	AttackStart = true;
	MonsterAttackStart = true;
	AttackDone = false;
	MonsterAttackDone = false;
	ExpCounted = false;
	bRun = false;
	ViewEnemyHP = false;
	EnemySilenced = false;
	bCrystalClearOn = false;
	bBonusAttackOn = false;
	BonusDamage = 0;
	PenaltyDamage = 0;
	BackAlpha = 170;
	PlayerPositionOffset = 0;
	iSucked = 0;
	MonsterBonusDamage = 0;
	bBoss = false;
	iShield = 0;
	iSpellShield = 0;
	Reduction = 0;

	for (int i=0; i<MAX_MONSTERS; i++)
	{
		Monsters[i].Tile = NULL;
		Monsters[i].Sprite = NULL;
		Monsters[i].Width = 40;
		Monsters[i].Height = 40;
		Monsters[i].MaxHP = 0;
		Monsters[i].HP = 0;
		Monsters[i].MP = 0;
		Monsters[i].AC = 0;
		Monsters[i].Exp = 0;
		Monsters[i].Gold = 0;
		Monsters[i].Status = OK;
		Monsters[i].bDoubleAttack = false;
		Monsters[i].zoom = 1;
	}

	for (int i=0; i<MAX_PLAYERS; i++)
	{
		Players[i].Tile = NULL;
		Players[i].Sprite = NULL;
		Players[i].Width = 40;
		Players[i].Height = 40;
		Players[i].MaxHP = 0;
		Players[i].HP = 0;
		Players[i].MP = 0;
		Players[i].AC = 0;
		Players[i].Status = OK;
		Players[i].bDoubleAttack = false;
		Players[i].zoom = 1;
	}
}

void CBattleEngine::AddMonster(char *strMonster, char *bmpFilename, int level, int hp, int mp, int ac, char *Weapon, int iWeapon, char *Armor, int iArmor, int CastRate, int Exp, int Gold, int Width, int Height)
{
	if (NumMonsters >= MAX_MONSTERS)
		return;

	strcpy(Monsters[NumMonsters].Name, strMonster);
	Monsters[NumMonsters].Width = Width;
	Monsters[NumMonsters].Height = Height;
	Monsters[NumMonsters].Level = level;
	Monsters[NumMonsters].HP = hp;
	Monsters[NumMonsters].MaxHP = hp;
	Monsters[NumMonsters].MP = mp;
	Monsters[NumMonsters].AC = ac;
	Monsters[NumMonsters].Exp = Exp;
	Monsters[NumMonsters].Gold = Gold;
	Monsters[NumMonsters].SpellCaster = CastRate; // unlikely to cast
	Monsters[NumMonsters].Status = OK;
	strcpy(Monsters[NumMonsters].Weapon, Weapon);
	Monsters[NumMonsters].iWeapon = iWeapon;
	strcpy(Monsters[NumMonsters].Armor, Armor);
	Monsters[NumMonsters].iArmor = iArmor;

	// If HP, MP, AC == 0, generate random values based upon level.
	if (hp == 0)
	{
		int temp_hp = 0;
		for (int i=0; i<level; i++)
		{
			//temp_hp += rand() % 6 + 5; // 5 - 10 hit points
			temp_hp += rand() % (level * 2) + (level);
		}

		Monsters[NumMonsters].HP = temp_hp;
		Monsters[NumMonsters].MaxHP = temp_hp;
	}
	if (mp == 0)
	{
		int temp_mp = 0;
		for (int i=0; i<level; i++)
		{
			temp_mp += rand() % 5 + 4; // 3 - 6 magic points
		}

		Monsters[NumMonsters].MP = temp_mp;
	}
	if (Exp == 0)
	{
		for (int i=0; i<level; i++)
		{
			Monsters[NumMonsters].Exp += 25; // 25 XP per level
		}
	}
	if (Gold == 0)
	{
		for (int i=0; i<level; i++)
		{
			Monsters[NumMonsters].Gold += rand() % 15; // 0-20 gold per level
		}
	}

	Monsters[NumMonsters].AC = level;

	if (bmpFilename == NULL)
	{
		// No image supplied.
	}
	else
	{
		// Load images for this monster.
		SAFEDELETE(Monsters[NumMonsters].Tile);
		SAFEDELETE(Monsters[NumMonsters].Sprite);
		Monsters[NumMonsters].Tile = new CDXTile();
		Monsters[NumMonsters].Tile->Create(Screen, bmpFilename, Monsters[NumMonsters].Width, Monsters[NumMonsters].Height, 0);
		Monsters[NumMonsters].Tile->SetColorKey(0);
		Monsters[NumMonsters].Sprite = new CDXSprite();
		Monsters[NumMonsters].Sprite->Create(Monsters[NumMonsters].Tile);
	}

	NumMonsters++;
}

void CBattleEngine::AddPlayer(char *strPlayer, char *bmpFilename, int level, int maxhp, int hp, int maxmp, int mp, int ac, char *Weapon, int iWeapon, char *Armor, int iArmor, int Width, int Height)
{
	if (NumPlayers >= MAX_PLAYERS)
		return;

	strcpy(Players[NumPlayers].Name, strPlayer);
	Players[NumPlayers].Width = Width;
	Players[NumPlayers].Height = Height;
	Players[NumPlayers].Level = level;
	Players[NumPlayers].HP = hp;
	Players[NumPlayers].MaxHP = maxhp;
	Players[NumPlayers].MaxMP = maxmp;
	Players[NumPlayers].MP = mp;
	Players[NumPlayers].AC = ac;
	Players[NumPlayers].Status = OK;
	strcpy(Players[NumPlayers].Weapon, Weapon);
	Players[NumPlayers].iWeapon = iWeapon;
	strcpy(Players[NumPlayers].Armor, Armor);
	Players[NumPlayers].iArmor = iArmor;
	
	if (bmpFilename == NULL)
	{
		// No image supplied.
	}
	else
	{
		// Load images for this monster.
		SAFEDELETE(Players[NumPlayers].Tile);
		SAFEDELETE(Players[NumPlayers].Sprite);
		Players[NumPlayers].Tile = new CDXTile();
		Players[NumPlayers].Tile->Create(Screen, bmpFilename, Players[NumPlayers].Width, Players[NumPlayers].Height, 0);
		Players[NumPlayers].Tile->SetColorKey(0);
		Players[NumPlayers].Sprite = new CDXSprite();
		Players[NumPlayers].Sprite->Create(Players[NumPlayers].Tile);
	}

	NumPlayers++;
}

void CBattleEngine::Initialize(CDXScreen *screen, CDXInput *input, CDXSound *sound, char *BackBmp, char *FrameBmp, int Level/*=1*/, bool abBeorne/*=false*/)
{
	Init();

	Screen = screen;
	Input = input;
	Sound = sound;

	bBeorne = abBeorne;

	NumMonsters = 0;
	NumPlayers = 0;

	SAFEDELETE(SmallSurface);
	SAFEDELETE(SmallSurface2);
	SAFEDELETE(SmallSurfaceFade);
	SAFEDELETE(Background);
	SAFEDELETE(BattleLayerBack);
	SAFEDELETE(BattleFront);
	SAFEDELETE(FrameSprite);
	SAFEDELETE(FrameTile);
	SAFEDELETE(HandSprite);
	SAFEDELETE(HandTile);

	SmallSurface = new CDXSurface();
	SmallSurface->Create(Screen, Screen->GetWidth(), Screen->GetHeight(), CDXMEM_SYSTEMONLY);
	SmallSurfaceFade = new CDXSurface();
	SmallSurfaceFade->Create(Screen, Screen->GetWidth(), Screen->GetHeight(), CDXMEM_SYSTEMONLY);
	SmallSurface2 = new CDXSurface();
	SmallSurface2->Create(Screen, Screen->GetWidth(), Screen->GetHeight(), CDXMEM_SYSTEMONLY);
	SmallSurface2->SetColorKey(0);

	Background = new CDXSurface();
	Background->Create(Screen, Screen->GetWidth(), Screen->GetHeight(), CDXMEM_SYSTEMONLY);

	// Store a copy of the actual screen as our Background image.
	Screen->GetFront()->DrawBlk(Background, Screen->GetWidth(), Screen->GetHeight());
	
	BattleLayerBack = new CDXLayer();
	BattleLayerBack->Create(Screen, BackBmp);

	FrameTile = new CDXTile;
	FrameTile->Create(Screen, FrameBmp, 510, 310, 0);
	FrameTile->SetColorKey(0);
	FrameSprite = new CDXSprite();
	FrameSprite->Create(FrameTile);

	HandTile = new CDXTile;
	HandTile->Create(Screen, (char*)"graphics/target.bmp", 40, 40, 0);
	HandTile->SetColorKey(0);
	HandSprite = new CDXSprite();
	HandSprite->Create(HandTile);
	HandSprite->SetFrame(1);

	// Everything drawn here will be centered around (0,0)
	// But when drawn onto Background surface, it will be clipped and re-positioned.
	BattleFront = new CDXSurface();
	BattleFront->Create(Screen, Screen->GetWidth(), Screen->GetHeight(), CDXMEM_SYSTEMONLY);

	BattleMenu.Load(Screen, Input, NULL, (char*)"", 0, 0);
	BattleMenu.AddItem((char*)"Attack");
	BattleMenu.AddItem((char*)"Cast Spell");
	BattleMenu.AddItem((char*)"Run");

	SpellMenu.Load(Screen, Input, NULL, (char*)"Choose a spell to cast - MP 10");
	SpellMenu.SetSpacing(15);
	SpellMenu.AddItem((char*)"Cancel");

	MagicMissileSound = new CDXSoundBuffer;
	MagicMissileSound->Load(Sound, (char*)"music/battleeffects/magicmissile.wav", 4);
	SlashSound = new CDXSoundBuffer;
	SlashSound->Load(Sound, (char*)"music/battleeffects/slash.wav", 4);
	Fire1Sound = new CDXSoundBuffer;
	Fire1Sound->Load(Sound, (char*)"music/battleeffects/fire1.wav", 4);
	Fire2Sound = new CDXSoundBuffer;
	Fire2Sound->Load(Sound, (char*)"music/battleeffects/fire2.wav", 4);
	LightningSound = new CDXSoundBuffer;
	LightningSound->Load(Sound, (char*)"music/battleeffects/lightning2.wav", 4);
	FluxalMeltSound = new CDXSoundBuffer;
	FluxalMeltSound->Load(Sound, (char*)"music/battleeffects/fluxalmelt.wav", 4);
	BioFlareSound = new CDXSoundBuffer;
	BioFlareSound->Load(Sound, (char*)"music/battleeffects/bioflare.wav", 4);
	LightShockSound = new CDXSoundBuffer;
	LightShockSound->Load(Sound, (char*)"music/battleeffects/lightshock.wav", 4);
	CrystalClearSound = new CDXSoundBuffer;
	CrystalClearSound->Load(Sound, (char*)"music/battleeffects/crystalclear.wav", 4);
	CureSound = new CDXSoundBuffer;
	CureSound->Load(Sound, (char*)"music/battleeffects/cure.wav", 4);
	MindNumbSound = new CDXSoundBuffer;
	MindNumbSound->Load(Sound, (char*)"music/battleeffects/mindnumb.wav", 4);
	DarknessSound = new CDXSoundBuffer;
	DarknessSound->Load(Sound, (char*)"music/battleeffects/crystalclear.wav", 4);
	SuckedSound = new CDXSoundBuffer;
	SuckedSound->Load(Sound, (char*)"music/battleeffects/sucked.wav", 4);
	DesecrateSound = new CDXSoundBuffer;
	DesecrateSound->Load(Sound, (char*)"music/battleeffects/desecrate.wav", 4);

	if (Level >= 1)
	{
		if (bBeorne)
		{
			if (Level < 7)
				SpellMenu.AddItem((char*)"Magic Missile - MP 2");
			else
				SpellMenu.AddItem((char*)"Desecrate Soul - MP 20");
		}
		else
		{
			if (Level < 10)
				SpellMenu.AddItem((char*)"Magic Missile - MP 2");
			else
				SpellMenu.AddItem((char*)"Magic Explosion - MP 10");
		}
	}

	// this should be level 2
	if (Level >= 1)
	{
		SpellMenu.AddItem((char*)"Cure - MP 2");
	}

	if (Level >= 2)
	{
		SpellMenu.AddItem((char*)"Crystal Clear - MP 2");
	}

	if (Level >= 3)
	{
		if (Level < 12)
			SpellMenu.AddItem((char*)"Bio Flare - MP 3");
		else
			SpellMenu.AddItem((char*)"Bio Field - MP 11");
	}

	if (Level >= 4)
	{
		if (Level < 14)
			SpellMenu.AddItem((char*)"Light Shock - MP 4");
		else
			SpellMenu.AddItem((char*)"Holy Light - MP 13");

		SpellMenu.AddItem((char*)"Mind Numb - MP 3");
	}

	if (Level >= 5)
	{
		SpellMenu.AddItem((char*)"Fire - MP 6");
	}

	if (Level >= 6)
	{
		SpellMenu.AddItem((char*)"Lightning - MP 8");
	}

	if (Level >= 7)
	{
		SpellMenu.AddItem((char*)"Fluxal Melt - MP 10");
	}

	if (Level >= 8)
	{
		SpellMenu.AddItem((char*)"Body Shield - MP 5");
	}

	if (Level >= 8)
	{
		SpellMenu.AddItem((char*)"Mind Shield - MP 5");
	}

	Phase = 0;
	MonsterAttackCounter = 0;
	PlayerAttackCounter = 0;
	strcpy(strAttackMessage, (char*)"");
	Spell = NO_SPELL;
	MonsterSpell = NO_SPELL;

	srand( (unsigned)time( NULL ) );
}

bool CBattleEngine::EngageCombat()
{
	// Called every movement, checks for monster encounter.
	// User is gauranteed at least 3 monster-free moves after each battle.
	static int Chance = 0;
	int r = 0;

	r = rand() % 90 + 1; // 1 - 90

	if (r + Chance > 100)
	{
		Chance = 0;
		return true;
	}
	else
	{
		Chance++;
		return false;
	}
}

void CBattleEngine::PickRandomMonsters(int Area)
{
	// Populates battle with random monsters, according to area.
	int r = 0;

	// Choose how many monsters arrive.
	r = rand() % 180 + 1; // 1 - 180
	if (r < 2)
		r = 4;
	else if (r < 5)
		r = 3;
	else if (r < 20)
		r = 2;
	else
		r = 1;

	for (int i=0; i<r; i++)
	{
		// Add r number of monsters to battle.
		if (Area == FOREST)
		{
			int ran = rand() % 7;
			int lev = rand() % 2 + 1; // 1 - 2

			switch (ran)
			{
				case 0 : AddMonster((char*)"Spider", (char*)"graphics/spider.bmp", lev, 0, 0, 0, (char*)"Bite", BITE, (char*)"None", NO_ARMOR); break;
				case 1 : AddMonster((char*)"Gremlin", (char*)"graphics/gremlin.bmp", lev, 0, 0, 0, (char*)"Dagger", DAGGER, (char*)"None", NO_ARMOR, 5); break;
				case 2 : AddMonster((char*)"Tree Ent", (char*)"graphics/foresttreeent.bmp", lev, 0, 0, 0, (char*)"Thorns", CLUB, (char*)"None", ARMOR_9); break;
				case 3 : AddMonster((char*)"Trug", (char*)"graphics/foresttrug.bmp", lev, 0, 0, 0, (char*)"Bite", BITE, (char*)"Scales", ARMOR_10); break;
				case 4 : AddMonster((char*)"Leorn", (char*)"graphics/forestleorn.bmp", lev, 0, 0, 0, (char*)"Claws", CLUB, (char*)"Hide", ARMOR_45); break;
				case 5 : AddMonster((char*)"Krinar", (char*)"graphics/forestkrinar.bmp", lev, 0, 0, 0, (char*)"Claws", BITE, (char*)"Hide", NO_ARMOR, 5); break;
				case 6 : AddMonster((char*)"Grey Wolf", (char*)"graphics/forestwolf.bmp", lev, 0, 0, 0, (char*)"Claws", DAGGER, (char*)"Hide", ARMOR_9); break;
			}
		}
		else if (Area == SWAMP)
		{
			int ran = rand() % 5;
			int lev = rand() % 4 + 3; // 3 - 6

			switch (ran)
			{
				case 0 : AddMonster((char*)"Chigger", (char*)"graphics/swampchigger.bmp", lev, 0, 0, 0, (char*)"Bite", CLUB, (char*)"None", NO_ARMOR); break;
				case 1 : AddMonster((char*)"Centipede", (char*)"graphics/swampcentipede.bmp", lev, 0, 0, 0, (char*)"Bite", CLUB, (char*)"None", NO_ARMOR, 5, 50, 10, 77, 39); break;
				case 2 : AddMonster((char*)"Blow Fly", (char*)"graphics/swampstablefly.bmp", lev, 0, 0, 0, (char*)"Bite", DAGGER, (char*)"Scales", ARMOR_10); break;
				case 3 : AddMonster((char*)"Swamp Fly", (char*)"graphics/swampblowfly.bmp", lev, 0, 0, 0, (char*)"Bite", DAGGER, (char*)"Scales", ARMOR_20); break;
				case 4 : AddMonster((char*)"Belfry Wyrm", (char*)"graphics/swamplizard.bmp", lev, 0, 0, 0, (char*)"Bite", DAGGER, (char*)"Scales", ARMOR_45, 0, 50, 10, 60, 37); break;
			}
		}
		else if (Area == SWAMPCAVE)
		{
			int ran = rand() % 6;
			int lev = rand() % 4 + 4; // 4 - 7

			switch (ran)
			{
				case 0 : AddMonster((char*)"Death Mole", (char*)"graphics/swampcavedeathmole.bmp", lev, 0, 0, 0, (char*)"Bite", CLUB, (char*)"None", NO_ARMOR, 5); break;
				case 1 : AddMonster((char*)"Acanthophis", (char*)"graphics/swampcavesnake.bmp", lev, 0, 0, 0, (char*)"Bite", SHORTSWORD, (char*)"Scales", ARMOR_10, 0); break;
				case 2 : AddMonster((char*)"Vampire Bat", (char*)"graphics/swampcavebat.bmp", lev, 0, 0, 0, (char*)"Bite", DAGGER, (char*)"Scales", ARMOR_10, 0); break;
				case 3 : AddMonster((char*)"Decapitation", (char*)"graphics/swampcavedecap.bmp", lev, 0, 0, 0, (char*)"Mess", BITE, (char*)"Bone", NO_ARMOR, 10); break;
				case 4 : AddMonster((char*)"Deathfoot", (char*)"graphics/swampcavefootbeast.bmp", lev, 0, 0, 0, (char*)"Thorns", BITE, (char*)"Bone", ARMOR_9, 10); break;
				case 5 : AddMonster((char*)"Poison Eye", (char*)"graphics/swampcavepoisoneye.bmp", lev, 0, 0, 0, (char*)"Hook", CLUB, (char*)"None", ARMOR_9, 5); break;
			}
		}
		else if (Area == TREE)
		{
			int ran = rand() % 5;
			int lev = rand() % 3 + 8; // 8 - 10

			switch (ran)
			{
				case 0 : AddMonster((char*)"Tree Ent", (char*)"graphics/foresttreeent.bmp", lev, 0, 0, 0, (char*)"Thorns", CLUB, (char*)"Bark", ARMOR_9, 5); break;
				case 1 : AddMonster((char*)"Silhouette", (char*)"graphics/silloette.bmp", lev, 0, 0, 0, (char*)"Nails", DAGGER, (char*)"Mist", ARMOR_10, 0); break;
				case 2 : AddMonster((char*)"Tree Sloth", (char*)"graphics/treesloth.bmp", lev, 0, 0, 0, (char*)"Spines", BITE, (char*)"Spines", ARMOR_10, 10); break;
				case 3 : AddMonster((char*)"Rot Hound", (char*)"graphics/treerothound.bmp", lev, 0, 0, 0, (char*)"Bite", DAGGER, (char*)"Scales", ARMOR_20, 0); break;
				case 4 : AddMonster((char*)"Noern", (char*)"graphics/treeneorn.bmp", lev, 0, 0, 0, (char*)"Thorns", DAGGER, (char*)"Scales", ARMOR_10, 5); break;
			}
		}
		else if (Area == FORESTCAMP)
		{
			int ran = rand() % 5;
			int lev = rand() % 5 + 8; // 8 - 12
			
			switch (ran)
			{
				case 0 : AddMonster((char*)"Flame Trug", (char*)"graphics/forestcamp_firebug.bmp", lev, 0, 0, 0, (char*)"Flames", CLUB, (char*)"Bark", ARMOR_9, 5); break;
				case 1 : AddMonster((char*)"Psyopsis", (char*)"graphics/forestcamp_lighteye.bmp", lev, 0, 0, 0, (char*)"Bolts", DAGGER, (char*)"Mist", ARMOR_10, 10); break;
				case 2 : AddMonster((char*)"Chameo", (char*)"graphics/forestcamp_chameo.bmp", lev, 0, 0, 0, (char*)"Breath", BITE, (char*)"Spines", ARMOR_10, 0); break;
				case 3 : AddMonster((char*)"Dread Fish", (char*)"graphics/dreadfish.bmp", lev, 0, 0, 0, (char*)"Bite", BITE, (char*)"Spines", ARMOR_20, 0); break;
				case 4 : AddMonster((char*)"Flesh Beast", (char*)"graphics/fleshbeast.bmp", lev, 0, 0, 0, (char*)"Bite", BITE, (char*)"Teeth", ARMOR_10, 5); break;
			}
		}
		else if (Area == DEMONPIT)
		{
			int ran = rand() % 6;
			int lev = rand() % 6 + 9; // 9 - 14
			
			switch (ran)
			{
				case 0 : AddMonster((char*)"Pit Dweller", (char*)"graphics/pitdweller.bmp", lev, 0, 0, 0, (char*)"Rotting Nails", CLUB, (char*)"Skin", ARMOR_10, 0); 
						 if (i < 3) 
						 { 
							 AddMonster((char*)"Pit Dweller", (char*)"graphics/pitdweller.bmp", lev, 0, 0, 0, (char*)"Rotting Nails", CLUB, (char*)"Skin", ARMOR_10, 0);
							 i += 1;
						 } // indicate we already added 2 monsters, maybe more will come maybe not.
						 break;
				case 1 : AddMonster((char*)"Pit Zombie", (char*)"graphics/pitzombie.bmp", lev, 0, 0, 0, (char*)"Disease", CLUB, (char*)"Rags", ARMOR_20, 5, 350, 0, 60, 60); break;
				case 2 : AddMonster((char*)"Static Bug", (char*)"graphics/pitstaticbug.bmp", lev, 0, 0, 0, (char*)"Electricity", CLUB, (char*)"Static", ARMOR_10, 5); break;
				case 3 : AddMonster((char*)"Pit Ghast", (char*)"graphics/pitghast.bmp", lev, 0, 0, 0, (char*)"Claws", DAGGER, (char*)"Smoke", ARMOR_45, 5); break;
				case 4 : AddMonster((char*)"Rot Round", (char*)"graphics/pitrotround.bmp", lev, 0, 0, 0, (char*)"Bite", BITE, (char*)"Hide", ARMOR_20, 0); break;
				case 5 : AddMonster((char*)"Pit Snuffer", (char*)"graphics/pitsnuffer.bmp", lev, 0, 0, 0, (char*)"Tubes", BITE, (char*)"Hide", ARMOR_10, 5); break;
			}
		}
		else if (Area == DEMONTOWN)
		{
			int ran = rand() % 4;
			int lev = rand() % 6 + 10; // 10 - 15
			
			switch (ran)
			{
				case 0 : AddMonster((char*)"Peepers", (char*)"graphics/demontown_peepers.bmp", lev-2, 0, 0, 0, (char*)"Stare", CLUB, (char*)"Skin", ARMOR_10, 0);
						 if (i < 3) 
						 { 
							 AddMonster((char*)"Peepers", (char*)"graphics/demontown_peepers.bmp", lev-2, 0, 0, 0, (char*)"Stare", CLUB, (char*)"Skin", ARMOR_10, 0);
							 i += 1;
						 } // indicate we already added 2 monsters, maybe more will come maybe not.
						 break;
				case 1 : AddMonster((char*)"Blub", (char*)"graphics/demontown_blob.bmp", lev, 0, 0, 0, (char*)"Disease", CLUB, (char*)"Rags", ARMOR_20, 5); break;
				case 2 : AddMonster((char*)"Tree Fiend", (char*)"graphics/demontown_treefiend.bmp", lev, 0, 0, 0, (char*)"Thorns", CLUB, (char*)"Static", ARMOR_45, 10); break;
				case 3 : AddMonster((char*)"Snagger", (char*)"graphics/demontown_snagger.bmp", lev, 0, 0, 0, (char*)"Thorns", DAGGER, (char*)"Smoke", ARMOR_20, 5); break;
			}
		}
		else if (Area == DEEPNETHERWORLD)
		{
			int ran = rand() % 4;
			int lev = rand() % 4 + 6; // 6 - 9
			
			switch (ran)
			{
				case 0 : AddMonster((char*)"Nether Beast", (char*)"graphics/deepnetherbeast.bmp", lev, 0, 0, 0, (char*)"Claws", CLUB, (char*)"Skin", ARMOR_10, 0, 175, 0, 40, 35);
						 if (i < 3)
						 { 
							 AddMonster((char*)"Nether Beast", (char*)"graphics/deepnetherbeast.bmp", lev, 0, 0, 0, (char*)"Claws", CLUB, (char*)"Skin", ARMOR_10, 0, 175, 0, 40, 35);
							 i += 1;
						 } // indicate we already added 2 monsters, maybe more will come maybe not.
						 break;
				case 1 : AddMonster((char*)"Nether Jelly", (char*)"graphics/deepnetherjelly.bmp", lev, 0, 0, 0, (char*)"Jellies", CLUB, (char*)"Rags", ARMOR_20, 5); break;
				case 2 : AddMonster((char*)"Nether Fish", (char*)"graphics/deepnetherfish.bmp", lev, 0, 0, 0, (char*)"Fins", CLUB, (char*)"Rags", ARMOR_10, 0); break;
				case 3 : AddMonster((char*)"Nether Slime", (char*)"graphics/deepnetherslime.bmp", lev, 0, 0, 0, (char*)"Slimers", CLUB, (char*)"Rags", ARMOR_10, 5); break;
			}
		}
	}
}

int CBattleEngine::GetWeaponDamage(int Level, int Weapon, bool bPlayer, int i)
{
	// Returns the damage done by this weapon.
	int r = 0;
	BonusDamage = 0;
	PenaltyDamage = 0;
	MonsterBonusDamage = 0;

	if (Weapon == CLAWS)
	{
		for (int i=0; i<Level; i++)
			r += rand() % 2 + 1; // 1 - 2 per level
	}
	else if (Weapon == BITE)
	{
		for (int i=0; i<Level; i++)
			r += rand() % 3 + 1; // 1 - 3 per level
	}
	if (Weapon == CLUB)
	{
		for (int i=0; i<Level; i++)
			r += rand() % 3 + 1; // 1 - 3 per level
		r += 1;
	}
	if (Weapon == SHORTSWORD)
	{
		for (int i=0; i<Level; i++)
			r += rand() % 4 + 1; // 1 - 4 per level
	}
	if (Weapon == DAGGER)
	{
		for (int i=0; i<Level; i++)
		{
			r += rand() % 6 + 1; // 1-6 + 1 per level
			r += 1;
		}
	}
	if (Weapon == LONGSWORD)
	{
		for (int i=0; i<Level; i++)
		{
			r += rand() % 8 + 2; // 1-7 + 2 per level
			r += 1;
		}
	}

	if (bPlayer && Players[0].Status == BLIND)
	{
		// Damage cut by 1/2.
		PenaltyDamage = r * 0.5;
	}
	else if (!bPlayer && Monsters[i].Status == BLIND)
	{
		PenaltyDamage = r * 0.5;
	}

	// Account for accuracy bonus.
	if (bPlayer && HandSprite->GetFrame() == 9)
	{
		// Bingo, power hit bonus of damage + ~1/4 damage!
		BonusDamage = r * 0.4;
	}
	else if (strcmp(Players[0].Name, (char*)"Ayli")==0)
		BonusDamage = r * 0.4;

	// Account for sucked monster bonus.
	if (!bPlayer && iSucked > 0)
	{
		MonsterBonusDamage = r * (0.4 * iSucked);
	}

	// Account for shielding spell on player.
	if (!bPlayer && iShield > 0)
	{
		Reduction = (float)iShield / 100;
		Reduction *= (float)r;
		r -= (int)Reduction;
	}

	return r;
}

int CBattleEngine::GetArmorProtection(int Armor)
{
	// Returns the decimal percentage of reduction.
	float r = 0;

	if (Armor == ARMOR_9)
	{
		r = 0.09; // 9%
	}
	else if (Armor == ARMOR_10)
	{
		r = 0.1; // 10%
	}
	else if (Armor == ARMOR_20)
	{
		r = 0.2; // 20%
	}
	else if (Armor == ARMOR_45)
	{
		r = 0.45; // 45%
	}

	// Do deduction.
	AttackDamage = AttackDamage - (AttackDamage * r);

	if (AttackDamage < 1) AttackDamage = 1;

	return (AttackDamage * r);
}

bool CBattleEngine::CanCast(int aSpell, int i)
{
	if (aSpell == MAGIC_MISSILE)
	{
		if (Monsters[i].MP - 2 < 0)
			aSpell = NO_SPELL;
	}
	else if (aSpell == BIO_FLARE)
	{
		if (Monsters[i].MP - 3 < 0)
			aSpell = NO_SPELL;
	}
	else if (aSpell == LIGHT_SHOCK)
	{
		if (Monsters[i].MP - 4 < 0)
			aSpell = NO_SPELL;
	}
	else if (aSpell == DARKNESS)
	{
		if (Monsters[i].MP - 3 < 0)
			aSpell = NO_SPELL;
	}
	else if (aSpell == SUCKED)
	{
		if (Monsters[i].MP - 3 < 0)
			aSpell = NO_SPELL;
	}
	else if (aSpell == FIRE)
	{
		if (Monsters[i].MP - 6 < 0)
			aSpell = NO_SPELL;
	}
	else if (aSpell == LIGHTNING)
	{
		if (Monsters[i].MP - 8 < 0)
			aSpell = NO_SPELL;
	}
	else if (aSpell == FLUXAL_MELT)
	{
		if (Monsters[i].MP - 10 < 0)
			aSpell = NO_SPELL;
	}
	else if (aSpell == CURE)
	{
		if (Monsters[i].MP - 2 < 0)
			aSpell = NO_SPELL;
	}
	else if (aSpell == MENTAL_SHIELD)
	{
		if (Monsters[i].MP - 5 < 0)
			aSpell = NO_SPELL;
	}
	else if (aSpell == MAGIC_EXPLOSION)
	{
		if (Monsters[i].MP - 10 < 0)
			aSpell = NO_SPELL;
	}
	else if (aSpell == BIO_FIELD)
	{
		if (Monsters[i].MP - 11 < 0)
			aSpell = NO_SPELL;
	}
	else if (aSpell == HOLY_LIGHT)
	{
		if (Monsters[i].MP - 13 < 0)
			aSpell = NO_SPELL;
	}
	else if (aSpell == DESECRATE)
	{
		if (Monsters[i].MP - 20 < 0)
			aSpell = NO_SPELL;
	}

	if (aSpell == NO_SPELL)
		return false;
	else
		return true;
}

int CBattleEngine::GetRandomSpell(int i)
{
	// Lets a monster pick a random spell to cast.
	int r = 0;
	bool Done = false;
	int Tries = 0;

	if (Monsters[i].SpellCaster == 0 ||
		EnemySilenced)
	{
		MonsterSpell = NO_SPELL;
		return MonsterSpell;
	}

	// First, should he cast at all?
	r = rand() % (10 + Monsters[i].SpellCaster) + 0; // default 0 - 9

	if (r > 9)
	{
		while (!Done && Tries++ < 10)
		{
			// Ok, he'll cast a spell.
			// We do level - 1 because monsters are always at least lvl 1
			// and we don't want a lvl 4 monster casting a lvl 5 spell.
			if (Monsters[i].Level == 1)
				r = 1;
			else
				r = rand() % (Monsters[i].Level - 1) + 1; // 1 - level

			switch (r)
			{
			case 1 : if (Monsters[i].Level < 10) MonsterSpell = MAGIC_MISSILE; else MonsterSpell = MAGIC_EXPLOSION; break;
			case 2 : MonsterSpell = CURE; break;
			case 3 : if (Monsters[i].Level < 12) MonsterSpell = BIO_FLARE; else MonsterSpell = BIO_FIELD; break;
			case 4 : if (Monsters[i].Level < 14) MonsterSpell = LIGHT_SHOCK; else MonsterSpell = HOLY_LIGHT; break;
			case 5 : MonsterSpell = FIRE; break;
			case 6 : MonsterSpell = LIGHTNING; break;
			case 7 : MonsterSpell = FLUXAL_MELT; break;
			}

			// Special monsters casting status spells.
			if ((r == 3 || r == 2 || r == 4) && Players[0].Status != BLIND && (strcmp(Monsters[i].Name, (char*)"King Tree Ent") == 0 ||
				strcmp(Monsters[i].Name, (char*)"Silhouette") == 0 ||
				strcmp(Monsters[i].Name, (char*)"Kaputos") == 0 ||
				strcmp(Monsters[i].Name, (char*)"Pool Gaurdian") == 0 ||
				strcmp(Monsters[i].Name, (char*)"Rii") == 0 ||
				(strcmp(Monsters[i].Name, (char*)"Beorne") == 0 && Players[0].Level >= 10)
				))
			{
				// Replace bio flare with darkness.
				MonsterSpell = DARKNESS;
			}

			if ((r == 1) && iSucked < 3 && (strcmp(Monsters[i].Name, (char*)"King Tree Ent") == 0 ||
				strcmp(Monsters[i].Name, (char*)"Lineer") == 0 ||
				strcmp(Monsters[i].Name, (char*)"Kaputos") == 0 ||
				strcmp(Monsters[i].Name, (char*)"Pool Gaurdian") == 0 ||
				strcmp(Monsters[i].Name, (char*)"Rii") == 0
				))
			{
				// Replace magic missile with thorn grab.
				MonsterSpell = SUCKED;
			}

			if ((r == 3 || r == 4) && strcmp(Monsters[i].Name, (char*)"Beorne") == 0 && Players[0].Level >= 10 && Players[0].HP > 10 && Monsters[i].MP > 19)
			{
				// Replace holy light with Desecrate.
				MonsterSpell = DESECRATE;
			}

			// Don't let a monster case cure if he doesn't need it! duh.
			if (MonsterSpell == CURE && Monsters[i].HP >= (Monsters[i].MaxHP - (Monsters[i].MaxHP * 0.20)))
			{
				// He doesn't need a cure spell, pick another.
				MonsterSpell = NO_SPELL;
			}
			else
			{
				// The spell makes sense, lets try to cast it.
				if (CanCast(MonsterSpell, i))
					Done = true;
				else
					MonsterSpell = NO_SPELL;
			}
		}
	}

	return MonsterSpell;
}

int CBattleEngine::GetSpellDamage(bool bPlayer, int i, int MonsterSpell)
{
	// Determines damage Spell does, checks/deducts MP etc.
	AttackDamage = 0;
	int aSpell = Spell;
	int MP = 0;
	int lev = 0;

	if (bPlayer)
	{
		// Setup for player casting.
		MP = Players[0].MP;
		lev = Players[0].Level;
	}
	else
	{
		// Setup for monster casting.
		MP = Monsters[i].MP;
		aSpell = MonsterSpell;
		lev = Monsters[i].Level;
	}

	if (aSpell == MAGIC_MISSILE)
	{
		MagicMissileSound->Play();

		if (MP - 2 >= 0)
		{
			// Max level of 4 for this spell.
			if (lev > 4)
				lev = 4;

			// Has enough MP to cast.
			for (int j=0; j<lev; j++)
				AttackDamage += rand() % 6 + 7; // 7 - 12 per level

			// Account for shielding against spells.
			if (!bPlayer && iSpellShield > 0)
			{
				Reduction = (float)iSpellShield / 100;
				Reduction *= (float)AttackDamage;
				AttackDamage -= (int)Reduction;
			}

			MP -= 2;
			char buf[10];
			if (bPlayer)
			{
				strcpy(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" casts Magic Missile on the ");
				strcat(strAttackMessage, Monsters[HandTarget].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
			else
			{
				strcpy(strAttackMessage, Monsters[i].Name);
				strcat(strAttackMessage, (char*)" casts Magic Missile on ");
				strcat(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	if (aSpell == MAGIC_EXPLOSION)
	{
		MagicMissileSound->Play();

		if (MP - 10 >= 0)
		{
			// Max level of 11 for this spell.
			if (lev > 11)
				lev = 11;

			// Has enough MP to cast.
			for (int j=0; j<lev; j++)
				AttackDamage += rand() % 6 + 7; // 7 - 12 per level

			// Account for shielding against spells.
			if (!bPlayer && iSpellShield > 0)
			{
				Reduction = (float)iSpellShield / 100;
				Reduction *= (float)AttackDamage;
				AttackDamage -= (int)Reduction;
			}

			MP -= 10;
			char buf[10];
			if (bPlayer)
			{
				strcpy(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" casts Magic Explosion on the ");
				strcat(strAttackMessage, Monsters[HandTarget].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
			else
			{
				strcpy(strAttackMessage, Monsters[i].Name);
				strcat(strAttackMessage, (char*)" casts Magic Explosion on ");
				strcat(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	if (aSpell == CURE)
	{
		CureSound->Play();

		if (MP - 2 >= 0)
		{
			// Has enough MP to cast.
			int lev=0;
			int maxhp=0;
			int hp=0;

			if (bPlayer)
			{
				lev = Players[0].Level;
				maxhp = Players[0].MaxHP;
				hp = Players[0].HP;
			}
			else
			{
				lev = Monsters[i].Level;
				maxhp = Monsters[i].MaxHP;
				hp = Monsters[i].HP;
			}

			AttackDamage = 0;
			for (int j=0; j<lev; j++)
				AttackDamage += rand() % 10 + (lev * 3); // (1-10) + (level * 3) per level

			// Special case for low heals.
			// Give them a nice heal amount.
			if (AttackDamage < 12)
				AttackDamage = 12;
				
			// Reduce regained HP to only make you reach full health.
			if (hp + AttackDamage > maxhp)
				AttackDamage = maxhp - hp;

			MP -= 2;
			char buf[10];
			if (bPlayer)
			{
				strcpy(strAttackMessage, Players[0].Name);
				if (strcmp(Players[0].Name, (char*)"Ayli")==0)
					strcat(strAttackMessage, (char*)" casts Cure on herself and heals ");
				else
					strcat(strAttackMessage, (char*)" casts Cure on himself and heals ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" hit points.");
			}
			else
			{
				strcpy(strAttackMessage, Monsters[i].Name);
				strcat(strAttackMessage, (char*)" casts Cure on itself and heals ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" hit points.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	if (aSpell == CRYSTAL_CLEAR)
	{
		CrystalClearSound->Play();

		if (MP - 2 >= 0)
		{
			// Has enough MP to cast.
			AttackDamage = 0;
			MP -= 2;
			if (bPlayer)
			{
				strcpy(strAttackMessage, (char*)"The enemy becomes more clear.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	if (aSpell == DARKNESS)
	{
		DarknessSound->Play();

		if (MP - 3 >= 0)
		{
			// Has enough MP to cast.
			AttackDamage = 1;
			MP -= 3;
			if (!bPlayer)
			{
				Players[0].Status = BLIND;
				strcpy(strAttackMessage, (char*)"The enemy becomes harder to see.");
			}
			else
			{
				Monsters[i].Status = BLIND;
				sprintf(strAttackMessage, (char*)"You become harder to see by the %s.", Monsters[i].Name);
			}
		}
		else
		{
			//strcpy(strAttackMessage, (char*)"Not enough Magic Points, the spell fails!");
			aSpell = NO_SPELL;
		}
	}
	if (aSpell == SUCKED)
	{
		SuckedSound->Play();

		if (MP - 3 >= 0)
		{
			// Has enough MP to cast.
			AttackDamage = Players[0].HP * 0.1; // 10% of hp damage
			MP -= 3;
			sprintf(strAttackMessage, (char*)"An overwhelming thorn aura grabs you.");
		}
		else
		{
			//strcpy(strAttackMessage, (char*)"Not enough Magic Points, the spell fails!");
			aSpell = NO_SPELL;
		}

		iSucked++;
	}
	if (aSpell == MIND_NUMB)
	{
		MindNumbSound->Play();

		if (MP - 3 >= 0 && !bBoss)
		{
			// Has enough MP to cast.
			AttackDamage = 0;
			MP -= 3;
			if (bPlayer)
			{
				EnemySilenced = true; // all enemies?
				strcpy(strAttackMessage, (char*)"The enemy becomes incapable of casting magic.");
			}
		}
		else if (bBoss)
		{
			strcpy(strAttackMessage, (char*)"The monster is too powerfull, your spell fails!");
			aSpell = NO_SPELL;
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	if (aSpell == MENTAL_SHIELD)
	{
		MindNumbSound->Play();

		if (MP - 5 >= 0)
		{
			// Has enough MP to cast.
			AttackDamage = 0;
			MP -= 5;
			if (bPlayer)
			{
				if (iShield < 90)
					iShield += 30; // 30% damage reduced from all attacks
				else
					iShield = 90; // 90% damage reduced is max!

				char buf[10];
				strcpy(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" focuses a body shield ");
				strcat(strAttackMessage, _itoa(iShield, buf, 10));
				strcat(strAttackMessage, (char*)"%.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	if (aSpell == PSY_SHIELD)
	{
		MindNumbSound->Play();

		if (MP - 5 >= 0)
		{
			// Has enough MP to cast.
			AttackDamage = 0;
			MP -= 5;
			if (bPlayer)
			{
				if (iSpellShield < 90)
					iSpellShield += 30; // 30% damage reduced from all attacks
				else
					iSpellShield = 90; // 90% damage reduced is max!

				char buf[10];
				strcpy(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" focuses a spell shield ");
				strcat(strAttackMessage, _itoa(iSpellShield, buf, 10));
				strcat(strAttackMessage, (char*)"%.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	else if (aSpell == BIO_FLARE)
	{
		BioFlareSound->Play();

		if (MP - 3 >= 0)
		{
			// Max level of 4 for this spell.
			if (lev > 4)
				lev = 4;

			// Has enough MP to cast.
			for (int j=0; j<lev; j++)
				AttackDamage += rand() % 10 + 7; // 7 - 16 per level

			// Account for shielding against spells.
			if (!bPlayer && iSpellShield > 0)
			{
				Reduction = (float)iSpellShield / 100;
				Reduction *= (float)AttackDamage;
				AttackDamage -= (int)Reduction;
			}

			MP -= 3;
			char buf[10];
			if (bPlayer)
			{
				strcpy(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" casts Bio Flare on the ");
				strcat(strAttackMessage, Monsters[HandTarget].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
			else
			{
				strcpy(strAttackMessage, Monsters[i].Name);
				strcat(strAttackMessage, (char*)" casts Bio Flare on ");
				strcat(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	else if (aSpell == BIO_FIELD)
	{
		BioFlareSound->Play();

		if (MP - 11 >= 0)
		{
			// Max level of 12 for this spell.
			if (lev > 12)
				lev = 12;

			// Has enough MP to cast.
			for (int j=0; j<lev; j++)
				AttackDamage += rand() % 10 + 6; // 6 - 15 per level

			// Account for shielding against spells.
			if (!bPlayer && iSpellShield > 0)
			{
				Reduction = (float)iSpellShield / 100;
				Reduction *= (float)AttackDamage;
				AttackDamage -= (int)Reduction;
			}

			MP -= 11;
			char buf[10];
			if (bPlayer)
			{
				strcpy(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" casts Bio Field on the ");
				strcat(strAttackMessage, Monsters[HandTarget].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
			else
			{
				strcpy(strAttackMessage, Monsters[i].Name);
				strcat(strAttackMessage, (char*)" casts Bio Field on ");
				strcat(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	else if (aSpell == LIGHT_SHOCK)
	{
		LightShockSound->Play();

		if (MP - 4 >= 0)
		{
			// Max level of 5 for this spell.
			if (lev > 5)
				lev = 5;

			// Has enough MP to cast.
			for (int j=0; j<lev; j++)
				AttackDamage += rand() % 10 + 5; // 5 - 14 per level

			// Account for shielding against spells.
			if (!bPlayer && iSpellShield > 0)
			{
				Reduction = (float)iSpellShield / 100;
				Reduction *= (float)AttackDamage;
				AttackDamage -= (int)Reduction;
			}

			MP -= 4;
			char buf[10];
			if (bPlayer)
			{
				strcpy(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" casts Light Shock on the ");
				strcat(strAttackMessage, Monsters[HandTarget].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
			else
			{
				strcpy(strAttackMessage, Monsters[i].Name);
				strcat(strAttackMessage, (char*)" casts Light Shock on ");
				strcat(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	else if (aSpell == HOLY_LIGHT)
	{
		LightShockSound->Play();

		if (MP - 13 >= 0)
		{
			// Max level of 15 for this spell.
			if (lev > 15)
				lev = 15;

			// Has enough MP to cast.
			for (int j=0; j<lev; j++)
				AttackDamage += rand() % 10 + 6; // 5 - 14 per level

			// Account for shielding against spells.
			if (!bPlayer && iSpellShield > 0)
			{
				Reduction = (float)iSpellShield / 100;
				Reduction *= (float)AttackDamage;
				AttackDamage -= (int)Reduction;
			}

			MP -= 13;
			char buf[10];
			if (bPlayer)
			{
				strcpy(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" casts Holy Light on the ");
				strcat(strAttackMessage, Monsters[HandTarget].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
			else
			{
				strcpy(strAttackMessage, Monsters[i].Name);
				strcat(strAttackMessage, (char*)" casts Holy Light on ");
				strcat(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	else if (aSpell == FIRE)
	{
		Fire1Sound->Play();
		Fire2Sound->Play();

		if (MP - 6 >= 0)
		{
			// Max level of 6 for this spell.
			if (lev > 6)
				lev = 6;

			// Has enough MP to cast.
			for (int j=0; j<lev; j++)
				AttackDamage += rand() % 4 + 11; // 11 - 14

			// Account for shielding against spells.
			if (!bPlayer && iSpellShield > 0)
			{
				Reduction = (float)iSpellShield / 100;
				Reduction *= (float)AttackDamage;
				AttackDamage -= (int)Reduction;
			}

			MP -= 6;
			char buf[10];
			if (bPlayer)
			{
				strcpy(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" casts Fire on the ");
				strcat(strAttackMessage, Monsters[HandTarget].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
			else
			{
				strcpy(strAttackMessage, Monsters[i].Name);
				strcat(strAttackMessage, (char*)" casts Fire on ");
				strcat(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	else if (aSpell == LIGHTNING)
	{
		LightningSound->Play();

		if (MP - 8 >= 0)
		{
			// Max level of 7 for this spell.
			if (lev > 7)
				lev = 7;

			// Has enough MP to cast.
			for (int j=0; j<lev; j++)
				AttackDamage += rand() % 9 + 7; // 7 - 15

			// Account for shielding against spells.
			if (!bPlayer && iSpellShield > 0)
			{
				Reduction = (float)iSpellShield / 100;
				Reduction *= (float)AttackDamage;
				AttackDamage -= (int)Reduction;
			}

			MP -= 8;
			char buf[10];
			if (bPlayer)
			{
				strcpy(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" casts Lightning on the ");
				strcat(strAttackMessage, Monsters[HandTarget].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
			else
			{
				strcpy(strAttackMessage, Monsters[i].Name);
				strcat(strAttackMessage, (char*)" casts Lightning on ");
				strcat(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	else if (aSpell == FLUXAL_MELT)
	{
		FluxalMeltSound->Play();

		if (MP - 10 >= 0)
		{
			// Max level of 8 for this spell.
			if (lev > 8)
				lev = 8;

			// Has enough MP to cast.
			for (int j=0; j<lev; j++)
				AttackDamage += rand() % 12 + 9; // 9 - 20

			// Account for shielding against spells.
			if (!bPlayer && iSpellShield > 0)
			{
				Reduction = (float)iSpellShield / 100;
				Reduction *= (float)AttackDamage;
				AttackDamage -= (int)Reduction;
			}

			MP -= 10;
			char buf[10];
			if (bPlayer)
			{
				strcpy(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" casts Fluxal Melt on the ");
				strcat(strAttackMessage, Monsters[HandTarget].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
			else
			{
				strcpy(strAttackMessage, Monsters[i].Name);
				strcat(strAttackMessage, (char*)" casts Fluxal Melt on ");
				strcat(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}
	else if (aSpell == DESECRATE)
	{
		DesecrateSound->Play();

		if (MP - 20 >= 0)
		{
			// Has enough MP to cast.
			MP -= 20;
			char buf[10];
			if (bPlayer)
			{
				AttackDamage = Monsters[HandTarget].HP - 1; // leave enemy with 1 hit point
				strcpy(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" casts Desecrate on the ");
				strcat(strAttackMessage, Monsters[HandTarget].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
			else
			{
				AttackDamage = Players[0].HP - 1; // leave you with 1 hit point
				strcpy(strAttackMessage, Monsters[i].Name);
				strcat(strAttackMessage, (char*)" casts Desecrate on ");
				strcat(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" for ");
				strcat(strAttackMessage, _itoa(AttackDamage, buf, 10));
				strcat(strAttackMessage, (char*)" damage.");
			}
		}
		else
		{
			strcpy(strAttackMessage, (char*)"Not enough Magic Points, your spell fails!");
			aSpell = NO_SPELL;
		}
	}

	if (bPlayer)
	{
		// Setup for player casting.
		Players[0].MP = MP;
		Spell = aSpell;
	}
	else
	{
		// Setup for monster casting.
		Monsters[i].MP = MP;
		MonsterSpell = aSpell;
	}

	return AttackDamage;
}

void CBattleEngine::DrawSpells(CDXSurface *Surface)
{
	// Shows any spell animations on battle screen.
	static bool TransUp = true;
	static int TransValue = 150;
	static int FrameIndex = 1;
	static int FrameCount = 0;
	static int DmgX=0;
	static int DmgY=0;
	static bool UseTrans = false;

	if (SpellStart)
	{
		if (Spell == CURE || Spell == CRYSTAL_CLEAR || Spell == MIND_NUMB || Spell == MENTAL_SHIELD)
		{
			DmgX = Players[0].Sprite->m_PosX + 20;
			DmgY = Players[0].Sprite->m_PosY + 20;
		}
		else
		{
			DmgX = Monsters[HandTarget].Sprite->m_PosX + (Monsters[HandTarget].Width / 2);//20;
			DmgY = Monsters[HandTarget].Sprite->m_PosY + (Monsters[HandTarget].Height / 2);//20;
		}
	}

	if (Spell == MAGIC_MISSILE || Spell == MAGIC_EXPLOSION)
	{
		UseTrans = false;
		if (SpellStart)
		{
			// Init sprite.
			SAFEDELETE(SpellTile);
			SAFEDELETE(SpellSprite);
			SpellTile = new CDXTile;
			if (Spell == MAGIC_MISSILE)
				SpellTile->Create(Screen, (char*)"graphics/magicmissile.bmp", 30, 20, 0);
			else
				SpellTile->Create(Screen, (char*)"graphics/magicexplosion.bmp", 30, 20, 0);
			SpellTile->SetColorKey(0);
			SpellSprite = new CDXSprite();
			SpellSprite->Create(SpellTile);
			SpellSprite->SetFrame(1);
			SpellSprite->SetPos(Players[0].Sprite->m_PosX - 5, Players[0].Sprite->m_PosY + 5);
			SpellStart = false;
		}

		// Move spell.
		SpellSprite->m_PosX -= 26;
		if (SpellSprite->m_PosY < Monsters[HandTarget].Sprite->m_PosY)
			SpellSprite->m_PosY+=2;
		else if (SpellSprite->m_PosY > Monsters[HandTarget].Sprite->m_PosY)
			SpellSprite->m_PosY-=2;

		// Is spell done?
		if (SpellSprite->m_PosX < Monsters[HandTarget].Sprite->m_PosX)
		{
			Spell = NO_SPELL;
			SpellStart = true;
			TransUp = false;
			TransValue = 150;
		}
	}
	else if (Spell == BIO_FLARE || Spell == BIO_FIELD)
	{
		UseTrans = true;
		if (SpellStart)
		{
			// Init sprite.
			SAFEDELETE(SpellTile);
			SAFEDELETE(SpellSprite);
			SpellTile = new CDXTile;
			if (Spell == BIO_FLARE)
				SpellTile->Create(Screen, (char*)"graphics/bioflare.bmp", 30, 20, 0);
			else
				SpellTile->Create(Screen, (char*)"graphics/biofield.bmp", 30, 20, 0);
			SpellTile->SetColorKey(0);
			SpellSprite = new CDXSprite();
			SpellSprite->Create(SpellTile);
			SpellSprite->SetFrame(1);
			SpellSprite->SetPos(Players[0].Sprite->m_PosX - 5, Players[0].Sprite->m_PosY + 5);
			SpellStart = false;
		}

		// Move spell.
		SpellSprite->m_PosX -= 16;
		if (SpellSprite->m_PosY < Monsters[HandTarget].Sprite->m_PosY)
			SpellSprite->m_PosY+=2;
		else if (SpellSprite->m_PosY > Monsters[HandTarget].Sprite->m_PosY)
			SpellSprite->m_PosY-=2;

		// Is spell done?
		if (SpellSprite->m_PosX < Monsters[HandTarget].Sprite->m_PosX)
		{
			Spell = NO_SPELL;
			SpellStart = true;
			TransUp = false;
			TransValue = 150;
		}
	}
	else if (Spell == LIGHT_SHOCK || Spell == HOLY_LIGHT)
	{
		if (Spell == LIGHT_SHOCK)
			UseTrans = true;
		else
			UseTrans = false;

		if (SpellStart)
		{
			// Init sprite.
			SAFEDELETE(SpellTile);
			SAFEDELETE(SpellSprite);
			SpellTile = new CDXTile;
			if (Spell == LIGHT_SHOCK)
				SpellTile->Create(Screen, (char*)"graphics/lightshock.bmp", 30, 20, 0);
			else
				SpellTile->Create(Screen, (char*)"graphics/holylight.bmp", 30, 20, 0);
			SpellTile->SetColorKey(0);
			SpellSprite = new CDXSprite();
			SpellSprite->Create(SpellTile);
			SpellSprite->SetFrame(1);
			SpellSprite->SetPos(Players[0].Sprite->m_PosX - 5, Players[0].Sprite->m_PosY + 5);
			SpellStart = false;
			FrameIndex = 1;
		}

		// Move spell.
		SpellSprite->m_PosX -= 27;
		if (SpellSprite->m_PosY < Monsters[HandTarget].Sprite->m_PosY)
			SpellSprite->m_PosY+=3;
		else if (SpellSprite->m_PosY > Monsters[HandTarget].Sprite->m_PosY)
			SpellSprite->m_PosY-=3;

		// Change frame.
		SpellSprite->SetFrame(FrameIndex++);
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (SpellSprite->m_PosX < Monsters[HandTarget].Sprite->m_PosX)
		{
			Spell = NO_SPELL;
			SpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameIndex = 0;
		}
	}
	else if (Spell == FIRE)
	{
		UseTrans = false;
		if (SpellStart)
		{
			// Init sprite.
			SAFEDELETE(SpellTile);
			SAFEDELETE(SpellSprite);
			SpellTile = new CDXTile;
			SpellTile->Create(Screen, (char*)"graphics/fire.bmp", 40, 40, 0);
			SpellTile->SetColorKey(0);
			SpellSprite = new CDXSprite();
			SpellSprite->Create(SpellTile);
			SpellSprite->SetFrame(1);
			SpellSprite->SetPos(Monsters[HandTarget].Sprite->m_PosX + (Monsters[HandTarget].Width / 2) - 20, Monsters[HandTarget].Sprite->m_PosY + (Monsters[HandTarget].Height / 2) - 20);
			SpellStart = false;
			FrameCount = 0;
			FrameIndex = 1;
		}

		// Move spell.
		SpellSprite->SetFrame(FrameIndex++);
		FrameCount++;
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (FrameCount > 24)
		{
			Spell = NO_SPELL;
			SpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameCount = 0;
			FrameIndex = 0;
		}
	}
	else if (Spell == LIGHTNING)
	{
		UseTrans = false;
		if (SpellStart)
		{
			// Init sprite.
			SAFEDELETE(SpellTile);
			SAFEDELETE(SpellSprite);
			SpellTile = new CDXTile;
			SpellTile->Create(Screen, (char*)"graphics/lightning.bmp", 40, 40, 0);
			SpellTile->SetColorKey(0);
			SpellSprite = new CDXSprite();
			SpellSprite->Create(SpellTile);
			SpellSprite->SetFrame(1);
			SpellSprite->SetPos(Monsters[HandTarget].Sprite->m_PosX + (Monsters[HandTarget].Width / 2) - 20, Monsters[HandTarget].Sprite->m_PosY + (Monsters[HandTarget].Height / 2) - 20);
			SpellStart = false;
			FrameCount = 0;
			FrameIndex = 1;
		}

		// Move spell.
		SpellSprite->SetFrame(FrameIndex++);
		FrameCount++;
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (FrameCount > 24)
		{
			Spell = NO_SPELL;
			SpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameCount = 0;
			FrameIndex = 0;
		}
	}
	else if (Spell == FLUXAL_MELT)
	{
		UseTrans = false;
		if (SpellStart)
		{
			// Init sprite.
			SAFEDELETE(SpellTile);
			SAFEDELETE(SpellSprite);
			SpellTile = new CDXTile;
			SpellTile->Create(Screen, (char*)"graphics/fluxalmelt.bmp", 40, 40, 0);
			SpellTile->SetColorKey(0);
			SpellSprite = new CDXSprite();
			SpellSprite->Create(SpellTile);
			SpellSprite->SetFrame(1);
			SpellSprite->SetPos(Monsters[HandTarget].Sprite->m_PosX + (Monsters[HandTarget].Width / 2) - 20, Monsters[HandTarget].Sprite->m_PosY + (Monsters[HandTarget].Height / 2) - 20);
			SpellStart = false;
			FrameCount = 0;
			FrameIndex = 1;
		}

		// Move spell.
		SpellSprite->SetFrame(FrameIndex++);
		FrameCount++;
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (FrameCount > 24)
		{
			Spell = NO_SPELL;
			SpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameCount = 0;
			FrameIndex = 0;
		}
	}
	else if (Spell == DESECRATE)
	{
		static bool bMovingLeft = true;

		UseTrans = true;
		if (SpellStart)
		{
			// Init sprite.
			SAFEDELETE(SpellTile);
			SAFEDELETE(SpellSprite);
			SpellTile = new CDXTile;
			SpellTile->Create(Screen, (char*)"graphics/beorne.bmp", 40, 40, 0);
			SpellTile->SetColorKey(0);
			SpellSprite = new CDXSprite();
			SpellSprite->Create(SpellTile);
			SpellSprite->SetFrame(1);
			SpellSprite->SetPos(Monsters[HandTarget].Sprite->m_PosX + (Monsters[HandTarget].Width / 2) - 20, Monsters[HandTarget].Sprite->m_PosY + (Monsters[HandTarget].Height / 2) - 20);
			SpellStart = false;
			FrameCount = 0;
			FrameIndex = 1;
			bMovingLeft = true;
			TransUp = true;
		}

		// Move spell.
		SpellSprite->SetFrame(/*FrameIndex++*/0);
		FrameCount++;
		TransValue = 25; // always half trans

		if (bMovingLeft)
		{
			SpellSprite->m_PosX -= 2;
			if (SpellSprite->m_PosX < Monsters[HandTarget].Sprite->m_PosX - 20)
				bMovingLeft = false;
		}
		else
		{
			SpellSprite->m_PosX += 2;
			if (SpellSprite->m_PosX > Monsters[HandTarget].Sprite->m_PosX + Monsters[HandTarget].Width)
				bMovingLeft = true;
		}


		// Is spell done?
		if (FrameCount > 55)
		{
			Spell = NO_SPELL;
			SpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameCount = 0;
			FrameIndex = 0;
		}
	}
	else if (Spell == CURE)
	{
		UseTrans = true;
		if (SpellStart)
		{
			// Init sprite.
			SAFEDELETE(SpellTile);
			SAFEDELETE(SpellSprite);
			SpellTile = new CDXTile;
			SpellTile->Create(Screen, (char*)"graphics/cure.bmp", 40, 40, 0);
			SpellTile->SetColorKey(0);
			SpellSprite = new CDXSprite();
			SpellSprite->Create(SpellTile);
			SpellSprite->SetFrame(1);
			SpellSprite->SetPos(Players[0].Sprite->m_PosX, Players[0].Sprite->m_PosY);
			SpellStart = false;
			FrameCount = 0;
			FrameIndex = 1;
		}

		// Move spell.
		SpellSprite->SetFrame(FrameIndex++);
		FrameCount++;
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (FrameCount > 16)
		{
			Spell = NO_SPELL;
			SpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameCount = 0;
			FrameIndex = 0;
		}
	}
	else if (Spell == CRYSTAL_CLEAR)
	{
		UseTrans = true;
		if (SpellStart)
		{
			// Init sprite.
			SAFEDELETE(SpellTile);
			SAFEDELETE(SpellSprite);
			SpellTile = new CDXTile;
			SpellTile->Create(Screen, (char*)"graphics/crystalclear.bmp", 40, 40, 0);
			SpellTile->SetColorKey(0);
			SpellSprite = new CDXSprite();
			SpellSprite->Create(SpellTile);
			SpellSprite->SetFrame(1);
			SpellSprite->SetPos(Players[0].Sprite->m_PosX, Players[0].Sprite->m_PosY);
			SpellStart = false;
			FrameCount = 0;
			FrameIndex = 1;
		}

		// Move spell.
		SpellSprite->SetFrame(FrameIndex++);
		FrameCount++;
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (FrameCount > 16)
		{
			Spell = NO_SPELL;
			SpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameCount = 0;
			FrameIndex = 0;
		}
	}
	else if (Spell == MIND_NUMB)
	{
		UseTrans = true;
		if (SpellStart)
		{
			// Init sprite.
			SAFEDELETE(SpellTile);
			SAFEDELETE(SpellSprite);
			SpellTile = new CDXTile;
			SpellTile->Create(Screen, (char*)"graphics/mindnumb.bmp", 40, 40, 0);
			SpellTile->SetColorKey(0);
			SpellSprite = new CDXSprite();
			SpellSprite->Create(SpellTile);
			SpellSprite->SetFrame(1);
			SpellSprite->SetPos(Players[0].Sprite->m_PosX, Players[0].Sprite->m_PosY);
			SpellStart = false;
			FrameCount = 0;
			FrameIndex = 1;
		}

		// Move spell.
		if (FrameCount > 8)
		{
			SpellSprite->m_PosX -= 7;
		}

		// Change frame.
		FrameCount++;
		SpellSprite->SetFrame(FrameIndex++);
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (SpellSprite->m_PosX < Monsters[0].Sprite->m_PosX)
		{
			Spell = NO_SPELL;
			SpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameIndex = 0;
			FrameCount = 0;
		}
	}
	else if (Spell == MENTAL_SHIELD || Spell == PSY_SHIELD)
	{
		UseTrans = true;
		if (SpellStart)
		{
			// Init sprite.
			SAFEDELETE(SpellTile);
			SAFEDELETE(SpellSprite);
			SpellTile = new CDXTile;
			if (Spell == MENTAL_SHIELD)
				SpellTile->Create(Screen, (char*)"graphics/mentalshield.bmp", 40, 40, 0);
			else
				SpellTile->Create(Screen, (char*)"graphics/psyshield.bmp", 40, 40, 0);
			SpellTile->SetColorKey(0);
			SpellSprite = new CDXSprite();
			SpellSprite->Create(SpellTile);
			SpellSprite->SetFrame(1);
			SpellSprite->SetPos(Players[0].Sprite->m_PosX, Players[0].Sprite->m_PosY);
			SpellStart = false;
			TransValue = 190;
			FrameCount = 0;
			FrameIndex = 1;
		}

		// Move spell.
		if (FrameCount > 10 && SpellSprite->m_PosX > Players[0].Sprite->m_PosX - 25)
		{
			SpellSprite->m_PosX -= 2;
		}

		// Change frame.
		FrameCount++;
		SpellSprite->SetFrame(FrameIndex++);
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (/*SpellSprite->m_PosX < Players[0].Sprite->m_PosX - 25*/FrameCount > 35)
		{
			Spell = NO_SPELL;
			SpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameIndex = 0;
			FrameCount = 0;
		}
	}

	if (Spell != NO_SPELL)
	{
		// Animate spell.
		if (SpellSprite != NULL)
		{
			if (UseTrans)
				SpellSprite->SetAlphaValue(TransValue);
			SpellSprite->Draw(Surface, 0, 0, CDXBLT_TRANSALPHA);
		}

		// Trans Alpha the spell image.
		if (TransUp)
		{
			TransValue += 10;
			if (TransValue > 200)
			{
				TransUp = false;
			}
		}
		else
		{
			TransValue -= 10;
			if (TransValue < 0)
			{
				TransUp = true;
			}
		}
	}
	else
	{
		SAFEDELETE(SpellSprite);
		SAFEDELETE(SpellTile);
	}

	if (Spell != CRYSTAL_CLEAR && Spell != MIND_NUMB && Spell != MENTAL_SHIELD && Spell != PSY_SHIELD)
	{
		// Show damage rise above monster.
		char buf[10];
		if (Spell == CURE)
		{
			//Surface->TextXY(DmgX, DmgY, RGB(0, 255, 0), (LPCTSTR)_itoa(AttackDamage, buf, 10));
			CDXMenu menu;
			menu.TextXY(Surface, DmgX, DmgY, RGB(0, 255, 0), _itoa(AttackDamage, buf, 10));
		}
		else
		{
			//Surface->TextXY(DmgX, DmgY, RGB(255, 255, 255), (LPCTSTR)_itoa(AttackDamage, buf, 10));
			CDXMenu menu;
			menu.TextXY(Surface, DmgX, DmgY, RGB(255, 255, 255), _itoa(AttackDamage, buf, 10));
		}
		DmgY -= 3;
	}
}

void CBattleEngine::DrawMonsterSpells(CDXSurface* Surface, int i)
{
	// Shows any spell animations on battle screen.
	static bool TransUp = true;
	static int TransValue = 150;
	static int FrameIndex = 1;
	static int FrameCount = 0;
	static int DmgX = 0;
	static int DmgY = 0;
	static bool UseTrans = false;

	if (MonsterSpellStart)
	{
		if (MonsterSpell == CURE)
		{
			DmgX = Monsters[i].Sprite->m_PosX + 20;
			DmgY = Monsters[i].Sprite->m_PosY + 20;
		}
		else
		{
			DmgX = Players[0].Sprite->m_PosX + 20;
			DmgY = Players[0].Sprite->m_PosY + 20;
		}
	}

	if (MonsterSpell == MAGIC_MISSILE || MonsterSpell == MAGIC_EXPLOSION)
	{
		if (MonsterSpellStart)
		{
			UseTrans = false;
			// Init sprite.
			SAFEDELETE(MonsterSpellTile);
			SAFEDELETE(MonsterSpellSprite);
			MonsterSpellTile = new CDXTile;
			if (MonsterSpell == MAGIC_MISSILE)
				MonsterSpellTile->Create(Screen, (char*)"graphics/magicmissile_monster.bmp", 30, 20, 0);
			else
				MonsterSpellTile->Create(Screen, (char*)"graphics/magicexplosion_monster.bmp", 30, 20, 0);
			MonsterSpellTile->SetColorKey(0);
			MonsterSpellSprite = new CDXSprite();
			MonsterSpellSprite->Create(MonsterSpellTile);
			MonsterSpellSprite->SetFrame(1);
			MonsterSpellSprite->SetPos(Monsters[i].Sprite->m_PosX + 5, Monsters[i].Sprite->m_PosY + 5);
			MonsterSpellStart = false;
		}

		// Move spell.
		MonsterSpellSprite->m_PosX += 15;
		if (MonsterSpellSprite->m_PosY < Players[0].Sprite->m_PosY)
			MonsterSpellSprite->m_PosY += 2;
		else if (MonsterSpellSprite->m_PosY > Players[0].Sprite->m_PosY)
			MonsterSpellSprite->m_PosY -= 2;

		// Is spell done?
		if (MonsterSpellSprite->m_PosX > Players[0].Sprite->m_PosX)
		{
			MonsterSpell = NO_SPELL;
			MonsterSpellStart = true;
			TransUp = false;
			TransValue = 150;
		}
	}
	else if (MonsterSpell == BIO_FLARE || MonsterSpell == BIO_FIELD)
	{
		UseTrans = true;
		if (MonsterSpellStart)
		{
			// Init sprite.
			SAFEDELETE(MonsterSpellTile);
			SAFEDELETE(MonsterSpellSprite);
			MonsterSpellTile = new CDXTile;
			if (MonsterSpell == BIO_FLARE)
				MonsterSpellTile->Create(Screen, (char*)"graphics/bioflare_monster.bmp", 30, 20, 0);
			else
				MonsterSpellTile->Create(Screen, (char*)"graphics/biofield.bmp", 30, 20, 0);
			MonsterSpellTile->SetColorKey(0);
			MonsterSpellSprite = new CDXSprite();
			MonsterSpellSprite->Create(MonsterSpellTile);
			MonsterSpellSprite->SetFrame(1);
			MonsterSpellSprite->SetPos(Monsters[i].Sprite->m_PosX - 5, Monsters[i].Sprite->m_PosY + 5);
			MonsterSpellStart = false;
		}

		// Move spell.
		MonsterSpellSprite->m_PosX += 10;
		if (MonsterSpellSprite->m_PosY < Players[0].Sprite->m_PosY)
			MonsterSpellSprite->m_PosY += 6;
		else if (MonsterSpellSprite->m_PosY > Players[0].Sprite->m_PosY)
			MonsterSpellSprite->m_PosY -= 2;

		// Is spell done?
		if (MonsterSpellSprite->m_PosX > Players[0].Sprite->m_PosX)
		{
			MonsterSpell = NO_SPELL;
			MonsterSpellStart = true;
			TransUp = false;
			TransValue = 150;
		}
	}
	else if (MonsterSpell == LIGHT_SHOCK || MonsterSpell == HOLY_LIGHT)
	{
		if (MonsterSpell == LIGHT_SHOCK)
			UseTrans = true;
		else
			UseTrans = false;

		if (MonsterSpellStart)
		{
			// Init sprite.
			SAFEDELETE(MonsterSpellTile);
			SAFEDELETE(MonsterSpellSprite);
			MonsterSpellTile = new CDXTile;
			if (MonsterSpell == LIGHT_SHOCK)
				MonsterSpellTile->Create(Screen, (char*)"graphics/lightshock.bmp", 30, 20, 0);
			else
				MonsterSpellTile->Create(Screen, (char*)"graphics/holylight.bmp", 30, 20, 0);
			MonsterSpellTile->SetColorKey(0);
			MonsterSpellSprite = new CDXSprite();
			MonsterSpellSprite->Create(MonsterSpellTile);
			MonsterSpellSprite->SetFrame(1);
			MonsterSpellSprite->SetPos(Monsters[i].Sprite->m_PosX - 5, Monsters[i].Sprite->m_PosY + 5);
			MonsterSpellStart = false;
			FrameIndex = 1;
		}

		// Move spell.
		MonsterSpellSprite->m_PosX += 16;
		if (MonsterSpellSprite->m_PosY < Players[0].Sprite->m_PosY)
			MonsterSpellSprite->m_PosY += 3;
		else if (MonsterSpellSprite->m_PosY > Players[0].Sprite->m_PosY)
			MonsterSpellSprite->m_PosY -= 3;

		// Change frame.
		MonsterSpellSprite->SetFrame(FrameIndex++);
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (MonsterSpellSprite->m_PosX > Players[0].Sprite->m_PosX)
		{
			MonsterSpell = NO_SPELL;
			MonsterSpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameIndex = 0;
		}
	}
	else if (MonsterSpell == DARKNESS)
	{
		UseTrans = true;
		if (MonsterSpellStart)
		{
			// Init sprite.
			SAFEDELETE(MonsterSpellTile);
			SAFEDELETE(MonsterSpellSprite);
			MonsterSpellTile = new CDXTile;
			MonsterSpellTile->Create(Screen, (char*)"graphics/darkness.bmp", 40, 40, 0);
			MonsterSpellTile->SetColorKey(0);
			MonsterSpellSprite = new CDXSprite();
			MonsterSpellSprite->Create(MonsterSpellTile);
			MonsterSpellSprite->SetFrame(1);
			MonsterSpellSprite->SetPos(Monsters[i].Sprite->m_PosX - 5, Monsters[i].Sprite->m_PosY + 5);
			MonsterSpellStart = false;
			FrameIndex = 1;
		}

		// Move spell.
		MonsterSpellSprite->m_PosX += 16;
		if (MonsterSpellSprite->m_PosY < Players[0].Sprite->m_PosY)
			MonsterSpellSprite->m_PosY += 3;
		else if (MonsterSpellSprite->m_PosY > Players[0].Sprite->m_PosY)
			MonsterSpellSprite->m_PosY -= 3;

		// Change frame.
		MonsterSpellSprite->SetFrame(FrameIndex++);
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (MonsterSpellSprite->m_PosX > Players[0].Sprite->m_PosX)
		{
			MonsterSpell = NO_SPELL;
			MonsterSpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameIndex = 0;
		}
	}
	else if (MonsterSpell == FIRE)
	{
		UseTrans = false;
		if (MonsterSpellStart)
		{
			// Init sprite.
			SAFEDELETE(MonsterSpellTile);
			SAFEDELETE(MonsterSpellSprite);
			MonsterSpellTile = new CDXTile;
			MonsterSpellTile->Create(Screen, (char*)"graphics/fire.bmp", 40, 40, 0);
			MonsterSpellTile->SetColorKey(0);
			MonsterSpellSprite = new CDXSprite();
			MonsterSpellSprite->Create(MonsterSpellTile);
			MonsterSpellSprite->SetFrame(1);
			MonsterSpellSprite->SetPos(Players[0].Sprite->m_PosX, Players[0].Sprite->m_PosY);
			MonsterSpellStart = false;
			FrameCount = 0;
			FrameIndex = 1;
		}

		// Move spell.
		MonsterSpellSprite->SetFrame(FrameIndex++);
		FrameCount++;
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (FrameCount > 24)
		{
			MonsterSpell = NO_SPELL;
			MonsterSpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameCount = 0;
			FrameIndex = 0;
		}
	}
	else if (MonsterSpell == LIGHTNING)
	{
		UseTrans = false;
		if (MonsterSpellStart)
		{
			// Init sprite.
			SAFEDELETE(MonsterSpellTile);
			SAFEDELETE(MonsterSpellSprite);
			MonsterSpellTile = new CDXTile;
			MonsterSpellTile->Create(Screen, (char*)"graphics/lightning.bmp", 40, 40, 0);
			MonsterSpellTile->SetColorKey(0);
			MonsterSpellSprite = new CDXSprite();
			MonsterSpellSprite->Create(MonsterSpellTile);
			MonsterSpellSprite->SetFrame(1);
			MonsterSpellSprite->SetPos(Players[0].Sprite->m_PosX, Players[0].Sprite->m_PosY);
			MonsterSpellStart = false;
			FrameCount = 0;
			FrameIndex = 1;
		}

		// Move spell.
		MonsterSpellSprite->SetFrame(FrameIndex++);
		FrameCount++;
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (FrameCount > 24)
		{
			MonsterSpell = NO_SPELL;
			MonsterSpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameCount = 0;
			FrameIndex = 0;
		}
	}
	else if (MonsterSpell == FLUXAL_MELT)
	{
		UseTrans = false;
		if (MonsterSpellStart)
		{
			// Init sprite.
			SAFEDELETE(MonsterSpellTile);
			SAFEDELETE(MonsterSpellSprite);
			MonsterSpellTile = new CDXTile;
			MonsterSpellTile->Create(Screen, (char*)"graphics/fluxalmelt.bmp", 40, 40, 0);
			MonsterSpellTile->SetColorKey(0);
			MonsterSpellSprite = new CDXSprite();
			MonsterSpellSprite->Create(MonsterSpellTile);
			MonsterSpellSprite->SetFrame(1);
			MonsterSpellSprite->SetPos(Players[0].Sprite->m_PosX, Players[0].Sprite->m_PosY);
			MonsterSpellStart = false;
			FrameCount = 0;
			FrameIndex = 1;
		}

		// Move spell.
		MonsterSpellSprite->SetFrame(FrameIndex++);
		FrameCount++;
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (FrameCount > 24)
		{
			MonsterSpell = NO_SPELL;
			MonsterSpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameCount = 0;
			FrameIndex = 0;
		}
	}
	else if (MonsterSpell == SUCKED)
	{
		UseTrans = false;
		if (MonsterSpellStart)
		{
			// Init sprite.
			SAFEDELETE(MonsterSpellTile);
			SAFEDELETE(MonsterSpellSprite);
			MonsterSpellTile = new CDXTile;
			MonsterSpellTile->Create(Screen, (char*)"graphics/sucked.bmp", 40, 40, 0);
			MonsterSpellTile->SetColorKey(0);
			MonsterSpellSprite = new CDXSprite();
			MonsterSpellSprite->Create(MonsterSpellTile);
			MonsterSpellSprite->SetFrame(1);
			MonsterSpellSprite->SetPos(Players[0].Sprite->m_PosX, Players[0].Sprite->m_PosY);
			MonsterSpellStart = false;
			FrameCount = 0;
			FrameIndex = 1;
		}

		// Move spell.
		MonsterSpellSprite->SetFrame(FrameIndex++);
		MonsterSpellSprite->SetPos(Players[0].Sprite->m_PosX, Players[0].Sprite->m_PosY);
		FrameCount++;
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (FrameCount > 35)
		{
			MonsterSpell = NO_SPELL;
			MonsterSpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameCount = 0;
			FrameIndex = 0;
		}
	}
	else if (MonsterSpell == CURE)
	{
		UseTrans = true;
		if (MonsterSpellStart)
		{
			// Init sprite.
			SAFEDELETE(MonsterSpellTile);
			SAFEDELETE(MonsterSpellSprite);
			MonsterSpellTile = new CDXTile;
			MonsterSpellTile->Create(Screen, (char*)"graphics/cure.bmp", 40, 40, 0);
			MonsterSpellTile->SetColorKey(0);
			MonsterSpellSprite = new CDXSprite();
			MonsterSpellSprite->Create(MonsterSpellTile);
			MonsterSpellSprite->SetFrame(1);
			MonsterSpellSprite->SetPos(Monsters[i].Sprite->m_PosX, Monsters[i].Sprite->m_PosY);
			MonsterSpellStart = false;
			FrameCount = 0;
			FrameIndex = 1;
		}

		// Move spell.
		MonsterSpellSprite->SetFrame(FrameIndex++);
		FrameCount++;
		if (FrameIndex >= MAX_SPELL_FRAMES)
			FrameIndex = 1;

		// Is spell done?
		if (FrameCount > 16)
		{
			MonsterSpell = NO_SPELL;
			MonsterSpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameCount = 0;
			FrameIndex = 0;
		}
	}
	else if (MonsterSpell == DESECRATE)
	{
		static bool bMovingLeft = true;

		UseTrans = true;
		if (MonsterSpellStart)
		{
			// Init sprite.
			SAFEDELETE(MonsterSpellTile);
			SAFEDELETE(MonsterSpellSprite);
			MonsterSpellTile = new CDXTile;
			MonsterSpellTile->Create(Screen, (char*)"graphics/beorne.bmp", 40, 40, 0);
			MonsterSpellTile->SetColorKey(0);
			MonsterSpellSprite = new CDXSprite();
			MonsterSpellSprite->Create(MonsterSpellTile);
			MonsterSpellSprite->SetFrame(1);
			MonsterSpellSprite->SetPos(Players[0].Sprite->m_PosX + (Players[0].Width / 2) - 20, Players[0].Sprite->m_PosY + (Players[0].Height / 2) - 20);
			MonsterSpellStart = false;
			FrameCount = 0;
			FrameIndex = 1;
			bMovingLeft = true;
			TransUp = true;
		}

		// Move spell.
		MonsterSpellSprite->SetFrame(/*FrameIndex++*/0);
		FrameCount++;
		TransValue = 25; // always half trans

		if (bMovingLeft)
		{
			MonsterSpellSprite->m_PosX -= 2;
			if (MonsterSpellSprite->m_PosX < Players[0].Sprite->m_PosX - 20)
				bMovingLeft = false;
		}
		else
		{
			MonsterSpellSprite->m_PosX += 2;
			if (MonsterSpellSprite->m_PosX > Players[0].Sprite->m_PosX + Players[0].Width)
				bMovingLeft = true;
		}


		// Is spell done?
		if (FrameCount > 55)
		{
			MonsterSpell = NO_SPELL;
			MonsterSpellStart = true;
			TransUp = false;
			TransValue = 150;
			FrameCount = 0;
			FrameIndex = 0;
		}
	}

	if (MonsterSpell != NO_SPELL)
	{
		// Animate spell.
		if (MonsterSpellSprite != NULL)
		{
			if (UseTrans)
				MonsterSpellSprite->SetAlphaValue(TransValue);
			MonsterSpellSprite->Draw(Surface, 0, 0, CDXBLT_TRANSALPHA);
		}

		// Trans Alpha the spell image.
		if (TransUp)
		{
			TransValue += 10;
			if (TransValue > 200)
			{
				TransUp = false;
			}
		}
		else
		{
			TransValue -= 10;
			if (TransValue < 0)
			{
				TransUp = true;
			}
		}
	}
	else
	{
		SAFEDELETE(MonsterSpellSprite);
		SAFEDELETE(MonsterSpellTile);
	}

	// Show damage rise above player.
	char buf[10];
	if (MonsterSpell == CURE)
	{
		//Surface->TextXY(DmgX, DmgY, RGB(0, 255, 0), (LPCTSTR)_itoa(AttackDamage, buf, 10));
		CDXMenu menu;
		menu.TextXY(Surface, DmgX, DmgY, RGB(0, 255, 0), _itoa(AttackDamage, buf, 10));
	}
	else
	{
		char msg[10];
		sprintf(msg, (char*)"%d", AttackDamage);
		//Surface->TextXY(DmgX, DmgY, RGB(255,255,255), (LPCTSTR)msg);
		CDXMenu menu;
		menu.TextXY(Surface, DmgX, DmgY, RGB(255, 255, 255), msg);
	}
	DmgY -= 3;
}

void CBattleEngine::DrawAttacks(CDXSurface *Surface)
{
	// Draw a slash type mark on monster.
	static int x=0, y=0;
	static int DmgX=0, DmgY=0;
	bool bDoubleSlash = false;

	if (strcmp(Players[0].Name, (char*)"Ayli")==0)
		bDoubleSlash = true;

	if (AttackDone || AttackDamage < 1)
		return;

	if (AttackStart)
	{
		// Setup start of slash in upper left corner.
		x = Monsters[HandTarget].Sprite->m_PosX;
		y = Monsters[HandTarget].Sprite->m_PosY;
		DmgX = x + (Monsters[HandTarget].Width / 2);//20;
		DmgY = y + (Monsters[HandTarget].Height / 2);//20;
		AttackStart = false;
		if (HandSprite->GetFrame() == 9)
		{
			Surface->Fill(RGB(255,255,255)); // flash white for accuracy bonus
			DmgX -= 5;
			//BonusSlashSound->Play();
		}
		else
		{
			SlashSound->Play();
		}
	}

	if (x < Monsters[HandTarget].Sprite->m_PosX + 40)
	{
		// Draw slash.
		Surface->Lock();
		Surface->Line(x, y, x + 10, y + 10, RGB2(0, 168, 0));
		Surface->Line(x+1, y, x + 11, y + 10, RGB2(0, 168, 0));
		Surface->Line(x+2, y, x + 12, y + 10, RGB2(0, 168, 0));
		Surface->Line(x+3, y, x + 13, y + 10, RGB2(0, 168, 0));

		if (bDoubleSlash)
		{
			Surface->Line(12+x, y, 12+x + 10, y + 10, RGB2(0, 168, 0));
			Surface->Line(12+x+1, y, 12+x + 11, y + 10, RGB2(0, 168, 0));
			Surface->Line(12+x+2, y, 12+x + 12, y + 10, RGB2(0, 168, 0));
			Surface->Line(12+x+3, y, 12+x + 13, y + 10, RGB2(0, 168, 0));
		}

		Surface->UnLock();
		x += 8;
		y += 8;
	}

	// Show damage rise above monster.
	if (HandSprite->GetFrame() == 9)
	{
		// Show bonus damage.
		// We minus the bonus damage because when we get here it's already added in to AttackDamage.
		char msg[50];
//		if (PenaltyDamage == 0)
//			sprintf(msg, (char*)"%d + %d", AttackDamage - BonusDamage, BonusDamage);
//		else
		sprintf(msg, (char*)"%d + %d", AttackDamage - BonusDamage, BonusDamage);

		//Surface->TextXY(DmgX, DmgY, RGB(255,255,255), (LPCTSTR)msg);
		CDXMenu menu;
		menu.TextXY(Surface, DmgX, DmgY, RGB(255, 255, 255), msg);
	}
	else
	{
		char msg[50];
//		if (PenaltyDamage == 0)
			sprintf(msg, (char*)"%d", AttackDamage);
//		else
//			sprintf(msg, (char*)"%d - %d", AttackDamage + PenaltyDamage, PenaltyDamage);

		//Surface->TextXY(DmgX, DmgY, RGB(255,255,255), (LPCTSTR)msg/*_itoa(AttackDamage, buf, 10)*/);
		CDXMenu menu;
		menu.TextXY(Surface, DmgX, DmgY, RGB(255, 255, 255), msg/*_itoa(AttackDamage, buf, 10)*/);
	}
	DmgY -= 3;

	if (DmgY < (Monsters[HandTarget].Sprite->m_PosY - 10))
	{
		AttackStart = true;
		AttackDone = true;
	}
}

void CBattleEngine::DrawMonsterAttacks(CDXSurface *Surface)
{
	// Draw a slash type mark on player.
	static int x=0, y=0;
	static int DmgX=0, DmgY=0;

	if (MonsterAttackDone)
		return;

	if (MonsterAttackStart)
	{
		// Setup start of slash in upper left corner.
		x = Players[0].Sprite->m_PosX;
		y = Players[0].Sprite->m_PosY;
		DmgX = x + 20;
		DmgY = y + 20;
		MonsterAttackStart = false;
		MonsterAttackDone = false;
		SlashSound->Play();
	}

	if (x < Players[0].Sprite->m_PosX + 40)
	{
		// Show slash mark.
		Surface->Lock();
		Surface->Line(x, y, x + 10, y + 10, RGB2(0, 168, 0));
		Surface->Line(x+1, y, x + 11, y + 10, RGB2(0, 168, 0));
		Surface->Line(x+2, y, x + 12, y + 10, RGB2(0, 168, 0));
		Surface->Line(x+3, y, x + 13, y + 10, RGB2(0, 168, 0));
/*		if (bDoubleAttack)
		{
			Surface->Line(x+5, y, x + 10 + 5, y + 10, RGB(0, 168, 0));
			Surface->Line(x+1+5, y, x + 11 + 5, y + 10, RGB(0, 168, 0));
			Surface->Line(x+2+5, y, x + 12 + 5, y + 10, RGB(0, 168, 0));
			Surface->Line(x+3+5, y, x + 13 + 5, y + 10, RGB(0, 168, 0));
		}*/
		Surface->UnLock();
		x += 10;
		y += 10;
	}

	// Show damage rise above player.
//	char buf[10];
	char msg[50];
//	if (PenaltyDamage == 0)

	if (MonsterBonusDamage == 0)
		sprintf(msg, (char*)"%d", AttackDamage);
	else if (MonsterBonusDamage > 0)
		sprintf(msg, (char*)"%d + %d", AttackDamage - MonsterBonusDamage, MonsterBonusDamage);
//	else
//		sprintf(msg, (char*)"%d", AttackDamage);
	//Surface->TextXY(DmgX, DmgY, RGB(255,255,255), (LPCTSTR)msg/*_itoa(AttackDamage, buf, 10)*/);
	CDXMenu menu;
	menu.TextXY(Surface, DmgX, DmgY, RGB(255, 255, 255), msg/*_itoa(AttackDamage, buf, 10)*/);

	
	DmgY -= 3;

	if (DmgY < (Players[0].Sprite->m_PosY - 10))
	{
		MonsterAttackStart = true;
		MonsterAttackDone = true;
	}
}

bool CBattleEngine::isMonstersAlive()
{
	for (int i=0; i<NumMonsters; i++)
	{
		if (Monsters[i].HP > 0)
			return true;
	}

	return false;
}

void CBattleEngine::Draw(int Direction)
{
	int ArmorAbsorbedAmount = 0;

	// Size of background battle.
	RECT BattleBackRect;
	BattleBackRect.left = 0;
	BattleBackRect.top = 0;
	BattleBackRect.right = 500;
	BattleBackRect.bottom = 300;

	// Size of foreground battle.
	RECT BattleFrontRect;
	BattleFrontRect.left = 0;
	BattleFrontRect.top = 0;
	BattleFrontRect.right = 487 - LEFT_MARGIN;
	BattleFrontRect.bottom = 287 - TOP_MARGIN;

	// Draw background onto actual screen back.
	Background->DrawBlk(Screen->GetBack(), Background->GetWidth(), Background->GetHeight());

	// Draw background onto mini-screen.
	if (BackAlpha > 5)
	{
		//
		// This is the start of a new battle.
		// Fade in the background into the battle.
		//
		// First, clear out battle screen.
		SmallSurface->Fill(0);
		// Next, draw background bitmap onto temp surface before fade.
		BattleLayerBack->Draw(SmallSurfaceFade);
		// Next, draw temp surface onto battle surface with alpha value.
		SmallSurfaceFade->DrawBlkAlpha(SmallSurface, 0, 0, &BattleBackRect, BackAlpha);
		// Finally, decrease the fade amount.
		BackAlpha-=5;
	}
	else
	{
		//
		// We're already into the battle, no need to fade just draw it quickly.
		//
		BattleLayerBack->Draw(SmallSurface);
	}

	switch (Direction)
	{
		case LEFT : BattleLayerBack->ScrollLeft(1); break;
		case RIGHT : BattleLayerBack->ScrollRight(1); break;
		case UP : BattleLayerBack->ScrollUp(1); break;
		case DOWN : BattleLayerBack->ScrollDown(1); break;
	};

	// Clear temp surface.
	SmallSurface2->Fill(0);

	// Draw sub-image ontop of background on mini-screen.
	BattleFront->DrawBlk(SmallSurface2, BattleFront->GetWidth(), BattleFront->GetHeight());

	//
	// Draw onto SmallSurface2 all your character movements,
	// battle action, hit points, stats, etc.
	// Then DrawTrans it onto SmallSurface when it is ready.
	// The background will be the moving BackBmp graphic.
	//
	// TODO: Drawing on SmallSurface2 here.
	//
	
	// 1. Draw monster names on left side.
	SmallSurface2->GetDC();
	SmallSurface2->ChangeFont("Impact", 5, 15, FW_NORMAL);
	SmallSurface2->SetFont();
	SmallSurface2->ReleaseDC();
	int Y_Value = 0;
	int X_Value = 20;
	for (int i=0; i<NumMonsters; i++)
	{
		if (i > 1)
		{
			// Second row of monsters.
			if (i % 2 == 0)
			{
				// Top row of 2nd column.
				Y_Value = 0;
				X_Value += 120;
			}
		}

		if (Monsters[i].HP > 0)
		{
			// Draw Monster Image.
			if (Monsters[i].Sprite != NULL)
			{
				Monsters[i].Sprite->SetPos(MONSTER_START_POSX + X_Value, MONSTER_START_POSY + Y_Value);
				if (Players[0].Status == BLIND)
				{
					Monsters[i].Sprite->SetAlphaValue(200);
					Monsters[i].Sprite->Draw(SmallSurface2, 0, 0, CDXBLT_TRANSALPHA);
				}
				else
				{
					Monsters[i].Sprite->Draw(SmallSurface2, 0, 0, CDXBLT_TRANS);
				}
			}
			
			Y_Value += Monsters[i].Height;
			
			// Draw Monster Name below it.
			SmallSurface2->FillRect(MONSTER_START_POSX + X_Value - 20, MONSTER_START_POSY + Y_Value, 120, 20, RGB(1, 1, 1));
//			char strText[600];
//			_itoa(i + 1, strText, 10);
//			strcat(strText, (char*)". ");
//			SmallSurface2->TextXY(MONSTER_START_POSX + X_Value - 20, MONSTER_START_POSY + Y_Value, RGB(255,255,255), strText);
			//SmallSurface2->TextXY(MONSTER_START_POSX + X_Value - 5, MONSTER_START_POSY + Y_Value, RGB(255,200,0), (LPCTSTR)Monsters[i].Name);
			CDXMenu menu;
			menu.TextXY(SmallSurface2, MONSTER_START_POSX + X_Value - 5, MONSTER_START_POSY + Y_Value, RGB(255, 200, 0), Monsters[i].Name);

			if (ViewEnemyHP || bCrystalClearOn)
			{
				//
				// Draw monster's HP status.
				//
				Y_Value += 15;
				float PercentHP = (float)((float)Monsters[i].HP / (float)Monsters[i].MaxHP) * 100;

				COLORREF HPColor = RGB(0, 190, 0);

				if (PercentHP > 85.0)
					HPColor = RGB(0, 190, 46);
				else if (PercentHP > 75.0)
					HPColor = RGB(0, 170, 70);
				else if (PercentHP > 35.0 && PercentHP < 76.0)
					HPColor = RGB2(0, 160, 120); // yellow
				else if (PercentHP > 0.0 && PercentHP < 36.0)
					HPColor = RGB2(0, 178, 0); // bright red
				
				int BarLength = 30; // 30 pixels for bar length.
				float MeterLength = (float)Monsters[i].HP / (float)Monsters[i].MaxHP;
				MeterLength = BarLength * MeterLength;
				
				// Draw black empty bar.
				SmallSurface2->FillRect(MONSTER_START_POSX + X_Value - 5, MONSTER_START_POSY + Y_Value, MONSTER_START_POSX + X_Value - 5 + BarLength, MONSTER_START_POSY + Y_Value + 5, RGB(1,1,1));
				// Draw player's hp amount over black.
				SmallSurface2->FillRect(MONSTER_START_POSX + X_Value - 5, MONSTER_START_POSY + Y_Value, MONSTER_START_POSX + X_Value - 5 + MeterLength, MONSTER_START_POSY + Y_Value + 5, HPColor);
			}

			Y_Value += 40;
		}
		else
		{
			if (Monsters[i].HP <= 0 && Monsters[i].zoom > 0)
			{
				// Dieing .. zoom out
				Monsters[i].zoom -= 0.1;
				Monsters[i].Sprite->SetScale(Monsters[i].zoom);
				Monsters[i].Sprite->Draw(SmallSurface2, 0, 0, CDXBLT_TRANSSCALED);
				Monsters[i].Sprite->m_PosX-=3;
				Monsters[i].Sprite->m_PosY+=3;
			}

			Y_Value += Monsters[i].Height;
			Y_Value += 40;
		}
	}

	// If player got sucked, move him gradually to the left.
	if (iSucked > 0)
	{
		if (PlayerPositionOffset < 35 * iSucked)
			PlayerPositionOffset++;
	}
	else
	{
		PlayerPositionOffset = 0;
	}

	//
	// Draw player graphic on right side.
	//
	Y_Value = 0;
	for (int i=0; i<NumPlayers; i++)
	{
		if (Players[i].HP > 0)
		{
			// Draw Player Image.
			if (Players[i].Sprite != NULL)
			{
				Players[i].Sprite->SetFrame(1);
				Players[i].Sprite->SetPos(365 - PlayerPositionOffset, 95 + Y_Value);
				Players[i].Sprite->Draw(SmallSurface2, 0, 0, CDXBLT_TRANS);
			}
			
			Y_Value += Players[i].Height;
		}
		else if (Players[i].HP <= 0 && Players[i].zoom > 0)
		{
			// Dieing .. zoom out
			Players[i].zoom -= 0.1;
			if (Players[i].Sprite != NULL)
			{
				Players[i].Sprite->SetFrame(1);
				Players[i].Sprite->SetScale(Players[i].zoom);
				Players[i].Sprite->Draw(SmallSurface2, 0, 0, CDXBLT_TRANSSCALED);
				Players[i].Sprite->m_PosX+=3;
				Players[i].Sprite->m_PosY+=3;
			}
		}
		else
		{
			// Player is totally dead, done zoom.
			// Put him back in proper place in case other enemies want to hit his dead body.
			Players[i].Sprite->SetPos(365 - PlayerPositionOffset, 95 + Y_Value);
		}
	}

	//
	// Draw players HP status.
	//

	float PercentHP = (float)((float)Players[0].HP / (float)Players[0].MaxHP) * 100;
	COLORREF HPColor = RGB(0, 190, 0);

	if (PercentHP > 85.0)
		HPColor = RGB(0, 190, 46);
	else if (PercentHP > 75.0)
		HPColor = RGB(0, 170, 70);
	else if (PercentHP > 35.0 && PercentHP < 76.0)
		HPColor = RGB2(0, 160, 120); // yellow
	else if (PercentHP > 0.0 && PercentHP < 36.0)
		HPColor = RGB2(0, 178, 0); // bright red

	int BarLength = 30; // 30 pixels for bar length.
	float MeterLength = (float)Players[0].HP / (float)Players[0].MaxHP;
	MeterLength = BarLength * MeterLength;

	// Draw black empty bar.
	SmallSurface2->FillRect(370 - PlayerPositionOffset, 140, 370 + BarLength - PlayerPositionOffset, 145, RGB(1,1,1));
	// Draw player's hp amount over black.
	SmallSurface2->FillRect(370 - PlayerPositionOffset, 140, 370 + MeterLength - PlayerPositionOffset, 145, HPColor);

	//
	// Text Box Area
	//
	// Draw black command box.
	SmallSurface2->FillRect(11, BattleFrontRect.bottom - 80, BattleFrontRect.right - 20, BattleFrontRect.bottom - 17, RGB(1,1,1));

	// Draw frame around box.
	SmallSurface2->Rect(10, BattleFrontRect.bottom - 81, BattleFrontRect.right - 19, BattleFrontRect.bottom - 16, RGB(255,255,255));

	// Determine what to draw in text box.
	if (Phase == COMMAND)
	{
		//
		// Draw list of commands for action.
		//		
		Spell = NO_SPELL;
		MonsterSpell = NO_SPELL;
		SpellStart = true;
		AttackDone = false;
		MonsterAttackDone = true;
		MonsterAttackStart = true;
		AttackStart = true;

		AttackDamage = 0;

		// Draw commands.
		BattleMenu.SetPos(20, BattleFrontRect.bottom - 97);
		BattleMenu.SetSpacing(20);
		BattleMenu.SetSurface(SmallSurface2);
		BattleMenu.Draw2();

		int iCommand = -1;
		Attacking = true;

		// Check key hits.
		Input->Update();
		Input->UpdateLastKey(true);
		if (Input->GetLastKey() == 208)
		{
			BattleMenu.Down();
			BattleMenu.Draw2();
		}
		else if (Input->GetLastKey() == 200)
		{
			BattleMenu.Up();
			BattleMenu.Draw2();
		}
		else if (Input->GetLastKey() == 28 || Input->GetLastKey() == 57)
		{
			iCommand = BattleMenu.Enter();
		}

		if (iCommand == 0)
		{
			// Attack
			// Remove this later on, just to test.
			strcpy(strAttackMessage, (char*)"Select your target.");
			Attacking = true;
			Phase = PICK_TARGET;
		}
		else if (iCommand == 1)
		{
			// Cast Spell
			strcpy(strAttackMessage, (char*)"Select your target.");
			Attacking = false;
			Phase = CHOOSE_SPELL;
		}
		else if (iCommand == 2)
		{
			// Run
			int r = rand() % 10 + 1; // 1 - 10

			// Can't run from a boss!
			if (bBoss)
				r = 0;

			if (r > 4)
			{
				strcpy(strAttackMessage, (char*)"You run away.");
				bRun = true;
				Phase = RESULTS;
			}
			else
			{
				strcpy(strAttackMessage, (char*)"You can't get away this time!");
				bRun = false;
				Phase = ATTACK;
			}
		}

/*		for (int c=0; c < 50; c++)
		{
			SmallSurface2->Lock();
			SmallSurface2->PutPixel(150+c, BattleFrontRect.bottom - 50, RGB(0, 42, 0));
			SmallSurface2->UnLock();
		}*/
	}
	else if (Phase == CHOOSE_SPELL)
	{
		//
		// First, ChooseSpell();
		//
		SpellMenu.SetPos(200, 55);
		SpellMenu.SetSurface(SmallSurface2);
		char strTitle[1000];
		char buf[10];
		strcpy(strTitle, (char*)"Choose Spell MP: ");
		strcat(strTitle, _itoa(Players[0].MP, buf, 10));
		strcat(strTitle, (char*)" / ");
		strcat(strTitle, _itoa(Players[0].MaxMP, buf, 10));

		SpellMenu.SetTitle(strTitle);
		SpellMenu.Draw2(true);
		SpellStart = true;
		Spell = NO_SPELL;

		int iCommand = -1;

		// Check key hits.
		Input->Update();
		Input->UpdateLastKey(true);
		if (Input->GetLastKey() == 208)
		{
			SpellMenu.Down();
			SpellMenu.Draw2();
		}
		else if (Input->GetLastKey() == 200)
		{
			SpellMenu.Up();
			SpellMenu.Draw2();
		}
		else if (Input->GetLastKey() == 28 || Input->GetLastKey() == 57)
		{
			iCommand = SpellMenu.Enter();
		}

		if (iCommand == 0)
		{
			// Cancel
			Phase = COMMAND;
		}
		if (iCommand == 1)
		{
			// Magic Missile/Magic Explosion
			Phase = PICK_TARGET;

			if (/*strcmp(Players[0].Name, (char*)"Beorne") == 0*/bBeorne)
			{
				if (Players[0].Level < 7)
					Spell = MAGIC_MISSILE;
				else
					Spell = DESECRATE;
			}
			else
			{
				if (Players[0].Level < 10)
					Spell = MAGIC_MISSILE;
				else
					Spell = MAGIC_EXPLOSION;
			}
		}
		else if (iCommand == 2)
		{
			// Cure
			Phase = ATTACK;
			Spell = CURE;
			// Casting a spell.
			AttackDone = true;
			GetSpellDamage();
			Players[0].HP += AttackDamage;
		}
		else if (iCommand == 3)
		{
			// Crystal Clear
			Phase = ATTACK;
			Spell = CRYSTAL_CLEAR;
			AttackDone = true;
			ViewEnemyHP = true;
			GetSpellDamage(); // Makes sure you can cast it.
		}
		else if (iCommand == 4)
		{
			// Bio Flare
			Phase = PICK_TARGET;
			if (Players[0].Level < 12)
				Spell = BIO_FLARE;
			else
				Spell = BIO_FIELD;
		}
		else if (iCommand == 5)
		{
			// Light Shock
			Phase = PICK_TARGET;
			if (Players[0].Level < 14)
				Spell = LIGHT_SHOCK;
			else
				Spell = HOLY_LIGHT;
		}
		else if (iCommand == 6)
		{
			// Mind Numb
			Phase = ATTACK;
			Spell = MIND_NUMB;
			AttackDone = true;
			GetSpellDamage(); // Makes sure you can cast it.
		}
		else if (iCommand == 7)
		{
			// Cancel
			Phase = PICK_TARGET;
			Spell = FIRE;
		}
		else if (iCommand == 8)
		{
			// Cancel
			Phase = PICK_TARGET;
			Spell = LIGHTNING;
		}
		else if (iCommand == 9)
		{
			// Cancel
			Phase = PICK_TARGET;
			Spell = FLUXAL_MELT;
		}
		else if (iCommand == 10)
		{
			Phase = ATTACK;
			Spell = MENTAL_SHIELD;
			AttackDone = true;
			GetSpellDamage(); // Make sure you can cast it.
		}
		else if (iCommand == 11)
		{
			Phase = ATTACK;
			Spell = PSY_SHIELD;
			AttackDone = true;
			GetSpellDamage(); // Make sure you can cast it.
		}	
	}
	else if (Phase == PICK_TARGET)
	{
		// Hand shows, lets user pick target to hit.
		//SmallSurface2->TextXY(20, BattleFrontRect.bottom - 75, RGB(255,255,255), (LPCTSTR)strAttackMessage);
		CDXMenu menu;
		menu.TextXY(SmallSurface2, 20, BattleFrontRect.bottom - 75, RGB(255, 255, 255), strAttackMessage);

		int YValue = 0;//(HandTarget % 2) * 80;
		int XValue = 0;//20;

//		if (HandTarget > 1)
		XValue = Monsters[HandTarget].Sprite->m_PosX + (Monsters[HandTarget].Width / 2) - 20;
		//XValue += 120;
//		if (HandTarget == 1 || HandTarget == 3)
//			YValue = 80 + Monsters[HandTarget].Height;
		YValue = Monsters[HandTarget].Sprite->m_PosY + (Monsters[HandTarget].Height / 2) - 20;

		// Old target, is dead. Target next monster.
		if (Monsters[HandTarget].HP <= 0)
		{
			for (int i=0; i<NumMonsters; i++)
			{
				// Select new monster to attack default.
				if (Monsters[i].HP > 0)
				{
					YValue = 0;
					XValue = 20;
					HandTarget = i;
//					if (HandTarget > 1)
					XValue = Monsters[HandTarget].Sprite->m_PosX + (Monsters[HandTarget].Width / 2) - 20;
					//XValue += 120;

//					if (HandTarget == 1 || HandTarget == 3)
//						YValue = 80;
					YValue = Monsters[HandTarget].Sprite->m_PosY + (Monsters[HandTarget].Height / 2) - 20;

					i = 1000; // exit loop
				}
			}
		}

		static int TargetDelay = 0;
		int Threshold = 1;
		if (Monsters[HandTarget].HP > Players[0].HP)
			Threshold = 0;
		if (TargetDelay++ >= Threshold)
		{
			// Animate target 1 frame.
			TargetDelay = 0;
			int index = HandSprite->GetFrame();
			if (++index > 9) index = 1;
			if (Spell == NO_SPELL && bBonusAttackOn)
			{
				// During attacks, allow for bonus hit chance.
				HandSprite->SetFrame(index);
			}
		}

		// Position target on monster.
/*		int ixModifier = 0, iyModifier = 0;
		if (Monsters[HandTarget].Width > 40)
		{
			// If monster is bigger, position target in center.
			ixModifier = Monsters[HandTarget].Width / 2;
			// minus half the width of the target sprite.
			ixModifier -= 20;
		}
		if (Monsters[HandTarget].Height > 40)
		{
			// If monster is bigger, position target in center.
			iyModifier = Monsters[HandTarget].Height / 2;
			// minus half the height of the target sprite.
			iyModifier -= 20;
		}*/

		HandSprite->SetPos(/*MONSTER_START_POSX + */XValue/* + ixModifier*/, /*MONSTER_START_POSY + */YValue/* + iyModifier*/);
		HandSprite->Draw(SmallSurface2, 0, 0, CDXBLT_TRANS);

		Input->Update();
		Input->UpdateLastKey(true);
		if (Input->GetLastKey() == 208)
		{
			// Down
			if (HandTarget+1 < NumMonsters)
			{
				// More monsters to scroll to.
				if (Monsters[HandTarget+1].HP > 0)
					HandTarget++; // Safe to select this monster.
				else
				{
					// Find next available monster.
					if (HandTarget+2 >= NumMonsters)
						HandTarget = 0;
					else
						HandTarget += 2;
					for (int i=HandTarget; i<NumMonsters; i++)
					{
						if (Monsters[i].HP > 0)
						{
							HandTarget = i;
							i = 1000; // exit loop
						}
					}
				}
			}
		}
		else if (Input->GetLastKey() == 200)
		{
			// Up
			if (HandTarget-1 >= 0)
			{
				// More monsters to scroll to.
				if (Monsters[HandTarget-1].HP > 0)
					HandTarget--; // Safe to select this monster.
				else
				{
					// Find next available monster.
					if (HandTarget-2 < 0)
						HandTarget = NumMonsters - 1;
					else
						HandTarget -= 2;
					for (int i=HandTarget; i>=0; i--)
					{
						if (Monsters[i].HP > 0)
						{
							HandTarget = i;
							i = -1; // exit loop
						}
					}
				}
			}
		}
		else if (Input->GetLastKey() == 205)
		{
			// Right
			if (HandTarget < NumMonsters - 2 && 
				Monsters[HandTarget + 2].HP > 0)
				HandTarget += 2;
			else
			{
				if (HandTarget > 1)
					HandTarget -= 2; // Wrap
			}
		}
		else if (Input->GetLastKey() == 203)
		{
			// Left
			if (HandTarget > 1)
				HandTarget -= 2;
			else
			{
				HandTarget += 2; // Wrap
				if (HandTarget > NumMonsters - 1)
					HandTarget = NumMonsters - 1;
			}
		}
		else if (Input->GetLastKey() == 28 || Input->GetLastKey() == 57)
		{
			// Selected
			if (Attacking)
			{
				AttackDamage = GetWeaponDamage(Players[0].Level, Players[0].iWeapon);
				AttackDamage += BonusDamage; // account for accuracy bonus
				AttackDamage -= PenaltyDamage; // account for penalties
				ArmorAbsorbedAmount = GetArmorProtection(Monsters[HandTarget].iArmor);

				strcpy(strAttackMessage, Players[0].Name);
				strcat(strAttackMessage, (char*)" hits the ");
				strcat(strAttackMessage, Monsters[HandTarget].Name);
				if (strcmp(Players[0].Name, (char*)"Ayli") == 0)
					strcat(strAttackMessage, (char*)" with her ");
				else
					strcat(strAttackMessage, (char*)" with his ");
				strcat(strAttackMessage, Players[0].Weapon);
				strcat(strAttackMessage, (char*)" for ");
				char strTemp[10];
				_itoa(AttackDamage, strTemp, 10);
				strcat(strAttackMessage, strTemp);
/*				if (BonusDamage > 0)
				{
					strcat(strAttackMessage, (char*)" + ");
					strcat(strAttackMessage, _itoa(BonusDamage, strTemp, 10));
				}*/
				strcat(strAttackMessage, (char*)" damage.");
				// Show armor absorbtion.
/*				_itoa(ArmorAbsorbedAmount, strTemp, 10);
				strcat(strAttackMessage, strTemp);
				strcat(strAttackMessage, (char*)" absorbed by ");
				strcat(strAttackMessage, Monsters[HandTarget].Armor);
				strcat(strAttackMessage, (char*)")");*/

				Monsters[HandTarget].HP -= AttackDamage;

				// Show slash animation.
				AttackDone = false;
				AttackStart = true;
			}
			else
			{
				// Casting a spell.
				AttackDone = true;
				GetSpellDamage();
				Monsters[HandTarget].HP -= AttackDamage;
			}
			
			Phase = ATTACK;
		}
	}
	else if (Phase == ATTACK)
	{
		//
		// TODO:
		// Show any attack effects occuring.
		// Show any attack messages occuring.
		//
		// 1. Attack() is called, fills strAttackMessage with text
		//    and adjusts variables for hit points, etc.
		//SmallSurface2->TextXY(20, BattleFrontRect.bottom - 75, RGB(255,255,255), (LPCTSTR)strAttackMessage);
		CDXMenu menu;
		menu.TextXY(SmallSurface2, 20, BattleFrontRect.bottom - 75, RGB(255, 255, 255), strAttackMessage);
		if (MonsterAttackCounter < NumMonsters && Monsters[MonsterAttackCounter].HP > 0 &&
			Monsters[MonsterAttackCounter].Status == OK)
		{
			// Let each monster make an attack.
			// Hitting ENTER or SPACE advances to next screen.
			// Reading your attack damage, hit enter monsters now attack.
			Input->Update();
			Input->UpdateLastKey(true);
			if (Input->GetLastKey() == 28 || Input->GetLastKey() == 57)
			{
				// Make points rising above monster head stop.
				AttackDone = true;
				//
				// 2. MonsterAttack() is called, same as #1 but for each monster.
				//
				// Monster is alive and active, so attack.
				// MonsterSpell will contain result of casting.
				GetRandomSpell(MonsterAttackCounter);
				
				if (MonsterSpell != NO_SPELL && CanCast(MonsterSpell, MonsterAttackCounter))
				{
					// He casted a spell.
					GetSpellDamage(false, MonsterAttackCounter, MonsterSpell);
					MonsterSpellStart = true;

					if (MonsterSpell == CURE)
					{
						MonsterAttackDone = true;
						Monsters[MonsterAttackCounter].HP += AttackDamage;
					}
				}
				else
				{
					AttackDamage = GetWeaponDamage(Monsters[MonsterAttackCounter].Level, Monsters[MonsterAttackCounter].iWeapon, false, MonsterAttackCounter);
					ArmorAbsorbedAmount = GetArmorProtection(Players[0].iArmor);
					AttackDamage += MonsterBonusDamage; // account for sucked bonus damage.

//					_itoa(MonsterAttackCounter, strAttackMessage, 10);
					strcpy(strAttackMessage, Monsters[MonsterAttackCounter].Name);
					strcat(strAttackMessage, (char*)" hits ");
					strcat(strAttackMessage, Players[0].Name);
					strcat(strAttackMessage, (char*)" with his ");
					strcat(strAttackMessage, Monsters[MonsterAttackCounter].Weapon);
					strcat(strAttackMessage, (char*)" for ");
					char strTemp[10];
					_itoa(AttackDamage, strTemp, 10);
					strcat(strAttackMessage, strTemp);

/*					if (iShield > 0)
					{
						_itoa((int)Reduction, strTemp, 10);
						strcat(strAttackMessage, (char*)" - ");
						strcat(strAttackMessage, strTemp);
					}*/

					strcat(strAttackMessage, (char*)" damage.");
/*					char msg[100];
					if (BonusDamage == 0)
						sprintf(msg, (char*)"%s %d damage.", strAttackMessage, AttackDamage);
					else
						sprintf(msg, (char*)"%s %d + %d damage.", strAttackMessage, AttackDamage - BonusDamage, BonusDamage);

					strcpy(strAttackMessage, msg);
*/
					// Show armor absorbtion.
/*					_itoa(ArmorAbsorbedAmount, strTemp, 10);
					strcat(strAttackMessage, strTemp);
					strcat(strAttackMessage, (char*)" absorbed by ");
					strcat(strAttackMessage, Players[0].Armor);
					strcat(strAttackMessage, (char*)")");*/

					// Show slash animation.
					MonsterAttackDone = false;
					MonsterAttackStart = true;
				}

				if (MonsterSpell != CURE)
					Players[0].HP -= AttackDamage;
				
				// Next monster's turn to attack.
				MonsterAttackCounter++;
			}
		}
		else
			MonsterAttackCounter++;

		// Check if this battle round is over.
		if (Players[0].HP < 1 || !isMonstersAlive())
		{
			// Wait for final key input, then move on to next round.
			Input->Update();
			Input->UpdateLastKey(true);
			if (Input->GetLastKey() == 28 || Input->GetLastKey() == 57)
			{
				// Player attacked, monster attacked, next round.
				Phase = RESULTS;
				
				// Reset so each monster can attack again.
				MonsterAttackCounter = 0;
			}
		}
		else if (MonsterAttackCounter >= NumMonsters)
		{
			// Wait for final key input, then move on to next round.
			Input->Update();
			Input->UpdateLastKey(true);
			if (Input->GetLastKey() == 28 || Input->GetLastKey() == 57)
			{
				// Next battle round.
				Phase = COMMAND;
				MonsterAttackCounter = 0;
			}
		}
	}
	else if (Phase == RESULTS)
	{
		// Battle is over.
		if (Players[0].HP < 1)
		{
			strcpy(strAttackMessage, (char*)"Sorry, you were killed.");
		}
		else if (!bRun)
		{
			//
			// GetResults(); // get treasure, exp
			//
			// Count up experience points.
			if (!ExpCounted)
			for (int i=0; i<NumMonsters; i++)
			{
				Exp += Monsters[i].Exp;
				Gold += Monsters[i].Gold;
			}

			ExpCounted = true;

			char buf[10];
			strcpy(strAttackMessage, (char*)"You've won! You get ");
			_itoa(Exp, buf, 10);
			strcat(strAttackMessage, buf);
			strcat(strAttackMessage, (char*)" experience, ");
			_itoa(Gold, buf, 10);
			strcat(strAttackMessage, buf);
			strcat(strAttackMessage, (char*)" gold pieces.");
		}
		else if (bRun)
		{
			// User RAN away.
			ExpCounted = true;
			strcpy(strAttackMessage, (char*)"Whew, that was a close one.");
		}

		//SmallSurface2->TextXY(20, BattleFrontRect.bottom - 75, RGB(255,255,255), (LPCTSTR)strAttackMessage);
		CDXMenu menu;
		menu.TextXY(SmallSurface2, 20, BattleFrontRect.bottom - 75, RGB(255, 255, 255), strAttackMessage);

		Input->Update();
		Input->UpdateLastKey(true);
		if (Input->GetLastKey() == 28 || Input->GetLastKey() == 57)
		{
			// Battle has completed.
			Phase = DONE;
			Spell = NO_SPELL;
			MonsterSpell = NO_SPELL;
			SpellStart = true;
		}
	}

	if (Phase == ATTACK && Spell != NO_SPELL)
	{
		// Show spell effects.
		DrawSpells(SmallSurface2);
	}
	else if (Phase == ATTACK && !AttackDone)
	{
		// Show attack effects.
		DrawAttacks(SmallSurface2);
	}

	if (Phase == ATTACK && !MonsterAttackDone)
	{
		// Show attack effects.
		// Note, the MonsterAttackCounter was already incremented, so use -1.
		DrawMonsterAttacks(SmallSurface2/*, Monsters[MonsterAttackCounter - 1].bDoubleAttack*/);
	}
	else if (Phase == ATTACK && MonsterSpell != NO_SPELL)
	{
		// Show spell effects.
		// Note, the MonsterAttackCounter was already incremented, so use -1.
		if (MonsterAttackCounter - 1 >= NumMonsters)
			MonsterAttackCounter = NumMonsters;

		if (MonsterAttackCounter - 1 < NumMonsters)
		{
			DrawMonsterSpells(SmallSurface2, MonsterAttackCounter - 1);
		}
	}
	// END TODO.

	SmallSurface2->DrawTrans(SmallSurface, LEFT_MARGIN, TOP_MARGIN, &BattleFrontRect);
	// Next, draw this temp surface onto the actual screen.
	SmallSurface->DrawBlk(Screen->GetBack(), START_X, START_Y, &BattleBackRect);

	// Finally, draw frame graphic on top of the final images.
	FrameSprite->SetPos(START_X-10, START_Y-10);
	FrameSprite->Draw(Screen->GetBack(), 0, 0, CDXBLT_TRANS);
}