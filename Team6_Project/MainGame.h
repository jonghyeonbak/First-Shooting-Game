#pragma once
#ifndef __MAINGAME_H__
#define __MAINGAME_H__

#include "Player.h"
#include "Monster.h"


class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

private:
	HDC			m_DC;				// dc 보관하기 위한 변수
	DWORD		m_dwTime;			// 시간 담는 변수
	int			m_iFPS;				// ips 담는 변수
	TCHAR		m_szFPS[256];		// 둘다 
	int			m_iCount;			// 카운트 
	int			m_iCount2;

	bool		m_Switch_Tank;
	bool        m_Switch_Carrier;

	DWORD		m_Time_Tank;
	DWORD		m_Time_KF_15;
	DWORD		m_Time_Carrier;

	int			m_iCount_Carrier;
};

#endif