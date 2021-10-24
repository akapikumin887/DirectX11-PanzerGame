/*-----------------------------------------------------------

	[Audio.h]
	Author : �o���đ�

------------------------------------------------------------*/
#include "myLib.h"
#include "Audio.h"
#include "Graphics.h"
#include "Utility.h"

LoadAudio::LoadAudio()
{
	
}

LoadAudio::~LoadAudio()
{

}

void LoadAudio::Load(const std::string & name, bool loop, IXAudio2* xaudio2)
{
	// �T�E���h�t�@�C���̓o�^
	m_Filename = name;
	m_Loop = loop;

	HRESULT hr = S_OK;;
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̃N���A
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// �T�E���h�f�[�^�t�@�C���̐���
	hFile = CreateFile(m_Filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		ThrowIfFailed(hr, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s(1)");
		return;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		ThrowIfFailed(hr, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s(2)");
		return;
	}

	// WAVE�t�@�C���̃`�F�b�N
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)");
		return;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)");
		return;
	}
	if (dwFiletype != 'EVAW')
	{
		ThrowIfFailed(hr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)");
		return;
	}

	// �t�H�[�}�b�g�`�F�b�N
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)");
		return;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)");
		return;
	}

	// �I�[�f�B�I�f�[�^�ǂݍ���
	hr = CheckChunk(hFile, 'atad', &m_sizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)");
		return;
	}
	m_dataAudio = (BYTE*)malloc(m_sizeAudio);
	hr = ReadChunkData(hFile, m_dataAudio, m_sizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)");
		return;
	}

	// �\�[�X�{�C�X�̐���
	hr = xaudio2->CreateSourceVoice(&m_sourceVoice, &(wfx.Format));
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "�\�[�X�{�C�X�̐����Ɏ��s�I");
		return;
	}

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sizeAudio;
	buffer.pAudioData = m_dataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	m_Loop ? buffer.LoopCount = -1 : buffer.LoopCount = 0;

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_sourceVoice->SubmitSourceBuffer(&buffer);
}

void LoadAudio::Unload()
{
	if (m_sourceVoice)
	{
		// �ꎞ��~
		m_sourceVoice->Stop(0);

		// �\�[�X�{�C�X�̔j��
		m_sourceVoice->DestroyVoice();
		m_sourceVoice = NULL;

		// �I�[�f�B�I�f�[�^�̊J��
		free(m_dataAudio);
		m_dataAudio = NULL;
	}
}

void LoadAudio::Play()
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sizeAudio;
	buffer.pAudioData = m_dataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	m_Loop ? buffer.LoopCount = -1 : buffer.LoopCount = 0;

	// ��Ԏ擾
	m_sourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
	 // �ꎞ��~
		m_sourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_sourceVoice->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_sourceVoice->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_sourceVoice->Start(0);
}

void LoadAudio::Stop()
{
	if (m_sourceVoice)
	{
		// �ꎞ��~
		m_sourceVoice->Stop(0);
	}
}

void LoadAudio::SetVolume(float volume)
{
	// �{�����[����1.0f���傫���Ȃ�Ȃ��悤�ɂ���
	float v = Math::Min(volume, 1.0f);
	m_sourceVoice->SetVolume(v);
}

HRESULT LoadAudio::CheckChunk(HANDLE hFile, DWORD format, DWORD * pChunkSize, DWORD * pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

HRESULT LoadAudio::ReadChunkData(HANDLE hFile, void * pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}

Audio::Audio()
{
	HRESULT hr;
	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_xAudio2, 0);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "Xaudio2�I�u�W�F�N�g�쐬���s");

		// COM���C�u�����̏I������
		CoUninitialize();

		return;
	}

	// �}�X�^�[�{�C�X�̐���
	hr = m_xAudio2->CreateMasteringVoice(&m_masteringVoice);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "�}�X�^�[�{�C�X�̐����Ɏ��s");
		if (m_xAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_xAudio2->Release();
			m_xAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return;
	}
}

Audio::~Audio()
{
	Unload();
	// �}�X�^�[�{�C�X�̔j��
	m_masteringVoice->DestroyVoice();
	m_masteringVoice = NULL;

	if (m_xAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_xAudio2->Release();
		m_xAudio2 = NULL;
	}

	// COM���C�u�����̏I������
	CoUninitialize();
}

// ���[�h����(name = �t�@�C����, loop = ���[�v���邩�ǂ���)
void Audio::Load(const std::string & name, bool loop)
{
	m_Map[name] = std::make_unique<LoadAudio>();
	std::string file = "Asset\\Audio\\" + name + ".wav";
	m_Map[name]->Load(file, loop, m_xAudio2);
}

// �w��̂��̂����A�����[�h
void Audio::Unload(const std::string & name)
{
	m_Map[name]->Unload();
}

// ���ׂăA�����[�h
void Audio::Unload()
{
	// �I�[�f�B�I�̃A�����[�h
	for (auto itr = m_Map.begin(); itr != m_Map.end(); ++itr)
	{
		itr->second->Unload();
		itr->second.reset();
		itr->second = nullptr;
	}
	// �N���A
	m_Map.clear();
	if (!m_Map.empty())
	{
		throw std::domain_error("m_Map is Not empty");
	}
}

void Audio::Play(const std::string & name, float volume)
{
	// �Đ�����I�[�f�B�I��T��
	auto itr = m_Map.find(name);
	// �L�[������������Đ�
	if (itr != m_Map.end())
	{
		itr->second->SetVolume(volume);
		itr->second->Play();
	}
	else
	{
		throw std::domain_error("Not find key");
	}
}

void Audio::Stop()
{
	for (auto itr = m_Map.begin(); itr != m_Map.end(); ++itr)
	{
		itr->second->Stop();
	}
}

void Audio::SetVolume(const std::string & name, float volume)
{
	// �Đ�����I�[�f�B�I��T��
	auto itr = m_Map.find(name);
	// �L�[������������Đ�
	if (itr != m_Map.end())
	{
		itr->second->SetVolume(volume);
	}
}
