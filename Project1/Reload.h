/*--------------------------------------------------------------

	[Reload.h]
	Author : �o���đ�

	�����[�h���ɕ`�悷��UI

--------------------------------------------------------------*/
#pragma once
#include "Effect.h"

class Reload : public Effect
{
public:
	Reload();
	~Reload();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

