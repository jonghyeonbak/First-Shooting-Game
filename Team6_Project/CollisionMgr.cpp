#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Player.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}
void CCollisionMgr::Collision_Player(list<CObj*> _Dest, list<CObj*> _Src, int _Damage)		// 두 물체 충돌 함수, 플레이어는 데미지 입음, 상대는 삭제
{

	for (auto& Dest : _Dest)											// 대상 1의 정보를 Dest에 복사
	{
		for (auto& Src : _Src)											// 대상 2의 정보를 Src에 복사
		{
			if (Check_Sphere(Dest, Src))								// 구 모양의 두 물체가 충돌했는지 확인하는 함수
			{
				static_cast<CPlayer*>(Dest)->Set_Hp(_Damage);			// CObj형 변수를 CPlayer형으로 변환 후 set_hp 함수를 이용해 데미지를 입힌다.
				Src->Set_Dead();										// 상대는 삭제
			}
		}
	}
}
void CCollisionMgr::Collision_Player2(list<CObj*> _Dest, list<CObj*> _Src, int _Damage)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dest, Src))
			{
				static_cast<CPlayer*>(Dest)->Set_Hp(_Damage);
				
			}
		}
	}
}
void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Src->Get_Rect())))		// intersectrect 함수로 충돌 확인
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src)	// 사각형 모양의 두 물체가 충돌하면 상대를 밀어내는 함수
{

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			float	fWidth = 0.f, fHeight = 0.f;							// 밑변, 높이 변수 선언과 동시에 0으로 초기화

			if (Check_Rect(Dest, Src, &fWidth, &fHeight))					// 사각형 충돌 확인 함수, 대상1, 2, 밑변, 높이
			{
				// 상 하 충돌
				if (fWidth > fHeight)										// 밑변이 높이보다 클 경우
				{
						//하 충돌
					if (Dest->Get_Info().fY < Src->Get_Info().fY)			// 대상 1의 중점 y보다 대상 2의 중점 y가 클 경우
					{
						Src->Set_PosY(fHeight);								// 대상 2를 아래 방향으로 높이만큼 이동
					}
					else
						// 상 충돌
						Src->Set_PosY(-fHeight);							// 대상 2를 위쪽 방향으로 높이만큼 이동
				}

				//  좌 우 충돌
				else
				{		// 우 충돌
					if (Dest->Get_Info().fX < Src->Get_Info().fX)			// 대상 1의 중점 x보다 대상 2의 중점 x가 클 경우
					{
						Src->Set_PosX(fWidth);								// 대상 2를 오른쪽 방향으로 밑변 만큼 이동
					}
					else
						// 좌 충돌
						Src->Set_PosX(-fWidth);								// 대상 2를 왼쪽 방향으로 밑변 만큼 이동
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src)	// 구 모양의 두 물체 충돌
{

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dest, Src))
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSrc)									// 구 모양의 두 물체 충돌 확인 함수
{
	float		fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);					// 밑변 = 절댓값(대상1의 중점x - 대상 2의 중점x)
	float		fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);					// 높이 = 절댓값(대상1의 중점y - 대상 2의 중점y)

	float		fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);						// 거리 = 제곱근(밑변*밑변 + 높이*높이)

	float		fRadius = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;			// 반지름 = (대상1의 가로사이즈 + 대상2의 가로사이즈) / 2

	return fRadius > fDistance;																// 반지름이 거리보다 클 경우 (충돌이므로 1반환)
}

bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSrc, float* _pWidth, float* _pHeight)		// 플레이어 정보, 몬스터 정보, 가로세로 0
{
	float		fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);						// 밑변 = 절댓값(대상1의 중점x - 대상 2의 중점x)
	float		fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);						// 높이 = 절댓값(대상1의 중점y - 대상 2의 중점y)

	float		fCX = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;					// 두 개의 사각형(플레이어와 몬스터)의 반지름을 더한 값
	float		fCY = (pDest->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;					// 두 개의 사각형((플레이어와 몬스터)의 반지름을 더한 값

	if (fCX > fWidth && fCY > fHeight)					// 두 물체의 반지름을 더한 후 2로 나눈 것보다 밑변이 크고, 다른 조건도 만족할 경우
	{
		*_pWidth = fCX - fWidth;						// p_width = 사이즈 - 밑변
		*_pHeight = fCY - fHeight;

		return true;									// 참 반환
	}

	return false;										// 거짓 반환
}
