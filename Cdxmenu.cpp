//////////////////////////////////////////////////////////////////////////////////
// $Source: /cvsroot/cdx/cdx3.0/addons/CDXMenu/CDXMENU.CPP,v $
// $Author: mindcry $
//
// $Log: CDXMENU.CPP,v $
// Revision 1.2  2000/06/30 08:31:46  mindcry
// Some minor fixes from Mike
//
// Revision 1.1.1.1  2000/04/22 16:50:12  hebertjo
// Initial checkin of v3.0 to SourceForge CVS.
//
// Revision 1.1.1.1  1999/05/04 23:59:23  bsimser
// Imported addons
//
// $Revision: 1.2 $
//////////////////////////////////////////////////////////////////////////////////
#include "CDX.h"
#include "CDXMenu.h"
#include "cdxmap.h"
#include <fstream>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////
// CDXMenu Default Constructor
//////////////////////////////////////////////////////////////////////////////////
CDXMenu::CDXMenu()
{
	m_CurrentItemStr = NULL;
}

//////////////////////////////////////////////////////////////////////////////////
// CDXMenu Constructor
//////////////////////////////////////////////////////////////////////////////////
void CDXMenu::Create(CDXSurface *pSurface, int Spacing)
{
	m_Spacing = Spacing;
	m_ItemCount = 0;
	m_CurrentItem = 0;
	m_pSurface = pSurface;
	m_bWrap = TRUE;
	ZeroMemory(&m_Title, sizeof(m_Title));
}

//////////////////////////////////////////////////////////////////////////////////
// Sets the wrapping capabilities of the menu
//////////////////////////////////////////////////////////////////////////////////
void CDXMenu::SetWrap(BOOL bWrap)
{
	m_bWrap = bWrap;
}

//////////////////////////////////////////////////////////////////////////////////
// Sets the title used by the menu (optional)
//////////////////////////////////////////////////////////////////////////////////
void CDXMenu::SetTitle(const char *szTitle, COLORREF color)
{
	strcpy(m_Title.m_szTitle, szTitle);
	m_Title.m_color = color;
	m_Title.m_bActive = TRUE;
}

//////////////////////////////////////////////////////////////////////////////////
// Adds an item to the menu
//////////////////////////////////////////////////////////////////////////////////
int CDXMenu::AddItem(char *szString, COLORREF oncolor, COLORREF offcolor, COLORREF disabledcolor)
{
	strcpy(m_MenuItems[m_ItemCount].m_szString, szString);
	m_MenuItems[m_ItemCount].m_OnColor = oncolor;
	m_MenuItems[m_ItemCount].m_OffColor = offcolor;
	m_MenuItems[m_ItemCount].m_DisabledColor = disabledcolor;
	m_MenuItems[m_ItemCount].m_Enabled = TRUE;
	m_ItemCount++;

	return m_ItemCount - 1;
}

//////////////////////////////////////////////////////////////////////////////////
// Returns the current menu item
//////////////////////////////////////////////////////////////////////////////////
int CDXMenu::Enter()
{
	return m_CurrentItem;
}


//////////////////////////////////////////////////////////////////////////////////
// Enables / Disables a menu item
//////////////////////////////////////////////////////////////////////////////////
void CDXMenu::EnableItem(int item, BOOL bEnable)
{
	m_MenuItems[item].m_Enabled = bEnable;
}

//////////////////////////////////////////////////////////////////////////////////
// Sets the current item to the first on in the menu
//////////////////////////////////////////////////////////////////////////////////
void CDXMenu::Home()
{
	m_CurrentItem = 0;
	m_CurrentItemStr = m_MenuItems[m_CurrentItem].m_szString;
}

//////////////////////////////////////////////////////////////////////////////////
// Moves up one menu option. If wrapping is enabled, wraps to the last item
//////////////////////////////////////////////////////////////////////////////////
void CDXMenu::Up()
{
	m_CurrentItem--;
	if(m_CurrentItem < 0) {
		if(m_bWrap) {
			End();
		}
		else {
			Home();
		}
	}
	if (!m_MenuItems[m_CurrentItem].m_Enabled) Up();

	m_CurrentItemStr = m_MenuItems[m_CurrentItem].m_szString;
}

//////////////////////////////////////////////////////////////////////////////////
// Moves down one menu option. If wrapping is enabled, wraps to the first item
//////////////////////////////////////////////////////////////////////////////////
void CDXMenu::Down()
{
	m_CurrentItem++;
	if(m_CurrentItem > (m_ItemCount-1)) {
		if(m_bWrap) {
			Home();
		}
		else {
			End();
		}
	}
	if (!m_MenuItems[m_CurrentItem].m_Enabled) Down();

	m_CurrentItemStr = m_MenuItems[m_CurrentItem].m_szString;
}

//////////////////////////////////////////////////////////////////////////////////
// Sets the last menu item as the current one
//////////////////////////////////////////////////////////////////////////////////
void CDXMenu::End()
{
	m_CurrentItem = m_ItemCount - 1;
	m_CurrentItemStr = m_MenuItems[m_CurrentItem].m_szString;
}

//////////////////////////////////////////////////////////////////////////////////
// Draws the menu to the surface specified in the constructor. This method
// draws the menu centered on the screen and centers all the items in
// the menu.
//////////////////////////////////////////////////////////////////////////////////
void CDXMenu::DrawCentered(void)
{
    SIZE sz;
    COLORREF col;
    int X, Y, i;
	HDC hdc;

    hdc = m_pSurface->GetDC();
    m_pSurface->SetFont();

    // get the height and width of the title in the current font
    GetTextExtentPoint32(hdc, (LPCTSTR)m_Title.m_szTitle,
        lstrlen((LPCWSTR)m_Title.m_szTitle), &sz);

    // calc the full height of the menu
    int mh = (m_Spacing * (m_ItemCount));

    // if the title is active add it to the height
    if(m_Title.m_bActive) {
        mh+=m_Spacing;
    }

    // calc the vertical starting point
    Y = (m_pSurface->GetHeight() - mh) / 2;

    // draw the title if its active
    if(m_Title.m_bActive) {
        // determine the X drawing for the title and draw it
        X = (m_pSurface->GetWidth() - sz.cx) / 2;
        //m_pSurface->TextXY(X, Y, m_Title.m_color, (LPCTSTR)m_Title.m_szTitle);
		TextXY(m_pSurface, X, Y, m_Title.m_color, m_Title.m_szTitle);
    }

    // draw all the items
    for(i=0; i<m_ItemCount; i++) {
        // get the width of the current string
        GetTextExtentPoint32(hdc, (LPCTSTR)m_MenuItems[i].m_szString,
            lstrlen((LPCTSTR)m_MenuItems[i].m_szString), &sz);
        // calc its horizontal position
        X = (m_pSurface->GetWidth() - sz.cx) / 2;

		col = (i == m_CurrentItem) ? m_MenuItems[i].m_OnColor : m_MenuItems[i].m_OffColor;
		if (!m_MenuItems[i].m_Enabled) col = m_MenuItems[i].m_DisabledColor;
		if(m_Title.m_bActive) {
			//m_pSurface->TextXY(X, Y+((i+1)*m_Spacing), col, (LPCTSTR)m_MenuItems[i].m_szString);
			TextXY(m_pSurface, X, Y + ((i + 1) * m_Spacing), col, m_MenuItems[i].m_szString);
		}
		else {
			//m_pSurface->TextXY(X, Y+((i+1)*m_Spacing), col, (LPCTSTR)m_MenuItems[i].m_szString);
			TextXY(m_pSurface, X, Y + ((i + 1) * m_Spacing), col, m_MenuItems[i].m_szString);
		}
	}

	m_pSurface->ReleaseDC();
}

//////////////////////////////////////////////////////////////////////////////////
// Draws the menu to the surface specified in the constructor. This
// method figures out the X and Y values and places the menu in the
// center of the screen
//////////////////////////////////////////////////////////////////////////////////
void CDXMenu::Draw(void)
{
    SIZE sz;
    int dwWidest, i;
	HDC hdc;

    hdc = m_pSurface->GetDC();
    m_pSurface->SetFont();

    // get the height and width of the title in the current font
    GetTextExtentPoint32(hdc, (LPCTSTR)m_Title.m_szTitle,
        lstrlen((LPCTSTR)m_Title.m_szTitle), &sz);

    // calc the full height of the menu
    int mh = (m_Spacing * (m_ItemCount));

    // if the title is active, add it to the height also
    if(m_Title.m_bActive) {
        dwWidest = sz.cx;
        mh+=m_Spacing;
    }
    else {
        dwWidest = 0;
    }

    // go through each item and figure out the widest one
    for(i=0; i<m_ItemCount; i++) {
        // get the width of the current string
        GetTextExtentPoint32(hdc, (LPCTSTR)m_MenuItems[i].m_szString,
            lstrlen((LPCTSTR)m_MenuItems[i].m_szString), &sz);
        dwWidest = max(sz.cx, dwWidest);
    }

    // calc the horizontal and vertical starting point
    int X = (m_pSurface->GetWidth() - dwWidest) / 2;
    int Y = (m_pSurface->GetHeight() - mh) / 2;

    // release the handle and draw the menu
    m_pSurface->ReleaseDC();

    Draw(X, Y);
}

//////////////////////////////////////////////////////////////////////////////////
// Draws the menu to the surface specified in the constructor. This
// uses the X and Y parameters passed to place the menu.
//////////////////////////////////////////////////////////////////////////////////
void CDXMenu::Draw(int X, int Y)
{
	COLORREF col;
    int i;

	m_pSurface->GetDC();
	m_pSurface->SetFont();

	if(m_Title.m_bActive) {
		//m_pSurface->TextXY(X, Y, m_Title.m_color, (LPCTSTR)m_Title.m_szTitle);
		TextXY(m_pSurface, X, Y, m_Title.m_color, m_Title.m_szTitle);
	}

    for(i=0; i<m_ItemCount; i++) {
		col = (i == m_CurrentItem) ? m_MenuItems[i].m_OnColor : m_MenuItems[i].m_OffColor;
		if (!m_MenuItems[i].m_Enabled) col = m_MenuItems[i].m_DisabledColor;
		if(m_Title.m_bActive) {
			//m_pSurface->TextXY(X, Y+((i+1)*m_Spacing), col, (LPCTSTR)m_MenuItems[i].m_szString);
			TextXY(m_pSurface, X, Y+((i+1)*m_Spacing), col,m_MenuItems[i].m_szString);
		}
		else {
			//m_pSurface->TextXY(X, Y+(i+1*m_Spacing), col, (LPCTSTR)m_MenuItems[i].m_szString);
			TextXY(m_pSurface, X, Y+((i+1)*m_Spacing), col, m_MenuItems[i].m_szString);
		}
	}

	m_pSurface->ReleaseDC();
}

HRESULT CDXMenu::TextXY(CDXSurface* surface, int x, int y, COLORREF col, const char* pString)
{
	HRESULT rval;
	HDC dc;

	if (pString == NULL)
		return 0;

	dc = surface->GetDC();

	if (dc != NULL)
	{
		SetBkMode(dc, TRANSPARENT);
		SetTextColor(dc, col);

		// Convert narrow string to wide string
		int len = MultiByteToWideChar(CP_ACP, 0, pString, -1, NULL, 0);
		wchar_t* wString = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, pString, -1, wString, len);

		rval = ::TextOut(dc, x, y, wString, wcslen(wString));

		delete[] wString;
		surface->ReleaseDC();
	}

	if (rval == 0)
		return -1;

	return 0;
}
/*
//////////////////////////////////////////////////////////////////////////////////
// Loads a map from a ASCII text file denoting tiles by letter.
// You just specify the Width and Height to be the same number of characters
// in the map horizontally (width) and vertically (height).
// The map can be made using Notepad having the format:
// aaaaabbaaaa
// aaaabbaaaaa
// aaabbaaaaaa
// aaaabbaaaaa
// Where a = first tile in tiles.bmp  (always clear black tile)
//       b = second tile in tiles.bmp (1st actual graphic tile)
//       c = third tile in tiles.bmp
//
// Map has certain format here is full example:
// [MAP NON-WALKABLE]
// a                  <-- tile a is non-walkable
// [NEXT SYMBOL]
// d                  <-- tile d is non-walkable
// [MAP SYMBOLS]
// a                  <-- symbol is animated
// 1                  <-- tile 1 is first frame
// 4                  <-- tile 4 is last frame
// [NEXT SYMBOL]
// d
// 8
// 12
// [MAP]
// aaaaabbaaaa
// addabbacaaa
// aaabbadaaaa
// aaaabbaaaaa
//////////////////////////////////////////////////////////////////////////////////
BOOL CDXMap::LoadAscii(const char* szFilename, int Width, int Height)
{
	if (szFilename == NULL) return FALSE;

	if (Create(Width, Height, 0) == FALSE)
		return FALSE;

	m_DATA = new CDXMapCell[m_SIZE];
	for (int i = 0; i < m_SIZE; i++)
		m_DATA[i].SetTile(0);

	ifstream f(szFilename);

	// Read tile symbols which have animations.
	char line[100];
	char cSymbol;
	int tile_start, tile_end;
	f.getline(line, 100); // read description line.

	// First, read non-walkable tiles.
	if (strcmp(line, "[MAP NON-WALKABLE]") == 0)
	{
		// while next command set is not found, read non-walkables
		while (strstr(line, "[MAP SYMBOLS]") == NULL &&
			strstr(line, "[MAP]") == NULL)
		{
			f >> cSymbol;
			f.getline(line, 100); // read rest of line.
			//m_DATA[tile_index].SetTileWalkable(false);
			WalkableSymbols[WalkableSymbolIndex++] = cSymbol;
			f.getline(line, 100); // read title of next line.
		}
	}

	// Next, read animated tiles.
	while (strcmp(line, "[MAP]") != 0 && !f.eof())
	{
		// Reading animated symbols.
		f >> cSymbol;
		f.getline(line, 100); // read rest of line.
		f >> tile_start;
		f.getline(line, 100); // read rest of line.
		f >> tile_end;
		f.getline(line, 100); // read rest of line.

		AnimatedSymbols[AnimatedSymbolIndex].chSymbol = cSymbol;
		AnimatedSymbols[AnimatedSymbolIndex].TileStart = tile_start;
		AnimatedSymbols[AnimatedSymbolIndex].TileEnd = tile_end;
		AnimatedSymbolIndex++;

		f.getline(line, 100); // read title of next line.
	}

	// Read character x character for tile number.
	int index = 0;
	char ch;

	// Finally, read tile data.
	while (!f.eof() && index < m_SIZE)
	{
		f.get(ch);

		if (ch == '\n' || ch == '\t' || ch == '\r')
		{
			// Ignore bad character.
		}
		else
		{
			// Read each character.
			char lower_ch = tolower(ch);

			switch (lower_ch)
			{
			case 'a': m_DATA[index].SetTile(0); break;
			case 'b': m_DATA[index].SetTile(1); break;
			case 'c': m_DATA[index].SetTile(2); break;
			case 'd': m_DATA[index].SetTile(3); break;
			case 'e': m_DATA[index].SetTile(4); break;
			case 'f': m_DATA[index].SetTile(5); break;
			case 'g': m_DATA[index].SetTile(6); break;
			case 'h': m_DATA[index].SetTile(7); break;
			case 'i': m_DATA[index].SetTile(8); break;
			case 'j': m_DATA[index].SetTile(9); break;
			case 'k': m_DATA[index].SetTile(10); break;
			case 'l': m_DATA[index].SetTile(11); break;
			case 'm': m_DATA[index].SetTile(12); break;
			case 'n': m_DATA[index].SetTile(13); break;
			case 'o': m_DATA[index].SetTile(14); break;
			case 'p': m_DATA[index].SetTile(15); break;
			case 'q': m_DATA[index].SetTile(16); break;
			case 'r': m_DATA[index].SetTile(17); break;
			case 's': m_DATA[index].SetTile(18); break;
			case 't': m_DATA[index].SetTile(19); break;
			case 'u': m_DATA[index].SetTile(20); break;
			case 'v': m_DATA[index].SetTile(21); break;
			case 'w': m_DATA[index].SetTile(22); break;
			case 'x': m_DATA[index].SetTile(23); break;
			case 'y': m_DATA[index].SetTile(24); break;
			case 'z': m_DATA[index].SetTile(25); break;
			case '0': m_DATA[index].SetTile(26); break;
			case '1': m_DATA[index].SetTile(27); break;
			case '2': m_DATA[index].SetTile(28); break;
			case '3': m_DATA[index].SetTile(29); break;
			case '4': m_DATA[index].SetTile(30); break;
			case '5': m_DATA[index].SetTile(31); break;
			case '6': m_DATA[index].SetTile(32); break;
			case '7': m_DATA[index].SetTile(33); break;
			case '8': m_DATA[index].SetTile(34); break;
			case '9': m_DATA[index].SetTile(35); break;

			default: m_DATA[index].SetTile(0); break;
			};

			// Set animation properties.
			for (int i = 0; i < AnimatedSymbolIndex; i++)
			{
				if (lower_ch == AnimatedSymbols[i].chSymbol)
				{
					// We have an animated symbol.
					m_DATA[index].SetTileAnimation(AnimatedSymbols[i].TileStart, AnimatedSymbols[i].TileEnd);
					i = AnimatedSymbolIndex + 10; // end loop
				}
			}

			// Set walkable properties.
			for (int i = 0; i < WalkableSymbolIndex; i++)
			{
				if (lower_ch == WalkableSymbols[i])
				{
					// We have a non-walkable tile.
					m_DATA[index].SetTileWalkable(false);
					i = WalkableSymbolIndex + 10; // end loop
				}
			}

			index++;
		}
	}

	f.close();

	return TRUE;
}

BOOL CDXMap::SaveAscii(const char* szFilename)
{
	if (szFilename == NULL) return FALSE;

	ofstream f(szFilename);

	// Read tile symbols which have animations.
	f << "[MAP]" << endl;

	// Finally, read tile data.
	for (int y = 0; y < GetMapHeight(); y++)
	{
		for (int x = 0; x < GetMapWidth(); x++)
		{
			switch (GetTile(x, y))
			{
			case 0: f << "a"; break;
			case 1: f << "b"; break;
			case 2: f << "c"; break;
			case 3: f << "d"; break;
			case 4: f << "e"; break;
			case 5: f << "f"; break;
			case 6: f << "g"; break;
			case 7: f << "h"; break;
			case 8: f << "i"; break;
			case 9: f << "j"; break;
			case 10: f << "k"; break;
			case 11: f << "l"; break;
			case 12: f << "m"; break;
			case 13: f << "n"; break;
			case 14: f << "o"; break;
			case 15: f << "p"; break;
			case 16: f << "q"; break;
			case 17: f << "r"; break;
			case 18: f << "s"; break;
			case 19: f << "t"; break;
			case 20: f << "u"; break;
			case 21: f << "v"; break;
			case 22: f << "w"; break;
			case 23: f << "x"; break;
			case 24: f << "y"; break;
			case 25: f << "z"; break;
			case 26: f << "0"; break;
			case 27: f << "1"; break;
			case 28: f << "2"; break;
			case 29: f << "3"; break;
			case 30: f << "4"; break;
			case 31: f << "5"; break;
			case 32: f << "6"; break;
			case 33: f << "7"; break;
			case 34: f << "8"; break;
			case 35: f << "9"; break;
			default: f << "a"; break;
			};
		}

		f << endl;
	}

	f.close();

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////
// Returns the width of the map in map units
//////////////////////////////////////////////////////////////////////////////////
int CDXMap::GetMapWidth()
{
	return m_Width;
}

//////////////////////////////////////////////////////////////////////////////////
// Returns the height of the map in map units
//////////////////////////////////////////////////////////////////////////////////
int CDXMap::GetMapHeight()
{
	return m_Height;
}

//
// Returns if tile has animated frames.
//
bool CDXMap::IsAnimated(int MapX, int MapY)
{
	return (GetCell(MapX, MapY)->IsAnimated());
}

bool CDXMap::IsWalkable(int MapX, int MapY)
{
	return (GetCell(MapX, MapY)->IsWalkable());
}

bool CDXMapCell::IsAnimated()
{
	return Animated;
}

bool CDXMapCell::IsWalkable()
{
	return Walkable;
}

int CDXMapCell::GetTileStart()
{
	return TileStart;
}

int CDXMapCell::GetTileEnd()
{
	return TileEnd;
}

void CDXMapCell::SetTileAnimation(int Start, int End)
{
	Animated = true;
	TileStart = Start;
	TileEnd = End;
}

void CDXMapCell::SetTileWalkable(bool w)
{
	Walkable = w;
}

void CDXMap::AnimateMap(int Speed)
{
	static int Delay = 0;

	if (++Delay > Speed)
	{
		for (int i = 0; i < GetMapWidth(); i++)
			for (int j = 0; j < GetMapHeight(); j++)
			{
				AnimateTile(i, j);
			}
		Delay = 0;
	}
}

//
// Moves tile frame to next in line.
// TileStart and TileEnd frames must already be specified in the MapCell.
//
void CDXMap::AnimateTile(int MapX, int MapY)
{
	CDXMapCell* MapCell = GetCell(MapX, MapY);

	if (!MapCell->IsAnimated())
		return;

	int TileCurrent = MapCell->GetTile();
	int TileStart = MapCell->GetTileStart();
	int TileEnd = MapCell->GetTileEnd();

	// Move tile to next frame of animation.
	if (++TileCurrent > TileEnd)
	{
		TileCurrent = TileStart;
	}

	MapCell->SetTile(TileCurrent);
}

//////////////////////////////////////////////////////////////////////////////////
// Returns the number of the tile at the right end of the screen.
//////////////////////////////////////////////////////////////////////////////////
int CDXMap::GetScreenMapPosX2()
{
	int NumHorizBlocks = GetScreenBlocksWidth(); // # blocks on screen horiz
	int TilePosX2 = GetPosX(); // pixel coord of Map x pos.
	TilePosX2 /= GetTileWidth(); // Tile # of x1 pos.
	TilePosX2 += NumHorizBlocks; // Tile # of x2 pos.

	return TilePosX2;
}

//////////////////////////////////////////////////////////////////////////////////
// Returns the number of the tile at the bottom end of the screen.
//////////////////////////////////////////////////////////////////////////////////
int CDXMap::GetScreenMapPosY2()
{
	int NumVertBlocks = GetScreenBlocksHeight(); // # blocks on screen vert
	int TilePosY2 = GetPosY(); // pixel coord of Map y pos.
	TilePosY2 /= GetTileHeight(); // Tile # of y1 pos.
	TilePosY2 += NumVertBlocks; // Tile # of y2 pos.

	return TilePosY2;
}
*/