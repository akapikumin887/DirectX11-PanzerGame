/*--------------------------------------------------------------
	
	[Target.h]
	Author : �o���đ�

	�`���[�g���A���̓I

---------------------------------------------------------------*/
#pragma once
#include "Effect.h"

class Target final: public Effect
{
public:
	Target();
	~Target();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	bool m_NotDraw = false; // true�ŕ`�悵�Ȃ�
	int32_t m_CoolTime = 100; // �`�悵�Ȃ�����
};

