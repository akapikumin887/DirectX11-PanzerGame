/*------------------------------------------------------------

	[PanzerGarage.h]
	Author : �o���đ�

	��ԑq��

-------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class PanzerGarage : public StageObject
{
public:
	PanzerGarage();
	~PanzerGarage();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:
	class Graphics& m_Graphics;
};

