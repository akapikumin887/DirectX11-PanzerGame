/*------------------------------------------------------------
	
	[Grass.h]
	Author : �o���đ�

	����1�̐ݒ�

-------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class Grass final : public StageObject
{
public:
	Grass();
	~Grass();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

