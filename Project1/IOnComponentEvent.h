/*-------------------------------------------------------------

	[IOnCompoennt.h]
	Author : �o���đ�

	�����蔻����������̃C�x���g���Ǘ�

--------------------------------------------------------------*/
#pragma once

class IOnComponentEventToPawn
{
public:
	virtual ~IOnComponentEventToPawn() {}
	virtual void BeginOverlap(class Pawn* pawn) = 0;
};

class IOnComponentEventToActor
{
public:
	virtual ~IOnComponentEventToActor() {}
	virtual void BeginOverlap(class Actor* pActor) = 0;
};