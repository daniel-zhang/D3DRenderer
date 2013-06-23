#include "RenderCore.h"

/**
RenderCore--Public
*/
RenderCore::RenderCore( HWND hwnd ):
	mWindowHandle(hwnd),
	mDriverType(D3D_DRIVER_TYPE_NULL),
	mFeatureLevel(D3D_FEATURE_LEVEL_11_0),
	mpDevice(NULL), mpContext(NULL), 
	mpSwapChain(NULL), mpRenderTargetView(NULL), 
	mpDepthStencil(NULL), mpDepthStencilView(NULL), 
	mpSceneMgr(NULL)
{
	mpSceneMgr = new SceneManager();
}

RenderCore::~RenderCore()
{
	if (mpSceneMgr) delete mpSceneMgr;
}

bool RenderCore::init()
{
	//The order of initialization is vital.
	if (!initDevice())
		return false;

	if (!initScene())
		return false;

	return true;
}

void RenderCore::go()
{
	float backgroundColor[4] = {0.2f, 0.2f, 0.2f, 0.1f};//RGBA
	
	if (mpContext == NULL || mpSceneMgr == NULL || mpSwapChain == NULL) return;

	mpContext->ClearRenderTargetView(mpRenderTargetView, backgroundColor);
	mpContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.f, 0);

	float deltaTime = timeElapsed();
	for (unsigned int i = 0; i < mpSceneMgr->getObjNum(); ++i)
	{
		mpSceneMgr->mObjects[i]->update(deltaTime);
		mpSceneMgr->mObjects[i]->drawSelf(mpContext);
	}

	mpSwapChain->Present(0, 0);
}

void RenderCore::clear()
{
	clearDevice();
	clearScene();
}

std::vector<IDXGIAdapter*> RenderCore::listVideocards()
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

/**
RenderCore--Private
*/
float RenderCore::timeElapsed()
{
	static DWORD timeStart = 0;
	DWORD timeCurrent = GetTickCount();
	if (timeStart == 0)
		timeStart = timeCurrent;
	return (timeCurrent - timeStart) / 1000.f;
}

bool RenderCore::initDevice()
{
	HRESULT hr = S_OK;
	updateWindowInfo();

	//
	//Create device, device context, and swap chain, using the best possible hardware/features on the target machine.
	//
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
	sd.BufferDesc.Width = mWindowWidth;
	sd.BufferDesc.Height = mWindwHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mWindowHandle;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		mDriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain( NULL, mDriverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &mpSwapChain, &mpDevice, &mFeatureLevel, &mpContext );
		if( SUCCEEDED( hr ) )
			break;
	}
	if( FAILED( hr ) )
		return false;

	//
	// Create Render Target View" on swap chain's back buffer.
	//
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = mpSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	if( FAILED( hr ) )
		return false;

	hr = mpDevice->CreateRenderTargetView( pBackBuffer, NULL, &mpRenderTargetView );
	pBackBuffer->Release();
	if( FAILED( hr ) )
		return false;

	//
	//Create depth texture; 
	//
	D3D11_TEXTURE2D_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(depthDesc));

	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;//Data in a depth buffer is normalized to [0,1]

	depthDesc.Width = mWindowWidth;
	depthDesc.Height = mWindwHeight;
	depthDesc.MipLevels = 1; //Turn off MIP levels
	depthDesc.ArraySize = 1; 
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;

	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0; //Turn off multi-sampling

	hr = mpDevice->CreateTexture2D(&depthDesc, NULL, &mpDepthStencil);
	if(FAILED(hr))
		return false;

	//
	//Create depth view
	//
	D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc;
	ZeroMemory(&depthViewDesc, sizeof(depthViewDesc));
	depthViewDesc.Format = depthDesc.Format;
	depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthViewDesc.Texture2D.MipSlice = 0;

	hr = mpDevice->CreateDepthStencilView(mpDepthStencil, &depthViewDesc, &mpDepthStencilView);
	if (FAILED(hr))
		return false;

	//Set the render target and depth view to the Output Merger state of the pipeline
	//Not sure why a "pp" is needed for the RTV here? 
	mpContext->OMSetRenderTargets( 1, &mpRenderTargetView, mpDepthStencilView );

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)mWindowWidth;
	vp.Height = (FLOAT)mWindwHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mpContext->RSSetViewports( 1, &vp );

	return SUCCEEDED(hr);
}

void RenderCore::clearDevice()
{
	if (mpContext) mpContext->ClearState();

	if (mpDepthStencil) mpDepthStencil->Release();
	if (mpDepthStencilView) mpDepthStencilView->Release();

	if (mpSwapChain) mpSwapChain->Release();
	if (mpRenderTargetView) mpRenderTargetView->Release();

	if (mpContext) mpContext->Release();
	if (mpDevice) mpDevice->Release();
}

bool RenderCore::initScene()
{
	if (mpSceneMgr->initAll(mpDevice, mpContext) == false)
		return false;

	return true;
}

void RenderCore::clearScene()
{
	mpSceneMgr->clearAll();
}

void RenderCore::updateWindowInfo()
{
	RECT rc;
	GetClientRect(mWindowHandle, &rc);
	mWindowWidth = rc.right - rc.left;
	mWindwHeight = rc. bottom - rc.top;
}
