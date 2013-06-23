#ifndef _VERTEX_LAYOUT_H
#define _VERTEX_LAYOUT_H

#include "D3DHeaders.h"

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
#endif