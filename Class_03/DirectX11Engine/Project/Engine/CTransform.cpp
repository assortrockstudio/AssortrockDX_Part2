#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, m_RelativeScale(Vec3(1.f, 1.f, 1.f))
{
}

CTransform::~CTransform()
{
}

void CTransform::finaltick()
{
	m_matWorld = XMMatrixIdentity();

	m_matWorld._11 = m_RelativeScale.x;
	m_matWorld._22 = m_RelativeScale.y;
	m_matWorld._33 = m_RelativeScale.z;

	m_matWorld._41 = m_RelativePos.x;
	m_matWorld._42 = m_RelativePos.y;
	m_matWorld._43 = m_RelativePos.z;
}

void CTransform::Binding()
{
	// SysMem -> GPU
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);

	tTransform trans = {};
	trans.matWorld = m_matWorld;

	pCB->SetData(&trans);
	pCB->Binding();
}