/*--------------------------------------------------------------

	[Factory.cpp]
	Author : �o���đ�

	�I�u�W�F�N�g�������Ǘ�����

---------------------------------------------------------------*/
#include "Vehicle.h"
#include "vehicle.h"
#include "PanzerPilot.h"
#include "Shadow.h"
#include "Factory.h"
#include "PanzerContainer.h"
#include "PanzerNameList.h"
#include "PanzerList.h"

Factory::FVehicle::FVehicle()
{	
	m_PanzerNameList = PanzerNameList::Get().GetPanzerList();
}

Factory::FVehicle::~FVehicle()
{
}

// �r�[�N��
std::unique_ptr<class Vehicle> Factory::FVehicle::Create(int32_t Type)
{
	// �ꎞ�ۑ�
	std::unique_ptr<Vehicle> tmp = nullptr;
	PanzerContainer pc;
	// CPU���ɐݒ肷���Ԃ����߂�
	pc.DecisionofCpuPanzer();
	switch (Type)
	{
	case EType::E_PLAYER:
		tmp = Create(pc.StringFindPlayerTag());
		return tmp;
		break;
	case EType::E_CPU:
		tmp = Create(pc.StringFindCpuTag());
		return tmp;
		break;
	}
	return nullptr;
}

std::unique_ptr<class Vehicle> Factory::FVehicle::Create(const std::string & name)
{
	// ��Ԃ̃��X�g�����v�������̂�����
	if (name == m_PanzerNameList[0])
	{
		return std::make_unique<Tiger>();
	}
	else if (name == m_PanzerNameList[1])
	{
		return std::make_unique<Centurion>();
	}
	else if (name == m_PanzerNameList[2])
	{
		return std::make_unique<Patton>();
	}
	else if (name == m_PanzerNameList[3])
	{
		return std::make_unique<T_34_85>();
	}
	else if (name == m_PanzerNameList[4])
	{
		return std::make_unique<IV_H>();
	}
	else if(name == m_PanzerNameList[5])
	{
		return std::make_unique<Sherman>();
	}

	return nullptr;
}

const std::vector<std::string>& Factory::FVehicle::GetPanzerNameList() const
{
	return m_PanzerNameList;
}

// ���
std::unique_ptr<class Panzer> Factory::FPanzer::Create(const std::string & PanzerName)
{
	return std::make_unique<Panzer>(PanzerName);
}

// ���
std::unique_ptr<class PanzerPilot> Factory::FPilot::Create(Vehicle & vehicle)
{
	std::unique_ptr<PanzerPilot> tmp = std::make_unique<PanzerPilot>(vehicle);
	auto pos = vehicle.GetBodyTransform().GetPosition();
	pos.y += 5.0f;
	// �����ʒu�̐ݒ�
	tmp->GetTransform().SetPosition(pos);
	tmp->GetTransform().SetRotation(vehicle.GetBodyTransform().GetRotation());
	return tmp;
}

// �e
std::unique_ptr<class Shadow> Factory::FShadow::Create()
{
	return std::make_unique<Shadow>();
}