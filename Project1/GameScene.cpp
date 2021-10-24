/*------------------------------------------------------------ -

	[GameScene.cpp]
	Author : �o���đ�

	�Q�[���V�[���̊Ǘ�

--------------------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "Application.h"
#include "GameBg.h"
#include "GameCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "Command.h"
#include "GarageCamera.h"
#include "PanzerGarage.h"
#include "PlaneGarage.h"
#include "PanzerContainer.h"
#include "Pause.h"
#include "GameManager.h"
#include "Gage.h"
#include "Timer.h"
#include "Hp.h"
#include "TutorialStage.h"
#include "GameStage.h"
#include "GameScene.h"
#include "DrawSkill.h"
#include <thread>

#pragma region GameScene::PanzerSelect_method
void GameScene::PanzerSelect::Init()
{	
	AddGameObject<GarageCamera>(ELayer::LAYER_CAMERA);
	AddGameObject<PlaneGarage>(ELayer::LAYER_3D_STAGE);
	AddGameObject<PanzerGarage>(ELayer::LAYER_3D_STAGE);
	AddGameObject<GameBg::PanzerSelectUi>(ELayer::LAYER_2D_UI);
	AddGameObject<PanzerContainer>(ELayer::LAYER_3D_ACTOR);
	AddGameObject<SelectCommand>(ELayer::LAYER_SYSTEM);
	AddGameObject<GameBg::Mode>(ELayer::LAYER_2D_BG);
	Engine::Get().GetResource()->AudioLoad("PanzerSelect", true);
	Engine::Get().GetResource()->AudioPlay("PanzerSelect", 0.6f);
	Load();
	Begin();
}

void GameScene::PanzerSelect::Uninit()
{
	Unload();
	Scene::Uninit();
}

void GameScene::PanzerSelect::Load()
{
	std::thread thA(&GameScene::PanzerSelect::Thread_A, this);
	std::thread thB(&GameScene::PanzerSelect::Thread_B, this);
	std::thread thC(&GameScene::PanzerSelect::Thread_C, this);
	std::thread thD(&GameScene::PanzerSelect::Thread_D, this);

	thA.join();
	thB.join();
	thC.join();
	thD.join();
}

void GameScene::PanzerSelect::Unload()
{
	Engine::Get().GetResource()->UnloadModel("PanzerGarage");
	Engine::Get().GetResource()->UnloadTexture("Plane");
	Engine::Get().GetResource()->UnloadTexture("Ui03");
	Engine::Get().GetResource()->UnloadModel("Param");
	Engine::Get().GetResource()->UnloadTexture("SelectUi");
	Engine::Get().GetResource()->UnloadTexture("Waffuru");
	Engine::Get().GetResource()->UnloadTexture("SelectList");
	Engine::Get().GetResource()->AudioUnload();
}

void GameScene::PanzerSelect::Thread_A()
{
	//�I�[�f�B�I�֌W
	Engine::Get().GetResource()->AudioLoad("Select", false);
	Engine::Get().GetResource()->AudioLoad("Enter", false);
	Engine::Get().GetResource()->AudioLoad("Cancel", false);
	Engine::Get().GetResource()->AudioLoad("Button", false);
}

void GameScene::PanzerSelect::Thread_B()
{
	Engine::Get().GetResource()->LoadTexture("SelectUi", "SelectUi.png");
	Engine::Get().GetResource()->LoadTexture("Param", "Parameters.png");
	Engine::Get().GetResource()->LoadTexture("Waffuru", "waffuru.tif");
}

void GameScene::PanzerSelect::Thread_C()
{
	Engine::Get().GetResource()->LoadTexture("Ui03", "Ui03.png");
	Engine::Get().GetResource()->LoadTexture("Plane", "Plane.png");	
	Engine::Get().GetResource()->LoadTexture("SelectList", "psUI.png");
}

void GameScene::PanzerSelect::Thread_D()
{
	// ���f��
	Engine::Get().GetResource()->LoadModel("PanzerGarage", "Other\\souko.obj");
}

#pragma endregion GameScene::PanzerSelect���\�b�h

#pragma region GameScene::Tutorial_method
void GameScene::Tutorial::Init()
{
	AddGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	AddGameObject<TutorialStage>(ELayer::LAYER_3D_STAGE);
	AddGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	AddGameObject<GameBg::Scope>(ELayer::LAYER_2D_UI);
	AddGameObject<GameCommand>(ELayer::LAYER_SYSTEM);
	AddGameObject<Pause>(ELayer::LAYER_2D_BG);
	AddGameObject<GameBg::TutorialUi>(ELayer::LAYER_2D_UI);
	AddGameObject<PauseCommand>(ELayer::LAYER_SYSTEM);
	AddGameObject<GameManager>(ELayer::LAYER_SYSTEM);
	AddGameObject<GameBg::Hp>(ELayer::LAYER_2D_UI);
	AddGameObject<GameBg::DrawSkill>(ELayer::LAYER_2D_UI);
	Load();
	Begin();
}

void GameScene::Tutorial::Uninit()
{
	Unload();
	Scene::Uninit();
}
void GameScene::Tutorial::Load()
{
	Engine::Get().GetResource()->AudioLoad("Select", false);
	Engine::Get().GetResource()->AudioLoad("Shot", false);
	Engine::Get().GetResource()->AudioLoad("Idel", true);
	Engine::Get().GetResource()->LoadTexture("Target", "Target.png");
	Engine::Get().GetResource()->LoadTexture("Ui04", "Ui04.png");
}

void GameScene::Tutorial::Unload()
{
	Engine::Get().GetResource()->UnloadTexture("Ui04");
	Engine::Get().GetResource()->UnloadTexture("Target");
	Engine::Get().GetResource()->AudioUnload();
}
#pragma endregion GameScene::Tutorial���\�b�h

#pragma region GameScene::Game_method
void GameScene::Game::Init()
{
	AddGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	AddGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	AddGameObject<Enemy>(ELayer::LAYER_3D_ACTOR);
	AddGameObject<GameStage>(ELayer::LAYER_3D_STAGE);
	AddGameObject<GameBg::Scope>(ELayer::LAYER_2D_UI);
	AddGameObject<GameCommand>(ELayer::LAYER_SYSTEM);
	AddGameObject<Pause>(ELayer::LAYER_2D_BG);
	AddGameObject<PauseCommand>(ELayer::LAYER_SYSTEM);
	AddGameObject<GameBg::DrawGage>(ELayer::LAYER_2D_UI);
	AddGameObject<GameManager>(ELayer::LAYER_SYSTEM);
	AddGameObject<GameBg::Timer>(ELayer::LAYER_2D_UI);
	AddGameObject<GameBg::Hp>(ELayer::LAYER_2D_UI);
	AddGameObject<GameBg::DrawSkill>(ELayer::LAYER_2D_UI);
	Load();
	Begin();
}

void GameScene::Game::Uninit()
{
	Unload();
	Scene::Uninit();
}

void GameScene::Game::Load()
{
	Engine::Get().GetResource()->AudioLoad("Select", false);
	Engine::Get().GetResource()->AudioLoad("Idel", true);
	Engine::Get().GetResource()->AudioLoad("Shot", false);
}

void GameScene::Game::Unload()
{
	Engine::Get().GetResource()->AudioUnload();
}

#pragma endregion GameScene::Game���\�b�h
