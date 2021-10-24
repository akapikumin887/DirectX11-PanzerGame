/*-------------------------------------------------------------

	[GameScene.h]
	Author : �o���đ�

--------------------------------------------------------------*/
#pragma once
#include "Scene.h"
#include "GameBg.h"

namespace GameScene
{
	// ��ԑI��
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
		void Thread_A();
		void Thread_B();
		void Thread_C();
		void Thread_D();
	};

	// �`���[�g���A��
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

	// �Q�[��
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