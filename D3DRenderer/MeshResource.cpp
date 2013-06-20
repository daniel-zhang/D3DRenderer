#include "MeshResource.h"


bool MeshResource::create( ID3D11Device* pDevice, Vertex* vertices, UINT numOfVertices )
{
	if ( vertices == NULL || pDevice == NULL || numOfVertices == 0)
		return false;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex)*24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertices;

	HRESULT hr = pDevice->CreateBuffer(&bd, &initData, &mpVertexBuffer);
	mTopologyType = StripTopo;
	return SUCCEEDED(hr);
}

bool MeshResource::create( ID3D11Device* pDevice, Vertex* vertices, UINT numOfVertices, WORD* indices, UINT numOfIdx )
{
	if (vertices == NULL || pDevice == NULL || numOfVertices == 0 || numOfIdx == 0)
		return false;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex)*24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertices;

	HRESULT hr = pDevice->CreateBuffer(&bd, &initData, &mpVertexBuffer);

	bd.ByteWidth = sizeof(WORD)* numOfIdx;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	initData.pSysMem = indices;

	HRESULT hr = pDevice->CreateBuffer(&bd, &initData, &mpVertexBuffer);
	mTopologyType = ListTopo;

	return SUCCEEDED(hr);
}

void MeshResource::bind( ID3D11DeviceContext* pDeviceContext )
{
	if (pDeviceContext == NULL)
		return;

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	switch(mTopologyType)
	{
	case StripTopo:
		pDeviceContext->IASetVertexBuffers(0,1,&mpVertexBuffer, &stride, &offset);
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		break;

	case ListTopo:
		pDeviceContext->IASetVertexBuffers(0,1,&mpVertexBuffer, &stride, &offset);
		pDeviceContext->IASetIndexBuffer(mpIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;

	default:
		break;
	}
}

void MeshResource::clear()
{
	if (mpVertexBuffer)
	{
		mpVertexBuffer->Release();
		mpVertexBuffer = NULL;
	}

	if ( mpIndexBuffer)
	{
		mpIndexBuffer->Release();
		mpIndexBuffer = NULL;
	}

	mTopologyType = Invalid;
}
