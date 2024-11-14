#include "pch.h"
#include "CAssetMgr.h"

#include "CPathMgr.h"

void CAssetMgr::init()
{
	CreateDefaultMesh();

	CreateDefaultTexture();

	CreateDefaultGraphicShader();

	CreateDefaultComputeShader();

	CreateDefaultMaterial();
}

void CAssetMgr::CreateDefaultMesh()
{
	Ptr<CMesh> pMesh = nullptr;

	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;

	// =========
	// Rect Mesh
	// =========
	// 0 -- 1
	// | \  |
	// 3 -- 2
	v.vPos = Vec3(-0.5, 0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUV = Vec2(1.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	v.vUV = Vec2(1.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 1.f);
	vecVtx.push_back(v);

	// Index Buffer
	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset<CMesh>(L"RectMesh", pMesh);

	vecVtx.clear();
	vecIdx.clear();

	// ===========
	// Circle Mesh
	// ===========
	// 원점을 vector 에 넣는다.
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(v);

	float Radius = 0.5f;
	UINT Slice = 60;
	float AngleStep = (2 * XM_PI) / Slice;

	float Angle = 0.f;
	for (UINT i = 0; i <= Slice; ++i)
	{
		v.vPos = Vec3(cosf(Angle) * Radius, sinf(Angle) * Radius, 0.f);
		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
		vecVtx.push_back(v);

		Angle += AngleStep;
	}

	for (UINT i = 0; i < Slice; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset<CMesh>(L"CircleMesh", pMesh);
	vecVtx.clear();
	vecIdx.clear();
}

void CAssetMgr::CreateDefaultTexture()
{
	Load<CTexture>(L"texture\\Character.png", L"texture\\Character.png");
	Load<CTexture>(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp");	
}


void CAssetMgr::CreateDefaultGraphicShader()
{
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	Ptr<CGraphicShader> pShader = nullptr;
	
	// ===========
	// Std2DShader
	// ===========
	pShader = new CGraphicShader;
	pShader->CreateVertexShader(strPath + L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(strPath + L"shader\\std2d.fx", "PS_Std2D");
	pShader->SetRSType(RS_TYPE::CULL_NONE);

	AddAsset<CGraphicShader>(L"Std2DShader", pShader);

	// ================
	// DebugShapeShader
	// ================
	pShader = new CGraphicShader;
	pShader->CreateVertexShader(strPath + L"shader\\debug_shape.fx", "VS_DebugShape");
	pShader->CreatePixelShader(strPath + L"shader\\debug_shape.fx", "PS_DebugShape");
	pShader->SetRSType(RS_TYPE::CULL_NONE);

	AddAsset<CGraphicShader>(L"DebugShapeShader", pShader);
}

void CAssetMgr::CreateDefaultComputeShader()
{
}


void CAssetMgr::CreateDefaultMaterial()
{
	Ptr<CMaterial> pMtrl = nullptr;

	// Std2DMtrl
	pMtrl = new CMaterial;
	pMtrl->SetName(L"Std2DMtrl");
	pMtrl->SetShader(FindAsset<CGraphicShader>(L"Std2DShader"));
	AddAsset<CMaterial>(pMtrl->GetName(), pMtrl);

	// DebugShapeMtrl
	pMtrl = new CMaterial;
	pMtrl->SetName(L"DebugShapeMtrl");
	pMtrl->SetShader(FindAsset<CGraphicShader>(L"DebugShapeShader"));
	AddAsset<CMaterial>(pMtrl->GetName(), pMtrl);	
}