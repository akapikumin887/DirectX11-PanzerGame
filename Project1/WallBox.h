/*--------------------------------------------------------------

	[WallFence.h]
	Author : �o���đ�

	BOX�^�̕�

---------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class WallBox final : public StageObject
{
public:
	WallBox();
	~WallBox();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

