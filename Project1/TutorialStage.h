/*--------------------------------------------------------------

	[TutorialStage.h]
	Author : �o���đ�

	�`���[�g���A���X�e�[�W

---------------------------------------------------------------*/
#pragma once
#include "Stage.h"

// �`���[�g���A���p�̃X�e�[�W
class TutorialStage : public Stage
{
public:
	TutorialStage();
	~TutorialStage();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
};
