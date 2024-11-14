#include "pch.h"
#include "CMeshRender.h"

#include "CTransform.h"
#include "CMaterial.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::finaltick()
{
}

void CMeshRender::render()
{
	// ������Ʈ�� ��ġ���� ������۸� ���ؼ� ���ε�
	GetOwner()->Transform()->Binding();

	// ����� ���̴� ���ε�
	GetMaterial()->Binding();
	
	// �޽� ���ε� �� ������
	GetMesh()->render();
}