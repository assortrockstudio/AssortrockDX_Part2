#pragma once
#include "singleton.h"

class CCollisionMgr :
    public CSingleton<CCollisionMgr>
{
    SINGLE(CCollisionMgr);
private:
    UINT        m_Matrix[(UINT)MAX_LAYER];

public:
    void tick();

public:
    void LayerCheck(UINT _LayerLeftIdx, UINT _LayerRightIdx);
};

