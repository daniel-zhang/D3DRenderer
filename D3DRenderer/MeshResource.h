#ifndef MESH_RESOURCE_H
#define MESH_RESOURCE_H

#include "RenderResource.h"



class MeshResource : public RenderResource
{
public:
	MeshResource():
	  mResourceType(MeshType),
	  mpVertexBuffer(NULL),
	  mpIndexBuffer(NULL),
	  mTopologyType(Invalid)
	  {}
	~MeshResource(){this->clear();}

	typedef enum Topology
	{
		StripTopo = 0,
		ListTopo,
		Invalid
	}Topology;
	
	bool create(ID3D11Device* pDevice, Vertex* vertices, UINT mNumOfVertices);
	bool create(ID3D11Device* pDevice, Vertex* vertices, UINT mNumOfVertices, WORD* indices, UINT numOfIdx);
	void bind(ID3D11DeviceContext* pDeviceContext);
	void clear();

private:
	ID3D11Buffer* mpVertexBuffer;
	ID3D11Buffer* mpIndexBuffer;
	Topology mTopologyType;
};




#endif