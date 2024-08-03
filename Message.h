// Message.h: interface for the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGE_H__B72B4340_9F55_11D5_9857_D5CF9032E940__INCLUDED_)
#define AFX_MESSAGE_H__B72B4340_9F55_11D5_9857_D5CF9032E940__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>

class CMessage  
{
private:
	int Count; // time till message dissapears.
	int x, y;
	char Message[10000];
	
	CDXSurface *Surface;

public:
	CMessage();
	virtual ~CMessage();

	void NewText(CDXSurface *surface, char *msg, int a=10, int b=380);
	void Draw();
};

#endif // !defined(AFX_MESSAGE_H__B72B4340_9F55_11D5_9857_D5CF9032E940__INCLUDED_)
