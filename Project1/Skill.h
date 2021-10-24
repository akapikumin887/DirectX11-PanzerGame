/*---------------------------------------------------------------

	[Skill.h]
	Author : �o���đ�

	�X�L�����Ǘ�����

----------------------------------------------------------------*/
#pragma once
#include <memory>
#include <vector>

class Status;
class IUseSkill;
class Skill
{
public:
	Skill();
	~Skill();
	void SetSkill(std::unique_ptr<IUseSkill> useSkill);
	void Begin(float enableTime);
	void Update(Status& status);
	void SetTime(float time); //�@�i�߂鎞��
	void Enable();
	const int32_t GetPhase() const;
	const float GetEnableTime() const;
	const bool GetAlreadyUseble() const;
private:
	std::vector<std::unique_ptr<IUseSkill>> m_UseSkill;
	int32_t m_Phase = 0;	// �t�F�[�Y
	float m_EnableTime = 30.0f;		// �X�L����L���ɂ��鎞��
	float m_Time = 1.0f;	// �i�߂鎞��
	float m_NowTime = 0.0f;
	bool m_AlreadyUseble = false; // �X�L�����g�����Ԃ��ǂ���
};