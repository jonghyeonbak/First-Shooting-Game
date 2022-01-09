#pragma once
#ifndef  __STRUCT_H__
#define  __STRUCT_H__

typedef struct tagInfo
{
	float		fX;	// 내가 그리고자 하는 물체의 중점 x
	float		fY; // 내가 그리고자 하는 물체의 중점 y
	float		fCX; // 가로 사이즈
	float		fCY; // 세로 사이즈

}INFO;

typedef struct tagStatus
{
	int			iHp;			// 체력
	int			iMaxHp;			// 최대체력
	int			iAtt;			// 데미지

}STATUS;

class CDeleteObj				// 인스턴스 지우는 용도의 클래스
{
public:
	CDeleteObj() {}	
	~CDeleteObj() {}

public:
	template<typename T>		// 템플릿 함수, 연산자 오버로딩()을 이용한 인스턴스 삭제
	void operator()(T& Temp)
	{
		if (nullptr != Temp)	// 객체가 null이 아닐 경우
		{
			delete Temp;		// 삭제해라
			Temp = nullptr;		// null로 초기화해, 댕글링 포인터 방지
		}
	}
};

template<typename T>			// 템플릿 함수, 안전하게 객체 지우는 함수
void		Safe_Delete(T& Temp)
{
	if (Temp)					// 인스턴스가 존재할 경우
	{
		delete Temp;			// 삭제해라
		Temp = nullptr;			// null로 초기화
	}
}

#endif // ! __STRUCT_H__

