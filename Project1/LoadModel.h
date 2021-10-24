/*-------------------------------------------------------------
	
	[LoadModel.h]
	���f���̃��[�h����֐�
	Author : �o���đ�

--------------------------------------------------------------*/
#pragma once
#include "Loader.h"

// �}�e���A���\����
struct ModelMaterial
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Texture;
	Material Material;
	char	 Name[256];
	char	 TextureName[256];
};

// �`��T�u�Z�b�g�\����
struct Sebset
{
	ModelMaterial Material;
	uint32_t StartIndex;
	uint32_t IndexNum;
};

// ���f���̏��
struct ModelInfo
{
	Vertex3D* VertexArray;
	uint32_t  VertexNum;

	uint32_t* IndexArray;
	uint32_t  IndexNum;

	Sebset*  SubsetArray;
	uint32_t SubsetNum;
};

// ���f��
class Model final : public Loader
{
public:
	Model() = delete;
	Model(Graphics & graphics);
	~Model();
	void Load(const std::string& name)override;
	void Unload();
	void Draw();
private:
	Graphics& m_Graphics;
	ComPtr<ID3D11Buffer> m_VertexBuffer;
	ComPtr<ID3D11Buffer> m_IndexBuffer;

	Sebset*	 m_SubsetArray;
	uint32_t m_SubsetNum;

	void LoadObj(const std::string& FileName, ModelInfo *Model);
	void LoadMaterial(const std::string& FileName, ModelMaterial **MaterialArray, uint32_t *MaterialNum);
};