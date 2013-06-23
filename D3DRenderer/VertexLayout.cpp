#include "VertexLayout.h"

/*****
*/
void InputLayout::reset( UINT descNum )
{
	if (mpLayoutDesc != NULL)
	{
		delete[] mpLayoutDesc;
		mpLayoutDesc = NULL;
	}

	if (mpInputLayout != NULL)
	{
		mpInputLayout->Release();
		mpInputLayout = NULL;
	}

	mNumOfInputLayoutElements = descNum;
	mCurIndex = 0;

	if ( descNum > 0)
	{
		mpLayoutDesc = new D3D11_INPUT_ELEMENT_DESC[mNumOfInputLayoutElements];
		ZeroMemory(mpLayoutDesc, mNumOfInputLayoutElements* sizeof(D3D11_INPUT_ELEMENT_DESC));
	}
}

void InputLayout::addDesc( 
	LPCSTR semanticName, UINT semanticIndex, DXGI_FORMAT format, 
	UINT inputSlot, UINT alignedByteOffset, 
	D3D11_INPUT_CLASSIFICATION inputSlotClass /*= D3D11_INPUT_PER_VERTEX_DATA*/, 
	UINT instanceDataStepRate /*= 0*/ )
{
	if (mCurIndex >= mNumOfInputLayoutElements)
		return; 

	if (mpLayoutDesc == NULL)
		return;

	mpLayoutDesc[mCurIndex].SemanticName = semanticName;
	mpLayoutDesc[mCurIndex].SemanticIndex = semanticIndex;
	mpLayoutDesc[mCurIndex].Format = format;
	mpLayoutDesc[mCurIndex].InputSlot = inputSlot;
	mpLayoutDesc[mCurIndex].AlignedByteOffset = alignedByteOffset;
	mpLayoutDesc[mCurIndex].InputSlotClass = inputSlotClass;
	mpLayoutDesc[mCurIndex].InstanceDataStepRate = instanceDataStepRate;

	++mCurIndex;
}

bool InputLayout::create( ID3D11Device* pDevice, ID3DBlob* pVSByteCode )
{
	if (mpLayoutDesc == NULL || pDevice == NULL || pVSByteCode == NULL)
		return false;

	HRESULT hr = pDevice->CreateInputLayout(mpLayoutDesc, mNumOfInputLayoutElements, pVSByteCode->GetBufferPointer(), pVSByteCode->GetBufferSize(), &mpInputLayout);

	return SUCCEEDED(hr);
}

void InputLayout::bind( ID3D11DeviceContext* pDeviceContext )
{
	if (mpInputLayout == NULL || pDeviceContext == NULL)
		return;

	pDeviceContext->IASetInputLayout(mpInputLayout);
}