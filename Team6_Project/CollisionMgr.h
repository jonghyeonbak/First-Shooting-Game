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
	static void	Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src);		// �簢�� ����� �� ��ü �浹 �Լ�
	static void	Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src);		// �簢�� ����� �� ��ü�� �ε����� ��븦 �о�� �Լ�
	static void	Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src);		// �� ����� �� ��ü �浹 �Լ�

	static void CCollisionMgr::Collision_Player(list<CObj*> _Dest, list<CObj*> _Src, int _Damage);	// �� ��ü�� �ε����� �÷��̾�� ������ ����, ���� ����
	static void CCollisionMgr::Collision_Player2(list<CObj*> _Dest, list<CObj*> _Src, int _Damage);

private:
	static bool Check_Sphere(CObj* pDest, CObj* pSrc);		// �� ����� �� ��ü �浹 Ȯ�� �Լ�
	static bool Check_Rect(CObj* pDest, CObj* pSrc, float* _pWidth, float* _pHeight);	// �簢�� ����� �� ��ü �浹 Ȯ�� �Լ�

};

#endif // 
