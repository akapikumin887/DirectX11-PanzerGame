/*--------------------------------------------------------------

	[Status.h]
	Author : �o���đ�

	��Ԃ̃X�e�[�^�X

---------------------------------------------------------------*/
#pragma once
#include "stdafx.h"

class Status
{
public:
	enum Country : int32_t
	{
		DE, // �h�C�c
		UK, // �C�M���X
		US, // �A�����J
		RU, // ���V�A
	};

	Status() = delete;
	// param = ���AHp�A�U���́A�h��́A�ړ����x�A���U���ԁA��]���x
	Status(Country country, float cost, float hp, float attack, float defence, float speed, float reloadTime, float rotSpeed);
	~Status();
	
	void Update();
	void ResetReloadTime();

	// ��
	const Country& GetCountry() const;

	// �R�X�g
	const float GetCost() const;

	// HP
	const float GetMaxHp()const;
	void SetHp(float Hp);
	const float GetHp() const;

	// �U����
	void SetAttack(float Attack);
	const float GetAttack()const;

	// �h���
	void SetDefence(float Defence);
	const float GetDefence()const;

	// �ړ����x
	void SetSpeed(float Speed);
	const float GetSpeed() const;
	// �����x
	void SetAddForce(float force);
	const float GetAddForce() const;

	// ��]���x
	const float GetRotSpeed() const;
	
	// ��C�̍ő�p�x
	const float GetGunAngleUpMax() const;
	const float GetGunAngleDownMax() const;

	void SetReloadTime(float Time);
	// �����[�h�͊������Ă��邩
	const float GetReloadTime()const;
	const bool GetFinishReload() const;
private:
	Country m_Country;
	const float m_MaxHp; // Max�l
	const float m_ReloadTime; // �����[�h�ɕK�v�ȕb��
	
	float m_Cost; // ��Ԃ̃R�X�g
	float m_Hp;		// Hp
	float m_Attack; // �U����
	float m_Defense;  // �h���

	float m_Time; // �����[�h�����鎞��
	float m_NowReloadTime; // �����[�h���Ԓ�

	float m_Speed; // �ړ����x
	float m_AddForce = 0.1f; // �����x
	float m_RotSpeed; // ��]���x

	// ��C�̍ő�l
	const float m_GunUpMax;
	const float m_GunDownMax;

	bool m_FinishReload;  // true�Ō����Ƃ��ł���
};

