/*--------------------------------------------------------------

	[PanzerState.cpp]
	Author ; �o���đ�

---------------------------------------------------------------*/
#include "PanzerState.h"
#include "Player.h"
#include "Vehicle.h"
#include "Body.h"
#include "Engine.h"
#include "Application.h"


PanzerState::PanzerState()
{
}

// ���݂̃v���C���[�̈ʒu
const Math::Vector3& PanzerState::SearchPlayer() const
{
	Math::Vector3& playerPosition = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->GetVehicle().GetBodyTransform().GetPosition();
	return playerPosition;
}