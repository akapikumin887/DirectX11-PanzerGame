/*--------------------------------------------------------------
	
	[Parameters.h]
	Author : �o���đ�

	�p�����[�^�̕\��

---------------------------------------------------------------*/
#pragma once
#include "myLib.h"
#include "Bg.h"

// �p�����[�^�\��
class Parameters final 
{
public:
	Parameters();
	~Parameters();
	void Draw(float Param, const Math::Vector2& pos);
private:
	std::unique_ptr<class Render> m_Render;
	std::unique_ptr<class Renderer2D> m_Bg;
};