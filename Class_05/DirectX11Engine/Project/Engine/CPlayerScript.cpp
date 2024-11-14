#include "pch.h"
#include "CPlayerScript.h"

CPlayerScript::CPlayerScript()
	: m_Speed(1.f)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::tick()
{
	// Ű �Է¿� ���� ��ġ�̵�
	Vec3 vCurPos = GetOwner()->Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		vCurPos.y += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vCurPos.y -= DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vCurPos.x -= DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vCurPos.x += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::Z))
	{
		Vec3 vRot = GetOwner()->Transform()->GetRelativeRotation();
		vRot.z += DT * XM_PI;
		GetOwner()->Transform()->SetRelativeRotation(vRot);
	}



	GetOwner()->Transform()->SetRelativePos(vCurPos);
}