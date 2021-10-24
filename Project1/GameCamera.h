/*------------------------------------------------------------

	[GameCamera.h]
	Author : �o���đ�

	�Q�[���p�J����

--------------------------------------------------------------*/
#pragma once
#include "Camera.h"

// �Q�[���J����
class CameraMode;
class GameCamera final : public Camera
{
public:
	GameCamera();
	~GameCamera();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;

	// �J�������[�h�̕ύX
	void ChangeMode(std::unique_ptr<CameraMode> Mode);

	// Getter/Setter
	const DirectX::XMMATRIX GetInverseView() const;  // �t�s��

	void ChangeCameraMode(bool Change);
	const bool GetChageMode() const;
private:
	std::unique_ptr<CameraMode> m_Mode;	// �J�������[�h
	bool m_IsChangeMode; // �J�����̃��[�h��؂�ւ��� true�̂Ƃ�FPS�J�����ɂ���
};
