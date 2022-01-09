#pragma once
#ifndef  __ENUM_H__
#define  __ENUM_H__			

namespace BULLET		//�Ѿ��� ����� Ÿ���� ��� ����
{
	enum DIR { LEFT, RIGHT, UP, DOWN, TARGET, END };
}

namespace OBJID			// �÷��̾�, �Ѿ�, ������ ������ ��� ����
	// ������ ���� ��, ���͸� �ٸ� ���ӽ����̽��� ����� ��������, enum�� �߰��ؼ� �����߰ڴ�.
{
	enum ID { PLAYER, BULLET, DEFAULTBULLET, BLADESHIELD, GUIDEMISSILE, ENERGYWAVE, MOUSE, SHILED, MONSTER_CARRIER, MONSTER_GUIDED,
			  MONSTER, MONSTER_KF15, KF15_BULLET, UFO, UFO_BULLET, TANK, TANK_BULLET, WARM, WARM_BULLET, END };
}

namespace BULLETSKILL		// �÷��̾��� ��ų�� ��� ����
{
	enum BULLETSK { DEFAULTBULLET, BLADESHIELD, GUIDEMISSILE, ENERGYWAVE, END};		// �̻��� ��ų
}

#endif // ! __ENUM_H__
