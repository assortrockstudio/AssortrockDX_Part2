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

	Matrix matScale = XMMatrixIdentity();
	matScale._11 = m_RelativeScale.x;
	matScale._22 = m_RelativeScale.y;
	matScale._33 = m_RelativeScale.z;

	Matrix matZRot = XMMatrixIdentity();
	matZRot._11 = cosf(m_RelativeRotation.z);	matZRot._12 = sinf(m_RelativeRotation.z);
	matZRot._21 = -sinf(m_RelativeRotation.z);	matZRot._22 = cosf(m_RelativeRotation.z);	

	Matrix matTranslation = XMMatrixIdentity();
	matTranslation._41 = m_RelativePos.x;
	matTranslation._42 = m_RelativePos.y;
	matTranslation._43 = m_RelativePos.z;

	m_matWorld = matScale * matZRot * matTranslation;
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