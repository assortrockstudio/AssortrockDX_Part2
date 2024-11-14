#include "pch.h"
#include "CCameraMoveScript.h"

CCameraMoveScript::CCameraMoveScript()
	: m_Speed(200.f)
{
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::tick()
{
	// 키 입력에 따른 위치이동
	Vec3 vCurPos = Transform()->GetRelativePos();

	Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);

	if (KEY_PRESSED(KEY::W))
	{
		vCurPos += vFront * m_Speed * DT;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vCurPos += -vFront * m_Speed * DT;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vCurPos += -vRight * DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vCurPos += vRight * DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::Y))
	{
		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot.y += DT * XM_PI;
		Transform()->SetRelativeRotation(vRot);
	}

	GetOwner()->Transform()->SetRelativePos(vCurPos);
}