/*--------------------------------------------------------------

	[Reload.h]
	Author : 出合翔太

	リロード中に描画するUI

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

