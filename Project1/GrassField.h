/*------------------------------------------------------------
	
	[GrassField.h]
	Author : �o���đ�

	Grass�I�u�W�F�N�g���܂Ƃ߂�

--------------------------------------------------------------*/
#pragma once
#include "Actor.h"

class GrassField final : public Actor
{
public:
	GrassField();
	~GrassField();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

