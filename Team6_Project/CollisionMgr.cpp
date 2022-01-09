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
void CCollisionMgr::Collision_Player(list<CObj*> _Dest, list<CObj*> _Src, int _Damage)		// �� ��ü �浹 �Լ�, �÷��̾�� ������ ����, ���� ����
{

	for (auto& Dest : _Dest)											// ��� 1�� ������ Dest�� ����
	{
		for (auto& Src : _Src)											// ��� 2�� ������ Src�� ����
		{
			if (Check_Sphere(Dest, Src))								// �� ����� �� ��ü�� �浹�ߴ��� Ȯ���ϴ� �Լ�
			{
				static_cast<CPlayer*>(Dest)->Set_Hp(_Damage);			// CObj�� ������ CPlayer������ ��ȯ �� set_hp �Լ��� �̿��� �������� ������.
				Src->Set_Dead();										// ���� ����
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
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Src->Get_Rect())))		// intersectrect �Լ��� �浹 Ȯ��
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src)	// �簢�� ����� �� ��ü�� �浹�ϸ� ��븦 �о�� �Լ�
{

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			float	fWidth = 0.f, fHeight = 0.f;							// �غ�, ���� ���� ����� ���ÿ� 0���� �ʱ�ȭ

			if (Check_Rect(Dest, Src, &fWidth, &fHeight))					// �簢�� �浹 Ȯ�� �Լ�, ���1, 2, �غ�, ����
			{
				// �� �� �浹
				if (fWidth > fHeight)										// �غ��� ���̺��� Ŭ ���
				{
						//�� �浹
					if (Dest->Get_Info().fY < Src->Get_Info().fY)			// ��� 1�� ���� y���� ��� 2�� ���� y�� Ŭ ���
					{
						Src->Set_PosY(fHeight);								// ��� 2�� �Ʒ� �������� ���̸�ŭ �̵�
					}
					else
						// �� �浹
						Src->Set_PosY(-fHeight);							// ��� 2�� ���� �������� ���̸�ŭ �̵�
				}

				//  �� �� �浹
				else
				{		// �� �浹
					if (Dest->Get_Info().fX < Src->Get_Info().fX)			// ��� 1�� ���� x���� ��� 2�� ���� x�� Ŭ ���
					{
						Src->Set_PosX(fWidth);								// ��� 2�� ������ �������� �غ� ��ŭ �̵�
					}
					else
						// �� �浹
						Src->Set_PosX(-fWidth);								// ��� 2�� ���� �������� �غ� ��ŭ �̵�
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src)	// �� ����� �� ��ü �浹
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

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSrc)									// �� ����� �� ��ü �浹 Ȯ�� �Լ�
{
	float		fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);					// �غ� = ����(���1�� ����x - ��� 2�� ����x)
	float		fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);					// ���� = ����(���1�� ����y - ��� 2�� ����y)

	float		fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);						// �Ÿ� = ������(�غ�*�غ� + ����*����)

	float		fRadius = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;			// ������ = (���1�� ���λ����� + ���2�� ���λ�����) / 2

	return fRadius > fDistance;																// �������� �Ÿ����� Ŭ ��� (�浹�̹Ƿ� 1��ȯ)
}

bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSrc, float* _pWidth, float* _pHeight)		// �÷��̾� ����, ���� ����, ���μ��� 0
{
	float		fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);						// �غ� = ����(���1�� ����x - ��� 2�� ����x)
	float		fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);						// ���� = ����(���1�� ����y - ��� 2�� ����y)

	float		fCX = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;					// �� ���� �簢��(�÷��̾�� ����)�� �������� ���� ��
	float		fCY = (pDest->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;					// �� ���� �簢��((�÷��̾�� ����)�� �������� ���� ��

	if (fCX > fWidth && fCY > fHeight)					// �� ��ü�� �������� ���� �� 2�� ���� �ͺ��� �غ��� ũ��, �ٸ� ���ǵ� ������ ���
	{
		*_pWidth = fCX - fWidth;						// p_width = ������ - �غ�
		*_pHeight = fCY - fHeight;

		return true;									// �� ��ȯ
	}

	return false;										// ���� ��ȯ
}
