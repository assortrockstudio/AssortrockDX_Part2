#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel :
    public CEntity
{
private:
    CLayer*     m_arrLayer[MAX_LAYER];

public:
    void begin();
    void tick();
    void finaltick();
    void render();


public:
    void AddObject(UINT _LayerIdx, CGameObject* _Object);
    CLayer* GetLayer(int _iLayerIdx) { return m_arrLayer[_iLayerIdx]; }

   
public:
    CLevel();
    ~CLevel();
};

