#include "RenderWindow.h"


LRESULT RenderWindow::handleMsg( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_CLOSE://User click close button
		//if (MessageBox(mHwnd, L"Quit?", L"Sample App", MB_OKCANCEL) == IDOK)
		DestroyWindow(mHwnd);//Post a WM_Destory
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);//Post a WM_QUIT, which makes GetMessage() to return 0.
		return 0;

	default:
		return DefWindowProc(mHwnd, uMsg, wParam, lParam);
	}
}

PCWSTR RenderWindow::getClassName() const
{
	return L"D3D11 Render Window";
}

void RenderWindow::initRenderer()
{
	//mpRenderer->initDevice(mHwnd);
}

void RenderWindow::releaseRenderer()
{

}

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

HRESULT Renderer::compileShaderFile( wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** pBlob )
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(DEBUG) || defined(_DEBUG)
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile(fileName, NULL, NULL, entryPoint, shaderModel, dwShaderFlags, 0, NULL, pBlob, &pErrorBlob, NULL );
	if (FAILED(hr))
	{
		if (pErrorBlob)	
			OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );

		if (pErrorBlob)
			pErrorBlob->Release();

		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();
	return S_OK;
}

HRESULT Renderer::initDevice( HWND hwnd )
{
	HRESULT hr = S_OK;

	//
	//Create a swap chain.
	//
	RECT rc;
	GetClientRect( hwnd, &rc );
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		mDriverType = driverTypes[driverTypeIndex];
		//Create swap chain, plus D3D device and immediate context.
		hr = D3D11CreateDeviceAndSwapChain( NULL, mDriverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &mpSwapChain, &mpD3dDevice, &mFeatureLevel, &mpImmediateContext );
		if( SUCCEEDED( hr ) )
			break;
	}
	if( FAILED( hr ) )	return hr;

	//
	//Retrieve the swap chain's back buffer.
	//
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = mpSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	if( FAILED( hr ) )	return hr;

	//Then create default render target view on the back buffer.
	hr = mpD3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &mpRenderTargetView );
	pBackBuffer->Release();
	if( FAILED( hr ) )	return hr;

	//
	//Create depth stencil.
	//
	D3D11_TEXTURE2D_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(depthDesc));
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;//Data in a depth buffer is normalized to [0,1]
	depthDesc.Width = width;
	depthDesc.Height = height;
	depthDesc.MipLevels = 1; //Turn off MIP levels
	depthDesc.ArraySize = 1; 
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0; //Turn off multi-sampling

	hr = mpD3dDevice->CreateTexture2D(&depthDesc, NULL, &mpDepthStencil);
	if(FAILED(hr))	return hr;

	//
	//Create depth stencil view on the depth stencil.
	//
	D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc;
	ZeroMemory(&depthViewDesc, sizeof(depthViewDesc));
	depthViewDesc.Format = depthDesc.Format;
	depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthViewDesc.Texture2D.MipSlice = 0;

	hr = mpD3dDevice->CreateDepthStencilView(mpDepthStencil, &depthViewDesc, &mpDepthStencilView);
	if (FAILED(hr))	return hr;

	//
	//Bind render target view and depth stencil view to the Output Merger state of the pipeline.
	//
	mpImmediateContext->OMSetRenderTargets( 1, &mpRenderTargetView, mpDepthStencilView );

	//
	//Set view-port to specify which parts of the render target will be visible.
	//
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mpImmediateContext->RSSetViewports( 1, &vp );
}

void Renderer::releaseDeviece()
{

}

std::vector<IDXGIAdapter*> Renderer::enumerateAdapters()
{
	std::vector<IDXGIAdapter*> adapters;

	IDXGIFactory* pDXGIFactory = NULL;
	if (FAILED( CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pDXGIFactory) ))
		return adapters;

	IDXGIAdapter* pAdapter = NULL;
	for ( UINT i = 0; pDXGIFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i )
		adapters.push_back(pAdapter);

	if (pDXGIFactory)
		pDXGIFactory->Release();

	return adapters;
}
