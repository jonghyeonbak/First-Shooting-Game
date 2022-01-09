#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "Obj.h"
#include "Enum.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	void		Key_Input(void);				// Å° ¼³Á¤

private:
	POINT					m_tGun;
	POINT					m_tMaru[5];

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};

#endif // !__PLAYER_H__