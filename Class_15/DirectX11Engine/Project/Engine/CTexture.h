#pragma once
#include "CAsset.h"

class CTexture :
    public CAsset
{
private:
    ScratchImage                        m_Image;
    ComPtr<ID3D11Texture2D>             m_Tex2D;
    ComPtr<ID3D11ShaderResourceView>    m_SRV;

public:
    void Binding(int _RegisterNum);
    static void Clear(int _RegisterNum);

private:
    virtual int Load(const wstring& _FilePath) override;
    virtual int Save(const wstring& _FilePath) override;

public:
    CTexture();
    ~CTexture();
};

