// BattleEngine.h: interface for the CBattleEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BATTLEENGINE_H__6962AAEC_BC65_4F4D_8954_A7FB7A541C62__INCLUDED_)
#define AFX_BATTLEENGINE_H__6962AAEC_BC65_4F4D_8954_A7FB7A541C62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>
#include "Menu.h"

#define LEFT 1
#define RIGHT 15 + 1
#define UP 26 + 1
#define DOWN 27 + 1

// Space between background and start of Battle background.
#define LEFT_MARGIN 15
#define TOP_MARGIN 15

#define START_X 70
#define START_Y 100

#define MAX_MONSTERS 8
#define MAX_PLAYERS 1
#define MAX_SPELL_FRAMES 9 // 9 frames per spell for animation

// Starting coords of monster text, upper left.
#define MONSTER_START_POSX 30
#define MONSTER_START_POSY 35

#define COMMAND 0
#define CHOOSE_SPELL 1
#define PICK_TARGET 2
#define ATTACK 3
#define RESULTS 4
#define DONE 5

// The Statuses
#define OK 0
#define BLIND 2     // damage cut by 1/4
#define PARALYZED 1 // can not attack for 1-3 rounds

// The Spells
#define NO_SPELL -1
#define MAGIC_MISSILE 0
#define CURE 1
#define BIO_FLARE 2
#define LIGHT_SHOCK 3
#define FIRE 4
#define LIGHTNING 5
#define FLUXAL_MELT 6
#define CRYSTAL_CLEAR 7
#define MIND_NUMB 8
#define DARKNESS 9
#define SUCKED 10
#define MENTAL_SHIELD 11
#define PSY_SHIELD 12
#define MAGIC_EXPLOSION 13
#define BIO_FIELD 14
#define HOLY_LIGHT 15
#define DESECRATE 16

// The Weapons
#define NO_WEAPON 0		// DAMAGE PER LEVEL
#define CLAWS 1			// 1-2
#define BITE 2			// 1-3
#define CLUB 3			// 1-3 + 1
#define DAGGER 4		// 1-6 + 1
#define SHORTSWORD 5    // 1-4 per level
#define LONGSWORD 6		// 1-8 per level

// The Armor
#define NO_ARMOR 0		// PERCENTAGE
#define ARMOR_9	 1		// 9%
#define ARMOR_10 2	// 10%
#define ARMOR_20 3	// 20%
#define ARMOR_45 4		// 45%

// The Areas
#define FOREST 1
#define CAVE 2
#define DUNGEON 3
#define LAVA 4
#define LAVARUINS 5
#define BURNSWOOD 6
#define CRYSTALWATERS 7
#define INSECTARIUM 8
#define MOUNTWILLOW 9
#define SWAMP 10
#define SWAMPCAVE 11
#define TREE 12
#define TREETRUNK 13
#define TREETRUNKFINAL 14
#define FORESTCAMP 15
#define DEMONPIT 16
#define BLOODCHAMBER 17
#define DEMONTOWN 18
#define NETHERWORLD 19
#define DEEPNETHERWORLD 20

struct MonsterSpriteStruct
{
	char Armor[100];
	int iArmor;
	char Weapon[100];
	int iWeapon;
	int Level, MaxHP, MaxMP, HP, MP, AC;
	int Exp, Gold;
	int Width, Height;
	int SpellCaster; // likeliness to cast a spell. high_numbers = cast
	                 // 10 = 50% cast, 20 = 70% cast rate, etc.
	                 // 0 = 0% cast
	CDXTile *Tile;
	CDXSprite *Sprite;
	char Name[500];
	int Status;
	bool bDoubleAttack;
	float zoom;
};

class CBattleEngine  
{
public:
	// Max 4 monsters.
	MonsterSpriteStruct Monsters[MAX_MONSTERS];
	int NumMonsters;
	int iTemp; // temporary storage value.

	CBattleEngine();
	virtual ~CBattleEngine();

	void Initialize(CDXScreen *screen, CDXInput *input, CDXSound *sound, char *BackBmp, char *FrontBmp, int Level = 1, bool bBeorne = false);
	void Draw(int Direction = LEFT);

	// Called every movement to check if a battle starts.
	bool EngageCombat();

	// Called before a battle to setup the monster display.
	void AddMonster(char *strMonster, char *bmpFilename = NULL, int level = 0, int hp = 0, int mp = 0, int ac = 0, char *Weapon = (char*)"None", int iWeapon = 0, char *Armor = (char*)"None", int iArmor = 0, int CastRate = 0, int Exp = 0, int Gold = 0, int Width = 40, int Height = 40);
	void AddPlayer(char *strPlayer, char *bmpFilename = NULL, int level = 0, int maxhp = 10, int hp = 10, int maxmp = 0, int mp = 0, int ac = 0, char *Weapon = (char*)"None", int iWeapon = 0, char *Armor = (char*)"None", int iArmor = 0, int Width = 40, int Height = 40);
	void PickRandomMonsters(int Area);

	// Updates meter variables for player and monster hit points.
	int GetPhase() { return Phase; };
	int GetHP() { return Players[0].HP; };
	int GetMP() { return Players[0].MP; };
	int GetLevel() { return Players[0].Level; };
	bool isRun() { return bRun; };

	int Exp, Gold; // final holders for gains after battle.
	bool bCrystalClearOn; // true if player can permanently see crystal clear.
	bool bBonusAttackOn; // true if player can do bonus attack damage.
	bool bBoss; // true if a boss battle.
	bool bBeorne; // true if Beorne is main character

protected:
	void DrawSpells(CDXSurface *Surface);
	void DrawMonsterSpells(CDXSurface *Surface, int i);

	void DrawAttacks(CDXSurface *Surface);
	void DrawMonsterAttacks(CDXSurface *Surface);

	bool isMonstersAlive();
	int GetSpellDamage(bool bPlayer = true, int i=0, int MonsterSpell = NO_SPELL);
	int GetRandomSpell(int i);
	bool CanCast(int aSpell, int i);

	int GetWeaponDamage(int Level, int Weapon, bool bPlayer = true, int i=0);
	int GetArmorProtection(int Armor);

	void Init();

protected:
	CDXScreen *Screen;
	CDXInput *Input;
	CDXSound *Sound;

	// Temp surface for mini-battle screen.
	CDXSurface *SmallSurface;
	
	// Temp surface for sub-section of mini-battle screen.
	CDXSurface  *SmallSurface2;

	// Temp surface used for alpha fading of background before drawing to SmallSurface.
	CDXSurface *SmallSurfaceFade;

	// Copy of original background screen, Battle is shown on top of this.
	CDXSurface *Background;

	// Background layer of battle screen which can move.
	CDXLayer *BattleLayerBack;

	// Front surface where characters and action takes place.
	// This is drawn on top of the BattleLayerBack moving image
	// which in total is on top of the Background surface.
	CDXSurface *BattleFront;

	// The frame image should be all black inside so battle scene
	// shows through. It can have spikes etc hanging down for effects.
	CDXTile *FrameTile;
	CDXSprite *FrameSprite;

	CDXTile *HandTile;
	CDXSprite *HandSprite;
	CDXTile *SpellTile, *MonsterSpellTile;
	CDXSprite *SpellSprite, *MonsterSpellSprite;

	CDXSoundBuffer *MagicMissileSound, *SlashSound, *Fire1Sound, *Fire2Sound;
	CDXSoundBuffer *LightningSound, *FluxalMeltSound, *BioFlareSound, *LightShockSound;
	CDXSoundBuffer *CrystalClearSound, *CureSound, *MindNumbSound, *DarknessSound;
	CDXSoundBuffer *SuckedSound, *DesecrateSound;

	int BackAlpha;

	int HandTarget;
	int BonusDamage, PenaltyDamage, MonsterBonusDamage;

	MonsterSpriteStruct Players[MAX_PLAYERS];
	int NumPlayers;

	CMenu BattleMenu;
	CMenu SpellMenu;

	int Phase; // phase of combat
	bool Attacking; // attack or spell?
	bool SpellStart, MonsterSpellStart; // to initialize a spell.

	bool AttackStart, AttackDone, MonsterAttackDone; // to initialize an attack.
	bool MonsterAttackStart;

	char strAttackMessage[5000]; // message to display during current combat round.
	int MonsterAttackCounter; // counter so each monster can attack.
	int PlayerAttackCounter;

	int Spell; // spell selected to cast.
	int MonsterSpell;
	int AttackDamage; // damage done by attack or spell.

	bool ExpCounted; // so exp & gold is only counted up once.
	bool bRun; // true if user ran away.

	bool ViewEnemyHP; // true if user casted Crystal Clear spell.
	bool EnemySilenced; // true means all enemies can not cast magic.

	int PlayerPositionOffset; // normally 0, this value moves player left on the battle screen.
	int iSucked; // normally 0, if 1,2,3 the player is sucked towards the left to the value of PlayerPositionOffset * iSucked.
	int iShield, iSpellShield; // Percent damage deducted from an attack.
	float Reduction; // Amount of damage reduced by shielding.
};

#endif // !defined(AFX_BATTLEENGINE_H__6962AAEC_BC65_4F4D_8954_A7FB7A541C62__INCLUDED_)
