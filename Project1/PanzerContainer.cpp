/*--------------------------------------------------------------

	[PanzerContainer.cpp]
	Author : �o���đ�

	��Ԃ̃f�[�^�������Ă���R���e�i

---------------------------------------------------------------*/
#include "Cost.h"
#include "Parameters.h"
#include "PanzerContainer.h"
#include "Vehicle.h"
#include "PanzerList.h"
#include "Application.h"
#include "myLib.h"
#include "Shadow.h"
#include "Factory.h"
#include "PanzerNameList.h"

std::string PanzerContainer::m_PlayerofSelectedPanzer; // �v���C���[�̑I��������Ԃ��i�[
std::string PanzerContainer::m_CpuofSelectedPanzer; // �G���I�񂾐��

PanzerContainer::PanzerContainer() : m_Choose(0)
{
	m_PanzerName = PanzerNameList().Get().GetPanzerList();
}

PanzerContainer::~PanzerContainer()
{
}

void PanzerContainer::Begin()
{
	m_Parameters = std::make_unique<Parameters>();
	m_Number = std::make_unique<Cost>();
	Factory::FVehicle f;
	m_Map[m_PanzerName[0]] = f.Create(m_PanzerName[0]);
	m_Map[m_PanzerName[0]]->SetStartPosition(Math::Vector3(0.0f, 0.0f, 20.0f), Math::Vector3(0.0f, Math::ToRadians(180.0f), 0.0f));
	m_PlayerofSelectedPanzer = "Tiger";
}

void PanzerContainer::Update()
{
	// ��Ԃ̑I�����O�ƈႤ���ǂ���
	if (m_PanzerName[m_Choose] != m_PlayerofSelectedPanzer)
	{
		// �O�ɑI�����Ă�����Ԃ̃C���X�^���X�͍폜����
		m_Map[m_PlayerofSelectedPanzer].reset();
		// ���̐�Ԃ��Z�b�g
		Factory::FVehicle f;
		m_Map[m_PanzerName[m_Choose]] = f.Create(m_PanzerName[m_Choose]);
		m_Map[m_PanzerName[m_Choose]]->SetStartPosition(Math::Vector3(0.0f, 0.0f, 20.0f), Math::Vector3(0.0f, Math::ToRadians(180.0f), 0.0f));
	}

	// �o�^��Ԃ��X�V����
	m_PlayerofSelectedPanzer = m_PanzerName[m_Choose];
	// �p�����[�^�擾
	m_Cost = m_Map[m_PanzerName[m_Choose]]->GetStatus().GetCost();
	m_Hp = m_Map[m_PanzerName[m_Choose]]->GetStatus().GetHp();
	m_Attack = m_Map[m_PanzerName[m_Choose]]->GetStatus().GetAttack();
	m_Defence = 1.5f * m_Map[m_PanzerName[m_Choose]]->GetStatus().GetDefence();
	m_Speed = 3.0f * m_Map[m_PanzerName[m_Choose]]->GetStatus().GetSpeed();
	m_Reload = 300.0f - (20.0f * m_Map[m_PanzerName[m_Choose]]->GetStatus().GetReloadTime());
}

void PanzerContainer::Event()
{
}

void PanzerContainer::Draw()
{
	// �I�𒆂̐��
	m_Map[m_PanzerName[m_Choose]]->Draw();
	// �R�X�g
	m_Number->Draw((int32_t)m_Cost);
	// HP
	m_Parameters->Draw(m_Hp * 0.1f, Math::Vector2(1500.0f, 290.0f));
	// �U����
	m_Parameters->Draw(m_Attack, Math::Vector2(1500.0f, 360.0f));
	// ���b
	m_Parameters->Draw(m_Defence, Math::Vector2(1500.0f, 430.0f));
	// ���x
	m_Parameters->Draw(m_Speed, Math::Vector2(1500.0f, 500.0f));
	// ���U���x
	m_Parameters->Draw(m_Reload, Math::Vector2(1500.0f, 570.0f));
}

void PanzerContainer::SetChooseUp()
{
	m_Choose--;
	if (m_Choose < 0)
	{
		m_Choose = m_PanzerName.size() - 1;
	}
	m_InputButton = 1;
}

void PanzerContainer::SetChooseDown()
{
	m_Choose++;
	if (m_Choose == m_PanzerName.size())
	{
		m_Choose = 0;
	}
	m_InputButton = 2;
}

void PanzerContainer::DecisionofCpuPanzer()
{
	uint32_t rand = myLib::Random::Rand_R(0, m_PanzerName.size());
	//  �G�̐�Ԃ������_���őI��
	m_CpuofSelectedPanzer = m_PanzerName[rand];
}

const int32_t PanzerContainer::GetChose() const
{
	return m_Choose;
}

void PanzerContainer::Reset()
{
	m_InputButton = 0;
}

const int32_t PanzerContainer::GetButton() const
{
	return m_InputButton;
}

const std::string & PanzerContainer::StringFindPlayerTag() const
{
	return m_PlayerofSelectedPanzer;
}

const std::string & PanzerContainer::StringFindCpuTag() const
{
	return m_CpuofSelectedPanzer;
}