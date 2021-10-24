/*---------------------------------------------------------

	[Graphics.cpp]
	Author : �o���đ�

----------------------------------------------------------*/
#include "Engine.h"
#include "Utility.h"
#include "Graphics.h"

namespace
{
	// �E�B���h�E�T�C�Y
	const Math::Vector2 g_Size = Engine::Get().GetWindowSize(); 
}

Graphics::Graphics() :	m_Device(nullptr), m_DeviceContext(nullptr), m_SwapChain(nullptr), m_RenderTargetView(nullptr), 
						m_DepthStencilView(nullptr) ,m_DepthStateEnable(nullptr), m_DepthStateDisable(nullptr)
{
	HRESULT hr = S_OK;
	D3D_FEATURE_LEVEL featurelevel = D3D_FEATURE_LEVEL_11_0;

	// �f�o�C�X�A�X���b�v�`�F�[���A�R���e�L�X�g����
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = (UINT)g_Size.x;
	sd.BufferDesc.Height = (UINT)g_Size.y;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = Engine::Get().GetHwnd();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &sd,
		m_SwapChain.GetAddressOf(), m_Device.GetAddressOf(), &featurelevel, m_DeviceContext.GetAddressOf());
	ThrowIfFailed(hr, "D3D11CreateDeviceAndSwapchain");

	// �����_�[�^�[�Q�b�g�r���[�����A�ݒ�
	ID3D11Texture2D* pBackBuffer = NULL;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	m_Device->CreateRenderTargetView(pBackBuffer, NULL, m_RenderTargetView.GetAddressOf());
	pBackBuffer->Release();

	//�[�x�X�e���V���p�e�N�X�`���[�쐬
	ID3D11Texture2D* depthTexture = NULL;
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = sd.BufferDesc.Width;
	td.Height = sd.BufferDesc.Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc = sd.SampleDesc;
	td.Usage = D3D11_USAGE_DEFAULT;
	//td.Usage = D3D11_USAGE_DYNAMIC;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	m_Device->CreateTexture2D(&td, NULL, &depthTexture);

	//�[�x�X�e���V���^�[�Q�b�g�쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags = 0;
	m_Device->CreateDepthStencilView(depthTexture, &dsvd, m_DepthStencilView.GetAddressOf());
	m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());

	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = g_Size.x;
	vp.Height = g_Size.y;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &vp);

	// ���X�^���C�U�X�e�[�g�ݒ�
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	// �����_�����O���̕`�惂�[�h
	rd.FillMode = D3D11_FILL_SOLID;
	//rd.FillMode = D3D11_FILL_WIREFRAME;
	// �J�����O�ݒ肵�Ȃ�
	rd.CullMode = D3D11_CULL_NONE;
	// �w�ʃJ�����O
	//rd.CullMode = D3D11_CULL_BACK;
	rd.DepthClipEnable = TRUE;
	rd.MultisampleEnable = FALSE;

	ID3D11RasterizerState *rs;
	m_Device->CreateRasterizerState(&rd, &rs);
	m_DeviceContext->RSSetState(rs);

	// �u�����h�X�e�[�g�ݒ�
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_Device->CreateBlendState(&blendDesc, m_BlendState[0].GetAddressOf());
	SetBlendStateDefault();

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;

	m_Device->CreateBlendState(&blendDesc, m_BlendState[1].GetAddressOf());

	// �[�x�X�e���V���X�e�[�g�ݒ�
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;
	m_Device->CreateDepthStencilState(&depthStencilDesc, m_DepthStateEnable.GetAddressOf());//�[�x�L���X�e�[�g
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	m_Device->CreateDepthStencilState(&depthStencilDesc, m_DepthStateDisable.GetAddressOf());//�[�x�����X�e�[�g
	m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable.Get(), NULL);

	// �T���v���[�X�e�[�g�ݒ�
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	//samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	//samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState = NULL;
	m_Device->CreateSamplerState(&samplerDesc, &samplerState);
	m_DeviceContext->PSSetSamplers(0, 1, &samplerState);

	/// �萔�o�b�t�@����
	D3D11_BUFFER_DESC hBufferDesc{};
	hBufferDesc.ByteWidth = sizeof(DirectX::XMMATRIX);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	m_Device->CreateBuffer(&hBufferDesc, NULL, m_Buffer[EBuffer::CONSTANT_BUFFER_WORLD].GetAddressOf());
	m_DeviceContext->VSSetConstantBuffers(0, 1, m_Buffer[EBuffer::CONSTANT_BUFFER_WORLD].GetAddressOf());

	m_Device->CreateBuffer(&hBufferDesc, NULL, m_Buffer[EBuffer::CONSTANT_BUFFER_VIEW].GetAddressOf());
	m_DeviceContext->VSSetConstantBuffers(1, 1, m_Buffer[EBuffer::CONSTANT_BUFFER_VIEW].GetAddressOf());

	m_Device->CreateBuffer(&hBufferDesc, NULL, m_Buffer[EBuffer::CONSTANT_BUFFER_PROJECTION].GetAddressOf());
	m_DeviceContext->VSSetConstantBuffers(2, 1, m_Buffer[EBuffer::CONSTANT_BUFFER_PROJECTION].GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(Material);
	m_Device->CreateBuffer(&hBufferDesc, NULL, m_Buffer[EBuffer::CONSTANT_BUFFER_MATERIAL].GetAddressOf());
	m_DeviceContext->VSSetConstantBuffers(3, 1, m_Buffer[EBuffer::CONSTANT_BUFFER_MATERIAL].GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(Light);
	m_Device->CreateBuffer(&hBufferDesc, NULL,  m_Buffer[EBuffer::CONSTANT_BUFFER_LIGHT].GetAddressOf());
	m_DeviceContext->VSSetConstantBuffers(4, 1,  m_Buffer[EBuffer::CONSTANT_BUFFER_LIGHT].GetAddressOf());
	m_DeviceContext->PSSetConstantBuffers(4, 1,  m_Buffer[EBuffer::CONSTANT_BUFFER_LIGHT].GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(DirectX::XMFLOAT4);
	m_Device->CreateBuffer(&hBufferDesc, NULL,  m_Buffer[EBuffer::CONSTANT_BUFFER_CAMERA].GetAddressOf());
	m_DeviceContext->PSSetConstantBuffers(5, 1,  m_Buffer[EBuffer::CONSTANT_BUFFER_CAMERA].GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(DirectX::XMFLOAT4);
	m_Device->CreateBuffer(&hBufferDesc, NULL,  m_Buffer[EBuffer::CONSTANT_BUFFER_PARAMETER].GetAddressOf());
	m_DeviceContext->PSSetConstantBuffers(6, 1,  m_Buffer[EBuffer::CONSTANT_BUFFER_PARAMETER].GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(cbPerObject);
	m_Device->CreateBuffer(&hBufferDesc, NULL, m_Buffer[EBuffer::CONSTANT_BUFFER_EFFECT].GetAddressOf());
	m_DeviceContext->VSSetConstantBuffers(7, 1, m_Buffer[EBuffer::CONSTANT_BUFFER_EFFECT].GetAddressOf());

	// ���C�g������
	Light light;
	light.Enable = false;
	SetLight(light);

	// �}�e���A��������
	Material material;
	material.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);
}

Graphics::~Graphics()
{
	
}

void Graphics::Begin()
{
	// �o�b�N�o�b�t�@�N���A
	float ClearColor[4] = { 0.0f, 0.5f, 0.0f, 1.0f };
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), ClearColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Graphics::End()
{
	m_SwapChain->Present(1, 0);
}

void Graphics::SetDepthEnable(bool Enable)
{
	if (Enable)
	{
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable.Get(), NULL);
	}
	else
	{
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateDisable.Get(), NULL);
	}
}

void Graphics::SetWorldViewProjection2D()
{
	using namespace DirectX;
	XMMATRIX world = XMMatrixIdentity();
	world = XMMatrixTranspose(world);
	UpdateCBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_WORLD], &world);

	XMMATRIX view = XMMatrixIdentity();
	view = XMMatrixTranspose(view);
	UpdateCBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_VIEW], &view);

	XMMATRIX projection = XMMatrixOrthographicOffCenterLH(0.0f, g_Size.x, g_Size.y, 0.0f, 0.0f, 1.0f);
	projection = XMMatrixTranspose(projection);
	UpdateCBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_PROJECTION], &projection);
}

void Graphics::SetWorldMatrix(DirectX::XMMATRIX & WorldMatrix)
{
	WorldMatrix = DirectX::XMMatrixTranspose(WorldMatrix);
	UpdateCBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_WORLD], &WorldMatrix);
}

void Graphics::SetViewMatrix(DirectX::XMMATRIX & ViewMatrix)
{
	ViewMatrix = DirectX::XMMatrixTranspose(ViewMatrix);
	UpdateCBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_VIEW], &ViewMatrix);
}

void Graphics::SetProjectionMatrix(DirectX::XMMATRIX & ProjectionMatrix)
{
	ProjectionMatrix = DirectX::XMMatrixTranspose(ProjectionMatrix);
	UpdateCBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_PROJECTION], &ProjectionMatrix);
}

void Graphics::SetMaterial(Material Material)
{
	UpdateCBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_MATERIAL], &Material);
}

void Graphics::SetLight(Light Light)
{
	UpdateCBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_LIGHT], &Light);
}

void Graphics::SetCameraPosition(DirectX::XMFLOAT3 CameraPosition)
{
	UpdateCBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_CAMERA], &DirectX::XMFLOAT4(CameraPosition.x, CameraPosition.y, CameraPosition.z, 1.0f));
}

void Graphics::SetParameter(DirectX::XMFLOAT4 Parameter)
{
	UpdateCBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_PARAMETER], &Parameter);
}

void Graphics::SetEffectParameter(cbPerObject obj)
{
	UpdateCBuffer(m_Buffer[EBuffer::CONSTANT_BUFFER_EFFECT], &obj);
}

void Graphics::SetBlendStateDefault()
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_DeviceContext->OMSetBlendState(m_BlendState[0].Get(), blendFactor, 0xffffffff);
}

void Graphics::SetBlendStateSub()
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_DeviceContext->OMSetBlendState(m_BlendState[1].Get(), blendFactor, 0xffffffff);
}

const Microsoft::WRL::ComPtr<ID3D11Device> Graphics::GetDevice() const
{
	return m_Device;
}

const Microsoft::WRL::ComPtr<ID3D11DeviceContext> Graphics::GetDeviceContext() const
{
	return m_DeviceContext;
}

template<typename T>
void Graphics::UpdateCBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>  buffer, const T & src)
{
	m_DeviceContext->UpdateSubresource(buffer.Get(), 0, nullptr, src, 0, 0);
}