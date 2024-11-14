#pragma once
#include "CComponent.h"

#include "assets.h"

class CRenderComponent :
    public CComponent
{
private:
    Ptr<CMesh>          m_Mesh;
    Ptr<CMaterial>      m_Mtrl;
    
public:
    virtual void render() = 0;

public:
    void SetMesh(Ptr<CMesh> _Mesh) { m_Mesh = _Mesh; }
    void SetMaterial(Ptr<CMaterial> _Mtrl) { m_Mtrl = _Mtrl; }    

    Ptr<CMesh> GetMesh() { return m_Mesh; }
    Ptr<CMaterial> GetMaterial() { return m_Mtrl; }

public:
    CRenderComponent(COMPONENT_TYPE _Type);
    ~CRenderComponent();
};

