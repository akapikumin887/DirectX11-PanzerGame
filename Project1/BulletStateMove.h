/*-----------------------------------------------------------

	[BulletStateMove.h]
	Author : �o���đ�

	�e���ړ�����

------------------------------------------------------------*/
#pragma once
#include "State.h"

class BulletStateMove final : public BulletState
{
public:
	BulletStateMove();
	~BulletStateMove();
	void Update(Bullet* Bullet, float deltaTime)override;
private:
	void Destory(Bullet* Bullet);
};

