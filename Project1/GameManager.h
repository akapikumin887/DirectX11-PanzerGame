/*--------------------------------------------------------------

	[GameManager.h]
	Author : �o���đ�

	�Q�[���̐i�s���Ǘ�

	���X�|�[��, �r�ŃQ�[�W, ���s

---------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "Manager.h"
#include <memory>
#include <array>

enum ID : int32_t
{
	E_Player,
	//E_CPU1,
	E_Enemy1,
	//E_Enemy2,
};

class GameManager final : public DefaultObject
{
public:
	GameManager();
	~GameManager();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;

	// �C�x���g�J�n
	void BeginEvent(class Pawn* pawn, int32_t Id);
	
	// �Q�[���I��
	void GameSet();
	const bool GetGameEnd()const;

	// �ǂ��炪��������
	void SetWinner(int32_t type);
private:
	// true�ŃQ�[���I��
	bool m_GameEnd = false;
	std::array<std::unique_ptr<IManager>, 3> m_Manager;
};

class ResultManager final : public DefaultObject
{
public:
	ResultManager();
	~ResultManager(){}
	void Begin()override;
	void Update()override {}
	void Event()override {}
	void Draw()override {}
};