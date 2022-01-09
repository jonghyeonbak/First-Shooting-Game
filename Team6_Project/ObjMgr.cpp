#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;									// ���������� �������� �ʱ�ȭ�ؾ� ��
int			CObjMgr::m_count = 0;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
}
void CObjMgr::Set_Collision(OBJID::ID _eID, OBJID::ID _eID2)				// �浹�Լ� ����, �Ű����� OBJID ��� 1, 2
{
	CCollisionMgr::Collision_Sphere(m_ObjList[_eID], m_ObjList[_eID2]);		// �� ����� �浹�Լ�, �Ű����� OBJID ��� 1, 2
}

CObj* CObjMgr::Get_Target(OBJID::ID _eID, CObj* pObj)						// Ÿ�� ������ �Լ�, OBJID ��� 1, CObj* �� ���� 1
{
	CObj*		pTarget = nullptr;											// CObj* �� ���� ����� ���ÿ� null �ʱ�ȭ

	float		fDistance = 0.f;											// �Ÿ� 0���� �ʱ�ȭ

	for (auto& iter : m_ObjList[_eID])										// m_ObjList�� OBJID n��° ������ iter�� ����
	{
		float fWidth = iter->Get_Info().fX - pObj->Get_Info().fX;			// �غ� = ��� 1�� ������ǥ x - ��� 2�� ������ǥ x
		float fHeight = iter->Get_Info().fY - pObj->Get_Info().fY;			// ���� = ��� 1�� ������ǥ y - ��� 2�� ������ǥ y

		float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);		// �밢�� = ������(�غ�*�غ� + ����*����)

		if (fDistance > fDiagonal || !pTarget)								// �Ÿ��� �밢������ ũ�ų� Ÿ���� ���� ���
		{
			pTarget = iter;													// iter�� Ÿ�ٿ� ����
			fDistance = fDiagonal;											// �Ÿ��� �밢���� ����
		}
	}
	
	return pTarget;															// Ÿ���� ��ȯ
}

CObj * CObjMgr::Get_Object(OBJID::ID _eID)									// Ÿ���� ������ �Լ�, �Ű����� OBJID�� ��� 1, ��ȯ�� CObj*
{
	CObj* pObj = m_ObjList[_eID].front();									// m_ObjList[n��]�� ù ��° ���Ҹ� CObj*�� ���� pObj�� ����
	return pObj;															// pObj�� ��ȯ
}

void CObjMgr::Add_Object(OBJID::ID eID, CObj* pObj)							// ��ü�� �߰��ϴ� �Լ�, �Ű����� OBJID�� ���1, CObj*�� ��� 1
{
	m_ObjList[eID].push_back(pObj);											// m_ObjList[n��]�� pOBJ�� ���ҷ� �ڿ��� ����
}

int CObjMgr::Update(void)													// �ν��Ͻ� ������ ������Ʈ �κп��� �ϱ�� ���
{
	for (int i = 0; i < OBJID::END; ++i)									// OBJID�� ������ ������ ������ �� ����
	{
		auto& iter = m_ObjList[i].begin();									// m_ObjList[i��°]�� ���� ���Ҹ� iter�� ����
		for (; iter != m_ObjList[i].end(); )								// m_ObjList[i��°]�� ���������ҿ� �����Ҷ� ����
		{
			int	iEvent = (*iter)->Update();									// iter�� update �Լ��� ȣ���� �� iEvent ������ ����
			if (OBJ_DEAD == iEvent)											// iEvent�� obj_dead���, update�鿡 obj_deaad or obj_life�� ���ǵǾ� ����
			{	
				Safe_Delete(*iter);											// iter�� �����ϰ� ����
				iter = m_ObjList[i].erase(iter);							// m_ObjList[i��°]�� �߰�����(iter�κ�)
			}
			else
				++iter;														// iEvent�� obj_life��� iter++ 
																			// �ᱹ ��ü�� ��������� ���� �ܰ�, �׾������� �޸𸮵� ����
		}
	}
	
	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJID::END; ++i)									// OBJID�� ������ ������ �����Ҷ� ����
	{
		for (auto& iter : m_ObjList[i])										// m_ObjList[i ��°]������ iter�� ����
			iter->Late_Update();											// iter�� late_update �Լ� ȣ��
	}

	// �Ѿ� ���� ���� ����
	//CCollisionMgr::Collision_Rect(m_ObjList[OBJID::DEFAULTBULLET], m_ObjList[OBJID::MONSTER]);
	//CCollisionMgr::Collision_Rect(m_ObjList[OBJID::BLADESHIELD], m_ObjList[OBJID::MONSTER]);
	//CCollisionMgr::Collision_Rect(m_ObjList[OBJID::ENERGYWAVE], m_ObjList[OBJID::MONSTER]);

	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::BULLET], m_ObjList[OBJID::MONSTER]);
	//CCollisionMgr::Collision_RectEx(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER]);
	
	// UFO 
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::UFO], m_ObjList[OBJID::DEFAULTBULLET], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::UFO], m_ObjList[OBJID::BLADESHIELD], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::ENERGYWAVE], m_ObjList[OBJID::UFO], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::UFO], m_ObjList[OBJID::GUIDEMISSILE], 300);


	//CCollisionMgr::Collision_Rect(m_ObjList[OBJID::UFO_BULLET], m_ObjList[OBJID::PLAYER]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::UFO]);
	// Hp �ٿ� ����
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::UFO_BULLET], 50);
	CCollisionMgr::Collision_Player2(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::UFO], 50);
	
	/////////////////////////////////////////////////////////////////////////////////////
	// MONSTER_CARRIER
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::MONSTER_CARRIER], m_ObjList[OBJID::DEFAULTBULLET], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::MONSTER_CARRIER], m_ObjList[OBJID::BLADESHIELD], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::ENERGYWAVE], m_ObjList[OBJID::MONSTER_CARRIER], 50);

	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_CARRIER]);
	// Hp �ٿ� ����
	CCollisionMgr::Collision_Player2(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_CARRIER], 50);

	/////////////////////////////////////////////////////////////////////////////////////
	// MONSTER_GUIDED
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::MONSTER_GUIDED], m_ObjList[OBJID::DEFAULTBULLET], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::MONSTER_GUIDED], m_ObjList[OBJID::BLADESHIELD], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::ENERGYWAVE], m_ObjList[OBJID::MONSTER_GUIDED], 50);

	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_GUIDED]);
	// Hp �ٿ� ���� 
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_GUIDED], 50);
	
	/////////////////////////////////////////////////////////////////////////////////////  
	// MONSTER_KF15
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::MONSTER_KF15], m_ObjList[OBJID::DEFAULTBULLET], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::MONSTER_KF15], m_ObjList[OBJID::BLADESHIELD], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::ENERGYWAVE], m_ObjList[OBJID::MONSTER_KF15], 50);

	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::BULLET], m_ObjList[OBJID::MONSTER_KF15]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_KF15]);
	//CCollisionMgr::Collision_Att(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_KF15]);
	
	// Hp �ٿ� ����
	CCollisionMgr::Collision_Player2(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_KF15], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::KF15_BULLET], 50);

	/////////////////////////////////////////////////////////////////////////////////////
	// MONSTER_TANK
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::TANK], m_ObjList[OBJID::DEFAULTBULLET], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::TANK], m_ObjList[OBJID::BLADESHIELD], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::ENERGYWAVE], m_ObjList[OBJID::TANK], 0);

	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::TANK]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::TANK_BULLET], m_ObjList[OBJID::PLAYER]);
	
	// Hp �ٿ� ����
	CCollisionMgr::Collision_Player2(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::TANK], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::TANK_BULLET], 50);
	
	/////////////////////////////////////////////////////////////////////////////////////

	// �ֹ���
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::WARM], m_ObjList[OBJID::DEFAULTBULLET], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::WARM], m_ObjList[OBJID::BLADESHIELD], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::ENERGYWAVE], m_ObjList[OBJID::WARM], 50);

	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::WARM]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::WARM_BULLET], m_ObjList[OBJID::PLAYER]);

	// Hp �ٿ� ����
	CCollisionMgr::Collision_Player2(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::WARM], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::WARM_BULLET], 50);
	
}

void CObjMgr::Render(HDC m_DC)		// �׸��� �Լ�
{
	for (int i = 0; i < OBJID::END; ++i)		// objid�� ������ ������ ������ �� ����
	{
		for (auto& iter : m_ObjList[i])			// m_ObjList[i��°]������ iter�� ����
			iter->Render(m_DC);					// iter�� �����Լ� ȣ��
	}
}

void CObjMgr::Release(void)			// �Ҹ� �Լ�
{
	for (int i = 0; i < OBJID::END; ++i)		// objid�� ������ ������ ������ �� ����
	{	
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj());	// for_each = �����̳ʸ� ��ȸ�ϸ鼭 ���ҵ��� �����ڿ� �����ϸ� �ܼ� �����Ѵ�.
		m_ObjList[i].clear();					// m_ObjList[i��°]���Ҹ� �� ������
	}
}
