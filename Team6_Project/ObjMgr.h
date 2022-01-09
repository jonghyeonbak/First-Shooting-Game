#pragma once
#ifndef  __OBJMGR_H__
#define  __OBJMGR_H__			// �̱���,            �̵���Ʈ ����
								// �ν��Ͻ��� 1��      m:n ���迡�� 1:n ����
#include "Define.h"				// ��ũ�� ��� �뵵
#include "Enum.h"				// OBJID ��� �뵵
#include "Struct.h"				// SafeDelete Ŭ���� ���ø� ��� �뵵
#include "CollisionMgr.h"		// �浹 �Լ�

class CObj;						// CObj Ŭ���� ��� ���� ���� ����
class CObjMgr					
{                            
private:						// �̱����� �����ڸ� �ϳ��� ȣ���ؾߵǴµ�, 
								// ���Ǹ� ���� private���� ������ ȣ���� ����
	CObjMgr();
	virtual		~CObjMgr();		// �Ƹ� ��ӹ޴� �ڽ� Ŭ������ ���� ��

public:
	CObj*		Get_Target(OBJID::ID _eID, CObj* pObj);			// Ÿ���� ������ �Լ�, �Ű����� OBJID�� n�� ��ü, CObj* Ÿ�� ����, ��ȯ CObj*
	CObj*		Get_Object(OBJID::ID _eID);						// ����� ������ �Լ�, �Ű����� OBJID�� n�� ��ü, ��ȯ CObj*
	void		Set_Collision(OBJID::ID _eID, OBJID::ID _eID2); // �浹�Լ� ����, �Ű����� OBJ n�� ��ü, n�� ��ü 2

public:
	void		Add_Object(OBJID::ID eID, CObj* pObj);			// ����� �߰��ϴ� �Լ�, 
	int			Update(void);		
	void		Late_Update(void);
	void		Render(HDC m_DC);								// ����� �׸��� �Լ�, HDC
	void		Release(void);

private:
	list<CObj*>		m_ObjList[OBJID::END];						// OBJID�� �����͵��� ��� �ִ� CObj*�� ����Ʈ�� m_ObjList ���� ����

public:
	static	CObjMgr*		Get_Instance(void)			// ���� �ϳ��� �ν��Ͻ� ����, static���� ������ �� ���� ���ο����� ���� ����
	{
		if (nullptr == m_pInstance)						// m_pInstance�� null�̶��
			m_pInstance = new CObjMgr;					// �ν��Ͻ�ȭ 

		return m_pInstance;								// m_pInstance ��ȯ
	}

	static	void		Destroy_Intance(void)			//  �ν��Ͻ� ����
	{
		if (nullptr != m_pInstance)						// m_pInstance�� null�� �ƴ϶��
		{
			delete m_pInstance;							// m_pInstance ����
			m_pInstance = nullptr;						// null �ʱ�ȭ
		}
	}

private:
	static CObjMgr*			m_pInstance;				// CObjMgr*�� ���� ����, �̱��� ������ �ν��Ͻ��� �ϳ��� ���� �� ����

public:
	static int				m_count;					// count�� ���� ���� ���� ����
};

#endif // ! __OBJMGR_H__
