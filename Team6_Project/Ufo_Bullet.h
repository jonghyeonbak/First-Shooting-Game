#pragma once
#ifndef __UFO_BULLET_H__
#define __UFO_BULLET_H__

#include "Obj.h"
class CUfo_Bullet :
	public CObj
{
public:
	CUfo_Bullet();
	virtual ~CUfo_Bullet();

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);

	virtual void Render(HDC hDC);
	virtual void Release(void);
};

#endif // !__UFO_BULLET_H__
