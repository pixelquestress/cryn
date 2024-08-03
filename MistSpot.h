// MistSpot.h: interface for the CMistSpot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MistSpot_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
#define AFX_MistSpot_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>
#include "NPC.h"

class CMistSpot : public CNPC
{
private:
	int iAlpha;
	bool bAlphaUp;
	int iRecursion;
	bool bRandom;
	int iAlphaMax;
	int iAlphaMin;
	int iFadeSpeed;
	int LeftBorder, RightBorder, TopBorder, BottomBorder;

public:
	CMistSpot();
	virtual ~CMistSpot();

	void SetAlphaMax(int aiAlphaMax) { if (aiAlphaMax > 255) aiAlphaMax = 255; iAlphaMax = aiAlphaMax; };
	void SetAlphaMin(int aiAlphaMin) { if (aiAlphaMin < 0) aiAlphaMin = 0; iAlphaMin = aiAlphaMin; };
	void SetFadeSpeed(int aiFadeSpeed) { iFadeSpeed = aiFadeSpeed; };
	void SetBoundry(int a, int b, int c, int d) { LeftBorder = a; TopBorder = b; RightBorder = c; BottomBorder = d; };
	void SetRandom(bool abRandom);
	void MoveRandomSpot();
	void Init();
	bool Draw();
};

#endif // !defined(AFX_MistSpot_H__A15CDF99_539B_48FD_9016_D36A5D1DC45F__INCLUDED_)
