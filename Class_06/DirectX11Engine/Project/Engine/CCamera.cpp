#include "pch.h"
#include "CCamera.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CRenderComponent.h"

#include "CRenderMgr.h"
#include "CTransform.h"

#include "CDevice.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_CamPriority(-1)
	, m_Far(1000.f)
{
}

CCamera::~CCamera()
{
}

void CCamera::finaltick()
{
	// View 행렬 계산
	Vec3 vCamWorldPos = GetOwner()->Transform()->GetRelativePos();
	m_matView = XMMatrixTranslation(-vCamWorldPos.x, -vCamWorldPos.y, -vCamWorldPos.z);

	// Proj 행렬 계산
	Vec2 vRenderResol = CDevice::GetInst()->GetRenderResolution();
	float AspectRatio = vRenderResol.x / vRenderResol.y;
	m_matProj = XMMatrixPerspectiveFovLH((XM_PI / 3.f), AspectRatio, 1.f, m_Far);
}

void CCamera::render()
{
	g_Trans.matView = m_matView;
	g_Trans.matProj = m_matProj;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);
		pLayer->render();
	}
}

void CCamera::SetCameraPriority(int _Priority)
{
	m_CamPriority = _Priority;

	if (0 <= m_CamPriority)
	{
		CRenderMgr::GetInst()->RegisterCamera(this, m_CamPriority);
	}
}