/*--------------------------------------------------------

		[PanzerNameList.h]
		��Ԃ̖��O�̃��X�g
		Author : �o���đ�

----------------------------------------------------------*/
#pragma once
#include "Singleton.h"
#include <vector>
#include <string>

class PanzerNameList final : public Singleton<PanzerNameList>
{
	friend Singleton<PanzerNameList>;
public:
	void Register(); // ���O�̓o�^
	const std::vector<std::string>& GetPanzerList() const;
private:
	std::vector<std::string> m_PanzerName;
};

