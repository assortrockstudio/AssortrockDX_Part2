#include "pch.h"
#include "CCollisionMgr.h"

CCollisionMgr::CCollisionMgr()
	: m_Matrix{}	
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::tick()
{
	for (UINT Row = 0; Row < MAX_LAYER; ++Row)
	{
		for (UINT Col = Row; Col < MAX_LAYER; ++Col)
		{			
			if (m_Matrix[Row] & (1 << Col))
			{
				int a = 0;
			}
		}
	}
}

void CCollisionMgr::LayerCheck(UINT _LayerLeftIdx, UINT _LayerRightIdx)
{
	UINT Row = _LayerLeftIdx;
	UINT Col = _LayerRightIdx;

	if (Col < Row)
	{
		Row = _LayerRightIdx;
		Col = _LayerLeftIdx;
	}

	UINT CheckBit = (1 << Col);

	if (m_Matrix[Row] & CheckBit)
	{
		m_Matrix[Row] &= ~CheckBit;
	}
	else
	{
		m_Matrix[Row] |= CheckBit;
	}	
}
