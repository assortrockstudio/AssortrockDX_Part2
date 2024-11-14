#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer :
    public CEntity
{
private:
    vector<CGameObject*>    m_vecParent;    // Layer �Ҽ� ������Ʈ ��, �ֻ��� �θ� ����
    vector<CGameObject*>    m_vecObjects;   // Layer �Ҽ� ��� ������Ʈ��
    int                     m_LayerIdx;

public:
    void begin();
    void tick();
    void finaltick(); 
    
public:
    void AddObject(CGameObject* _Object);
   
    void RegisterObject(CGameObject* _Object) { m_vecObjects.push_back(_Object); }
    void Clear() { m_vecObjects.clear(); }

    const vector<CGameObject*>& GetObjects() { return m_vecObjects; }

public:
    CLayer();
    ~CLayer();

    friend class CLevel;
};
