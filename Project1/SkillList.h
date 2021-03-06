/*--------------------------------------------------

	[SkillList.h]
	Author : oãÄ¾

	XLÌXg

---------------------------------------------------*/
#pragma once
#include "IUseSkill.h"

class Status;
namespace UseSkill
{
	// UÍAbv
	class AttackUp : public IUseSkill
	{
	public:
		AttackUp() = delete;
		AttackUp(float mag);
		void Use(Status& status)override;
		void Reset(Status & status)override;
	private:
		float m_Defualt;
		float m_Mag; // {¦
	};

	// blAbv
	class DefenceUp : public IUseSkill
	{
	public:
		DefenceUp() = delete;
		DefenceUp(float mag);
		void Use(Status& status)override;
		void Reset(Status & status)override;
	private:
		float m_Defualt;
		float m_Mag; // {¦
	};

	// ¬xAbv
	class SpeedUp final : public IUseSkill
	{
	public:
		SpeedUp() = delete;
		SpeedUp(float mag);
		void Use(Status& status)override;
		void Reset(Status & status)override;
	private:
		float m_DefualtSpeed;
		float m_DefualtAddForce;
		float m_Mag; // {¦
	};

	// MAXHPÌ20%ñ
	class HealHp final : public IUseSkill
	{
	public:
		void Use(Status& status)override;
		void Reset(Status & status)override;
	private:
		float m_AmountHeal = 0.2f; // ñ·é = 20%
	};
}
#if 0
// ¡ûÌXLQ[Wð½ßé
class UseSkillAddGage
{

};
#endif


