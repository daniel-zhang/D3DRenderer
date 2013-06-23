#include "SceneManager.h"
#include "meshData.h" //For prototype only
#include "DebugTracer.h"

SceneManager::SceneManager() : 
	mpDevice(NULL), mpContext(NULL),
	mVS_Wrapper(NULL), mPS_Wrapper(NULL),
	mpVertexLayout(NULL)
{

}

SceneManager::~SceneManager()
{
	this->clearAll();
}

//Init orders are not breakable
bool SceneManager::initAll( ID3D11Device* pDevice, ID3D11DeviceContext* pContext )
{
	if (pDevice == NULL || pContext == NULL)
		return false;

	//Receive pipeline status from the render core
	mpDevice = pDevice;
	mpContext = pContext;

	if (initShaders() == false)
		return false;

	if (initVertexLayout() == false)
	{
		return false;
	}

	if (initSceneObjects() == false)
		return false;

	return true;
}

bool SceneManager::initShaders()
{
	//Avoid re-init to get rid of memory leak
	if (mVS_Wrapper)
	{
		_d_info(L"Attempt to over-write existing shaders");
		return false;
	}
	mVS_Wrapper = new VertexShader();
	mVS_Wrapper->setInput(L"", "", "vs_4_0" );
	if (mVS_Wrapper->create(mpDevice) == false)
		return false;

	if (mPS_Wrapper)
	{
		_d_info(L"Attempt to over-write existing shaders");
		return false;
	}
	mPS_Wrapper = new PixelShader();
	mPS_Wrapper->setInput(L"", "", "ps_4_0");
	if (mVS_Wrapper->create(mpDevice) == false )
		return false;

	return true;
}

bool SceneManager::initVertexLayout()
{
	if (mpVertexLayout)
		return false;
	//TODO
	//mpVertexLayout->addDesc();
	mpVertexLayout->create(mpDevice, mVS_Wrapper->getByteCode());

	return true;
}

bool SceneManager::initSceneObjects()
{
	SceneObject* pSceneObj = new SceneObject();
	//TODO
	pSceneObj->init(mpDevice,mpContext,cube, ARRAYSIZE(cube), cubeIndex, ARRAYSIZE(cubeIndex));
	mObjects.push_back(pSceneObj);

	return true;
}

void SceneManager::clearAll()
{
	clearSceneObjects();
	clearShaders();

	mpDevice = NULL;
	mpContext = NULL;
}

void SceneManager::clearSceneObjects()
{
	for (unsigned int i = 0; i < mObjects.size(); ++i)
	{
		if (mObjects[i])
			delete mObjects[i];
	}
	mObjects.clear();
}

void SceneManager::clearShaders()
{
	if (mVS_Wrapper)
	{
		delete mVS_Wrapper;
		mVS_Wrapper = NULL;
	}
	if (mPS_Wrapper)
	{
		delete mPS_Wrapper;
		mPS_Wrapper = NULL;
	}
}

void SceneManager::clearVertexLayout()
{
	if (mpVertexLayout)
	{
		delete mpVertexLayout;
		mpVertexLayout = NULL;
	}
}

unsigned int SceneManager::getObjNum()
{
	return mObjects.size();
}
