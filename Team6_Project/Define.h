#pragma once
#ifndef  __DEFINE_H__
#define   __DEFINE_H__			// ��ũ��, �����Ϸ��� ����Ǳ� ���� ��ó���⿡�� �ܼ� ġȯ

#define WINCX	 1280			// ������ ���� ������
#define WINCY	  800			// ������ ���� ������

#define PURE	  = 0			// ���� ���� �Լ����� �˸��� ���� 0�� �ִµ�, �������� ���̱����� ����.

#define OBJ_LIFE	0			// �ν��Ͻ�(��ü)�� ����ִٸ� 0 ��ȯ
#define OBJ_DEAD	1			// �ν��Ͻ�(��ü)�� �׾��ٸ� 1 ��ȯ

#define PI			3.141592f	// ����, ������ ���� ��ȯ�� �� ���

// �Ϲ������� ��ǻ�ʹ� ���� �����̴�
#define DEGREE_RADIAN(p)	((p) * (PI/180))	// ���� -> ����.
#define RADIAN_DEGREE(p)	((p) * (180/PI))	// ���� -> ����

extern	HWND		g_hWnd;						// HWND���� �ڵ��� ����ϱ� ���� ����.
// HWND�� ���� �����ε�, �� �������� ��ȣ�� �� ���̴ٸ� �˰� �־�� �ü������ ���� �����ϴ�.
extern	POINT		Point;						// ����� ��ǥ�� �˱����� ����
extern  DWORD		m_Dir;						// GetTickCountó�� �ð��� ������� ����

#endif // ! __DEFINE_H__