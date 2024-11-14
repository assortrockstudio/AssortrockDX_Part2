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
	// Shift 속도 배율
	float Speed = m_Speed;
	if (KEY_PRESSED(KEY::LSHILFT))
	{
		Speed *= 4.f;
	}

	// 키 입력에 따른 위치이동
	Vec3 vCurPos = Transform()->GetRelativePos();

	Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);

	if (KEY_PRESSED(KEY::W))
	{
		vCurPos += vFront * Speed * DT;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vCurPos += -vFront * Speed * DT;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vCurPos += -vRight * DT * Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vCurPos += vRight * DT * Speed;
	}

	if (KEY_PRESSED(KEY::RBTN))
	{
		Vec2 vDrag = CKeyMgr::GetInst()->GetMouseDrag();		

		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot.y += vDrag.x * DT * XM_PI * 20.f;
		vRot.x -= vDrag.y * DT * XM_PI * 20.f;

		Transform()->SetRelativeRotation(vRot);
	}

	GetOwner()->Transform()->SetRelativePos(vCurPos);
}