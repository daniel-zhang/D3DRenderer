#ifndef _RENDER_RESOURCE_H
#define _RENDER_RESOURCE_H

#include <string>
#include <d3dx11.h>
#include <D3Dcompiler.h>
#include <xnamath.h>

//A helper class to give resources unique id.
class ResourceIDGen
{
public:
	static unsigned int mBaseID;
	static unsigned int generateID(){return mBaseID++;}
};
unsigned int ResourceIDGen::mBaseID = 0;

typedef enum ResourceType
{
	Invalid = 0,
	MeshType = 1,
	TextureType = 2,
	ShaderType = 3
}ResourceType;

typedef struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
	XMFLOAT3 Normal;
	XMFLOAT2 Tex;
}Vertex;

class InputLayout
{
public:
	InputLayout():
	mpLayoutDesc(NULL), 
	mCurIndex(0),
	mNumOfInputLayoutElements(0), 
	mpInputLayout(NULL)
	{}
	~InputLayout(){this->reset();}

	//Reset the layout to empty, or the desired num of decs that is ready for adding.
	void reset(UINT descNum = 0);

	//addDesc() should be called carefully in sync with the vertex structure.
	void addDesc(
		LPCSTR semanticName, 
		UINT semanticIndex, 
		DXGI_FORMAT format, 
		UINT inputSlot, 
		UINT alignedByteOffset,
		D3D11_INPUT_CLASSIFICATION inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
		UINT instanceDataStepRate = 0);

	//Creating a layout requires that a corresponding VS is already compiled.
	bool create(ID3D11Device* pDevice, ID3DBlob* pVSByteCode);
	void bind(ID3D11DeviceContext* pDeviceContext);

private:
	D3D11_INPUT_ELEMENT_DESC* mpLayoutDesc;
	UINT mCurIndex;
	UINT mNumOfInputLayoutElements;
	ID3D11InputLayout* mpInputLayout;
};

class RenderResource
{
public:
	RenderResource();
	virtual ~RenderResource(){}
	
	std::string getTypeAlias(ResourceType rscType);
	
	unsigned int mID;
	ResourceType mResourceType;
};

#endif