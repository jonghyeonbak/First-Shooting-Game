#pragma once
#ifndef  __SHOTGUN_BULLET_H__
#define  __SHOTGUN_BULLET_H__

#include "Obj.h"

class CShotgun_Bullet :
	public CObj
{
public:
	CShotgun_Bullet();
	virtual ~CShotgun_Bullet();

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);
};

#endif // ! __SHOTGUN_BULLET_H__
