#pragma once
#ifndef __MONSTER_CARRIER_H__
#define __MONSTER_CARRIER_H__

#include"Obj.h"

class CMonster_Carrier :public CObj
{
public:
	CMonster_Carrier();
	~CMonster_Carrier();
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

public:
	POINT			m_tGun;			// �� ��ǥ
	DWORD			Carrier_Time;   // �ð� ��� ����
	bool			m_Switch;		// ��
};

#endif // !__MONSTER_CARRIER_H__