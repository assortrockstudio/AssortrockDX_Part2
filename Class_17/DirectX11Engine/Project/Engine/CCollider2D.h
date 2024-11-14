#pragma once
#include "CComponent.h"

class CCollider2D :
    public CComponent
{
private:
    Vec3    m_Offset;   // ������ ������
    Vec3    m_FinalPos; // �浹ü�� ���� ��ġ ( Object Position + Collider offset )

    Vec3    m_Scale;    // ������Ʈ�κ��� ������� ����    
    Vec3    m_Rotation; // ������Ʈ�κ��� ������� ȸ��(����)

    bool    m_Absolute; // true �� ���, ������Ʈ�� ũ�⿡ ������ �����ʴ� ����(����)ũ��� ���

    Matrix  m_matColWorld;

public:
    void SetOffset(Vec3 _Offset) { m_Offset = _Offset; }
    void SetScale(Vec3 _Scale) { m_Scale = _Scale; }
    void SetRotationZ(float _Angle) { m_Rotation.z = _Angle; }

    Vec3 GetOffset() { return m_Offset; }
    Vec3 GetScale() { return m_Scale; }
    Vec3 GetFinalPos() { return m_FinalPos; }
    float GetRotationZ() { return m_Rotation.z; }

    void SetAbsolute(bool _Abs) { m_Absolute = _Abs; }
    bool IsAbsolute() { return m_Absolute; }

public:
    virtual void finaltick() override;

public:
    CCollider2D();
    ~CCollider2D();
};
