/*-------------------------------------------------
	
	[ResultScene.h]
	Author : 出合翔太

--------------------------------------------------*/
#pragma once
#include "Scene.h"

namespace GameScene
{
	// リザルト
	class Result final : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	private:
		void Load()override;
		void Unload()override;
	};
}
