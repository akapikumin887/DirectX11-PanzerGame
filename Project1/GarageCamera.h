/*-----------------------------------------------------------

	[GarageCamera.h]
	Author : �o���đ�

	��ԑq�ɂ̃J����

------------------------------------------------------------*/
#pragma once
#include "Camera.h"

class GarageCamera final : public Camera
{
public:
	GarageCamera();
	~GarageCamera();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};

