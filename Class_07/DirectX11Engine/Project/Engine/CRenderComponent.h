#pragma once
#include "CComponent.h"

#include "assets.h"

class CRenderComponent :
    public CComponent
{
private:
    Ptr<CMesh>          m_Mesh;
    Ptr<CGraphicShader> m_Shader;
    Ptr<CTexture>       m_Tex;

public:
    virtual void render() = 0;

public:
    void SetMesh(Ptr<CMesh> _Mesh) { m_Mesh = _Mesh; }
    void SetShader(Ptr<CGraphicShader> _Shader) { m_Shader = _Shader; }
    void SetTexture(Ptr<CTexture> _Tex) { m_Tex = _Tex; }

    Ptr<CMesh> GetMesh() { return m_Mesh; }
    Ptr<CGraphicShader> GetShader() { return m_Shader; }
    Ptr<CTexture> GetTexture() { return m_Tex; }

public:
    CRenderComponent(COMPONENT_TYPE _Type);
    ~CRenderComponent();
};

