#pragma once
#include "CScript.h"
class CCameraMoveScript :
    public CScript
{
private:
    float       m_Speed;

public:
    virtual void tick() override;

public:
    CCameraMoveScript();
    ~CCameraMoveScript();
};

