/*--------------------------------------------------------------
	
	[Manager.h]
	Author : �o���đ�

	�Ǘ��N���X

----------------------------------------------------------------*/
#pragma once
#include <stdint.h>
#include <memory>
#include <string>

class GameManager;
class Pawn;
class IManager
{
public:
	virtual ~IManager() {};
	virtual void Update(GameManager* manager, Pawn* pawn, int32_t Type) = 0;
};

// �Q�[��BGM
class GameAudio final : public IManager
{
public:
	GameAudio();
	~GameAudio();
	void Update(GameManager* manager, Pawn* pawn, int32_t Type)override;
};

// ���U���gBGM
class ResultAudio final : public IManager
{
public:
	ResultAudio();
	~ResultAudio();
	void Update(GameManager* manager, Pawn* pawn, int32_t Type)override;
	void Begin(bool IsPlayerWin);
};