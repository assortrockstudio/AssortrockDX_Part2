#include "pch.h"
#include "CCollider2D.h"

#include "CTransform.h"
#include "CScript.h"

CCollider2D::CCollider2D()
	: CComponent(COMPONENT_TYPE::COLLIDER2D)
	, m_Scale(Vec3(1.f, 1.f, 1.f))
	, m_Absolute(false)
{

}

CCollider2D::~CCollider2D()
{

}

void CCollider2D::finaltick()
{
	// 최종 위치값을 계산
	Vec3 vObjPos = Transform()->GetRelativePos();
	m_FinalPos = vObjPos + m_Offset;

	if (false == m_Absolute)
	{
		Matrix matScale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		Matrix matRot = XMMatrixRotationZ(m_Rotation.z);
		Matrix matTrans = XMMatrixTranslation(m_Offset.x, m_Offset.y, m_Offset.z);

		m_matColWorld = matScale * matRot * matTrans;
		m_matColWorld *= Transform()->GetWorldMat();
	}
	else
	{
		Matrix matScale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		Matrix matRot = XMMatrixRotationZ(m_Rotation.z);
		Matrix matTrans = XMMatrixTranslation(m_Offset.x, m_Offset.y, m_Offset.z);

		m_matColWorld = matScale * matRot * matTrans;

		Matrix matObjScaleInv = XMMatrixIdentity();
		Vec3 vObjScale = Transform()->GetRelativeScale();
		matObjScaleInv = XMMatrixScaling(vObjScale.x, vObjScale.y, vObjScale.z);
		matObjScaleInv = XMMatrixInverse(nullptr, matObjScaleInv);

		m_matColWorld = m_matColWorld * matObjScaleInv * Transform()->GetWorldMat();
	}

	DrawDebugRect(m_matColWorld, Vec4(0.f, 1.f, 0.f, 1.f), 0.f);
}

void CCollider2D::BeginOverlap(CCollider2D* _OtherCollider)
{
	const vector<CScript*>& vecScripts = GetOwner()->GetScripts();

	for (size_t i = 0; i < vecScripts.size(); ++i)
	{
		vecScripts[i]->BeginOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
	}
}

void CCollider2D::Overlap(CCollider2D* _OtherCollider)
{
	const vector<CScript*>& vecScripts = GetOwner()->GetScripts();

	for (size_t i = 0; i < vecScripts.size(); ++i)
	{
		vecScripts[i]->Overlap(this, _OtherCollider->GetOwner(), _OtherCollider);
	}
}

void CCollider2D::EndOverlap(CCollider2D* _OtherCollider)
{
	const vector<CScript*>& vecScripts = GetOwner()->GetScripts();

	for (size_t i = 0; i < vecScripts.size(); ++i)
	{
		vecScripts[i]->EndOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
	}
}
