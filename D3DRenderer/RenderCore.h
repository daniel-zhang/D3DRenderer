#ifndef _RENDER_CORE_H
#define _RENDER_CORE_H

#include <string>

#include "D3DHeaders.h"
#include "SceneManager.h"

class RenderCore
{
public:
	RenderCore(HWND hwnd);
	~RenderCore();

public:
	bool init();
	void go();
	void clear();

	std::vector<IDXGIAdapter*> listVideocards();

private:
	float timeElapsed();

	bool initDevice();
	void clearDevice();

	bool initScene();
	void clearScene();

	void updateWindowInfo();

private:
	D3D_DRIVER_TYPE mDriverType;
	D3D_FEATURE_LEVEL mFeatureLevel;
	
	ID3D11Device* mpDevice;
	ID3D11DeviceContext* mpContext;

	IDXGISwapChain* mpSwapChain;
	ID3D11RenderTargetView* mpRenderTargetView;
	
	ID3D11Texture2D* mpDepthStencil;
	ID3D11DepthStencilView* mpDepthStencilView;
	
	//SceneMgr should be treated as a singleton
	SceneManager* mpSceneMgr;

	//Window specific
	HWND mWindowHandle;
	UINT mWindowWidth;
	UINT mWindwHeight;
};
#endif