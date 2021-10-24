/*-----------------------------------------------------------

	[NormalBullet.cpp]
	Author : �o���đ�

	�ʏ�e�̏���

------------------------------------------------------------*/
#include "Vehicle.h"
#include "Engine.h"
#include "Resource.h"
#include "BulletStateMove.h"
#include "BulletStateDestory.h"
#include "Fps.h"
#include "Engine.h"
#include "Application.h"
#include "MuzzleFlash.h"
#include "BulletComponentEvent.h"
#include "Player.h" 
#include "Enemy.h"
#include "NormalBullet.h"

NormalBullet::NormalBullet() : m_Resource(*Engine::Get().GetResource())
{
	AddComponentEvent<BulletEvent::OnComponentEventFence>();
	AddComponentEvent<BulletEvent::OnComponentEventWallBox>();
}

NormalBullet::~NormalBullet()
{
}

void NormalBullet::Begin()
{
}

void NormalBullet::Update()
{
	m_State->Update(this, Fps::Get().deltaTime);
	Actor::UpdateCollision(*m_BoxComponent);
}

void NormalBullet::Event()
{
	if(Actor::CollisionEnter())
	{
		ChangeState(std::make_unique<BulletStateDestory>());
	}
}

void NormalBullet::Draw()
{
	m_Resource.SetShader("Default");
	// �}�g���N�X�ݒ�
	Actor::UpdateMatrix(*m_Transform);
	m_Resource.SetStaticModel("Bullet");
	//m_BoxComponent->SystemDraw();
}

void NormalBullet::Create(const Math::Vector3& Position, const Math::Vector3 & Vector)
{
	// �C���X�^���X����
	Bullet::SetProperty(Vector, 300.0f, 240);
	m_Transform = Actor::AddComponent<Transform>();
	m_Transform->SetPosition(Position);
	m_Transform->SetScale(1.5f);

	m_BoxComponent = Actor::AddComponent<BoxComponent>();
	Math::Vector3 scale = m_Transform->GetScale() * 0.5f;
	m_BoxComponent->SetSphere3(*m_Transform, 1.0f);
	m_BoxComponent->SetAABB3(*m_Transform, scale);
	m_BoxComponent->SetOBB3(*m_Transform, scale);
	m_State = std::make_unique<BulletStateMove>();

	// ���\�[�X
	auto effect = Engine::Get().GetApplication()->GetScene()->AddGameObject<MuzzleFlash>(ELayer::LAYER_2D_EFFECT);
	effect->GetTransform().SetPosition(Position);
}

void NormalBullet::ChangeState(std::unique_ptr<BulletState> State)
{
	m_State = std::move(State);
}

void NormalBullet::OnCollision()
{
	BeginOverlap(this);
}