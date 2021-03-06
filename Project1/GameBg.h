/*------------------------------------------------------------

	[GameBg.h]
	Author : oγΔΎ

	Q[Μ2Dwi

-------------------------------------------------------------*/
#pragma once
#include "Bg.h"
#include <array>
#include <vector>

class Renderer2D;
namespace GameBg
{
	// XR[v
	class Scope final : public Bg
	{
	public:
		Scope();
		~Scope();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	};

	// IπζΚwiUI
	class PanzerSelectUi final : public Bg
	{
	public:
		PanzerSelectUi();
		~PanzerSelectUi();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
		void Down();
		void Up();
		void Enable();
		void Disable();
		const bool GetDrawFlag() const;
	private:
		// `ζ
		void DrawPanzerName();	// νΤΜΌO
		void DrawGameRule(Math::Vector2 pos, Math::Vector2 size);	// Q[ΰΎ	

		std::vector<Math::Vector2> m_TexCoord;
		std::unique_ptr<Renderer2D> m_List; // νΤΜXg
		std::unique_ptr<Renderer2D> m_Operation; // μϋ@UI
		int32_t m_Page;
		bool m_DrawFlag = false;
	};

	// [hIπ
	class Mode final : public Bg
	{
	public:
		Mode();
		~Mode();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
		bool SetMode(bool f); 
	private:		
		// `ζ
		void DrawFrame(Math::Vector2 pos, float size_y);	// wigΜ_Ε
		void DrawModeName(Math::Vector2 pos, float size_y);	// Q[[h

		std::unique_ptr<Renderer2D> m_Renderer;
		bool m_Mode; // trueΕ`[gAAfalseΕQ[
		float m_Alpha = 1.0f;
		float m_Color = 0.01f;
	};

	// `[gAΜμΰΎ
	class TutorialUi final : public Bg
	{
	public:
		TutorialUi();
		~TutorialUi();
		void Begin()override;
		void Update()override;
		void Event()override;
		void Draw()override;
	};
};
