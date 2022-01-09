#pragma once

#ifndef __MONSTER_UFO_H__
#define __MONSTER_UFO_H__

#include "Obj.h"
class CMonster_UFO :
	public CObj
{
public:
	CMonster_UFO();
	virtual ~CMonster_UFO();
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

public:
	DWORD MonsterTime;
};

#endif // !__MONSTER_UFO_H__
