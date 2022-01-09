#pragma once
#include "Obj.h"
class CKF15_Bullet :
	public CObj
{
public:
	CKF15_Bullet();
	virtual ~CKF15_Bullet();

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);

	virtual void Render(HDC hDC);
	virtual void Release(void);


private:
	CObj*			m_tPlayerTarget;			// Å¸°Ù
	POINTFLOAT		m_tCenterPos;				
	float			m_fRevolutionAngle;
	float			m_fCenterSpeed;
	bool			m_bStart;

	bool			m_bCenter1;
	bool			m_bCenter2;
	bool			m_bCenter3;
	bool			m_bCenter4;

	INFO			m_tInfoTemp;
};

