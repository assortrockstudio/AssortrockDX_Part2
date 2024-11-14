#pragma once
#include "CComponent.h"

class CCamera :
    public CComponent
{
private:
    int     m_CamPriority; // �����Ŵ����� ��ϵɶ� ī�޶��� �켱����(0 : ����ī�޶�, -1 : �̵�� ī�޶�, 0 ���� ũ�� : ���� ī�޶�)

    float   m_Far;

    Matrix  m_matView;
    Matrix  m_matProj;


public:
    void SetCameraPriority(int _Priority);    

public:
    virtual void finaltick() override;
    void render();



public:
    CCamera();
    ~CCamera();
};

