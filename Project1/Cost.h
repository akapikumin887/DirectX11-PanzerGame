/*--------------------------------------------------------------

	[Cost.h]
	Author : �o���đ�

	��Ԃ̃R�X�g��`�悷��

---------------------------------------------------------------*/
#pragma once
#include "IDrawNumber.h"
 
class Cost final : public IDrawNumber
{ 
public:
	Cost();
	~Cost();
	void Draw(int32_t n)override;
private:
	float m_Cost;
};

