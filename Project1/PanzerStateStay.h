/*------------------------------------------------------------
	
	[PanzerState.h]
	Author : �o���đ�
	
	�������Ȃ��X�e�[�g

--------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

namespace State
{
	class Stay final : public PanzerState
	{
	public:
		Stay();
		~Stay();
		void Update(Pawn* pPawn, float deltaTime)override;
	};
}