/*------------------------------------------------------------

	[vehicle.h]
	Author : �o���đ�

	��Ԃ��\������N���X

-------------------------------------------------------------*/
#pragma once
#include "Actor.h"
#include "Status.h"
#include <string>

class Body;
class Turret;
class MainGun;
class Panzer final : public Actor
{
public:
	Panzer() = delete;
	Panzer(const std::string& PanzerTag);
	~Panzer();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	
	// Setter&&Getter
	// �p�[�c
	const Body& GetBody() const;
	const Turret& GetTurret() const;
	const MainGun& GetMainGun() const;
private:
	// ��Ԃ̃p�[�c
	std::unique_ptr<Body> m_Body;
	std::unique_ptr<Turret> m_Turret;
	std::unique_ptr<MainGun> m_Gun;
	class Resource& m_Resource;
	class Graphics& m_Graphics;
};

