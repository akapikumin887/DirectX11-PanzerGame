/*--------------------------------------------------------

		[PanzerNameList.cpp]
		��Ԃ̖��O�̃��X�g
		Author : �o���đ�

----------------------------------------------------------*/
#include "PanzerNameList.h"

void PanzerNameList::Register()
{
	m_PanzerName = { "Tiger", "Centurion", "Patton", "T-34-85", "IV-H", "Shrman" };
}

const std::vector<std::string>& PanzerNameList::GetPanzerList() const
{
	return m_PanzerName;
}
