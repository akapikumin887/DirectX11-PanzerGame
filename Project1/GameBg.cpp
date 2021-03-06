/*------------------------------------------------------------

	[GameBg.cpp]
	Author : 出合翔太

	ゲームの2D背景

-------------------------------------------------------------*/
#include "Resource.h"
#include "Engine.h"
#include "Application.h"
#include "Renderer2D.h"
#include "TitleSystem.h"
#include "GameBg.h"
#include "GameCamera.h"
#include "PanzerContainer.h"
#include "Command.h"
#include <string>
#include <vector>
#include <algorithm>

#pragma region Scope_method
GameBg::Scope::Scope()
{
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Bg", Bg::GetSize() * 0.5f, Bg::GetSize(), Math::Vector2(0.0f, 0.0f), Math::Vector2(0.5f, 0.5f));
}

GameBg::Scope::~Scope()
{
}

void GameBg::Scope::Begin()
{
}

void GameBg::Scope::Update()
{
}

void GameBg::Scope::Event()
{
}

void GameBg::Scope::Draw()
{
	// カメラがFPSモードのときにスコープを描画する
	if(Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA)->GetChageMode() == true)
	{
		m_Renderer2D->Draw();
	}
}
#pragma endregion Scopeクラスのメソッド

#pragma region PanzerSelectUi_method
GameBg::PanzerSelectUi::PanzerSelectUi()
{
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "SelectUi");
	m_Operation = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Ui03");
	m_List = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "SelectList");
	
	// 戦車名のTexture座標
	m_TexCoord = 
	{ 
		Math::Vector2(0.0f, 0.25f), 
		Math::Vector2(0.0f, 0.5f), 
		Math::Vector2(0.0f, 0.75f), 
		Math::Vector2(0.25f, 0.5f), 
		Math::Vector2(0.25f, 0.75f), 
		Math::Vector2(0.5f, 0.0f) 
	};
}

GameBg::PanzerSelectUi::~PanzerSelectUi()
{
}

void GameBg::PanzerSelectUi::Begin()
{
}

void GameBg::PanzerSelectUi::Update()
{
	auto container = Engine::Get().GetApplication()->GetScene()->GetGameObject<PanzerContainer>(LAYER_3D_ACTOR);
	// 上
	if (container->GetButton() == 1)
	{
		std::rotate(m_TexCoord.rbegin(), m_TexCoord.rbegin() + 1, m_TexCoord.rend());
	}
	// 下
	else if (container->GetButton() == 2)
	{
		// 配列を左シフト
		std::rotate(m_TexCoord.begin(), m_TexCoord.begin() + 1, m_TexCoord.end());
	}
	// 選択をリセット
	container->Reset();
}

void GameBg::PanzerSelectUi::Event()
{
}

void GameBg::PanzerSelectUi::Draw()
{
	Math::Vector2 pos = Bg::GetSize() * 0.5f;
	Math::Vector2 size = Bg::GetSize();

	// 背景
	m_Renderer2D->Draw(pos, size, Math::Vector2(0.5f, 0.5f), Math::Vector2(1.0f, 1.0f));
	
	// 操作方法の説明
	if (g_IsInputGamePad == false)
	{
		m_Operation->Draw(Math::Vector2(960.0f, 960.0f), Math::Vector2(500.0f, 70.0f), Math::Vector2(0.0f, 0.0f), Math::Vector2(1.0f, 0.5f));
	}
	else
	{
		m_Operation->Draw(Math::Vector2(960.0f, 960.0f), Math::Vector2(500.0f, 70.0f), Math::Vector2(0.0f, 0.5f), Math::Vector2(1.0f, 1.0f));
	}
	
	// 戦車の名前
	DrawPanzerName();

	// ゲーム説明
	DrawGameRule(pos, size);
}

void GameBg::PanzerSelectUi::Down()
{
	m_Page--;
	if (m_Page < 0)
	{
		Disable();
	}
}

void GameBg::PanzerSelectUi::Up()
{
	m_Page++;
	if (m_Page > 2)
	{
		Disable();
	}
}

void GameBg::PanzerSelectUi::Enable()
{
	m_DrawFlag = true;
}

void GameBg::PanzerSelectUi::Disable()
{
	if (m_DrawFlag)
	{
		m_DrawFlag = false;
		m_Page = 0; // 最初のページに戻す
	}
}

const bool GameBg::PanzerSelectUi::GetDrawFlag() const
{
	return m_DrawFlag;
}

void GameBg::PanzerSelectUi::DrawPanzerName()
{
	// 描画する4つ
	std::array<float, 4> position = { 1.0f, 1.25f, 1.5f, 0.75f };
	// 描画位置の補正
	float x = Bg::GetWidth() * 0.1f + 30.0f;
	float y = Bg::GetHeight() * 0.5f + 30.0f;

	// 戦車のリスト
	// 配列の先頭から3つ
	auto offset = Math::Vector2(0.25f, 0.25f);
	for (int32_t i = 0; i < 3; ++i)
	{
		m_List->Draw(Math::Vector2(x, y * position[i]), Math::Vector2(432.0f, 128.0f), m_TexCoord[i], m_TexCoord[i] + offset);
	}

	// 配列の一番最後	
	Math::Vector2 end = m_TexCoord.back();
	m_List->Draw(Math::Vector2(x, y * position[3]), Math::Vector2(432.0f, 128.0f), end, end + offset);

	// 枠の描画
	m_List->Draw(Math::Vector2(x, y), Math::Vector2(432.0f, 128.0f), Math::Vector2(0.0f, 0.0f), Math::Vector2(0.25f, 0.25f));
}

void GameBg::PanzerSelectUi::DrawGameRule(Math::Vector2 pos, Math::Vector2 size)
{
	// ゲームの説明
	if (m_DrawFlag)
	{
		switch (m_Page)
		{
		case 0:
			m_Renderer2D->Draw(pos, size, Math::Vector2(0.0f, 0.02f), Math::Vector2(0.5f, 0.52f));
			break;
		case 1:
			m_Renderer2D->Draw(pos, size, Math::Vector2(0.5f, 0.0f), Math::Vector2(1.0f, 0.5f));
			break;
		case 2:
			m_Renderer2D->Draw(pos, size, Math::Vector2(0.0f, 0.5f), Math::Vector2(0.5f, 1.0f));
			break;
		}
	}
}
#pragma endregion PranzerSelectUi_method

#pragma region Mode_method
GameBg::Mode::Mode()
{
	m_Renderer2D = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "SelectList");
	m_Renderer = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "Ui");
}

GameBg::Mode::~Mode()
{
}

void GameBg::Mode::Begin()
{
}

void GameBg::Mode::Update()
{
	m_Alpha += m_Color;
	if (m_Alpha < 0.5f)
	{
		m_Alpha = 0.5f;
		m_Color *= -1;
	}
	else if (m_Alpha > 1.0f)
	{
		m_Alpha = 1.0f;
		m_Color *= -1;
	}
}

void GameBg::Mode::Event()
{
}

void GameBg::Mode::Draw()
{
	Math::Vector2 pos = Math::Vector2(1600.0f, 900.0f);
	float size_y = 128.0f;
	// 背景枠
	DrawFrame(pos, size_y);
	// ゲームモード
	DrawModeName(pos, size_y);
}

bool GameBg::Mode::SetMode(bool f)
{
	m_Mode = f;
	return m_Mode;
}

void GameBg::Mode::DrawFrame(Math::Vector2 pos, float size_y)
{
	if (Engine::Get().GetApplication()->GetScene()->GetGameObject<SelectCommand>(ELayer::LAYER_SYSTEM)->GetSelect() == false)
	{
		m_Renderer->Draw(pos, Math::Vector2(512.0f, size_y), Math::Vector2(0.0f, 0.375f), Math::Vector2(0.25f, 0.5f), Math::Vector4(1.0f, 1.0f, 1.0f, m_Alpha));
	}
	else
	{
		m_Renderer->Draw(pos, Math::Vector2(512.0f, size_y), Math::Vector2(0.0f, 0.375f), Math::Vector2(0.25f, 0.5f));
	}
}

void GameBg::Mode::DrawModeName(Math::Vector2 pos, float size_y)
{
	if (m_Mode)
	{
		m_Renderer2D->Draw(pos, Math::Vector2(432.0f, size_y), Math::Vector2(0.25f, 0.25f), Math::Vector2(0.5f, 0.5f));
	}
	else
	{
		m_Renderer2D->Draw(pos, Math::Vector2(432.0f, size_y), Math::Vector2(0.25f, 0.0f), Math::Vector2(0.5f, 0.25f));
	}
}
#pragma endregion Mode_method

GameBg::TutorialUi::TutorialUi()
{
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Ui04");
}

GameBg::TutorialUi::~TutorialUi()
{
}

void GameBg::TutorialUi::Begin()
{
}

void GameBg::TutorialUi::Update()
{
}

void GameBg::TutorialUi::Event()
{
}

void GameBg::TutorialUi::Draw()
{
	Math::Vector2 pos = Math::Vector2(1700.0f, 600.0f);
	Math::Vector2 size = Math::Vector2(256.0f, 256.0f);
	if (g_IsInputGamePad == false)
	{
		m_Renderer2D->Draw(pos, size, Math::Vector2(0.0f, 0.0f), Math::Vector2(0.5f, 1.0f));
	}
	else 
	{
		m_Renderer2D->Draw(pos, size, Math::Vector2(0.5f, 0.0f), Math::Vector2(1.0f, 1.0f));
	}
}
