#ifndef _SCENE_MANAGER_H
#define _SCENE_MANAGER_H

#include <vector>

#include "D3DHeaders.h"
#include "SceneObject.h"
#include "Shader.h"
#include "VertexLayout.h"

class SceneManager
{
public:
	SceneManager();

	~SceneManager();

public:
	void loadScene(){}
	void saveScene(){}

	//
	//Init shaders and all the Scene Objects
	//
	bool initAll(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	bool initShaders();
	bool initVertexLayout();
	bool initSceneObjects();

	void clearAll();
	void clearSceneObjects();
	void clearShaders();
	void clearVertexLayout();
	unsigned int getObjNum();

public:
	ID3D11Device* mpDevice;
	ID3D11DeviceContext* mpContext;

	//TODO: these members might have multiple instances in the future
	//Thus requires containers/managers for them.
	VertexShader* mVS_Wrapper;
	PixelShader* mPS_Wrapper;
	
	InputLayout* mpVertexLayout;

	//The render queue
	std::vector<SceneObject*> mObjects;
	
};

#endif