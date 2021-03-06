/*--------------------------------------------------------------
	
	[Manager.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "GameManager.h"
#include "Engine.h"
#include "Resource.h"
#include "Application.h"
#include "Vehicle.h"
#include "Status.h"
#include "Player.h"
#include "Audio.h"
#include "Gage.h"
#include "Spawn.h"
#include "AudioManager.h"

GameAudio::GameAudio()
{
	Player* player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		std::string name;
		auto resource = Engine::Get().GetResource();
		int32_t Country = player->GetVehicle().GetStatus().GetCountry();
		int32_t r = 0; // 乱数
		// 戦車のステータスの国によって、BGMを変える
		switch (Country)
		{
		case Status::Country::DE:
			r = myLib::Random::Rand_R(1, 3);
			if (r == 1)
			{
				name = "DE01";
			}
			else if (r == 2)
			{
				name = "DE02";
			}
			break;
		case Status::Country::UK:
			name = "UK01";
			break;
		case Status::Country::US:
			r = myLib::Random::Rand_R(1, 3);
			if (r == 1)
			{
				name = "US01";
			}
			else if (r == 2)
			{
				name = "US02";
			}
			break;
		case Status::Country::RU:
			name = "RU01";
			break;
		}
		
		// オーディオのロードと再生
		resource->AudioLoad(name, true);
		resource->AudioPlay(name, 0.3f);
	}
}

GameAudio::~GameAudio()
{
	
}

void GameAudio::Update(GameManager * manager, Pawn * pawn, int32_t Type)
{
}

ResultAudio::ResultAudio()
{
	
}

ResultAudio::~ResultAudio()
{
	
}

void ResultAudio::Update(GameManager * manager, Pawn * pawn, int32_t Type)
{
}

void ResultAudio::Begin(bool IsPlayerWin)
{
	std::string name;
	// プレイヤーが勝ったかどうか
	bool f = IsPlayerWin;
	// 勝ち
	if (f == true)
	{
		name = "Win";
	}
	// 負け
	else if(f == false)
	{
		name = "Lose";
	}
	// 登録したオーディオを再生
	Engine::Get().GetResource()->AudioLoad(name, true);
	Engine::Get().GetResource()->AudioPlay(name, 0.3f);
}
