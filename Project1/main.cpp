/*------------------------------------------------------------
	
	[main.cpp]
	Author : �o���đ�

-------------------------------------------------------------*/
#include "Engine.h"

int APIENTRY WinMain(HINSTANCE h, HINSTANCE p, LPSTR l, int c)
{
	auto& engine = Engine::Get();
	engine.Init(h);
	engine.Run();
	return 0;
}