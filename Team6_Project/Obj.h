#pragma once
#ifndef __OBJ_H__
#define __OBJ_H__					// ��ü�� ����� �������� ��Ƴ��� Ŭ����

#include "Define.h"					
#include "Struct.h"
#include "Enum.h"

class CObj												// ���� Ŭ�������� �θ� Ŭ����
{
public:
	CObj();
	virtual ~CObj();									// ��ӹ޴� Ŭ������ �����Ƿ� �Ҹ��ڸ� �������� ����, ���� ���縦 ����

public:
	void			Set_Pos(float _fX, float _fY);		// ��� ��ǥ ����
	void			Set_Size(float _fCX, float _fCY);	// ��� ������ ����
	void			Set_Direction(BULLET::DIR _eDir);	// ����� �Ѿ� ���� ����
	void			Set_Dead(void);						// ����� ���̴� �Լ�
	void			Set_Hp(int _Damage);				// ����� hp�� ��������ŭ ���ҽ�Ű�� �Լ�
	void			Set_Angle(float _fAngle);			// ��� ���� ����
	void			Set_Target(CObj* _pTarget);			// Ÿ�� ����, ��ȯ CObj*�� ����
	void			Set_PosX(float _fX);				// ��� ���� ��ǥ x ����
	void			Set_PosY(float _fY);				// ��� ���� ��ǥ y ����
	void			Set_Speed(float _fSpeed);			// ��� ���ǵ� ����

	const INFO&		Get_Info(void) const { return m_tInfo; }	// INFO Ÿ���� info ������ ��� ��ȯ�ϴ� �Լ�, ������ ��� ���۷����� �����ϴ� ����
	const RECT&		Get_Rect(void) const { return m_tRect; }	// const�� �ٿ� �ڵ��� ������ ���

public:
	virtual void		Initialize(void)PURE;			// �θ� Ŭ������ �Լ�������, �ڽ� Ŭ�����鵵 ����� ���̹Ƿ�, ���� �����Լ�, �������̵�
	virtual int			Update(void)PURE;
	virtual void		Late_Update(void)PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release(void)PURE;

	void				Update_Rect(void);				// rect�� ������Ʈ�ϴ� �뵵�� �Լ�

protected:
	RECT			m_tRect;							// 4���� ��ǥ�� ������ �ִ� �簢�� ����ü
	RECT			m_tRect2;
	INFO			m_tInfo;							// struct�� �ִ� ����ü�� ������ ������ �ִ� ����
	INFO			m_tInfo2;
	float			m_fSpeed;							// ���ǵ�
	float			m_fAngle;							// ����
	float			m_fMaru_Angle;						// ���ּ��� ����
	float			m_fDistance;						// �Ÿ�
	float			m_fMaru_Distance;
	bool			m_bDead;							// ����� ���� ���� Ȯ�� bool ����
	BULLET::DIR		m_eDir;								// �Ѿ� ���� Ȯ�� ����
	CObj*			m_pTarget;							// Ÿ�� ����
	STATUS			m_tStat;							// ����� ü��, ���ݷ��� ��� ����

};

#endif // !__OBJ_H__
