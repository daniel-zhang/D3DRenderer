#pragma once

#include "winroot.h"

#include <d3dx11.h>
#include <D3Dcompiler.h>
#include <xnamath.h>

#include <vector>
#include <string>

class Renderer;

class RenderWindow : public WinRoot<RenderWindow>
{
public:
	virtual LRESULT handleMsg(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual PCWSTR getClassName() const;
	
	void initRenderer();
	void releaseRenderer();
	void render(){}
	
private:
	Renderer* mpRenderer;
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	HRESULT initDevice(HWND hwnd);
	void releaseDeviece();

	std::vector<IDXGIAdapter*> enumerateAdapters();

private:
	HRESULT compileShaderFile(wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** pBlob );

	D3D_DRIVER_TYPE				mDriverType;
	D3D_FEATURE_LEVEL			mFeatureLevel;

	IDXGISwapChain*				mpSwapChain;
	ID3D11Device*				mpD3dDevice;
	ID3D11DeviceContext*		mpImmediateContext;

	ID3D11RenderTargetView*		mpRenderTargetView;
	ID3D11Texture2D*			mpDepthStencil;
	ID3D11DepthStencilView*		mpDepthStencilView;

	ID3D11VertexShader*			mpVertexShader;
	ID3D11PixelShader*			mpPixelShader;
	ID3D11PixelShader*			mpPixelShaderSolid;

	ID3D11InputLayout*			mpVertexLayout;
	ID3D11Buffer*				mpVertexBuffer;
	ID3D11Buffer*				mpIndexBuffer;

	ID3D11Buffer*				mpConstantBuffer;

};

class IRenderable
{
public:
	
};

