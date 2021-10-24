/*------------------------------------------------------------
	
	[Engine.h]
	Author : �o���đ�

-------------------------------------------------------------*/
#pragma once
#include "Singleton.h"
#include "myLib.h"
#include <Windows.h>

class Graphics;
class Resource;
class Application;
class Engine final : public Singleton<Engine>
{
	friend Singleton<Engine>;
public:
	void Init(HINSTANCE h);
	void Run();
	const Math::Vector2 GetWindowSize() const;
	const float GetWidth() const;
	const float GetHeight() const;
	const HWND& GetHwnd() const;
	const std::shared_ptr<Graphics> GetGraphics() const;
	const std::shared_ptr<Resource> GetResource() const;
	const std::shared_ptr<Application> GetApplication() const;
protected:
	Engine();
	~Engine();
private:
	void CreateGameWindow(HWND& hwnd, WNDCLASSEX& window);
	WNDCLASSEX m_WindowClass;
	HWND m_hwnd;
	
	std::shared_ptr<Graphics> m_Graphics;		// DirectX11
	std::shared_ptr<Resource> m_Resource;		// ���\�[�X�Ǘ�
	std::shared_ptr<Application> m_Application;	// �A�v���P�[�V����
	// Window���[�h/FullScreen���[�h
	bool m_WindowMode;

	// �T�C�Y
	const float m_Width = 1920.0f;
	const float m_Height = 1080.0f;
};

