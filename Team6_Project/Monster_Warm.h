#pragma once
#include "Obj.h"

class CMonster_Warm :
	public CObj
{
public:
	CMonster_Warm();
	virtual ~CMonster_Warm();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void		Set_Bullet(list<CObj*>*  _pBullet);

private:
	DWORD					m_dwTime;
	int						m_iFPS;
	TCHAR					m_szFPS[256];

	POINT					m_tGun1;
	POINT					m_tGun2;
	CObj*					pObj = nullptr;
	list<CObj*>*			m_pBullet = nullptr;
};

