#include "pch.h"
#include "CLevelMgr.h"

#include "CAssetMgr.h"

#include "CLevel.h"
#include "CGameObject.h"
#include "components.h"

#include "CPlayerScript.h"
#include "CCameraMoveScript.h"


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

	// Camera Object 생성
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);

	pCamObj->Camera()->SetCameraPriority(0); // 메인 카메라로 설정

	m_CurLevel->AddObject(0, pCamObj);


	// Player 오브젝트 생성
	CGameObject* pObject = new CGameObject;
	pObject->SetName(L"Player");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CPlayerScript);
		
	pObject->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	pObject->Transform()->SetRelativeScale(100.f, 100.f, 0.5f);

	pObject->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObject->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));	

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
