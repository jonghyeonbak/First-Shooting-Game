#pragma once
#include "Obj.h"
class CWarm_Bullet :
	public CObj
{
public:
	CWarm_Bullet();
	virtual ~CWarm_Bullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;

	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	POINTFLOAT		m_tCenterPos;					// �������� ȸ���� ���� ���� ��ǥ
	float			m_fRevolutionAngle;				// ȸ������
	float			m_fCenterSpeed;					// ���� �ӵ�
	bool			m_bStart;						// ȸ���� �����ߴ��� Ȯ���ϴ� bool ����

};

