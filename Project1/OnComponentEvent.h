/*--------------------------------------------------------------

	[OnComponentEvent.h]
	Author : �o���đ�

	�����蔻���̃C�x���g

---------------------------------------------------------------*/
#pragma once
#include "IOnComponentEvent.h"

class OnComponentEventWallBox final : public IOnComponentEventToPawn
{
public:
	void BeginOverlap(class Pawn* pPawn)override;
};