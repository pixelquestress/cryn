// Class Character object for each PC and NPC.

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include "cdx.h"
#include "InfoBox.h"

#define MAX_TEXT_LENGTH 50000

// The number of frames to show while walking to a tile.
//#define TILE_WIDTH 48
//#define TILE_HEIGHT 48

//#define STEPS_TO_MOVE TILE_WIDTH

//#define STEPS_TO_MOVE_HORIZ TILE_WIDTH
//#define STEPS_TO_MOVE_VERT TILE_HEIGHT
#define MAP_BUFFER 3 // tiles before end of map

#define MAX_DIRECTIONS 6 // left, right
#define MAX_WIDTH 640
#define MAX_HEIGHT 480

#define MOVE_NONE 0
#define MOVE_LEFT 1
#define MOVE_RIGHT 4
#define MOVE_UP 7
#define MOVE_DOWN 8

// +1 is for blank space at front of each direction sequence.
#define LEFT 1
#define LEFTUP 5 + 1
#define LEFTDOWN 10 + 1
#define RIGHT 15 + 1
#define RIGHTUP 20 + 1
#define RIGHTDOWN 25 + 1
#define UP 26 + 1
#define DOWN 27 + 1

/* To use for HUMAN players:

   CCharacter MyPlayer;
   
   // 1 frame, 40x40 pixels.
   MyPlayer.Initialize("player.bmp", 1, 40, 40);
   MyPlayer.SetPosTile(5, 5); // start at tile (5,5).
   MyPlayer.SetPush(LEFT_PUSH, RIGHT_PUSH, TOP_PUSH, BOTTOM_PUSH);
   MyPlayer.SetMap(&MyMap);

   while (!quit)
   {
      MyPlayer.Move(Direction);
      MyPlayer.Draw();
   }

  
   To use for NPC players:
   
   CCharacter NPC;

   NPC2.Initialize("tree.bmp", 1, 40, 40);
   NPC2.SetArea(1, 1, MAX_WIDTH, MAX_HEIGHT); // can roam through the area defined.
   NPC2.SetMap(&MyMap);
   NPC2.SetPosTile(3, 4);
   NPC2.SetTimeToMove(6); // moves 1/7 times.
   // Set "Item & Other_Character" map to check for collisions with others.
   NPC2.SetCharacterMap(&CharacterMapStruct);
   
   while (!quit)
   {
      NPC.Move();
      NPC.Draw();
   }

*/

struct MyCharacterMapStruct {
   int CharacterMap[MAX_WIDTH][MAX_HEIGHT];
};

class CCharacter
{
public:
	CDXSprite *Sprite;
	CDXTile *Tile, *LoadedTile;
	CDXScreen *Screen;
	CDXMap *Map, *Map2;
	CDXInput *Input;
	CDXSound *Sound;

	bool bLoaded; // true if NPC was previously loaded.

	int Facing; // direction NPC is facing.

	int StepsLeftVert, StepsLeftHoriz;
	int DirectionHoriz, DirectionVert;
	int TileLeftBorder, TileRightBorder, TileUpBorder, TileDownBorder;

	bool isAnimated; // flag to determine if graphic should animate frames.
	int MoveStep;

	int Delay, FacingOld, FrameIndex, FacingFlag;

	int TILE_WIDTH, TILE_HEIGHT, STEPS_TO_MOVE;

	int NumFramesPerDirection; // 3 frames per direction to draw

//#define TILE_WIDTH 48
//#define TILE_HEIGHT 48

//#define STEPS_TO_MOVE TILE_WIDTH

//#define STEPS_TO_MOVE_HORIZ TILE_WIDTH
//#define STEPS_TO_MOVE_VERT TILE_HEIGHT

protected:
//  int x, y; // position of character in pixels.
  int TileX, TileY; // position of character in tiles.
  int oldTileX, oldTileY;

  // Area frame where character is free to roam.
  // Used only for NPCs, set in tiles.
  int Tilex1, Tiley1, Tilex2, Tiley2;

  int PlayerWidth;
  int PlayerHeight;

  bool bSingleFrame; // if only one frame for NPC.
  int iAlphaValue; // transparency alpha value for NPC to be drawn with.

public:
  int Direction; // direction the player is moving.

protected:
  int TimeToMove; // Random number to hit (1-TimeToMove) for player to move.

  // Boundary limits where player is free to move within in tiles.
  int LeftPush, RightPush, TopPush, BottomPush;

  int Speed;

  // Character place holder map to check for collisions with items and other characters.
  MyCharacterMapStruct *CharacterMap;

  bool Initialized;

  CInfoBox MyMessage;
  char strText1[MAX_TEXT_LENGTH], strText2[MAX_TEXT_LENGTH], strText3[MAX_TEXT_LENGTH], strText4[MAX_TEXT_LENGTH], strText5[MAX_TEXT_LENGTH], strText6[MAX_TEXT_LENGTH], strText7[MAX_TEXT_LENGTH], strText8[MAX_TEXT_LENGTH], strText9[MAX_TEXT_LENGTH];

  // flag stored to tell if character just finished moving a block.
  bool isFinishedMove;

public:
  // The current frame position to draw of NPC moving towards tile.
  int MoveDirection;
  
public:
  CCharacter();
  CCharacter(int a, int b);
  ~CCharacter();

  // Load the bitmap for the character.
  bool Load(CDXScreen *screen, CDXInput *input, CDXSound *sound, CDXMap *map, CDXMap *map2, int Direction, char *filename, int Width, int Height);
  void Unload() { SAFEDELETE(Sprite); SAFEDELETE(Tile); };
  void Init(); // re-initialize all variables.

  // Moves the character in the direction passed in.
  // TRUE - the player moved successfully.
  // FALSE - the player could not walk that direction.
//  int Move(int Dir);

  // Moves the character in a random direction selected
  // by the characters' own personality attributes.
  // TRUE - the player moved successfully.
  // FALSE - the player could not move anywhere.
//  bool Move();

  // Draws the character if it should be visible on the screen.
  bool Draw2(); // leaves out tile movement stuff.

  // Displays message boxes for each line of text in Message.
  void Speak(int x = 10, int y = 335);
  void SetText(char *msg, int iText = 1);
  void SetSingleFrame() { bSingleFrame = true; };
  void SetAlphaValue(int aAlphaValue) { if (aAlphaValue < 256 && aAlphaValue > -1) iAlphaValue = aAlphaValue; else if (aAlphaValue == 999) iAlphaValue = aAlphaValue; };

//  void SetPosPixel(int a, int b) { /*x = a; b = y;*/ TileX = TileMap->GetTilex(x); TileY = TileMap->GetTiley(y); };

  void SetPosTile(int a, int b);

  // Used only for Human Player, to about 40, 640-40, 40, 480-40.
  // Otherwise it is set for whole screen.
  void SetPush(int a, int b, int c, int d) { LeftPush = a; RightPush = b; TopPush = c; BottomPush = d; };

  void SetMap(CDXMap *map) { Map = map; };
  void SetCharacterMap(MyCharacterMapStruct *map) { CharacterMap = map; };

  void SetTimeToMove(int a) { TimeToMove = a; };

  // Used only for NPCs. Sets area in tiles.
  void SetArea(int a, int b, int c, int d) 
  { 
	  Tilex1 = a/*+1*/; Tiley1 = b/*+2*/; Tilex2 = c/*+1*/; Tiley2 = d/*+2*/; 
	  TileLeftBorder = Tilex1;
	  TileUpBorder = Tiley1;
	  TileRightBorder = Tilex2;
	  TileDownBorder = Tiley2;
  };

  void ResetArea()
  {
	  TileLeftBorder = 0;
	  TileRightBorder = -1;	
	  TileUpBorder = 0;
	  TileDownBorder = -1;
	  Tilex1 = 0;
	  Tiley1 = 0;
	  Tilex2 = MAX_WIDTH;
	  Tiley2 = MAX_HEIGHT;
  };

  int GetTileX() { return TileX; };
  int GetTileY() { return TileY; };

  bool Move(int Dir, int Speed);

  void ResetBorders() { TileLeftBorder = -1; TileRightBorder = -1; TileUpBorder = -1; TileDownBorder = -1; };

  int OppositeDirection(int Dir);

  // true if character has just finished moving a block.
  bool isFinishedMoving() { return isFinishedMove; };
};

#endif
