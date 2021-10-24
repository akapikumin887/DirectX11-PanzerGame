/*------------------------------------------------------------
	
	[Stage.h]
	Author : �o���đ�

	�X�e�[�W�N���X
	�X�e�[�W�ɔz�u����N���X��ݒ肷��

-------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "ISetterObject.h"
#include <vector>

class Stage : public DefaultObject
{
public:
	Stage() {}
	virtual ~Stage() {}
	void Begin()override {}
	void Update()override {}
	void Event()override {}
	void Draw()override {}
protected:
	// �ǉ�
	template<typename T>
	void AddObject()
	{
		m_Object.emplace_back(std::make_unique<T>());
	}
	/// �폜
	void Remove()
	{
		m_Object.clear();
		assert(m_Object.empty());
	}
	// �ݒu
	void AllSet(Scene* scene)
	{
		for (auto& obj : m_Object)
		{
			obj->Set(scene);
		}
	}

	class Scene* m_Scene;
private:
	std::vector<std::unique_ptr<ISetterObject>> m_Object;
};
