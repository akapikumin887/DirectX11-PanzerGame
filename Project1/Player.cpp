/*------------------------------------------------------------

	[Player.h]
	Author : 出合翔太

	プレイヤーの処理

-------------------------------------------------------------*/
#include "Input.h"
#include "PanzerState.h"
#include "MoveComponent.h"
#include "Vehicle.h"
#include "PanzerContainer.h"
#include "Engine.h"
#include "Resource.h"
#include "Application.h"
#include "Command.h"
#include "Body.h"
#include "Turret.h"
#include "MainGun.h"
#include "Factory.h"
#include "Pause.h"
#include "Fps.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "PanzerPilot.h"
#include "OnComponentEvent.h"
#include "Player.h"

Player::Player() : Pawn(Factory::FVehicle::EType::E_PLAYER), m_Resource(*Engine::Get().GetResource())
{
	Pawn::Create();
	AddComponentEvent<OnComponentEventWallBox>();
}

Player::~Player()
{
	m_Audioplay = false;
}

void Player::Begin()
{
	Pawn::SetStartPosition(this, Math::Vector3(0.0f, 0.0f, -150.0f), Math::Vector3(0.0f, 0.0f, 0.0f));
}

void Player::Update()
{
	auto pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
	if (pause) { return; }
	OnSound();
	Pawn::Update();
	OnCollision();
}

void Player::Event()
{
	if (CollisionEnter())
	{
		auto enemy = Engine::Get().GetApplication()->GetScene()->GetGameObjects<Enemy>(ELayer::LAYER_3D_ACTOR);
		for (auto e : enemy)
		{
			GetVehicle().CalcuateDamege(e);
			ResetCollisionEnter();
		}
	}
	Pawn::CheckZeroHp(this);
}

void Player::Draw()
{
	GetVehicle().Draw();
}

void Player::ChangeState(std::unique_ptr<PanzerState> State)
{
	
}

void Player::Respawn(const Math::Vector3& pos)
{
	Pawn::SetStartPosition(this, pos, Math::Vector3(0.0f, 0.0f, 0.0f));
	Pawn::RespawnSetMaxHP();
	Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA)->Update();
	this->Update();
}

void Player::OnCollision()
{
	// 敵との当たり判定
	if(TriggerEvent())
	{
			if (Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(0))
			{
				GetMoveComponent().MoveBackward(GetVehicle().GetBodyTransform(), Fps::Get().deltaTime);
			}
			if (Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(1))
			{
				GetMoveComponent().MoveForward(GetVehicle().GetBodyTransform(), Fps::Get().deltaTime);
			}
	}
	BeginOverlap(this);
}

// サウンドを鳴らす
void Player::OnSound()
{
	bool nowInput = false;
	for (int32_t i = 0; i < 2; i++)
	{
		nowInput = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(i);
		if (nowInput == true)
		{
			break;
		}
	}
	myLib::Timeline audioVolume(0.1f, 1.0f, 0.01f);
	// タイムラインの設定
	/// 入力中かどうか調べる
	if (nowInput == true)
	{
		// エンジン音をあげる
		audioVolume.Start(m_Volume);
	}
	else if (nowInput == false)
	{
		// エンジン音を下げる
		audioVolume.Reverce(m_Volume);
	}
	if (m_Audioplay == false)
	{
		m_Resource.AudioPlay("Idel");
		m_Audioplay = true;
	}
	m_Resource.AudioSetVolume("Idel", m_Volume);
}
