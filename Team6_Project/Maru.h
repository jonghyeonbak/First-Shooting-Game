#pragma once
#include "Player.h"
class CMaru : public CPlayer
{
public:
	CMaru();
	virtual ~CMaru();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	POINT			m_tMaru[4];

};

