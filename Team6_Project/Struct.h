#pragma once
#ifndef  __STRUCT_H__
#define  __STRUCT_H__

typedef struct tagInfo
{
	float		fX;	// ���� �׸����� �ϴ� ��ü�� ���� x
	float		fY; // ���� �׸����� �ϴ� ��ü�� ���� y
	float		fCX; // ���� ������
	float		fCY; // ���� ������

}INFO;

typedef struct tagStatus
{
	int			iHp;			// ü��
	int			iMaxHp;			// �ִ�ü��
	int			iAtt;			// ������

}STATUS;

class CDeleteObj				// �ν��Ͻ� ����� �뵵�� Ŭ����
{
public:
	CDeleteObj() {}	
	~CDeleteObj() {}

public:
	template<typename T>		// ���ø� �Լ�, ������ �����ε�()�� �̿��� �ν��Ͻ� ����
	void operator()(T& Temp)
	{
		if (nullptr != Temp)	// ��ü�� null�� �ƴ� ���
		{
			delete Temp;		// �����ض�
			Temp = nullptr;		// null�� �ʱ�ȭ��, ��۸� ������ ����
		}
	}
};

template<typename T>			// ���ø� �Լ�, �����ϰ� ��ü ����� �Լ�
void		Safe_Delete(T& Temp)
{
	if (Temp)					// �ν��Ͻ��� ������ ���
	{
		delete Temp;			// �����ض�
		Temp = nullptr;			// null�� �ʱ�ȭ
	}
}

#endif // ! __STRUCT_H__

