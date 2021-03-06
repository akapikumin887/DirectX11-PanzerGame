/*--------------------------------------------------------------

	[BulletComponentEvent.cpp]
	Author : 出合翔太

	弾の当たり判定

---------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "WallBox.h"
#include "Fence.h"
#include "BulletComponentEvent.h"
#include <vector>

void BulletEvent::OnComponentEventWallBox::BeginOverlap(Actor * pActor)
{
	auto list = Engine::Get().GetApplication()->GetScene()->GetGameObjects<WallBox>(ELayer::LAYER_3D_STAGE);
	for (auto i : list)
	{
		if (Intersect(pActor->GetBoxComponent().GetAABB3(), i->GetBoxComponent().GetAABB3()))
		{
			pActor->OnCollisionEnter();
			i->OnCollisionEnter();
		}
	}
}

void BulletEvent::OnComponentEventFence::BeginOverlap(Actor * pActor)
{
	// フェンス
	std::vector<Fence*> fenceList = Engine::Get().GetApplication()->GetScene()->GetGameObjects<Fence>(ELayer::LAYER_3D_STAGE);
	for (Fence* fence : fenceList)
	{
		if (Intersect(pActor->GetBoxComponent().GetAABB3(), fence->GetBoxComponent().GetAABB3()))
		{
			pActor->OnCollisionEnter();
			fence->OnCollisionEnter();
		}
	}
}