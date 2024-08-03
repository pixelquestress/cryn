// FireDrop.h: interface for the CFireDrop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIREDROP_H__E2DEA6F9_D0A7_4E02_9FAC_DCC4B6B69904__INCLUDED_)
#define AFX_FIREDROP_H__E2DEA6F9_D0A7_4E02_9FAC_DCC4B6B69904__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SnowFlake.h"

class CFireDrop : public CSnowFlake  
{
public:
	CFireDrop();
	virtual ~CFireDrop();

	void Load(CDXScreen *screen, bool bblizzard = false);
};

#endif // !defined(AFX_FIREDROP_H__E2DEA6F9_D0A7_4E02_9FAC_DCC4B6B69904__INCLUDED_)
