/*--------------------------------------------------------------
	
	[Manager.cpp]
	Author : �o���đ�

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
#include "Manager.h"

GameAudio::GameAudio()
{
	Player* player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		std::string name;
		auto resource = Engine::Get().GetResource();
		int32_t Country = player->GetVehicle().GetStatus().GetCountry();
		int32_t r = 0; // ����
		// �������BGM��ς���
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
		resource->AudioLoad(name, true);
		//resource->AudioPlay(name, 0.3f);
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
	// �v���C���[�����������ǂ���
	bool f = IsPlayerWin;
	// ����
	if (f == true)
	{
		name = "Win";
	}
	// ����
	else if(f == false)
	{
		name = "Lose";
	}
	// �o�^�����I�[�f�B�I���Đ�
	Engine::Get().GetResource()->AudioLoad(name, true);
	Engine::Get().GetResource()->AudioPlay(name, 0.3f);
}