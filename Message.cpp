// Message.cpp: implementation of the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "Message.h"
#include "cdxmenu.h"

#define MESSAGE_DIE_COUNT 45

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessage::CMessage()
{
	Count = MESSAGE_DIE_COUNT;
}

CMessage::~CMessage()
{

}

void CMessage::NewText(CDXSurface *surface, char *msg, int a, int b)
{
	strcpy(Message, msg);
	x = a;
	y = b;
	Count = 0;
	Surface = surface;
}

void CMessage::Draw()
{
	// Draws a message on the screen for the number of tics.
	if (Count++ < MESSAGE_DIE_COUNT)
	{
		//Surface->TextXY(x, y, RGB(255,255,0), (LPCTSTR)Message);
		CDXMenu menu;
		menu.TextXY(Surface, x, y, RGB(255, 255, 0), Message);
		x += 7;
	}
}
