#ifndef SHADER_RESOURCE_H
#define SHADER_RESOURCE_H

#include "RenderResource.h"
#include <D3Dcompiler.h>

class ShaderResource : public RenderResource
{
public:
	ShaderResource();
	ShaderResource(wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel);
	~ShaderResource(){if (mpShaderByteCode) mpShaderByteCode->Release();}

	bool compileFromFile(wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel);
	ID3DBlob* getByteCode();

	virtual bool create(ID3D11Device* pDevice) = 0;
	virtual void bind(ID3D11DeviceContext* pDeviceContext) = 0;

protected:
	ID3DBlob* mpShaderByteCode; 
};

class VertexShader : public ShaderResource
{
public:
	VertexShader():mpVertexShader(NULL){}
	VertexShader(wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel):
		ShaderResource(fileName, entryPoint, shaderModel), 
		mpVertexShader(NULL){}
	~VertexShader(){if(mpVertexShader) mpVertexShader->Release();}

	virtual bool create(ID3D11Device* pDevice);
	virtual void bind(ID3D11DeviceContext* pDeviceContext);
protected:
	ID3D11VertexShader* mpVertexShader;
};

class PixelShader : public ShaderResource
{
public:
	PixelShader():mpPixelShader(NULL){}
	PixelShader(wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel):
		ShaderResource(fileName, entryPoint, shaderModel), 
		mpPixelShader(NULL){}
	~PixelShader(){if(mpPixelShader) mpPixelShader->Release();}

	virtual bool create(ID3D11Device* pDevice);
	virtual void bind(ID3D11DeviceContext* pDeviceContext);

protected:
	ID3D11PixelShader* mpPixelShader;
};

#endif