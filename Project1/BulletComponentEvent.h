/*--------------------------------------------------------------
	
	[BulletComponentEvent.h]
	Author : �o���đ�

	�e�̓����蔻��

---------------------------------------------------------------*/
#pragma once
#include "IOnComponentEvent.h"

namespace BulletEvent
{
	// ��
	class OnComponentEventWallBox final : public IOnComponentEventToActor
	{
	public:
		void BeginOverlap(class Actor* pActor)override;
	};

	// �t�F���X
	class OnComponentEventFence final : public IOnComponentEventToActor
	{
	public:
		void BeginOverlap(class Actor* pActor)override;
	};
}
