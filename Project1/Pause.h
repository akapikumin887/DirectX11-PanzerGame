/*--------------------------------------------------------------
	
	[Pause.h]
	Author : 出合翔太

	ポーズ画面

---------------------------------------------------------------*/
#pragma once
#include "DefaultObject.h"
#include "Renderer2D.h"
#include <memory>
#include <array>

class Renderer2D;
class Pause : public DefaultObject
{
public:
	Pause();
	~Pause();
	void Begin()override;
	void Update()override;
	void Event()override;
	void Draw()override;
	// ポーズ
	void Enable();
	void Disable();
	bool GetEnable()const;

	// ステート
	enum EState : uint32_t
	{
		KEEPON,
		OPERATION,
		END
	};
	void SetState(EState State);
	EState GetState()const
	{
		return m_State;
	}
	// a値
	float GetAlpha()const;

	void KeeponEnable();
	void KeeponDisable();

	void OperationEnable();
	void OperationDisable();
	bool GetOperation() const;

	void EndEnable();
	void EndDisable();
	bool GetEnd()const;

	void SelectTop();
	void SelectBottom();
	bool GetToorBottom();

private:
	void ChangeState(std::unique_ptr<class PauseState> State);

	std::unique_ptr<class Renderer2D> m_RenderBg; // 背景
	std::unique_ptr<class PauseState> m_PauseState;
	EState m_State;
	float m_Alpha = 1.0f;
	float m_Changecolor = 0.01f;
	// ポーズ中かどうか
	bool m_Enable = false;
	// ゲームを続けるか
	bool m_Keepon = false;
	// 操作方法
	bool m_Operation = false;
	// ゲーム終了を選んだか
	bool m_End = false;
	// 上か下か
	bool m_TopToBottom = true;
};


// State
class PauseState
{
public:
	PauseState();
	virtual ~PauseState(){}
	virtual void Draw(Pause* Pause) = 0;
protected:
	class Renderer2D& GetRenderer() const;
private:
	std::shared_ptr<class Renderer2D> m_Renderer; // Ui
};

// 続ける
class Keepon final : public PauseState
{
public:
	Keepon();
	void Draw(Pause* Pause)override;
};

// 操作方法の確認
class Operation final : public PauseState
{
public:
	Operation();
	void Draw(Pause* Pause)override;
};

// ゲーム終了
class GameEnd final : public PauseState
{
public:
	GameEnd();
	void Draw(Pause* Pause)override;
};