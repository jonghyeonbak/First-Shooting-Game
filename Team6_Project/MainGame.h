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
	HDC			m_DC;				// dc �����ϱ� ���� ����
	DWORD		m_dwTime;			// �ð� ��� ����
	int			m_iFPS;				// ips ��� ����
	TCHAR		m_szFPS[256];		// �Ѵ� 
	int			m_iCount;			// ī��Ʈ 
	int			m_iCount2;

	bool		m_Switch_Tank;
	bool        m_Switch_Carrier;

	DWORD		m_Time_Tank;
	DWORD		m_Time_KF_15;
	DWORD		m_Time_Carrier;

	int			m_iCount_Carrier;
};

#endif