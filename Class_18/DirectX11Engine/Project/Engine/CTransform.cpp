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
	m_WorldDir[(UINT)DIR_TYPE::RIGHT]	= m_RelativeDir[(UINT)DIR_TYPE::RIGHT]	= XAxis;
	m_WorldDir[(UINT)DIR_TYPE::UP]		= m_RelativeDir[(UINT)DIR_TYPE::UP]		= YAxis;
	m_WorldDir[(UINT)DIR_TYPE::FRONT]	= m_RelativeDir[(UINT)DIR_TYPE::FRONT]	= ZAxis;

	for (int i = 0; i < 3; ++i)
	{		
		m_RelativeDir[i] = XMVector3TransformNormal(m_RelativeDir[i], matRot);
		m_RelativeDir[i].Normalize();
	}

	// 부모 오브젝트가 있는 경우
	if (GetOwner()->GetParent())
	{
		const Matrix& matParentWorldMat = GetOwner()->GetParent()->Transform()->GetWorldMat();
		m_matWorld *= matParentWorldMat;

		for (int i = 0; i < 3; ++i)
		{
			m_WorldDir[i] = XMVector3TransformNormal(m_WorldDir[i], m_matWorld);
			m_WorldDir[i].Normalize();
		}
	}

	// 부모 오브젝트가 없는경우(본인이 최상위 부모 오브젝트)
	else
	{
		for (int i = 0; i < 3; ++i)
		{
			m_WorldDir[i] = m_RelativeDir[i];
		}
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