#pragma once

#include "Obj.h"
#include "Enum.h"
class CTank_Bullet : public CObj
{
public:
	CTank_Bullet();
	virtual ~CTank_Bullet();


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;

	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;




};



