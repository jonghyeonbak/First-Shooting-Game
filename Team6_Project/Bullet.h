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
	void		 Set_Target(void);			//  Ÿ���� ����

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

protected:
	BULLET::DIR		m_eDir;				// �Ѿ��� ������ ��� ����
	POINT			m_tTarget;			// Ÿ�� ���콺 ��ǥ

};

#endif // !__BULLET_H__

