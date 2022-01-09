#include "stdafx.h"
#include "Warm_Bullet.h"

CWarm_Bullet::CWarm_Bullet()											
	: m_fCenterSpeed(0.f), m_fRevolutionAngle(0.f), m_bStart(true)	// 시작
{
	ZeroMemory(&m_tCenterPos, sizeof(m_tCenterPos));			// POINT형 변수의 메모리를 0으로 초기화
}


CWarm_Bullet::~CWarm_Bullet()
{
	Release();
}

void CWarm_Bullet::Initialize(void)												
{
	m_tInfo.fCX = 3.f;											// 지렁이 가로 사이즈		
	m_tInfo.fCY = 3.f;											//		  세로 사이즈

	m_fSpeed = 3.f;												// 지렁이 스피드
/*	m_fCenterSpeed = 5.f;													
	m_fDistance = 10.f;															
	m_fRevolutionAngle = 0.f;	*/												
}

int CWarm_Bullet::Update(void)												
{
	if (true == m_bDead)									// 대상이 죽었으면
		return OBJ_DEAD;									// 함수 탈출

	if (m_bStart)											// 시작한다면				
	{
/*		m_tCenterPos.x = m_tInfo.fX;						// 중점 좌표 x = 대상의 중점 좌표 x					
		m_tCenterPos.y = m_tInfo.fY;											
		m_fRevolutionAngle = m_fAngle;						// 회전 각도 = 각도	
		m_bStart = false;		*/							// 시작했는지 유무 = false, 
		switch (m_eDir)
		{
			case BULLET::LEFT:							 // 총알의 방향은 왼쪽
			m_tInfo.fX -= m_fSpeed;						 // 총알의 중점 x를 스피드만큼 왼쪽으로 이동
			break;

		}

	//	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;	 // 중점좌표 x += cos 각도 ( 각도*파이 / 180)*스피드
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
	if (0	 >= m_tRect.left	 ||												// 회전 총알이 벽에 닿으면 소멸
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
