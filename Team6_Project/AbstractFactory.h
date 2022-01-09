#pragma once
#ifndef __ABSRACTFACTORY_H__
#define __ABSRACTFACTORY_H__			// �߻�ȭ ����

#include "Obj.h"
#include "Enum.h"

template<typename T>					// Ŭ���� ���ø� 
class CAbstractFactory					
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	// static �������� ���� �� ���� �������� ���� ����
	static CObj*		Create()		// ��ü�� �ν��Ͻ�ȭ �ϴ� �Լ�
	{
		CObj*		pObj = new T;		// CObj* Ÿ���� ������ �ν��Ͻ� ȭ 
		pObj->Initialize();				// pObj�� �̴ϼȶ����� �Լ� ȣ��

		return pObj;					// pObj ��ȯ
	}
	// ����� �߽� ��ǥ X,Y, �Ѿ��� ������ ������ �ִ� ��ü �ν��Ͻ�ȭ �ϴ� �Լ�
	static CObj*		Create(float _fX, float _fY, BULLET::DIR eDir = BULLET::UP)
	{
		CObj*		pObj = new T;		// ��ü�� �ν��Ͻ�ȭ �ϴ� �Լ�
		pObj->Initialize();				// pObj�� �̴ϼȶ����� �Լ� ȣ��
		pObj->Set_Pos(_fX, _fY);		// pObj�� �߽� ��ǥ ����
		pObj->Set_Direction(eDir);		// pObj�� �Ѿ� ���� ����

		return pObj;					// pObj ��ȯ
	}
	// ����� �߽� ��ǥ x,y, ������ ������ �ִ� ��ü �ν��Ͻ�ȭ �ϴ� �Լ�
	static CObj*		Create(float _fX, float _fY, float _Angle)
	{
		CObj*		pObj = new T;		// ��ü�� �ν��Ͻ�ȭ �ϴ� �Լ�
		pObj->Initialize();				// pObj�� �̴ϼȶ����� �Լ� ȣ��
		pObj->Set_Pos(_fX, _fY);		// pObj�� �߽� ��ǥ ����
		pObj->Set_Angle(_Angle);		// pObj�� ���� ����

		return pObj;					// pObj ��ȯ
	}
};

#endif