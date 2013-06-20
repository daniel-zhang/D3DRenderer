#include "ShaderResource.h"

ShaderResource::ShaderResource()
{
	mResourceType = ShaderType;
	mpShaderByteCode = NULL;
}

ShaderResource::ShaderResource( wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel )
{
	mResourceType = ShaderType;
	mpShaderByteCode = NULL;

	compileFromFile(fileName, entryPoint, shaderModel);
}

bool ShaderResource::compileFromFile( wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel )
{
	if (mpShaderByteCode)
	{
		mpShaderByteCode->Release();
		mpShaderByteCode = NULL;
	}

	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(DEBUG) || defined(_DEBUG)
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile(fileName, NULL, NULL, entryPoint, shaderModel, dwShaderFlags, 0, NULL, &mpShaderByteCode, &pErrorBlob, NULL );
	if (FAILED(hr))
	{
		if (pErrorBlob)	
			OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );

		if (pErrorBlob)
			pErrorBlob->Release();

		return false;
	}
	if (pErrorBlob)
		pErrorBlob->Release();
	return true;
}

ID3DBlob* ShaderResource::getByteCode()
{
	return mpShaderByteCode;
}

/**Vertex Shader
*/
bool VertexShader::create( ID3D11Device* pDevice )
{
	if (!pDevice || !mpShaderByteCode)
		return false;

	HRESULT hr = pDevice->CreateVertexShader(mpShaderByteCode->GetBufferPointer(), mpShaderByteCode->GetBufferSize(), NULL, &mpVertexShader);

	return SUCCEEDED(hr);
}

void VertexShader::bind( ID3D11DeviceContext* pDeviceContext )
{
	if (mpVertexShader && pDeviceContext)
		pDeviceContext->VSSetShader(mpVertexShader, NULL, 0);
}


/**Pixel Shader
*/
bool PixelShader::create( ID3D11Device* pDevice )
{
	if (!pDevice || !mpShaderByteCode)
		return false;

	HRESULT hr = pDevice->CreatePixelShader(mpShaderByteCode->GetBufferPointer(), mpShaderByteCode->GetBufferSize(), NULL, &mpPixelShader);

	return SUCCEEDED(hr);
}

void PixelShader::bind( ID3D11DeviceContext* pDeviceContext )
{
	if (mpPixelShader && pDeviceContext)
		pDeviceContext->PSSetShader(mpPixelShader, NULL, 0);
}
