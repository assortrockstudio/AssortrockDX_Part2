#pragma once
#include "CComponent.h"

class CCamera :
    public CComponent
{
private:
    Matrix  m_matView;

public:
    CCamera();
    ~CCamera();
};

