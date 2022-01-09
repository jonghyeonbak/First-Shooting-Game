#pragma once
#ifndef  __DEFAULTBULLET_H__
#define	 __DEFAULTBULLET_H__

#include "Bullet.h"
class CDefaultBullet : public CBullet
{
public:
	CDefaultBullet();
	virtual ~CDefaultBullet();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;

	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void CDefaultBullet::Set_Size(float _fCX, float _fCY);
	void CDefaultBullet::Set_Speed(float _fSpeed);
};

#endif // ! __DEFAULTBULLET_H__
