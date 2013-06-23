#ifndef _SCENE_OBJECT_H
#define _SCENE_OBJECT_H

#include <vector>
#include "D3DHeaders.h"

#include "Mesh.h"
#include "Texture.h"

class SceneObject
{
public:
	SceneObject():mpMesh(NULL)
	{

	}
	~SceneObject()
	{

	}

public:
	bool init(
		ID3D11Device* pDevice, ID3D11DeviceContext* pContext, 
		Vertex* pVertexData, UINT numOfVertices,
		WORD* indexData, UINT numOfIndices)
	{
		if (pDevice == NULL || pContext == NULL)
			return false;

		mpMesh = new Mesh();
		mpMesh->create(pDevice, pVertexData, numOfVertices, indexData,numOfIndices);

		return true;
	}

	void clear()
	{
		if (mpMesh)
		{
			delete mpMesh;
			mpMesh = NULL;
		}	
	}

	void update(float deltaTime)
	{

	}

	void drawSelf(ID3D11DeviceContext* pContext)
	{

	}

private:
	//Core data
	Mesh* mpMesh;
	
};

#endif