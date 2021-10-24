/*-------------------------------------------------
	
	[DrawSkill.h]
	Author : �o���đ�

--------------------------------------------------*/
#pragma once
#include "Bg.h"

class Render;
namespace GameBg
{
	// �X�L���̕`
	class DrawSkill final : public Actor
	{
	public:
		DrawSkill();
		~DrawSkill();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
		void Reset();
	private:
		std::unique_ptr<Render> m_Render;
		class Player* m_Player;
		const float m_MaxDrawSize = 400.0f;
		float m_DrawSize = 0.0f;
		float m_Add; // ���������
	};
}
