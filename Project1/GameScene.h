/*-------------------------------------------------------------

	[GameScene.h]
	Author : ?o???đ?

--------------------------------------------------------------*/
#pragma once
#include "Scene.h"
#include "GameBg.h"

namespace GameScene
{
	// ???ԑI??
	class PanzerSelect final : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override
		{
			Scene::Update();
		}
		void Draw()override
		{
			Scene::Draw();
		}
	private:
		void Load()override;
		void Unload()override;
		void Thread_Audio();
		void Thread_Texture_A();
		void Thread_Texture_B();
		void Thread_Model();
	};

	// ?`???[?g???A??
	class Tutorial final : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override
		{
			Scene::Update();
		}
		void Draw()override
		{
			Scene::Draw();
		}
	private:
		void Load()override;
		void Unload()override;
	};

	// ?Q?[??
	class Game final : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override
		{
			Scene::Update();
		}
		void Draw()override
		{
			Scene::Draw();
		}
	private:
		void Load()override;
		void Unload()override;
	};
}