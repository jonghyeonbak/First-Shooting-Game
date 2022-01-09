#include "stdafx.h"
#include "MainGame.h"
#include "HeadFile.h"
#include "MonsterFile.h"

CMainGame::CMainGame()
	: m_dwTime(0)
	, m_iFPS(0), m_Time_Tank(0), m_iCount(0), m_Switch_Tank(true), m_iCount2(0), m_Switch_Carrier(true),
	m_Time_KF_15(0),m_Time_Carrier(0), m_iCount_Carrier(0)
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 256);
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	// player 추가

	CObj*	pObj = nullptr;

	pObj = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, pObj);

	//pObj = CAbstractFactory<CMonster>::Create(500.f, 400.f);
	//CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);


	//pObj = CAbstractFactory<CMonster_KF15>::Create(600.f, 200.f, 5.f);
	//CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_KF15, pObj);

	///*for (int i = 0; i < 4; ++i)
	//{
	//	int move = 80;
	//	pObj = CAbstractFactory<CMonster_Tank>::Create(150.f + (i * move), (100.f + (move % 30)));
	//	CObjMgr::Get_Instance()->Add_Object(OBJID::TANK, pObj);
	//}*/

	//pObj = CAbstractFactory<CMonster_Warm>::Create(1000.f, 700.f, BULLET::LEFT);
	//CObjMgr::Get_Instance()->Add_Object(OBJID::WARM, pObj);


	//pObj = CAbstractFactory<CMonster_UFO>::Create();
	//CObjMgr::Get_Instance()->Add_Object(OBJID::UFO, pObj);

	//pObj = CAbstractFactory<CMonster_Carrier>::Create(1100.f, 700.f, BULLET::UP);
	//CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_CARRIER, pObj);

	//CObj*	pMonster = CAbstractFactory<CMonster>::Create(400.f, 300.f);			// 몬스터가 플레이어 따라가기
	//pMonster->Set_Target(m_ObjList[OBJID::PLAYER].front());
	//m_ObjList[OBJID::MONSTER].push_back(pMonster);
}

void CMainGame::Update(void)
{

	CObjMgr::Get_Instance()->Update();

	if (m_Time_KF_15 + 12000 <= GetTickCount())
	{
		CObj* pObj = nullptr;
		pObj = CAbstractFactory<CMonster_KF15>::Create(600.f, 200.f, 5.f);
		CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_KF15, pObj);

		m_Time_KF_15 = GetTickCount();
	}
	
	if (m_Time_Tank + 8000 <= GetTickCount() && (m_Switch_Tank == true) )
	{
		for (int i = 0; i < 4; ++i)
		{
			
			int move = 80;
			CObj* pObj = nullptr;

			pObj = CAbstractFactory<CMonster_Tank>::Create(150.f + (i * move), (100.f + (move % 30)));
			CObjMgr::Get_Instance()->Add_Object(OBJID::TANK, pObj);
		}
		++m_iCount;

		if (3 == m_iCount)
		{
			m_Switch_Carrier = false;
			
		}
		m_Time_Tank = GetTickCount();
	}

	if (m_Switch_Carrier == false)
	{
		//m_iCount = 0; 

		if (m_Time_Carrier + 3000 <= GetTickCount())
		{
			CObj* pObj = nullptr;

			pObj = CAbstractFactory<CMonster_Carrier>::Create(1100.f, 700.f, BULLET::UP);
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_CARRIER, pObj);

			++m_iCount_Carrier;

			m_Time_Carrier = GetTickCount();
		}
		if (3 == m_iCount_Carrier)
		{
			m_Switch_Carrier = true;			
		}
	}
		
	//++m_iCount2;

	//if ((m_iCount2 == 3) && (m_Switch == true))
	//{
	//	m_Switch = false;
	//	CObj* pObj = nullptr;

	//	pObj = CAbstractFactory<CMonster_UFO>::Create();
	//	CObjMgr::Get_Instance()->Add_Object(OBJID::UFO, pObj);
	//}
}

void CMainGame::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
	

}

void CMainGame::Render(void)
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);		// 창 크기

	CObjMgr::Get_Instance()->Render(m_DC);


	++m_iFPS;									// 프레임 조절

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);
		m_dwTime = GetTickCount();
		m_iFPS = 0;
	}

}

void CMainGame::Release(void)
{
	ReleaseDC(g_hWnd, m_DC);

	CObjMgr::Get_Instance()->Destroy_Intance();
}

