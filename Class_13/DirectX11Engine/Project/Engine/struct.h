#pragma once

// 정점
// 3D 공간의 좌표를 나타내는 단위 
struct Vtx
{	
	Vec3	vPos;
	Vec4	vColor;
	Vec2	vUV;
};


// 디버그 렌더 요청 정보
struct tDebugShapeInfo
{
	DEBUG_SHAPE		Shape;
	Vec3			Position;
	Vec3			Scale;
	Vec3			Rotation;
	Matrix			matWorld;
	Vec4			Color;
	float			Duration;
	float			Age;
};






// 상수버퍼 관련 구조체
struct tTransform
{
	Matrix	matWorld;
	Matrix	matView;
	Matrix  matProj;
};
extern tTransform g_Trans;


struct tMtrlConst
{
	int		iArr[4];
	float	fArr[4];
	Vec2	v2Arr[4];
	Vec4	v4Arr[4];
	Matrix	matArr[4];
};