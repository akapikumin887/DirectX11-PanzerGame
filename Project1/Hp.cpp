/*--------------------------------------------------------------
	
	[Hp.cpp]
	Author : �o���đ�

---------------------------------------------------------------*/
#include "Renderer2D.h"
#include "Status.h"
#include "Vehicle.h"
#include "Player.h"
#include "Hp.h"
#include "Engine.h"
#include "Application.h"

GameBg::Hp::Hp()
{
	m_Render = std::make_unique<Render>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource());
}

GameBg::Hp::~Hp()
{
}

void GameBg::Hp::Begin()
{
	m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	m_DrawRatio = m_MaxDrawSize / m_Player->GetVehicle().GetStatus().GetMaxHp();
}

void GameBg::Hp::Update()
{
	// ���݂�HP
	m_NowHp = m_Player->GetVehicle().GetStatus().GetHp();
	// �X�V�O��HP�Ɣ�r����
	if (m_OldHp != m_NowHp)
	{
		// ��v���Ȃ�������A�`��T�C�Y���v�Z���đO��HP���X�V����

		// ���݂�HP * ���߂��䗦
		m_DrawSize = m_NowHp * m_DrawRatio;
		m_OldHp = m_NowHp;
	}
}

void GameBg::Hp::Event()
{
}

void GameBg::Hp::Draw()
{
	Math::Vector2 pos = Math::Vector2(1450.0f, 900.0f);
	m_Render->Draw(m_MaxDrawSize, pos, Math::Vector4(0.35f, 0.35f, 0.35f, 0.75f));
	m_Render->Draw(m_DrawSize, pos, Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
}