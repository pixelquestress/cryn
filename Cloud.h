// Cloud.h: interface for the CCloud class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Cloud_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
#define AFX_Cloud_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>
#include "Character.h"

class CCloud : public CCharacter
{
private:
	int iTicker;
	int Width;
	int iTickSpeed;

public:
	CCloud();
	virtual ~CCloud();

	void Move(int iDirection = 0);
};

#endif // !defined(AFX_Cloud_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
