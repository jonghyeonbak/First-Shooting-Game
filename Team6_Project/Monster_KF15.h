#pragma once
#include "Obj.h"
class CMonster_KF15 :
	public CObj
{
public:
	CMonster_KF15();
	virtual ~CMonster_KF15();

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

public:
	DWORD			m_tTime;
	POINT					m_tGun;
	float		m_fGun_Distance;
};

