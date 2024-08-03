// Class file for CCharacter class.

#include "Character.h"
#include "Message.h"
#include <fstream>

CCharacter::CCharacter()
{
//  x = 0;
//  y = 0;
	TILE_WIDTH = 40;
	TILE_HEIGHT = 40;
	STEPS_TO_MOVE = 40;
  Sprite = NULL;
  Tile = NULL;
  LoadedTile = NULL; // a pre-loaded tile
  TileX = 0;
  TileY = 0;
  Direction = MOVE_LEFT;
  Map = NULL;
  LeftPush = 0;
  RightPush = MAX_WIDTH;
  TopPush = 0;
  BottomPush = MAX_HEIGHT;
  Speed = 40;
  PlayerWidth = 0;
  PlayerHeight = 0;
  TimeToMove = 5;
  Initialized = false;
  Tilex1 = 0;
  Tiley1 = 0;
  Tilex2 = MAX_WIDTH;
  Tiley2 = MAX_HEIGHT;
  CharacterMap = NULL;
  Facing = MOVE_LEFT;
  isAnimated = false;
  MoveStep = 0;
  Delay = 0;
  FacingOld = 0;
  FrameIndex = 0;
  FacingFlag = 0;
  isFinishedMove = false;
  bSingleFrame = false;
  iAlphaValue = 0;
  NumFramesPerDirection = 3;

  StepsLeftVert = 0;//STEPS_TO_MOVE_VERT;
  StepsLeftHoriz = 0;//STEPS_TO_MOVE_HORIZ;
  TileLeftBorder = 0;//1;
  TileRightBorder = -1;
  TileUpBorder = 0;//1;
  TileDownBorder = -1;

  bLoaded = false;
}

CCharacter::CCharacter(int a, int b)
{
   SetPosTile(a, b);

   Sprite = NULL;
   Tile = NULL;
   Direction = MOVE_LEFT;
   Map = NULL;
   LeftPush = 0;
   RightPush = MAX_WIDTH;
   TopPush = 0;
   BottomPush = MAX_HEIGHT;
   Speed = 40;
   PlayerWidth = 0;
   PlayerHeight = 0;
   TimeToMove = 5;
   Initialized = false;
   Tilex1 = 0;
   Tiley1 = 0;
   Tilex2 = MAX_WIDTH;
   Tiley2 = MAX_HEIGHT;
   CharacterMap = NULL;
   Facing = MOVE_LEFT;
   isAnimated = false;
   isFinishedMove = false;

   bLoaded = false;
}

CCharacter::~CCharacter()
{
	SAFEDELETE(Sprite);
	SAFEDELETE(Tile);
	SAFEDELETE(LoadedTile);
/*	if (Sprite != NULL)
	{
		delete(Sprite);
		Sprite = NULL;
	}*/

/*	if (Tile != NULL)
	{
		delete(Tile);
		Tile = NULL;
	}*/
}

void CCharacter::Init()
{
  TileX = 0;
  TileY = 0;
  Direction = MOVE_LEFT;
  Map = NULL;
  LeftPush = 0;
  RightPush = MAX_WIDTH;
  TopPush = 0;
  BottomPush = MAX_HEIGHT;
  Speed = 40;
  PlayerWidth = 0;
  PlayerHeight = 0;
  TimeToMove = 5;
  Initialized = false;
  Tilex1 = 0;
  Tiley1 = 0;
  Tilex2 = MAX_WIDTH;
  Tiley2 = MAX_HEIGHT;
  CharacterMap = NULL;
  Facing = MOVE_LEFT;
  isAnimated = false;
  MoveStep = 0;
  Delay = 0;
  FacingOld = 0;
  FrameIndex = 0;
  FacingFlag = 0;
  isFinishedMove = false;
  bSingleFrame = false;
  iAlphaValue = 0;

  StepsLeftVert = 0;//STEPS_TO_MOVE_VERT;
  StepsLeftHoriz = 0;//STEPS_TO_MOVE_HORIZ;
  TileLeftBorder = 0;//1;
  TileRightBorder = -1;
  TileUpBorder = 0;//1;
  TileDownBorder = -1;

  bLoaded = false;
}

void CCharacter::SetText(char *msg, int iText)
{
	switch (iText)
	{
		case 1 : 
			{ 
				// Setting first line of text,let's clear it out first.
				strcpy(strText2, (char*)"");
				strcpy(strText3, (char*)"");
				strcpy(strText4, (char*)"");
				strcpy(strText5, (char*)"");
				strcpy(strText6, (char*)"");
				strcpy(strText7, (char*)"");
				strcpy(strText8, (char*)"");
				strcpy(strText9, (char*)"");
				if (strlen(msg) <= MAX_TEXT_LENGTH) strcpy(strText1, msg); 
				break; 
			}
		case 2 : { if (strlen(msg) <= MAX_TEXT_LENGTH) strcpy(strText2, msg); break; }
		case 3 : { if (strlen(msg) <= MAX_TEXT_LENGTH) strcpy(strText3, msg); break; }
		case 4 : { if (strlen(msg) <= MAX_TEXT_LENGTH) strcpy(strText4, msg); break; }
		case 5 : { if (strlen(msg) <= MAX_TEXT_LENGTH) strcpy(strText5, msg); break; }
		case 6 : { if (strlen(msg) <= MAX_TEXT_LENGTH) strcpy(strText6, msg); break; }
		case 7 : { if (strlen(msg) <= MAX_TEXT_LENGTH) strcpy(strText7, msg); break; }
		case 8 : { if (strlen(msg) <= MAX_TEXT_LENGTH) strcpy(strText8, msg); break; }
		case 9 : { if (strlen(msg) <= MAX_TEXT_LENGTH) strcpy(strText9, msg); break; }
	};
}

bool CCharacter::Load(CDXScreen *screen, CDXInput *input, CDXSound *sound, CDXMap *map, CDXMap *map2, int Direction, char *filename, int Width, int Height)
{
	Screen = screen;
	Map = map;
    Map2 = map2;
	Input = input;
	Sound = sound;
	bLoaded = true;

	//SAFEDELETE(Tile);

	if (LoadedTile == NULL)
	{
		Tile = new CDXTile();
		if (Tile->Create(Screen, filename, Width, Height, 0) == FALSE)
		{
			char msg[1000];
			strcpy(msg, (char*)"could not load tiles from file character bitmap ");
			strcat(msg, filename);
			CDXError( Screen , msg );
		}
	}
	else
	{
		Tile = LoadedTile;
	}

	// set the top left pixel in tiles bitmap as transparent color
	Tile->SetColorKey(0);

	SAFEDELETE(Sprite);
	Sprite = new CDXSprite();
	Sprite->Create(Tile);

	Sprite->SetPos(TileX, TileY);
	Facing = Direction;
	FacingOld = -1;

	Sprite->SetShadowOffset(10,-10);
	Sprite->SetShadowValue(210);
	
	if (iAlphaValue > 0)
		Sprite->SetAlphaValue(iAlphaValue);

	MyMessage.Initialize(Screen, Input, Sound, 2);

	return true;
}

bool CCharacter::Move(int Dir, int Speed)
{
	// Moves the character in the direction, Speed # of pixels.
	// If we are between tiles, then change actual x value.
	// If we exceed between tiles, then change tile x value.
	// Returns true if it was able to move in the direction.
	// You can set the boundaries of movement by changing
	// The TileRightBorder .. variables to tile numbers.
//	static int FacingFlag = 0;
	int OrigTilex = TileX, OrigTiley = TileY;
	int OrigStepsLeftHoriz = StepsLeftHoriz, OrigStepsLeftVert = StepsLeftVert;
	int OrigDirectionHoriz = DirectionHoriz;
	int OrigDirectionVert = DirectionVert;
	int OrigFacingFlag = FacingFlag;

	if (TileRightBorder == -1 || TileRightBorder > Map->GetMapWidth())
		TileRightBorder = Map->GetMapWidth() - 1;
	if (TileDownBorder == -1 || TileDownBorder > Map->GetMapHeight())
		TileDownBorder = Map->GetMapHeight() - 1;
	if (TileLeftBorder < 0)
		TileLeftBorder = 0;
	if (TileUpBorder < 0)
		TileUpBorder = 0;

	MoveStep = STEPS_TO_MOVE;
    isFinishedMove = false; // we're just starting to move.

	switch (Dir)
	{
		case LEFT : 
		{
			DirectionHoriz = LEFT;
			FacingFlag |= ~RIGHT;
			FacingFlag |= LEFT;
		/*	StepsLeftHoriz -= Speed;
			if (StepsLeftHoriz <= 0)
			{*/
				if (TileX > TileLeftBorder &&
					Map->IsWalkable(TileX-1, TileY) &&
					Map2->IsWalkable(TileX-1, TileY) &&
					CharacterMap->CharacterMap[TileX-1][TileY] == 0)
				{
					// We have reached next left tile.
					//StepsLeftHoriz = STEPS_TO_MOVE_HORIZ;
					TileX--;
				}
				else
				{
					MoveStep = 0;
					//StepsLeftHoriz = 0;
					// Reached end of tiles, can not move further.
					return false;
				}
			//}
			break;
		}
		case RIGHT : 
		{
			DirectionHoriz = RIGHT;
			FacingFlag |= ~LEFT;
			FacingFlag |= RIGHT;
			/*StepsLeftHoriz -= Speed;
			if (StepsLeftHoriz <= 0)
			{*/
				if (TileX < TileRightBorder && 
					Map->IsWalkable(TileX+1, TileY) &&
					Map2->IsWalkable(TileX+1, TileY) &&
					CharacterMap->CharacterMap[TileX+1][TileY] == 0)
				{
					// We have reached next right tile.
					//StepsLeftHoriz = STEPS_TO_MOVE_HORIZ;
					TileX++;
				}
				else
				{
					MoveStep = 0;
					//StepsLeftHoriz = 0;
					// Reached end of tiles, can not move further.
					return false;
				}
			//}
			break;
		}
		case UP : 
		{
			DirectionVert = UP;
			FacingFlag |= ~DOWN;
			FacingFlag |= UP;
			/*StepsLeftVert -= Speed;
			if (StepsLeftVert <= 0)
			{*/
				if (TileY > TileUpBorder &&
					Map->IsWalkable(TileX, TileY-1) &&
					Map2->IsWalkable(TileX, TileY-1) &&
					CharacterMap->CharacterMap[TileX][TileY-1] == 0)
				{
					// We have reached next up tile.
			//		StepsLeftVert = STEPS_TO_MOVE_VERT;
					TileY--;
				}
				else
				{
					MoveStep = 0;
			//		StepsLeftVert = 0;
					// Reached end of tiles, can not move further.
					return false;
				}
			//}
			break;
		}
		case DOWN : 
		{
			DirectionVert = DOWN;
			FacingFlag |= ~UP;
			FacingFlag |= DOWN;
			/*StepsLeftVert -= Speed;
			if (StepsLeftVert <= 0)
			{*/
				if (TileY < TileDownBorder &&
					Map->IsWalkable(TileX, TileY+1) &&
					Map2->IsWalkable(TileX, TileY+1) &&
					CharacterMap->CharacterMap[TileX][TileY+1] == 0)
				{
					// We have reached next down tile.
			//		StepsLeftVert = STEPS_TO_MOVE_VERT;
					TileY++;
				}
				else
				{
					MoveStep = 0;
			//		StepsLeftVert = 0;
					// Reached end of tiles, can not move further.
					return false;
				}
			//}
			break;
		}
	} // end switch


	// Check for walkability.
/*	if (!Map->IsWalkable(TileX, TileY) ||
		CharacterMap->CharacterMap[TileX][TileY] != 0)
	{
		// Move back movement.
/*		TileX = OrigTilex;//TileMap->GetTilex(x);
		TileY = OrigTiley;//TileMap->GetTiley(y);
		StepsLeftHoriz = OrigStepsLeftHoriz;
		StepsLeftVert = OrigStepsLeftVert;
		DirectionHoriz = OrigDirectionHoriz;
		DirectionVert = OrigDirectionVert;
		FacingFlag = OrigFacingFlag;*/
//		MoveStep = 0;
//		Direction = MOVE_NONE;
/*		return false;
	}
	else 
	{*/
		// Move OK. Store previous location.
		oldTileX = OrigTilex;
		oldTileY = OrigTiley; 
		
		// Notify character map of movement.
		CharacterMap->CharacterMap[oldTileX][oldTileY] = 0;		
		CharacterMap->CharacterMap[TileX][TileY] = 1;
//	}


	// Calculate proper facing value.
	if (FacingFlag & RIGHT && FacingFlag & UP)
		Facing = RIGHTUP;
	else if (FacingFlag & RIGHT && FacingFlag & DOWN)
		Facing = RIGHTDOWN;
	else if (FacingFlag & LEFT && FacingFlag & UP)
		Facing = LEFTUP;
	else if (FacingFlag & LEFT && FacingFlag & DOWN)
		Facing = LEFTDOWN;
	else if (FacingFlag & RIGHT)
		Facing = RIGHT;
	else if (FacingFlag & LEFT)
		Facing = LEFT;

	return true;
}

bool CCharacter::Draw2()
{
	// Draws the character if it should be visibile on the screen.
	// Leaves out the movement of tiles and junk.
	int xOffset = ((int)(Map->GetPosX() / Map->GetTileWidth())) * Map->GetTileWidth();
	int yOffset = ((int)(Map->GetPosY() / Map->GetTileHeight())) * Map->GetTileHeight();
	int x = (TileX - (Map->GetPosX()/Map->GetTileWidth()))*Map->GetTileWidth() - (Map->GetPosX() - xOffset);
	int y = (TileY - (Map->GetPosY()/Map->GetTileHeight()))*Map->GetTileHeight() - (Map->GetPosY() - yOffset);

	// Account for offset in pixels from tile before showing it.
	bool moveleft = false, moveup = false;

	// Move NPC whether on screen or off screen.
	if (MoveStep > 0)
	{	 
		// Offset character from tile with distance he is walking towards it.
		switch (Direction)
		{
		case LEFT : x += MoveStep; moveleft = true; break;
		case UP : y += MoveStep; moveup = true; break;
		case RIGHT : x -= MoveStep; moveleft = false; break;
		case DOWN : y -= MoveStep; moveup = false; break;
		}

		MoveStep -= 1;

		if (MoveStep <= 0)
			isFinishedMove = true; // completed walking to position.
	}

	// Determine Facing value.
	if (Direction == LEFT)
		Facing = LEFT;
		//Facing = LEFTUP;
	else if (Direction == RIGHT)
		Facing = RIGHT;
		//Facing = RIGHTUP;
	else if (Direction == UP)
	{
		if (FacingOld == LEFTUP || FacingOld == LEFTDOWN || FacingOld == LEFT)
			Facing = LEFTUP;
		else
			Facing = RIGHTUP;
	}
	else if (Direction == DOWN)
	{
		if (FacingOld == RIGHTUP || FacingOld == RIGHTDOWN || FacingOld == RIGHT)
			Facing = RIGHTDOWN;
		else
			Facing = LEFTDOWN;
	}
	else
	{
		//Facing = RIGHTDOWN;
		Facing = RIGHT;
	}

	if (TileX >= (Map->GetPosX()/Map->GetTileWidth()) && TileX <= /*Map->GetScreenWidth()*/Map->m_SCREEN_TW+(Map->GetPosX()/Map->GetTileWidth()) &&
		TileY >= (Map->GetPosY()/Map->GetTileHeight()) && TileY <= /*Map->GetScreenHeight()*/Map->m_SCREEN_TH+(Map->GetPosY()/Map->GetTileHeight()))
	{
		// Character is on screen so draw it.
		if (Facing != FacingOld)
		{
			// Changed direction, so reset to new frame sequence.
			if (!bSingleFrame)
				Sprite->SetFrame(Facing);

			Delay = 0;
			FrameIndex = 0;
		}
		else
		{
			// Same direction, move on to next frame.
			if (isAnimated && ++Delay > 30)
			{
				// 4 frames per direction to animate.
				if (FrameIndex < NumFramesPerDirection)
					FrameIndex++;
				else
					FrameIndex = 0;

				if (!bSingleFrame)
					Sprite->SetFrame(Facing + FrameIndex);

				Delay = 0;
			}
		}

		Sprite->SetPos(x, y);
		if (iAlphaValue < 1)
			Sprite->Draw(Screen->GetBack() , 0 , 0 , CDXBLT_TRANS);
		else if (iAlphaValue == 999)
		{
			// Special case for CMistSpot
			Sprite->SetFrame(1);
			Sprite->Draw(Screen->GetBack() , 0 , 0 , CDXBLT_TRANSALPHA);
		}
		else
			Sprite->Draw(Screen->GetBack() , 0 , 0 , CDXBLT_TRANSALPHAFAST);
	
		FacingOld = Facing;

		return true;
	}
	
	return false;
}

void CCharacter::Speak(int x, int y)
{
	y = 335;

	// Displays spoken text from character.
	if (strlen(strText1) > 0)
		MyMessage.Display2(x, y, strText1);
	if (strlen(strText2) > 0)
		MyMessage.Display2(x, y, strText2, false); // false = no sound
	if (strlen(strText3) > 0)
		MyMessage.Display2(x, y, strText3, false);
	if (strlen(strText4) > 0)
		MyMessage.Display2(x, y, strText4, false);
	if (strlen(strText5) > 0)
		MyMessage.Display2(x, y, strText5, false);
	if (strlen(strText6) > 0)
		MyMessage.Display2(x, y, strText6, false);
	if (strlen(strText7) > 0)
		MyMessage.Display2(x, y, strText7, false);
	if (strlen(strText8) > 0)
		MyMessage.Display2(x, y, strText8, false);
	if (strlen(strText9) > 0)
		MyMessage.Display2(x, y, strText9, false);
}

int CCharacter::OppositeDirection(int Dir)
{
	if (Dir == MOVE_RIGHT)
		return MOVE_LEFT;
	if (Dir == MOVE_LEFT)
		return MOVE_RIGHT;
	if (Dir == MOVE_UP)
		return MOVE_DOWN;
	if (Dir == MOVE_DOWN)
		return MOVE_UP;
	else
		return MOVE_NONE;
}

void CCharacter::SetPosTile(int a, int b)
{
	if (CharacterMap != NULL)
		CharacterMap->CharacterMap[TileX][TileY] = 0; 
	TileX = a; 
	TileY = b; 
	
	if (CharacterMap != NULL) 
		CharacterMap->CharacterMap[a][b] = 1;
}