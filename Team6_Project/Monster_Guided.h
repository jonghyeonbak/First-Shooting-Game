#pragma once
#ifndef  __MONSTER_GUIDED_H__
#define  __MONSTER_GUIDED_H__

#include "Obj.h"
class CMonster_Guided : public CObj
{
public:
	CMonster_Guided();
	~CMonster_Guided();
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);
};

#endif // ! __MONSTER_GUIDED_H__
