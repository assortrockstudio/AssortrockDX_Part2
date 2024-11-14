#include "pch.h"
#include "CGameObject.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CComponent.h"
#include "CRenderComponent.h"
#include "CScript.h"


CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_LayerIdx(-1)
{
}

CGameObject::~CGameObject()
{
	Safe_Del_Array(m_arrCom);
	Safe_Del_Vector(m_vecScripts);
}

void CGameObject::begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if(nullptr != m_arrCom[i])
			m_arrCom[i]->begin();
	}

	for (size_t i = 0; i < m_vecScripts.size(); ++i)
	{
		m_vecScripts[i]->begin();
	}


	// �ڽ� ������Ʈ begin ȣ��
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->begin();
	}
}

void CGameObject::tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->tick();
	}

	for (size_t i = 0; i < m_vecScripts.size(); ++i)
	{
		m_vecScripts[i]->tick();
	}

	// �ڽ� ������Ʈ tick ȣ��
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->tick();
	}
}

void CGameObject::finaltick()
{
	// Component finaltick ȣ��
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->finaltick();
	}

	// �Ҽ� Layer�� �ڽ��� ���
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLayer = pCurLevel->GetLayer(m_LayerIdx); 
	pLayer->RegisterObject(this);


	// �ڽ� ������Ʈ finaltick ȣ��
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->finaltick();
	}
}

void CGameObject::render()
{
	if (m_RenderCom)
	{
		m_RenderCom->render();
	}
}

void CGameObject::AddComponent(CComponent* _Component)
{
	// �Է����� ������ ������Ʈ�� Ÿ���� Ȯ���Ѵ�.
	COMPONENT_TYPE type = _Component->GetComponentType();

	// �Էµ� ������Ʈ�� Script ������ ���
	if (COMPONENT_TYPE::SCRIPT == type)
	{
		m_vecScripts.push_back((CScript*)_Component);
	}

	else
	{
		// �Է����� ���� ������Ʈ�� �̹� ������ �ִ� ���
		assert(!m_arrCom[(UINT)type]);

		// �Էµ� ������Ʈ�� ������ ���� ������Ʈ���� Ȯ��
		CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(_Component);
		if (nullptr != pRenderCom)
		{
			// �̹� ������ ���� ������Ʈ�� ������ ���
			assert(!m_RenderCom);

			m_RenderCom = pRenderCom;
		}

		// �Էµ� ������Ʈ�� �迭�� �˸��� �ε��� �ڸ��� �ּҰ��� ����Ѵ�.
		m_arrCom[(UINT)type] = _Component;
	}

	// ������Ʈ�� ���� ������Ʈ�� �������� �˸�
	_Component->m_Owner = this;
}


void CGameObject::AddChild(CGameObject* _Object)
{
	_Object->m_Parent = this;
	m_vecChild.push_back(_Object);
}