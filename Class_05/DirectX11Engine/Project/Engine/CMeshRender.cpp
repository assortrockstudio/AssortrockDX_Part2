#include "pch.h"
#include "CMeshRender.h"

#include "CTransform.h"

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
	GetShader()->Biding();

	// ����� �ؽ��� ���ε�
	GetTexture()->Binding(0);

	// �޽� ���ε� �� ������
	GetMesh()->render();
}