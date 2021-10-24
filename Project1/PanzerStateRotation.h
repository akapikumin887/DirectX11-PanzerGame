/*--------------------------------------------------------------

	[PanzerStateRotation.h]
	Author : �o���đ�

	��]

----------------------------------------------------------------*/
#pragma once
#include "PanzerState.h"

namespace State
{

	class Rotation  : public PanzerState
	{
	public:
		Rotation(){}
		virtual ~Rotation(){}
		void Update(Pawn* pPawn, float deltaTime)override{}
	protected:
		float GetRightDirection(Pawn* pPawn); // �^�[�Q�b�g�̈ʒu�����g���E�ɂ��邩
	};

	// �{�f�B�̐���
	class BodyRotation final : public Rotation
	{
	public:
		BodyRotation();
		~BodyRotation();
		void Update(Pawn* pPawn, float deltaTime)override;
	private:
		int32_t m_Random;
	};

	// �^���b�g�̐���
	class TurretRotation final : public Rotation
	{
	public:
		TurretRotation();
		~TurretRotation();
		void Update(Pawn* pPawn, float deltaTime)override;
	};

	// ��C�̏㉺
	class GunRotation final : public Rotation
	{
	public:
		GunRotation();
		~GunRotation();
		void Update(Pawn* pPawn, float deltaTime)override;
	};
}