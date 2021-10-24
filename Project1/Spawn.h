/*--------------------------------------------------------------
	
	[Spwan.h]
	Author : �o���đ�

	�X�|�[��������

--------------------------------------------------------------*/
#pragma once
#include "Manager.h"
#include "myLib.h"
#include <array>

class Respawn final : public IManager
{
public:
	Respawn();
	~Respawn();
	void Update(GameManager* manager, Pawn* pawn, int32_t Type)override;
	const bool GetRespawn() const;
private:
	std::array<std::unique_ptr<class ISpawn>, 2> m_Spawn;
	bool m_IsRespawn = false; // true�Ń��X�|�[������
};


class ISpawn
{
public:
	ISpawn() = delete;
	ISpawn(const Math::Vector3& pos) : m_SpawnPoint(pos) {}
	virtual ~ISpawn() {}
	virtual void SetSpawn() = 0;
protected:
	const Math::Vector3& GetSpawnPoint() const { return m_SpawnPoint; }
private:
	Math::Vector3 m_SpawnPoint;
};

// �v���C���[�̃X�|�[��
class PlayerSpawn final : public ISpawn
{
public:
	PlayerSpawn();
	~PlayerSpawn();
	void SetSpawn()override;
};

// �G�l�~�[�̃X�|�[��
class EnemySpawn final : public ISpawn
{
public:
	EnemySpawn();
	~EnemySpawn();
	 void SetSpawn()override;
};