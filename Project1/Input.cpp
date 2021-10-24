/*-------------------------------------------------------------
	
	[Input.cpp]
	Author : �o���đ�

--------------------------------------------------------------*/
#include "Input.h"

LPDIRECTINPUT8			InputDevice::m_Input = NULL;			//	DirectInput�I�u�W�F�N�g

LPDIRECTINPUTDEVICE8	KeyBoard::m_DevKeyboard = NULL;				//	�L�[�{�[�h�f�o�C�X
BYTE					KeyBoard::m_aKeyState[NUM_KEY_MAX];			//	�L�[�{�[�h���i�����Ă���ԁj
BYTE					KeyBoard::m_aKeyStateTrigger[NUM_KEY_MAX];	//	�L�[�{�[�h���i�������u�ԁj
BYTE					KeyBoard::m_aKeyStateRelease[NUM_KEY_MAX];	//	�L�[�{�[�h���i�������u�ԁj

LPDIRECTINPUTDEVICE8	GamePad::m_GamePad[GAMEPADMAX] = { NULL, NULL, NULL, NULL };	//	�p�b�h�f�o�C�X
DWORD					GamePad::m_padState[GAMEPADMAX];								//	�p�b�h���i�����Ă���ԁj
DWORD					GamePad::m_padTrigger[GAMEPADMAX];								//	�p�b�h���i�������u��
int						GamePad::m_padCount = 0;	//	���o�����p�b�h�̐�

LPDIRECTINPUTDEVICE8	Mouse::m_Mouse = NULL;		//	�}�E�X�f�o�C�X
DIMOUSESTATE2			Mouse::m_mouseState;		//	�}�E�X�̃_�C���N�g�ȏ��
DIMOUSESTATE2			Mouse::m_mouseTrigger;		//	�����ꂽ�u�Ԃ���ON

#pragma region Proces_Input
//	���͏����̏�����
bool InputDevice::Init(HINSTANCE hInstance, HWND hWnd, bool UseMouse)
{
	if (m_Input == NULL)
	{
		//	�쐬�̎��s
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_Input, NULL)))
		{
			return false;
		}
	}
	//	���̓f�o�C�X�̏�����
	KeyBoard::Init(hInstance, hWnd);
	GamePad::Init(hInstance, hWnd);
	Mouse::Init(hInstance, hWnd, UseMouse);
	return true;
}

//	���͏����̏I������
void InputDevice::Uninit()
{
	Mouse::Uninit();
	GamePad::Uninit();
	KeyBoard::Uninit();
}

//	���͏����̍X�V����
void InputDevice::Update()
{
	KeyBoard::Update();
	GamePad::Update();
	Mouse::Update();
}
#pragma endregion �e�N���XInput�̏���

#pragma region Proces_KeyBoard
//	�L�[�{�[�h�̏�����
HRESULT KeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(m_Input->CreateDevice(GUID_SysKeyboard, &m_DevKeyboard, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return false;
	}

	if (FAILED(m_DevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return false;
	}
	//													 DISCL_BACKGROUND | DISCL_EXCLUSIVE	
	if (FAILED(m_DevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return false;
	}
	m_DevKeyboard->Acquire();
	return true;
}

//	�L�[�{�[�h�̏I������
void KeyBoard::Uninit()
{
	SAFE_RELEASE(m_DevKeyboard);
}

//	�L�[�{�[�h�̍X�V����
void KeyBoard::Update()
{
	BYTE aKeyState[NUM_KEY_MAX];

	if (SUCCEEDED(m_DevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			m_aKeyStateTrigger[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			m_aKeyStateRelease[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & m_aKeyState[nCnKey];

			m_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		m_DevKeyboard->Acquire();
	}
}

//�@�L�[�{�[�h�������Ă����
bool KeyBoard::IsPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//�@�L�[�{�[�h���������u��
bool KeyBoard::IsTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//�@�L�[�{�[�h�𗣂����Ƃ�
bool KeyBoard::IsRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
#pragma endregion �L�[�{�[�h�̏���

#pragma region Proces_GamePad
//�@�Q�[���p�b�h�p�R�[���o�b�N�֐�
BOOL GamePad::SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID)
{
	HRESULT result;

	result = m_Input->CreateDevice(lpddi->guidInstance, &m_GamePad[m_padCount++], NULL);
	return DIENUM_CONTINUE;	// ���̃f�o�C�X���
}

//�@�Q�[���p�b�h�̏���������
HRESULT GamePad::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT		result;
	int			i;

	m_padCount = 0;
	// �W���C�p�b�h��T��
	m_Input->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamePadCallback, NULL, DIEDFL_ATTACHEDONLY);
	// �Z�b�g�����R�[���o�b�N�֐����A�p�b�h�𔭌������������Ă΂��B

	for (i = 0; i < m_padCount; i++)
	{
		// �W���C�X�e�B�b�N�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
		result = m_GamePad[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(result))
			return false; // �f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s

		// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		//		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		//		if ( FAILED(result) )
		//			return false; // ���[�h�̐ݒ�Ɏ��s

		// ���̒l�͈̔͂�ݒ�
		// X���AY���̂��ꂼ��ɂ��āA�I�u�W�F�N�g���񍐉\�Ȓl�͈̔͂��Z�b�g����B
		// (max-min)�́A�ő�10,000(?)�B(max-min)/2�������l�ɂȂ�B
		// ����傫������΁A�A�i���O�l�ׂ̍��ȓ�����߂炦����B(�p�b�h�̐��\�ɂ��)
		DIPROPRANGE				diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = RANGE_MIN;
		diprg.lMax = RANGE_MAX;
		// X���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_X;
		m_GamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_Y;
		m_GamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �e�����ƂɁA�����̃]�[���l��ݒ肷��B
		// �����]�[���Ƃ́A��������̔����ȃW���C�X�e�B�b�N�̓����𖳎�����͈͂̂��ƁB
		// �w�肷��l�́A10000�ɑ΂��鑊�Βl(2000�Ȃ�20�p�[�Z���g)�B
		DIPROPDWORD				dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = DEADZONE;
		//X���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_X;
		m_GamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_Y;
		m_GamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		//�W���C�X�e�B�b�N���͐���J�n
		m_GamePad[i]->Acquire();
	}

	return true;
}

//	�Q�[���p�b�h�̏I������
void GamePad::Uninit()
{
	for (int i = 0; i < GAMEPADMAX; i++)
	{
		SAFE_RELEASE(m_GamePad[i]);
	}
}

//�@�Q�[���p�b�h�̍X�V����
void GamePad::Update()
{
	HRESULT			result;
	DIJOYSTATE2		dijs;	//�Q�[���p�b�h�̓��͒l
	int				i;
	long StickDefualt = 32767; //�E�X�e�B�b�N�̃f�t�H���g�l
	long offset = 2000; // �E�X�e�B�b�N�̃f�b�h�]�[���l

	for (i = 0; i < m_padCount; i++)
	{
		DWORD lastPadState;
		lastPadState = m_padState[i];	//�Q�[���p�b�h�̃{�^���z��
		m_padState[i] = 0x00000000l;	// ���͗p32�r�b�g�̏�����

		result = m_GamePad[i]->Poll();	// �W���C�X�e�B�b�N�Ƀ|�[����������
		if (FAILED(result))
		{
			result = m_GamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = m_GamePad[i]->Acquire();
		}

		result = m_GamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// �f�o�C�X��Ԃ�ǂݎ��
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
		{
			result = m_GamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = m_GamePad[i]->Acquire();
		}

		/*---------------------------------------------------------------------------------------------------
			�R�Q�̊e�r�b�g�ɈӖ����������A�{�^�������ɉ����ăr�b�g���I���ɂ���//long�^�f�t�H���g�i32767���炢�j
		-----------------------------------------------------------------------------------------------------*/

		//�@��	����
		//! �ԁ@Xbox�̂�
		//" �@PS4�̂�
		//!	���Ӂ@Xbox��PS4�̓��͂𓯎��Ɏg��Ȃ�����

		// Xbox��PS4:���X�e�B�b�Ny-axis (forward)
		if (dijs.lY < 0)					m_padState[i] |= LEFTSTICK_UP;
		// Xbox��PS4:���X�e�B�b�Ny-axis (backward)
		if (dijs.lY > 0)					m_padState[i] |= LEFTSTICK_DOWN;
		// Xbox��PS4:���X�e�B�b�Nx-axis (left)
		if (dijs.lX < 0)					m_padState[i] |= LEFTSTICK_LEFT;
		// Xbox��PS4:���X�e�B�b�Nx-axis (right)
		if (dijs.lX > 0)					m_padState[i] |= LEFTSTICK_RIGHT;

		//! Xbox:�E�X�e�B�b�Ny-axis (forward)
		if (dijs.lRy < StickDefualt - offset)				m_padState[i] |= XboxRIGHTSTICK_UP;
		//! Xbox:�E�X�e�B�b�Ny-axis (backward)
		if (dijs.lRy > StickDefualt + offset)				m_padState[i] |= XboxRIGHTSTICK_DOWN;
		//! Xbox:�E�X�e�B�b�Nx-axis (left)
		if (dijs.lRx < StickDefualt - offset)				m_padState[i] |= XboxRIGHTSTICK_LEFT;
		//! Xbox:�E�X�e�B�b�Nx-axis (right)
		if (dijs.lRx > StickDefualt + offset)				m_padState[i] |= XboxRIGHTSTICK_RIGHT;

		//" PS4:�E�X�e�B�b�Ny-axis (forward)
		if (dijs.lRz < StickDefualt - offset)				m_padState[i] |= RIGHTSTICK_UP;
		//" PS4:�E�X�e�B�b�Ny-axis (backward)
		if (dijs.lRz > StickDefualt + offset)				m_padState[i] |= RIGHTSTICK_DOWN;
		//" PS4:�E�X�e�B�b�Nx-axis (left)
		if (dijs.lZ < StickDefualt - offset)				m_padState[i] |= RIGHTSTICK_LEFT;
		//" PS4:�E�X�e�B�b�Nx-axis (right)
		if (dijs.lZ > StickDefualt + offset)				m_padState[i] |= RIGHTSTICK_RIGHT;

		//! Xbox:LT�g���K�[
		if (dijs.lZ > StickDefualt + offset)				m_padState[i] |= TRIGGER_LT;
		//! Xbox:RT�g���K�[
		if (dijs.lZ < StickDefualt - offset)				m_padState[i] |= TRIGGER_RT;
		//" PS4:L2�g���K�[
		if (dijs.lRx > 10000)				m_padState[i] |= TRIGGER_L2;
		//" PS4:R2�g���K�[
		if (dijs.lRy > 10000)				m_padState[i] |= TRIGGER_R2;

		//* Xbox:�`�{�^��	�@PS4�F���{�^��
		if (dijs.rgbButtons[0] & 0x80)		m_padState[i] |= BUTTON_1;
		//* Xbox:�w�{�^��	  PS4�F�Z�{�^��
		if (dijs.rgbButtons[2] & 0x80)		m_padState[i] |= BUTTON_2;
		//* Xbox:�a�{�^��	�@PS4�F�~�{�^��
		if (dijs.rgbButtons[1] & 0x80)		m_padState[i] |= BUTTON_3;
		//*	Xbox:�x�{�^��	�@PS4�F���{�^��
		if (dijs.rgbButtons[3] & 0x80)		m_padState[i] |= BUTTON_4;
		//* Xbox:LB�{�^��	�@PS4�FL1�{�^��
		if (dijs.rgbButtons[4] & 0x80)		m_padState[i] |= BUTTON_L1;
		//* Xbox:RB�{�^��	�@PS4�FR1�{�^��
		if (dijs.rgbButtons[5] & 0x80)		m_padState[i] |= BUTTON_R1;
		//* Xbox:BACK�{�^�� �@PS4 : OPTION�{�^��
		if (dijs.rgbButtons[6] & 0x80)		m_padState[i] |= BUTTON_BACK;
		//* Xbox:START�{�^���@PS4 : SHARE�{�^��
		if (dijs.rgbButtons[7] & 0x80)		m_padState[i] |= BUTTON_START;

		//! Xbox:L3�{�^��	
		if (dijs.rgbButtons[8] & 0x80)		m_padState[i] |= BUTTON_L3;
		//! Xbox:R3�{�^��	
		if (dijs.rgbButtons[9] & 0x80)		m_padState[i] |= BUTTON_OPTION;

		//* Xbox��PS4�F�����L�[��
		if (dijs.rgdwPOV[0] <= 0)									m_padState[i] |= BUTTON_UP;
		//* Xbox��PS4�F�����L�[��
		if (dijs.rgdwPOV[0] <= 18000 && dijs.rgdwPOV[0] > 9000)		m_padState[i] |= BUTTON_DOWN;
		//* Xbox��PS4�F�����L�[��
		if (dijs.rgdwPOV[0] <= 27000 && dijs.rgdwPOV[0] > 18000)	m_padState[i] |= BUTTON_LEFT;
		//* Xbox��PS4�F�����L�[�E
		if (dijs.rgdwPOV[0] <= 9000 && dijs.rgdwPOV[0] > 0)			m_padState[i] |= BUTTON_RIGHT;

		// Trigger�ݒ�
		m_padTrigger[i] = ((lastPadState ^ m_padState[i])	// �O��ƈ���Ă���
			& m_padState[i]);					// ��������ON�̂��

	}
}

//�@�Q�[���p�b�h�̃{�^���������Ă����
BOOL GamePad::IsPress(int padNo, DWORD button)
{
	return (button & m_padState[padNo]);
}

//�@�Q�[���p�b�h�̃{�^�����������u��
BOOL GamePad::IsTrigger(int padNo, DWORD button)
{
	return (button & m_padTrigger[padNo]);
}

#pragma endregion �Q�[���p�b�h�̏���

#pragma region Proces_Mouse
//	�}�E�X�̏�����
HRESULT Mouse::Init(HINSTANCE hInst, HWND hWnd, bool bShow)
{
	HRESULT result;
	// �f�o�C�X�쐬
	result = m_Input->CreateDevice(GUID_SysMouse, &m_Mouse, NULL);
	if (FAILED(result) || m_Mouse == NULL)
	{
		MessageBox(hWnd, "No mouse", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}
	// �f�[�^�t�H�[�}�b�g�ݒ�
	result = m_Mouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(result))

	{
		MessageBox(hWnd, "Can't setup mouse", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}
	// ���̃A�v���Ƌ������[�h�ɐݒ�
	result = m_Mouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(result))
	{
		MessageBox(hWnd, "Mouse mode error", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD prop;

	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = DIPROPAXISMODE_REL;		// �}�E�X�̈ړ��l�@���Βl

	result = m_Mouse->SetProperty(DIPROP_AXISMODE, &prop.diph);
	if (FAILED(result))
	{
		MessageBox(hWnd, "Mouse property error", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}

	//	�}�E�X�J�[�\���̐ݒ�
	ShowCursor(bShow);

	// �A�N�Z�X���𓾂�
	m_Mouse->Acquire();
	return result;
}

//	�}�E�X�̏I������
void Mouse::Uninit()
{
	SAFE_RELEASE(m_Mouse);
}

//	�}�E�X�̍X�V����
HRESULT Mouse::Update()
{
	HRESULT result;
	// �O��̒l�ۑ�
	DIMOUSESTATE2 lastMouseState = m_mouseState;
	// �f�[�^�擾
	result = m_Mouse->GetDeviceState(sizeof(m_mouseState), &m_mouseState);
	if (SUCCEEDED(result))
	{
		m_mouseTrigger.lX = m_mouseState.lX;
		m_mouseTrigger.lY = m_mouseState.lY;
		m_mouseTrigger.lZ = m_mouseState.lZ;
		// �}�E�X�̃{�^�����
		for (int i = 0; i < 8; i++)
		{
			m_mouseTrigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^ m_mouseState.rgbButtons[i]) & m_mouseState.rgbButtons[i]);
		}
	}
	else	// �擾���s
	{
		// �A�N�Z�X���𓾂Ă݂�
		result = m_Mouse->Acquire();
	}
	return result;
}

//	 ���N���b�N�������
BOOL Mouse::LeftPress()
{
	return (BOOL)(m_mouseState.rgbButtons[0] & 0x80);	// �����ꂽ�Ƃ��ɗ��r�b�g������
}

//	���N���b�N�����u��
BOOL Mouse::LeftTrigger()
{
	return (BOOL)(m_mouseTrigger.rgbButtons[0] & 0x80);
}

//	�E�N���b�N�������
BOOL Mouse::RightPress()
{
	return (BOOL)(m_mouseState.rgbButtons[1] & 0x80);
}

//	�E�N���b�N�����u��
BOOL Mouse::RightTrigger()
{
	return (BOOL)(m_mouseTrigger.rgbButtons[1] & 0x80);
}

//  �����N���b�N�������
BOOL Mouse::CenterPress()
{
	return (BOOL)(m_mouseState.rgbButtons[2] & 0x80);
}

//  �����N���b�N�����u��
BOOL Mouse::CenterTrigger()
{
	return (BOOL)(m_mouseTrigger.rgbButtons[2] & 0x80);
}

//  �}�E�X��X�����ɓ��������Βl
long Mouse::GetMouseX()
{
	return m_mouseState.lX;
}

//  �}�E�X��Y�����ɓ��������Βl
long Mouse::GetMouseY()
{
	return m_mouseState.lY;
}

//  �}�E�X�z�C�[�������������Βl
long Mouse::GetMouseZ()
{
	return m_mouseState.lZ;
}
#pragma endregion �}�E�X�̏���

