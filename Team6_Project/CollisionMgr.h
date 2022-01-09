#pragma once
#ifndef __COLLISIONMGR_H__
#define __COLLISIONMGR_H__

class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src);		// 사각형 모양의 두 물체 충돌 함수
	static void	Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src);		// 사각형 모양의 두 물체가 부딪히면 상대를 밀어내는 함수
	static void	Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src);		// 구 모양의 두 물체 충돌 함수

	static void CCollisionMgr::Collision_Player(list<CObj*> _Dest, list<CObj*> _Src, int _Damage);	// 두 물체가 부딪히면 플레이어는 데미지 감소, 상대는 삭제
	static void CCollisionMgr::Collision_Player2(list<CObj*> _Dest, list<CObj*> _Src, int _Damage);

private:
	static bool Check_Sphere(CObj* pDest, CObj* pSrc);		// 구 모양의 두 물체 충돌 확인 함수
	static bool Check_Rect(CObj* pDest, CObj* pSrc, float* _pWidth, float* _pHeight);	// 사각형 모양의 두 물체 충돌 확인 함수

};

#endif // 
