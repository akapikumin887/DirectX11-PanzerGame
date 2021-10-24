/*--------------------------------------------------------------
	
	[Target.cpp]
	Author : �o���đ�

---------------------------------------------------------------*/
#include "Target.h"
#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "Resource.h"
#include "GameCamera.h"
#include "Pause.h"
#include "NormalBullet.h"

Target::Target()
{
	m_Transform = Actor::AddComponent<Transform>();
	m_BoxComponent = Actor::AddComponent<BoxComponent>();
}

Target::~Target()
{
}

void Target::Begin()
{
	m_Transform->SetScale(5.0f, 5.0f, 1.0f);
	m_BoxComponent->SetSphere3(*m_Transform, 5.0f);
}

void Target::Update()
{
	auto pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG);
	if (pause->GetEnable()) { return; }
	// �^�[�Q�b�g
	auto Bullet = Engine::Get().GetApplication()->GetScene()->GetGameObject<NormalBullet>(ELayer::LAYER_3D_ACTOR);
	if(Bullet)
	{
		if (m_NotDraw == false)
		{
			if (Intersect(Bullet->GetBoxComponent().GetSphere3(), m_BoxComponent->GetSphere3()))
			{
				Bullet->OnCollisionEnter();
				// ����������`�悵�Ȃ�
				m_NotDraw = true;
				m_CoolTime = 100; // ����
			}
		}
	}

	if (m_NotDraw)
	{
		m_CoolTime--;
		// �N�[���^�C����0�Ȃ�`�悷��
		if (m_CoolTime <= 0)
		{
			m_NotDraw = false;
		}
	}
	Actor::UpdateCollision(*m_BoxComponent);
}

void Target::Event()
{
	
}

void Target::Draw()
{
	if (!m_NotDraw)
	{
		// �}�g���N�X�̐ݒ�
		auto camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);

		DirectX::XMMATRIX scale = Math::Matrix::MatrixScaling(m_Transform->GetScale());
		DirectX::XMMATRIX trans = Math::Matrix::MatrixTranslation(m_Transform->GetPosition());
		DirectX::XMMATRIX world = scale * trans;
		m_Graphics.SetWorldMatrix(world);

		// �}�e���A��
		Material m;
		m.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Graphics.SetMaterial(m);

		// �e�N�X�`���̐ݒ�
		m_Resource.SetTexture(0, "Target");

		Effect::Draw();
		m_BoxComponent->SystemDraw();
	}
}
