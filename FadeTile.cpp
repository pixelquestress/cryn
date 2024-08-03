// FadeTile.cpp: implementation of the CFadeTile class.
//
//////////////////////////////////////////////////////////////////////

#include "FadeTile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFadeTile::CFadeTile()
{
	RGBShade = 30;
	PixelX = 0;
	PixelY = 0;
	iShade = RGBShade;
	Screen = NULL;
	memset(TileBuffer, 0, sizeof(TileBuffer));
}

CFadeTile::~CFadeTile()
{

}

void CFadeTile::CopyTile(int x, int y, int iShade/*=0*/, int iShadeLevel/*=19*/)
{
	// Copies the pixels of this 40x40 tile into a buffer for redrawing later.
	SetPos(x, y);

	if (iShadeLevel > 40)
		iShadeLevel = 40;

	for (int i=0; i<40; i++)
		for (int j=0; j<40; j++)
		{
			COLORREF pColor = -1;

			if (PixelX+i > -1 && PixelY+j > -1)
			{
				pColor = Screen->GetBack()->GetPixel(PixelX+i, PixelY+j);
				
				// Pull out R,G,B and convert to 565 format.
				int r = GetRValue(pColor);
				int g = GetGValue(pColor);
				int b = GetBValue(pColor);			
				r >>= 3; // 8-bit to 5-bit
				g >>= 2; // 8-bit to 6-bit
				b >>= 3; // 8-bit to 5-bit
				
				if (iShade == 1 && i < iShadeLevel)
				{
					// SHADE LEFT OF TILE
					if (pColor > 0)
					{
					/*r -= (iShadeLevel)-i;
					g -= (iShadeLevel)-i;
						b -= (iShadeLevel)-i;*/
						
						if (r < 0) r = 0;
						if (g < 0) g = 0;
						if (b < 0) b = 0;
						
						pColor = RGB565(r, g, b);
					}
				}
				else if (iShade == 2 && i > iShadeLevel)
				{
					// SHADE RIGHT OF TILE
					if (pColor > 0)
					{
					/*r -= i-(iShadeLevel);
					g -= i-(iShadeLevel);
						b -= i-(iShadeLevel);*/
						
						if (r < 0) r = 0;
						if (g < 0) g = 0;
						if (b < 0) b = 0;
						
						pColor = RGB565(r, g, b);
					}
				}
				else if (iShade == 3 && j < iShadeLevel)
				{
					// SHADE TOP OF TILE
					if (pColor > 0)
					{
					/*r -= (iShadeLevel)-j;
					g -= (iShadeLevel)-j;
						b -= (iShadeLevel)-j;*/
						
						if (r < 0) r = 0;
						if (g < 0) g = 0;
						if (b < 0) b = 0;
						
						pColor = RGB565(r, g, b);
					}
				}
				else if (iShade == 4 && j > iShadeLevel)
				{
					// SHADE BOTTOM OF TILE
					if (pColor > 0)
					{
					/*r -= j-(iShadeLevel);
					g -= j-(iShadeLevel);
						b -= j-(iShadeLevel);*/
						
						if (r < 0) r = 0;
						if (g < 0) g = 0;
						if (b < 0) b = 0;
						
						pColor = RGB565(r, g, b);
					}
				}
			}

			TileBuffer[i][j] = pColor;
		}
}

void CFadeTile::DrawTile()
{
	for (int i=0; i<40; i++)
		for (int j=0; j<40; j++)
		{
			COLORREF pColor = TileBuffer[i][j];

			if (pColor != -1 && (PixelX+i > -1) && (PixelY+j > -1))
				Screen->GetBack()->PutPixel(PixelX+i, PixelY+j, pColor);
		}
}

/*void CFadeTile::Draw()
{
	if (Screen == NULL)
		return;

	// USER MUST LOCK SURFACE!
	if (iShade > 0)
	for (int xx=0; xx < 40; xx++)
		for (int yy=0; yy < 40; yy++)
		{
			int pColor = Screen->GetBack()->GetPixel24(PixelX + xx, PixelY+yy);
			if (pColor != 0)
			{
				pColor -= RGB565(iShade,iShade,iShade);
				if (pColor < 0) pColor = 0;
				
				Screen->GetBack()->PutPixel24(PixelX + xx, PixelY+yy, pColor);
			}
		}

	if (iShade < 1)
		iShade = RGBShade;
}*/