#pragma once
#ifndef  __ENEGYWAVE_H__
#define  __ENEGYWAVE_H__

#include "Bullet.h"
class CEnergyWave : public CBullet
{
public:
	CEnergyWave();
	virtual ~CEnergyWave();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	POINTFLOAT		m_tCenterPos;
	POINTFLOAT		m_tCenterPos2;
	float			m_fRevolutionAngle;
	float			m_fCenterSpeed;
	bool			m_bStart;

};

#endif // ! __ENEGYWAVE_H__
