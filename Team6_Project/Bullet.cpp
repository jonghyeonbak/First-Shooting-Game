#include "stdafx.h"
#include "Bullet.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Set_Target(void)
{
}

void CBullet::Initialize(void)
{
}

int CBullet::Update(void)
{
	Update_Rect();

	return OBJ_LIFE;			// 대상이 살아있음을 반환
}

void CBullet::Late_Update(void)
{
}

void CBullet::Render(HDC hDC)
{
}

void CBullet::Release(void)
{

}
