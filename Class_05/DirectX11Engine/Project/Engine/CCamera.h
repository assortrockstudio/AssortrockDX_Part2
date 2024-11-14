#pragma once
#include "CComponent.h"

class CCamera :
    public CComponent
{
private:
    int     m_CamPriority; // �����Ŵ����� ��ϵɶ� ī�޶��� �켱����(0 : ����ī�޶�, -1 : �̵�� ī�޶�, 0 ���� ũ�� : ���� ī�޶�)



    Matrix  m_matView;

public:
    void SetCameraPriority(int _Priority);    

public:
    virtual void finaltick() override;
    void render();



public:
    CCamera();
    ~CCamera();
};

