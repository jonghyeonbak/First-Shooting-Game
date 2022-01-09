#include "stdafx.h"
#include "Warm_Bullet.h"

CWarm_Bullet::CWarm_Bullet()											
	: m_fCenterSpeed(0.f), m_fRevolutionAngle(0.f), m_bStart(true)	// ����
{
	ZeroMemory(&m_tCenterPos, sizeof(m_tCenterPos));			// POINT�� ������ �޸𸮸� 0���� �ʱ�ȭ
}


CWarm_Bullet::~CWarm_Bullet()
{
	Release();
}

void CWarm_Bullet::Initialize(void)												
{
	m_tInfo.fCX = 3.f;											// ������ ���� ������		
	m_tInfo.fCY = 3.f;											//		  ���� ������

	m_fSpeed = 3.f;												// ������ ���ǵ�
/*	m_fCenterSpeed = 5.f;													
	m_fDistance = 10.f;															
	m_fRevolutionAngle = 0.f;	*/												
}

int CWarm_Bullet::Update(void)												
{
	if (true == m_bDead)									// ����� �׾�����
		return OBJ_DEAD;									// �Լ� Ż��

	if (m_bStart)											// �����Ѵٸ�				
	{
/*		m_tCenterPos.x = m_tInfo.fX;						// ���� ��ǥ x = ����� ���� ��ǥ x					
		m_tCenterPos.y = m_tInfo.fY;											
		m_fRevolutionAngle = m_fAngle;						// ȸ�� ���� = ����	
		m_bStart = false;		*/							// �����ߴ��� ���� = false, 
		switch (m_eDir)
		{
			case BULLET::LEFT:							 // �Ѿ��� ������ ����
			m_tInfo.fX -= m_fSpeed;						 // �Ѿ��� ���� x�� ���ǵ常ŭ �������� �̵�
			break;

		}

	//	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;	 // ������ǥ x += cos ���� ( ����*���� / 180)*���ǵ�
		//m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;
	}

/*	
	m_tCenterPos.x += m_fCenterSpeed * cosf(m_fRevolutionAngle * PI / 180.f);
	m_tCenterPos.y -= m_fCenterSpeed * sinf(m_fRevolutionAngle * PI / 180.f);  

	m_tInfo.fX = m_tCenterPos.x + (m_fDistance * cosf(m_fAngle * PI / 180.f));	
	m_tInfo.fY = m_tCenterPos.y - (m_fDistance * sinf(m_fAngle * PI / 180.f));

	m_fAngle += m_fSpeed;												*/		

	Update_Rect();																

	return OBJ_LIFE;															
}

void CWarm_Bullet::Late_Update(void)										
{
	if (0	 >= m_tRect.left	 ||												// ȸ�� �Ѿ��� ���� ������ �Ҹ�
	WINCX	 <= m_tRect.right	 ||
	0		 >= m_tRect.top		 ||
	WINCY	 <= m_tRect.bottom)
	{
	m_bDead = true;
	}
}

void CWarm_Bullet::Render(HDC hDC)									
{
	Rectangle(hDC, m_tRect.left-10, m_tRect.top, m_tRect.right+20, m_tRect.bottom);
}

void CWarm_Bullet::Release(void)
{

}
