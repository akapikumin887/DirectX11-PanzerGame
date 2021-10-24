/*-------------------------------------------------
	
	[TitleScene.cpp]
	Author : �o���đ�

--------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "TitleBg.h"
#include "TitleSystem.h"
#include "Command.h"
#include "TitleScene.h"
#include <thread>

#pragma region GameScene::Title_method
void GameScene::Title::Init()
{
	AddGameObject<TitleSystem>(ELayer::LAYER_2D_UI);
	AddGameObject<GameBg::TitleBg>(ELayer::LAYER_2D_BG);
	AddGameObject<TitleCommand>(ELayer::LAYER_SYSTEM);
	Load();
	Engine::Get().GetResource()->AudioPlay("Title", 0.3f);
	Begin();
}

void GameScene::Title::Uninit()
{
	Unload();
	Scene::Uninit();
}

void GameScene::Title::Update()
{
	Scene::Update();
}

void GameScene::Title::Draw()
{
	Scene::Draw();
}

void GameScene::Title::Load()
{
	Engine::Get().GetResource()->LoadTexture("TitleBg", "TitleBg.png");
	Engine::Get().GetResource()->AudioLoad("Title", true);
	Engine::Get().GetResource()->AudioLoad("Button", false);
	Engine::Get().GetResource()->AudioLoad("Enter", false);
	Engine::Get().GetResource()->AudioLoad("Cancel", false);
	Engine::Get().GetResource()->AudioLoad("Select", false);
}

void GameScene::Title::Unload()
{
	Engine::Get().GetResource()->UnloadTexture("TitleBg");
	Engine::Get().GetResource()->AudioUnload();
}
#pragma endregion GameScene::Title���\�b�h
