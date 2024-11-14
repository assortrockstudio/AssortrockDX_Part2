#pragma once
#include "singleton.h"

#include "CPathMgr.h"
#include "assets.h"

class CAssetMgr :
    public CSingleton<CAssetMgr>
{
    SINGLE(CAssetMgr)
private:
    map<wstring, Ptr<CAsset>>   m_mapAsset[(UINT)ASSET_TYPE::END];

public:
    void init();
    void CreateDefaultMesh();
    void CreateDefaultTexture();
    void CreateDefaultMaterial();
    void CreateDefaultGraphicShader();
    void CreateDefaultComputeShader();


public:
    template<typename T>
    Ptr<T> Load(const wstring& _strKey, const wstring& _strRelativePath);

    template<typename T>
    Ptr<T> FindAsset(const wstring& _strKey);

    template<typename T>
    void AddAsset(const wstring& _strKey, Ptr<T> pAsset);


};

template<typename T>
ASSET_TYPE GetAssetType()
{
    if constexpr (std::is_same_v<T, CMesh>)
    {
        return ASSET_TYPE::MESH;
    }  
    if constexpr (std::is_same_v<T, CGraphicShader>)
    {
        return ASSET_TYPE::GRAPHICS_SHADER;
    }
    if constexpr (std::is_same_v<T, CComputeShader>)
    {
        return ASSET_TYPE::COMPUTE_SHADER;
    }
    if constexpr (std::is_same_v<T, CTexture>)
    {
        return ASSET_TYPE::TEXTURE;
    }
    if constexpr (std::is_same_v<T, CMaterial>)
    {
        return ASSET_TYPE::MATERIAL;
    }
}

template<typename T>
inline Ptr<T> CAssetMgr::Load(const wstring& _strKey, const wstring& _strRelativePath)
{
    Ptr<CAsset> pAsset = FindAsset<T>(_strKey).Get();
    if (nullptr != pAsset.Get())
    {
        return (T*)pAsset.Get();
    }

    wstring strFullPath = CPathMgr::GetInst()->GetContentPath();
    strFullPath += _strRelativePath;

    pAsset = new T;
    if (FAILED(pAsset->Load(strFullPath)))
    {
        MessageBox(nullptr, strFullPath.c_str(), L"에셋 로딩 실패", MB_OK);
        return nullptr;
    }

    AddAsset<T>(_strKey, (T*)pAsset.Get());

    return (T*)pAsset.Get();
}

template<typename T>
inline Ptr<T> CAssetMgr::FindAsset(const wstring& _strKey)
{
    ASSET_TYPE type = GetAssetType<T>();

    map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)type].find(_strKey);

    if (iter == m_mapAsset[(UINT)type].end())
    {
        return nullptr;
    }

#ifdef _DEBUG
    T* pAsset = dynamic_cast<T*>(iter->second.Get());
    return pAsset;
#else
    return (T*)iter->second;
#endif
}

template<typename T>
inline void CAssetMgr::AddAsset(const wstring& _strKey, Ptr<T> _pAsset)
{
    Ptr<T> pFindAsset = FindAsset<T>(_strKey);

    assert(pFindAsset.Get() == nullptr);
    
    ASSET_TYPE type = GetAssetType<T>();

    m_mapAsset[(UINT)type].insert(make_pair(_strKey, _pAsset.Get()));
    _pAsset->m_Key = _strKey;
}