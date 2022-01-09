#pragma once
#include "Obj.h"

#ifndef __MONSTER_TANK_H_
#define __MONSTER_TANK_H_


class CMonster_Tank :
	public CObj
{
public:
	CMonster_Tank();
	virtual ~CMonster_Tank();

public:
	void LookPlayer();
	//void ShootBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	POINT m_tGun;
	float m_fDown;
	float m_fDistance;
	DWORD dTimer;


};

#endif // !__MONSTERTANK_H_

class CMonster_TANK
{
public:
	CMonster_TANK();
	~CMonster_TANK();
};
