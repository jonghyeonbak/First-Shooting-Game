#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "DefaultBullet.h"
#include "EnergyWave.h"
#include "BladeShield.h"
#include "EnergyWave.h"
#include "GuideMissile.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Key_Input(void)
{

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_fAngle += 5.f;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_fAngle -= 5.f;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * -m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * -m_fSpeed;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && m_Dir + 500   < GetTickCount())				// 일반 공격
	{
		CObj*  pObj = (CAbstractFactory<CDefaultBullet>::Create(float(m_tGun.x), float(m_tGun.y), m_fAngle));
		CObjMgr::Get_Instance()->Add_Object(OBJID::DEFAULTBULLET, pObj);

		m_Dir = GetTickCount();
	}

	if (GetAsyncKeyState('1') & 0x8000)			// 톱니 쉴드
	{
		CObj*  pObj = (CAbstractFactory<CBladeShield>::Create(float(m_tGun.x), float(m_tGun.y), m_fAngle));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BLADESHIELD, pObj);
	}

	if (GetAsyncKeyState('2') & 0x8000)				 // 유도 미사일
	{
		CObj*  pObj = (CAbstractFactory<CGuideMissile>::Create(float(m_tGun.x), float(m_tGun.y), m_fAngle));
		CObjMgr::Get_Instance()->Add_Object(OBJID::GUIDEMISSILE, pObj);
	}

	if (GetAsyncKeyState('3') & 0x8000)				// 레이저
	{
		CObj*  pObj = (CAbstractFactory<CEnergyWave>::Create(float(m_tGun.x), float(m_tGun.y), m_fAngle));
		CObjMgr::Get_Instance()->Add_Object(OBJID::ENERGYWAVE, pObj);
	}
}


void CPlayer::Initialize(void)
{
	m_tInfo.fX = 640.f;			// 시작 중점
	m_tInfo.fY = 700.f;			// 시작 중점

	m_tInfo.fCX = 72.f;			
	m_tInfo.fCY = 72.f;

	m_tGun.x = m_tInfo.fX;
	m_tGun.y = m_tInfo.fY;

	m_fDistance = 50.f;				// 포신 길이
	m_fMaru_Distance = 28.f;		// 마루간의 거리

	m_fSpeed = 10.f;
	
	m_tStat = { 5000,5000, 50 };
}

int CPlayer::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	Key_Input();

	Update_Rect();

	return OBJ_LIFE;
}

void CPlayer::Late_Update(void)
{
	m_fMaru_Angle += 3.f;			// 마루 회전 속도

	m_tGun.x = long(m_tInfo.fX + (cosf(m_fAngle * PI / 180.f) * m_fDistance));
	m_tGun.y = long(m_tInfo.fY - (sinf(m_fAngle * PI / 180.f) * m_fDistance));

	m_tMaru[0].x = long(m_tInfo.fX + (cosf(m_fMaru_Angle * PI / 180.f) * m_fMaru_Distance));
	m_tMaru[0].y = long(m_tInfo.fY - (sinf(m_fMaru_Angle * PI / 180.f) * m_fMaru_Distance));
	m_tMaru[1].x = long(m_tInfo.fX - (cosf((m_fMaru_Angle + 115) * PI / 180.f) * m_fMaru_Distance));
	m_tMaru[1].y = long(m_tInfo.fY + (sinf((m_fMaru_Angle + 115) * PI / 180.f) * m_fMaru_Distance));
	m_tMaru[2].x = long(m_tInfo.fX + (cosf((m_fMaru_Angle + 65) * PI / 180.f) * m_fMaru_Distance));
	m_tMaru[2].y = long(m_tInfo.fY - (sinf((m_fMaru_Angle + 65) * PI / 180.f) * m_fMaru_Distance));
	m_tMaru[3].x = long(m_tInfo.fX - (cosf((m_fMaru_Angle + 37) * PI / 180.f) * m_fMaru_Distance));
	m_tMaru[3].y = long(m_tInfo.fY + (sinf((m_fMaru_Angle + 37) * PI / 180.f) * m_fMaru_Distance));
	m_tMaru[4].x = long(m_tInfo.fX + (cosf((m_fMaru_Angle + 140) * PI / 180.f) * m_fMaru_Distance));
	m_tMaru[4].y = long(m_tInfo.fY - (sinf((m_fMaru_Angle + 140) * PI / 180.f) * m_fMaru_Distance));
}

void CPlayer::Render(HDC hDC)
{
	HBRUSH myBrush, myBrush1, myBrush2, myBrush3,myBrush4, oldBrush;
	myBrush = (HBRUSH)CreateSolidBrush(RGB(32, 32, 32));
	myBrush1 = (HBRUSH)CreateSolidBrush(RGB(154, 212, 213));
	myBrush2 = (HBRUSH)CreateSolidBrush(RGB(247, 229, 11));
	myBrush3 = (HBRUSH)CreateSolidBrush(RGB(146, 177, 72));
	myBrush4 = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));

	//myBrush2 = (HBRUSH)SelectObject(hDC, myBrush);
	//myBrush3 = (HBRUSH)SelectObject(hDC, myBrush2);
	//myBrush = (HBRUSH)SelectObject(hDC, oldBrush);
	//myBrush1 = (HBRUSH)SelectObject(hDC, myBrush);


	// 포신
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tGun.x, (int)m_tGun.y);

	// 몸체
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush3);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	myBrush3 = (HBRUSH)SelectObject(hDC, myBrush1);
	Ellipse(hDC, m_tRect.left + 17, m_tRect.top + 16, m_tRect.right - 17, m_tRect.bottom - 17);
	Rectangle(hDC, m_tRect.left + 36, m_tRect.top + 20, m_tRect.right - 35, m_tRect.bottom - 41); // 상
	Rectangle(hDC, m_tRect.left + 36, m_tRect.top + 41, m_tRect.right - 35, m_tRect.bottom - 19); // 하
	Rectangle(hDC, m_tRect.left + 20, m_tRect.top + 36, m_tRect.right - 41, m_tRect.bottom - 35); // 좌
	Rectangle(hDC, m_tRect.left + 41, m_tRect.top + 36, m_tRect.right - 20, m_tRect.bottom - 35); // 우

	for (int i = 0; i < 5; i++) 
	{
		myBrush1 = (HBRUSH)SelectObject(hDC, myBrush2);
		Ellipse(hDC, (int)m_tMaru[i].x - 3, (int)m_tMaru[i].y + 4, (int)m_tMaru[i].x + 4, (int)m_tMaru[i].y - 3);	// UFO 내부 돌아다니는 원 사이즈
	}

	// 체력바

	myBrush2 = (HBRUSH)SelectObject(hDC, myBrush4);

	Rectangle(hDC, m_tInfo.fX - 60, m_tInfo.fY + 60, m_tInfo.fX + 60, m_tInfo.fY + 52); // 플레이어 체력바
	myBrush4 = (HBRUSH)SelectObject(hDC, myBrush2);
	Rectangle(hDC, m_tInfo.fX - 58, m_tInfo.fY +58, m_tInfo.fX - 62 + (120 * (m_tStat.iHp / float(m_tStat.iMaxHp))), m_tInfo.fY +54);
	myBrush2 = (HBRUSH)SelectObject(hDC, oldBrush);

	int tt = m_tStat.iHp / m_tStat.iMaxHp;

	TCHAR	szTemp[10] = L"";

	swprintf_s(szTemp, L"%d", m_tStat.iHp);
	TextOut(hDC, m_tInfo.fX - 55, m_tInfo.fY + 60, szTemp, lstrlen(szTemp));

	if (m_tStat.iHp <= 0)
	{
		m_tStat.iHp = OBJ_LIFE;
	}

	DeleteObject(myBrush);
	DeleteObject(myBrush1);
	DeleteObject(myBrush2);
	DeleteObject(myBrush3);
	DeleteObject(myBrush4);
	DeleteObject(oldBrush);
}

void CPlayer::Release(void)
{
}

