#pragma once
#include "CAsset.h"

#include "assets.h"

class CMaterial :
    public CAsset
{
private:    
    Ptr<CGraphicShader>     m_Shader;

    tMtrlConst              m_Const;
    Ptr<CTexture>           m_arrTex[TEX_PARAM::END];


public:
    void SetShader(Ptr<CGraphicShader> _Shader) { m_Shader = _Shader; }
    Ptr<CGraphicShader> GetShader() { return m_Shader; }


public:
    void Binding();

    virtual int Load(const wstring& _FilePath) { return S_OK; };
    virtual int Save(const wstring& _FilePath) { return S_OK; };

public:
    CMaterial();
    ~CMaterial();
};

