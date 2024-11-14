#include "pch.h"
#include "CMaterial.h"

#include "CDevice.h"
#include "CConstBuffer.h"

#include "CGraphicShader.h"


CMaterial::CMaterial()
	: CAsset(ASSET_TYPE::MATERIAL)
{
	m_Const.iArr[0] = 2;
}

CMaterial::~CMaterial()
{

}


void CMaterial::Binding()
{
	if (nullptr != m_Shader.Get())
		m_Shader->Binding();

	CConstBuffer* pMtrlCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pMtrlCB->SetData(&m_Const);
	pMtrlCB->Binding();
}