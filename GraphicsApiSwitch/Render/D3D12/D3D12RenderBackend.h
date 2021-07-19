#pragma once

#include <dxgi1_4.h>
#include <d3d12.h>
#include <unordered_map>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>

#include "d3dx12.h"
#include "UploadBuffer.h"
#include "../../CommonUtils.h"
#include "../../Box.h"
#include "../../framework.h"

// Link necessary d3d12 libraries.
// Temporary solution
// It should be linked with build system
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

struct ObjectConstants
{
	DirectX::XMFLOAT4X4 WorldViewProj;
};

struct Vertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};

struct SubmeshGeometry
{
	UINT IndexCount = 0;
	UINT StartIndexLocation = 0;
	INT BaseVertexLocation = 0;

	DirectX::BoundingBox Bounds;
};

struct MeshGeometry
{
	std::string Name;

	Microsoft::WRL::ComPtr<ID3DBlob> VertexBufferCPU = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> IndexBufferCPU = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> VertexBufferGPU = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> IndexBufferGPU = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> VertexBufferUploader = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> IndexBufferUploader = nullptr;

	UINT VertexByteStride = 0;
	UINT VertexBufferByteSize = 0;
	DXGI_FORMAT IndexFormat = DXGI_FORMAT_R16_UINT;
	UINT IndexBufferByteSize = 0;

	std::unordered_map<std::string, SubmeshGeometry> DrawArgs;

	D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const
	{
		D3D12_VERTEX_BUFFER_VIEW vbv;
		vbv.BufferLocation = VertexBufferGPU->GetGPUVirtualAddress();
		vbv.StrideInBytes = VertexByteStride;
		vbv.SizeInBytes = VertexBufferByteSize;

		return vbv;
	}

	D3D12_INDEX_BUFFER_VIEW IndexBufferView()const
	{
		D3D12_INDEX_BUFFER_VIEW ibv;
		ibv.BufferLocation = IndexBufferGPU->GetGPUVirtualAddress();
		ibv.Format = IndexFormat;
		ibv.SizeInBytes = IndexBufferByteSize;

		return ibv;
	}

	void DisposeUploaders()
	{
		VertexBufferUploader = nullptr;
		IndexBufferUploader = nullptr;
	}
};

class D3D12RenderBackend
{
public:
	D3D12RenderBackend(
		HWND hwnd,
		int nClientWidth,
		int nClientHeight
	);

	D3D12RenderBackend(
		const D3D12RenderBackend& rhs
	) = delete;

	D3D12RenderBackend& operator=(
		const D3D12RenderBackend& rhs
	) = delete;

	~D3D12RenderBackend();

	void Draw(
		float fRadius,
		float fPhi,
		float fTheta,
		std::vector<Box>* Boxes
	);

	void OnResize(
		int nClientWidth,
		int nClientHeight
	);

private:
	void OnResize();
	float AspectRatio() const;

	void CreateCommandObjects();
	void CreateSwapChain(
		HWND hwnd
	);
	void CreateRtvAndDsvDescriptorHeaps();

	void BuildDescriptorHeaps();
	void BuildConstantBuffers();
	void BuildRootSignature();
	void BuildShadersAndInputLayout();
	void BuildBoxGeometry();
	void BuildPSO();

	void FlushCommandQueue();

	void UpdateConstantBuffers(
		std::vector<Box>* Boxes
	);
	void RenderBoxes(
		std::vector<Box>* Boxes
	);

	UINT CalcConstantBufferByteSize(
		UINT byteSize
	);

	ID3D12Resource* CurrentBackBuffer() const;
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;

	void LogAdapters();
	void LogAdapterOutputs(
		IDXGIAdapter* adapter
	);
	void LogOutputDisplayModes(
		IDXGIOutput* output, DXGI_FORMAT format
	);

	Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(
		const std::wstring& filename,
		const D3D_SHADER_MACRO* defines,
		const std::string& entrypoint,
		const std::string& target
	);
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateDefaultBuffer(
		ID3D12Device* device,
		ID3D12GraphicsCommandList* cmdList,
		const void* initData,
		UINT64 byteSize,
		Microsoft::WRL::ComPtr<ID3D12Resource>& uploadBuffer
	);

	Microsoft::WRL::ComPtr<IDXGIFactory4> m_dxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
	Microsoft::WRL::ComPtr<ID3D12Device> m_d3dDevice;

	Microsoft::WRL::ComPtr<ID3D12Fence> m_Fence;
	UINT64 m_nCurrentFence;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_DirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_CommandList;

	static const int m_nSwapChainBufferCount = 2;
	int m_nCurrBackBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_SwapChainBuffer[m_nSwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> m_DepthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_RtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_DsvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_CbvHeap;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> m_RootSignature;
	std::vector<D3D12_INPUT_ELEMENT_DESC> m_InputLayout;

	std::unique_ptr<UploadBuffer<ObjectConstants>> m_ObjectCB;

	std::unique_ptr<MeshGeometry> m_BoxGeom;

	Microsoft::WRL::ComPtr<ID3DBlob> m_vsByteCode;
	Microsoft::WRL::ComPtr<ID3DBlob> m_psByteCode;

	Microsoft::WRL::ComPtr<ID3D12PipelineState> m_PSO;

	DirectX::XMFLOAT4X4 m_World;
	DirectX::XMFLOAT4X4 m_View;
	DirectX::XMFLOAT4X4 m_Proj;

	D3D12_VIEWPORT m_ScreenViewport;
	D3D12_RECT m_ScissorRect;

	UINT m_nRtvDescriptorSize;
	UINT m_nDsvDescriptorSize;
	UINT m_nCbvSrvUavDescriptorSize;

	DXGI_FORMAT m_BackBufferFormat;
	DXGI_FORMAT m_DepthStencilFormat;

	int m_nClientWidth;
	int m_nClientHeight;
};