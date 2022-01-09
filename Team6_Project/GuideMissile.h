#pragma once

#ifndef __GUIDEMISSILE_H__
#define __GUIDEMISSILE_H__

#include "Bullet.h"
class CGuideMissile : public CBullet
{
public:
	CGuideMissile();
	virtual ~CGuideMissile();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

#endif // !__GUIDEMISSILE_H__
