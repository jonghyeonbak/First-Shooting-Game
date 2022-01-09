#pragma once
#ifndef  __OBJMGR_H__
#define  __OBJMGR_H__			// 싱글톤,            미디에이트 패턴
								// 인스턴스가 1개      m:n 관계에서 1:n 관계
#include "Define.h"				// 매크로 사용 용도
#include "Enum.h"				// OBJID 사용 용도
#include "Struct.h"				// SafeDelete 클래스 템플릿 사용 용도
#include "CollisionMgr.h"		// 충돌 함수

class CObj;						// CObj 클래스 사용 위해 전방 선언
class CObjMgr					
{                            
private:						// 싱글톤은 생성자를 하나만 호출해야되는데, 
								// 편의를 위해 private으로 생성자 호출을 차단
	CObjMgr();
	virtual		~CObjMgr();		// 아마 상속받는 자식 클래스가 있을 듯

public:
	CObj*		Get_Target(OBJID::ID _eID, CObj* pObj);			// 타겟을 얻어오는 함수, 매개변수 OBJID의 n번 객체, CObj* 타입 변수, 반환 CObj*
	CObj*		Get_Object(OBJID::ID _eID);						// 대상을 얻어오는 함수, 매개변수 OBJID의 n번 객체, 반환 CObj*
	void		Set_Collision(OBJID::ID _eID, OBJID::ID _eID2); // 충돌함수 세팅, 매개변수 OBJ n번 객체, n번 객체 2

public:
	void		Add_Object(OBJID::ID eID, CObj* pObj);			// 대상을 추가하는 함수, 
	int			Update(void);		
	void		Late_Update(void);
	void		Render(HDC m_DC);								// 대상을 그리는 함수, HDC
	void		Release(void);

private:
	list<CObj*>		m_ObjList[OBJID::END];						// OBJID의 데이터들을 담고 있는 CObj*형 리스트인 m_ObjList 변수 선언

public:
	static	CObjMgr*		Get_Instance(void)			// 오직 하나의 인스턴스 생성, static으로 선언해 이 파일 내부에서만 접근 가능
	{
		if (nullptr == m_pInstance)						// m_pInstance가 null이라면
			m_pInstance = new CObjMgr;					// 인스턴스화 

		return m_pInstance;								// m_pInstance 반환
	}

	static	void		Destroy_Intance(void)			//  인스턴스 삭제
	{
		if (nullptr != m_pInstance)						// m_pInstance가 null이 아니라면
		{
			delete m_pInstance;							// m_pInstance 삭제
			m_pInstance = nullptr;						// null 초기화
		}
	}

private:
	static CObjMgr*			m_pInstance;				// CObjMgr*형 변수 선언, 싱글톤 패턴은 인스턴스를 하나만 만들 수 있음

public:
	static int				m_count;					// count를 세기 위해 변수 선언
};

#endif // ! __OBJMGR_H__
