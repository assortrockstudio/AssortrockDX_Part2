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

	Matrix matScale = XMMatrixScaling(m_RelativeScale.x, m_RelativeScale.y, m_RelativeScale.z);
	
	Matrix matRot = XMMatrixRotationX(m_RelativeRotation.x);
	matRot *= XMMatrixRotationY(m_RelativeRotation.y);
	matRot *= XMMatrixRotationZ(m_RelativeRotation.z);
	
	Matrix matTranslation = XMMatrixTranslation(m_RelativePos.x, m_RelativePos.y, m_RelativePos.z);

	m_matWorld = matScale * matRot * matTranslation;
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