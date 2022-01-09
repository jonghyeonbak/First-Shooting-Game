#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include "Obj.h"
#include "Enum.h"

class CBullet : public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	void		 Set_Target(void);			//  타겟을 세팅

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

protected:
	BULLET::DIR		m_eDir;				// 총알의 방향을 담는 변수
	POINT			m_tTarget;			// 타겟 마우스 좌표

};

#endif // !__BULLET_H__

