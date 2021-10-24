/*-------------------------------------------------------------
	
	[LoadShader.h]
	Author : �o���đ�

	�V�F�[�_�[�t�@�C���̓ǂݍ���

--------------------------------------------------------------*/
#pragma once
#include "Loader.h"

// ���_�V�F�[�_�[
class LoadVertexShader final : public Loader
{
public:
	LoadVertexShader() = delete;
	LoadVertexShader(Graphics & graphics);
	~LoadVertexShader();
	void Load(const std::string& FileName)override;
	ComPtr<ID3D11VertexShader> GetVertexShader() const;
	ComPtr<ID3D11InputLayout> GetInputLayout() const;
private:
	class Graphics& m_Graphics;
	ComPtr<ID3D11VertexShader> m_VertexShader;
	ComPtr<ID3D11InputLayout> m_InputLayout;
};

// �s�N�Z���V�F�[�_�[
class LoadPixelShader final : public Loader
{
public:
	LoadPixelShader() = delete;
	LoadPixelShader(Graphics & graphics);
	~LoadPixelShader();
	void Load(const std::string& name)override;
	ComPtr<ID3D11PixelShader> GetPixelShader() const;
private:
	class Graphics& m_Graphics;
	ComPtr<ID3D11PixelShader> m_PixelShader;
};


/*
// �W�I���g���V�F�[�_�[
class LoadGeometryShader final : public Loader
{
public:
	LoadGeometryShader();
	LoadGeometryShader(Graphics & dx, std::string FileName);
	~LoadGeometryShader();
	ComPtr<ID3D11GeometryShader> GetGeometryShader() const;
private:
	void Create(Graphics& dx, ID3D11GeometryShader** Shader, std::string FileName);
	ComPtr<ID3D11GeometryShader> m_GeometryShader;
};

// �R���s���[�g�V�F�[�_�[
class LoadComputeShader final : public Loader
{
public:
	LoadComputeShader();
	LoadComputeShader(Graphics & dx, std::string FileName);
	~LoadComputeShader();
	ComPtr<ID3D11ComputeShader> GetComputeShader() const;
private:
	void Create(Graphics& dx, ID3D11ComputeShader** Shader, std::string FileName);
	ComPtr<ID3D11ComputeShader> m_ComputeShader;
};*/