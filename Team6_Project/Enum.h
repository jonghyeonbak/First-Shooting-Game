#pragma once
#ifndef  __ENUM_H__
#define  __ENUM_H__			

namespace BULLET		//총알의 방향과 타겟을 담고 있음
{
	enum DIR { LEFT, RIGHT, UP, DOWN, TARGET, END };
}

namespace OBJID			// 플레이어, 총알, 몬스터의 정보를 담고 있음
	// 다음에 만들 땐, 몬스터를 다른 네임스페이스로 만드려 하지말고, enum을 추가해서 만들어야겠다.
{
	enum ID { PLAYER, BULLET, DEFAULTBULLET, BLADESHIELD, GUIDEMISSILE, ENERGYWAVE, MOUSE, SHILED, MONSTER_CARRIER, MONSTER_GUIDED,
			  MONSTER, MONSTER_KF15, KF15_BULLET, UFO, UFO_BULLET, TANK, TANK_BULLET, WARM, WARM_BULLET, END };
}

namespace BULLETSKILL		// 플레이어의 스킬을 담고 있음
{
	enum BULLETSK { DEFAULTBULLET, BLADESHIELD, GUIDEMISSILE, ENERGYWAVE, END};		// 미사일 스킬
}

#endif // ! __ENUM_H__
