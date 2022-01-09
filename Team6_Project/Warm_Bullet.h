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
	POINTFLOAT		m_tCenterPos;					// 지렁이의 회오리 공격 중점 좌표
	float			m_fRevolutionAngle;				// 회전각도
	float			m_fCenterSpeed;					// 중점 속도
	bool			m_bStart;						// 회전을 시작했는지 확인하는 bool 변수

};

