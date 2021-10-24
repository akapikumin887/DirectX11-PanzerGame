/*-----------------------------------------------------------
	
	[PanzerStateMove.h]
	Author : �o���đ�

	�ړ�����X�e�[�g

------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

namespace State
{
	class Forward final : public PanzerState
	{
	public:
		Forward();
		~Forward();
		void Update(Pawn* pPawn, float deltaTime)override;
	};

	class Backward final : public PanzerState
	{
	public:
		Backward();
		~Backward();
		void Update(Pawn* pPawn, float deltaTime)override;
	};
}