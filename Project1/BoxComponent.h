/*----------------------------------------------------------
	
	[BoxComponent.h]
	Author : ?o???đ?

-----------------------------------------------------------*/
#pragma once
#include "Collision.h"
#include <memory>

class Sphere3;
class AABB3;
class OBB3;
class BoxComponent final
{
public:
	BoxComponent();
	~BoxComponent();
	void Update(const Math::Vector3& Position, const class Transform& t);
	void SystemDraw();
	// Sphere3
	void SetSphere3(const Transform& t, const float& Radius);
	const Sphere3& GetSphere3()const;
	// AABB3
	void SetAABB3(const Transform& t, const Math::Vector3& Size);
	const AABB3& GetAABB3() const;
	// OBB3
	void SetOBB3(const Transform& t, const Math::Vector3& Size);
	const OBB3& GetOBB3()const;
private:
	std::unique_ptr<Sphere3> m_sphere;
	std::unique_ptr<AABB3> m_aabb;
	std::unique_ptr<OBB3> m_obb;
};

void CollisionTriggerEvent();