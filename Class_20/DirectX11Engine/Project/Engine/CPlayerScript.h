#pragma once
#include "CScript.h"


class CPlayerScript :
    public CScript
{
private:
    float       m_Speed;

public:
    virtual void tick() override;   
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;


public:
    CPlayerScript();
    ~CPlayerScript();
};

