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

	// 오브젝트의 방향정보 계산
	m_RelativeDir[(UINT)DIR_TYPE::RIGHT]	= XAxis;
	m_RelativeDir[(UINT)DIR_TYPE::UP]		= YAxis;
	m_RelativeDir[(UINT)DIR_TYPE::FRONT]	= ZAxis;

	for (int i = 0; i < 3; ++i)
	{		
		m_RelativeDir[i] = XMVector3TransformNormal(m_RelativeDir[i], matRot);
		m_RelativeDir[i].Normalize();
	}
}

void CTransform::Binding()
{
	// SysMem -> GPU
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
		
	g_Trans.matWorld = m_matWorld;

	pCB->SetData(&g_Trans);
	pCB->Binding();
}