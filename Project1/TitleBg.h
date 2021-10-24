/*-------------------------------------------------
	
	[GameBg.h]
	Author : �o���đ�

--------------------------------------------------*/
#pragma once
#include "GameBg.h"

namespace GameBg
{
	//�^�C�g���w�i
	class TitleBg final : public Bg
	{
	public:
		TitleBg();
		~TitleBg();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	private:
		class TitleSystem* m_TitleSystem = nullptr;
	};
}