/*------------------------------------------------------------

	[Plane.h]
	Author : �o���đ�

	���I�u�W�F�N�g

--------------------------------------------------------------*/
#pragma once
#include "StageObject.h"

class Plane final : public StageObject
{
public:
	Plane();
	~Plane();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
private:	
	std::unique_ptr<class Renderer3D> m_Renderer;
};

