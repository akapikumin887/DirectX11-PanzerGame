/*----------------------------------------------------------

	[Renderer3D.h]
	Author : ?o???đ?

-----------------------------------------------------------*/
#pragma once
#include "myLib.h"

class Graphics;
class Renderer3D final
{
public:
	Renderer3D() = delete;
	Renderer3D(Graphics& graphics, Math::Vector3 pos, Math::Vector3 rot, Math::Vector3 scale);
	~Renderer3D();
	void Update(Math::Vector3 pos, Math::Vector3 rot, Math::Vector3 scale);
	void UpdeteMatrix(); // ?s???v?Z
	void Draw();
	
	//  distancee/???_?Ԃ̋???  untiling / ?e?N?X?`???̖??x?̔{??, texcoord / ?e?N?X?`?????W,
	// X?[?y?̕??ʂ̃|???S???̍쐬
	void CreatePlane(float distance = 10.0f, int uvtiling = 1, DirectX::XMFLOAT2 tex = DirectX::XMFLOAT2(1.0f, 1.0f)); 
	// ?w?[?x?̕ǂ̕??ʃ|???S??
	void CreateWall(float distance = 10.0f, int uvtiling = 1, DirectX::XMFLOAT2 tex = DirectX::XMFLOAT2(1.0f, 1.0f)); 
private:
	Graphics& m_Graphics;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	Math::Vector3 m_Position;
	Math::Vector3 m_Rotation;
	Math::Vector3 m_Scale;
};

