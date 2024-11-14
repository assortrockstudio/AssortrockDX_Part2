#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CGameObject.h"

#include "CTransform.h"
#include "CMeshRender.h"
#include "CPlayerScript.h"

#include "CAssetMgr.h"

CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_CurLevel)
	{
		delete m_CurLevel;
	}	
}

void CLevelMgr::init()
{
	m_CurLevel = new CLevel;

	CGameObject* pObject = new CGameObject;
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CPlayerScript);
		
	pObject->Transform()->SetRelativeScale(1.f, 1.f, 0.2f);

	pObject->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObject->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));
	pObject->MeshRender()->SetTexture(CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\Fighter.bmp"));

	m_CurLevel->AddObject(0, pObject);
}

void CLevelMgr::tick()
{
	if(nullptr != m_CurLevel)	
	{
		m_CurLevel->tick();
		m_CurLevel->finaltick();
	}
}

void CLevelMgr::render()
{
	if (nullptr != m_CurLevel)
		m_CurLevel->render();
}
