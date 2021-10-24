/*-------------------------------------------------------------
	
	[StageObejct.cpp]
	Author : �o���đ�

--------------------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "StageObject.h"

StageObject::StageObject() : m_Resource(*Engine::Get().GetResource())
{
}

StageObject::~StageObject()
{
}

void StageObject::Begin()
{
}

void StageObject::Update()
{
}

void StageObject::Event()
{
}

void StageObject::Draw()
{
}

Resource & StageObject::GetResource() const
{
	return m_Resource;
}
