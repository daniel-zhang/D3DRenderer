#ifndef MESH_RESOURCE_H
#define MESH_RESOURCE_H

#include "D3DHeaders.h"
#include "VertexLayout.h"

class Mesh
{
public:
	Mesh():mpVertexBuffer(NULL), mpIndexBuffer(NULL)
	{

	}
	~Mesh()
	{
		this->clear();
	}

public:
	typedef enum Topology
	{
		StripTopo = 0,
		ListTopo,
		Invalid
	}Topology;
	
	bool create(ID3D11Device* pDevice, Vertex* vertices, UINT mNumOfVertices);
	bool create(ID3D11Device* pDevice, Vertex* vertices, UINT mNumOfVertices, WORD* indices, UINT numOfIdx);
	void bind(ID3D11DeviceContext* pContext);
	void clear();

private:
	ID3D11Buffer* mpVertexBuffer;
	ID3D11Buffer* mpIndexBuffer;
	Topology mTopologyType;
};




#endif