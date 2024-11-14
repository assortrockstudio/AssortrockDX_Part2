#include "pch.h"

#include "CDbgRenderMgr.h"

void DrawDebugRect(Vec3 _WorldPos, Vec3 _WorldScale, Vec3 _WorldRotation, Vec4 _vColor, float _Duration)
{
	tDebugShapeInfo info = {};
	info.Shape = DEBUG_SHAPE::RECT;

	info.Position = _WorldPos;
	info.Scale = _WorldScale;
	info.Rotation = _WorldRotation;
	info.matWorld = XMMatrixIdentity();
	info.Color = _vColor;
	info.Duration = _Duration;
	info.Age = 0.f;

	CDbgRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void DrawDebugRect(Matrix _matWorld, Vec4 _vColor, float _Duration)
{
	tDebugShapeInfo info = {};

	info.Shape = DEBUG_SHAPE::RECT;
	info.matWorld = _matWorld;
	info.Color = _vColor;
	info.Duration = _Duration;
	info.Age = 0.f;

	CDbgRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void DrawDebugCircle(Vec3 _WorldPos, float _Radius, Vec4 _vColor, float _Duration)
{
	tDebugShapeInfo info = {};
	info.Shape = DEBUG_SHAPE::CIRCLE;

	info.Position = _WorldPos;
	info.Scale = Vec3(_Radius * 2.f, _Radius * 2.f, 1.f);	
	info.matWorld = XMMatrixIdentity();

	info.Color = _vColor;
	info.Duration = _Duration;
	info.Age = 0.f;

	CDbgRenderMgr::GetInst()->AddDebugShapeInfo(info);
}
