#include "stdafx.h"
#include "Tank_Bullet.h"
#include "ObjMgr.h"

CTank_Bullet::CTank_Bullet()
{
}


CTank_Bullet::~CTank_Bullet()
{
}
void CTank_Bullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
}

int CTank_Bullet::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;


	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;


	Update_Rect();

	return OBJ_LIFE;

}

void CTank_Bullet::Late_Update(void)
{
	/*CObjMgr::Get_Instance()->Set_Collision(OBJID::TANK_BULLET, OBJID::PLAYER);
	CObjMgr::Get_Instance()->Set_Collision(OBJID::BULLET, OBJID::MONSTER);*/

	if (0 >= m_tRect.left			||
		WINCX <= m_tRect.right		||
		0 >= m_tRect.top			||
		WINCY <= m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CTank_Bullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CTank_Bullet::Release(void)
{

}
