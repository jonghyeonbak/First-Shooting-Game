#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;									// 전역변수는 전역에서 초기화해야 함
int			CObjMgr::m_count = 0;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
}
void CObjMgr::Set_Collision(OBJID::ID _eID, OBJID::ID _eID2)				// 충돌함수 세팅, 매개변수 OBJID 대상 1, 2
{
	CCollisionMgr::Collision_Sphere(m_ObjList[_eID], m_ObjList[_eID2]);		// 구 모양의 충돌함수, 매개변수 OBJID 대상 1, 2
}

CObj* CObjMgr::Get_Target(OBJID::ID _eID, CObj* pObj)						// 타겟 얻어오는 함수, OBJID 대상 1, CObj* 형 변수 1
{
	CObj*		pTarget = nullptr;											// CObj* 형 변수 선언과 동시에 null 초기화

	float		fDistance = 0.f;											// 거리 0으로 초기화

	for (auto& iter : m_ObjList[_eID])										// m_ObjList의 OBJID n번째 정보를 iter에 복사
	{
		float fWidth = iter->Get_Info().fX - pObj->Get_Info().fX;			// 밑변 = 대상 1의 중점좌표 x - 대상 2의 중점좌표 x
		float fHeight = iter->Get_Info().fY - pObj->Get_Info().fY;			// 높이 = 대상 1의 중점좌표 y - 대상 2의 중점좌표 y

		float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);		// 대각선 = 제곱근(밑변*밑변 + 높이*높이)

		if (fDistance > fDiagonal || !pTarget)								// 거리가 대각선보다 크거나 타겟이 없을 경우
		{
			pTarget = iter;													// iter를 타겟에 대입
			fDistance = fDiagonal;											// 거리에 대각선을 대입
		}
	}
	
	return pTarget;															// 타겟을 반환
}

CObj * CObjMgr::Get_Object(OBJID::ID _eID)									// 타겟을 얻어오는 함수, 매개변수 OBJID의 대상 1, 반환형 CObj*
{
	CObj* pObj = m_ObjList[_eID].front();									// m_ObjList[n번]의 첫 번째 원소를 CObj*형 변수 pObj에 대입
	return pObj;															// pObj를 반환
}

void CObjMgr::Add_Object(OBJID::ID eID, CObj* pObj)							// 객체를 추가하는 함수, 매개변수 OBJID의 대상1, CObj*형 대상 1
{
	m_ObjList[eID].push_back(pObj);											// m_ObjList[n번]에 pOBJ를 원소로 뒤에서 삽입
}

int CObjMgr::Update(void)													// 인스턴스 삭제를 업데이트 부분에서 하기로 약속
{
	for (int i = 0; i < OBJID::END; ++i)									// OBJID의 마지막 정보에 도달할 때 까지
	{
		auto& iter = m_ObjList[i].begin();									// m_ObjList[i번째]의 시작 원소를 iter에 복사
		for (; iter != m_ObjList[i].end(); )								// m_ObjList[i번째]의 마지막원소에 도달할때 까지
		{
			int	iEvent = (*iter)->Update();									// iter의 update 함수를 호출한 후 iEvent 변수에 대입
			if (OBJ_DEAD == iEvent)											// iEvent가 obj_dead라면, update들에 obj_deaad or obj_life가 정의되어 있음
			{	
				Safe_Delete(*iter);											// iter를 안전하게 삭제
				iter = m_ObjList[i].erase(iter);							// m_ObjList[i번째]의 중간삭제(iter부분)
			}
			else
				++iter;														// iEvent가 obj_life라면 iter++ 
																			// 결국 객체가 살아있으면 다음 단계, 죽어있으면 메모리도 해제
		}
	}
	
	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJID::END; ++i)									// OBJID의 마지막 정보에 도달할때 까지
	{
		for (auto& iter : m_ObjList[i])										// m_ObjList[i 번째]정보를 iter에 복사
			iter->Late_Update();											// iter의 late_update 함수 호출
	}

	// 총알 맞은 몬스터 삭제
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
	// Hp 다운 실험
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::UFO_BULLET], 50);
	CCollisionMgr::Collision_Player2(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::UFO], 50);
	
	/////////////////////////////////////////////////////////////////////////////////////
	// MONSTER_CARRIER
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::MONSTER_CARRIER], m_ObjList[OBJID::DEFAULTBULLET], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::MONSTER_CARRIER], m_ObjList[OBJID::BLADESHIELD], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::ENERGYWAVE], m_ObjList[OBJID::MONSTER_CARRIER], 50);

	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_CARRIER]);
	// Hp 다운 실험
	CCollisionMgr::Collision_Player2(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_CARRIER], 50);

	/////////////////////////////////////////////////////////////////////////////////////
	// MONSTER_GUIDED
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::MONSTER_GUIDED], m_ObjList[OBJID::DEFAULTBULLET], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::MONSTER_GUIDED], m_ObjList[OBJID::BLADESHIELD], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::ENERGYWAVE], m_ObjList[OBJID::MONSTER_GUIDED], 50);

	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_GUIDED]);
	// Hp 다운 실험 
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_GUIDED], 50);
	
	/////////////////////////////////////////////////////////////////////////////////////  
	// MONSTER_KF15
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::MONSTER_KF15], m_ObjList[OBJID::DEFAULTBULLET], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::MONSTER_KF15], m_ObjList[OBJID::BLADESHIELD], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::ENERGYWAVE], m_ObjList[OBJID::MONSTER_KF15], 50);

	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::BULLET], m_ObjList[OBJID::MONSTER_KF15]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_KF15]);
	//CCollisionMgr::Collision_Att(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_KF15]);
	
	// Hp 다운 실험
	CCollisionMgr::Collision_Player2(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER_KF15], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::KF15_BULLET], 50);

	/////////////////////////////////////////////////////////////////////////////////////
	// MONSTER_TANK
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::TANK], m_ObjList[OBJID::DEFAULTBULLET], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::TANK], m_ObjList[OBJID::BLADESHIELD], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::ENERGYWAVE], m_ObjList[OBJID::TANK], 0);

	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::TANK]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::TANK_BULLET], m_ObjList[OBJID::PLAYER]);
	
	// Hp 다운 실험
	CCollisionMgr::Collision_Player2(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::TANK], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::TANK_BULLET], 50);
	
	/////////////////////////////////////////////////////////////////////////////////////

	// 애벌레
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::WARM], m_ObjList[OBJID::DEFAULTBULLET], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::WARM], m_ObjList[OBJID::BLADESHIELD], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::ENERGYWAVE], m_ObjList[OBJID::WARM], 50);

	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::WARM]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::WARM_BULLET], m_ObjList[OBJID::PLAYER]);

	// Hp 다운 실험
	CCollisionMgr::Collision_Player2(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::WARM], 50);
	CCollisionMgr::Collision_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::WARM_BULLET], 50);
	
}

void CObjMgr::Render(HDC m_DC)		// 그리기 함수
{
	for (int i = 0; i < OBJID::END; ++i)		// objid의 마지막 정보에 도달할 때 까지
	{
		for (auto& iter : m_ObjList[i])			// m_ObjList[i번째]정보를 iter에 저장
			iter->Render(m_DC);					// iter의 랜더함수 호출
	}
}

void CObjMgr::Release(void)			// 소멸 함수
{
	for (int i = 0; i < OBJID::END; ++i)		// objid의 마지막 정보에 도달할 때 까지
	{	
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj());	// for_each = 컨테이너를 순회하면서 원소들을 조건자에 전달하면 단순 수행한다.
		m_ObjList[i].clear();					// m_ObjList[i번째]원소를 다 지워라
	}
}
