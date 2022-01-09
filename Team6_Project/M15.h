#pragma once
#ifndef  __M15_H__
#define  __M15_H__

#include "Bullet.h"
class CM15: public CBullet
{
public:
	CM15();
	virtual ~CM15();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

#endif // ! __M15_H__
