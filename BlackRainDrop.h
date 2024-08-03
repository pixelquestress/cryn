// BlackRainDrop.h: interface for the CBlackRainDrop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLACKRAINDROP_H__FB2D8B09_9E3D_4992_8F1C_8807CF6D13BE__INCLUDED_)
#define AFX_BLACKRAINDROP_H__FB2D8B09_9E3D_4992_8F1C_8807CF6D13BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RainDrop.h"

class CBlackRainDrop : public CRainDrop  
{
public:
	CBlackRainDrop();
	virtual ~CBlackRainDrop();

	void Load(CDXScreen *screen);
};

#endif // !defined(AFX_BLACKRAINDROP_H__FB2D8B09_9E3D_4992_8F1C_8807CF6D13BE__INCLUDED_)
