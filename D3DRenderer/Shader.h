#ifndef SHADER_RESOURCE_H
#define SHADER_RESOURCE_H

#include "D3DHeaders.h"

class Shader 
{
public:
	Shader():mpShaderByteCode(NULL){}

	~Shader(){}

	void setInput(wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel)
	{
		mFileName = fileName;
		mEntryPoint = entryPoint;
		mShaderModel = shaderModel;
	}
	ID3DBlob* getByteCode();

	virtual bool create(ID3D11Device* pDevice) = 0;
	virtual void bind(ID3D11DeviceContext* pDeviceContext) = 0;
	virtual void clear() = 0;

protected:
	bool compileFromFile(wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel);

	wchar_t* mFileName;
	LPCSTR mEntryPoint;
	LPCSTR mShaderModel;

	ID3DBlob* mpShaderByteCode; 
};

class VertexShader : public Shader
{
public:
	VertexShader():mpVertexShader(NULL)
	{

	}

	~VertexShader()
	{
		clear();
	}

	virtual bool create(ID3D11Device* pDevice);
	virtual void bind(ID3D11DeviceContext* pDeviceContext);
	virtual void clear()
	{
		if (mpShaderByteCode) 
		{
			mpShaderByteCode->Release();
			mpShaderByteCode = NULL;
		}
		if (mpVertexShader)
		{
			mpVertexShader->Release();
			mpVertexShader = NULL;
		}
	}

private:
	ID3D11VertexShader* mpVertexShader;
};

class PixelShader : public Shader
{
public:
	PixelShader():mpPixelShader(NULL){}
	
	~PixelShader()
	{
		clear();
	}

	virtual bool create(ID3D11Device* pDevice);
	virtual void bind(ID3D11DeviceContext* pDeviceContext);
	virtual void clear()
	{
		if (mpShaderByteCode) 
		{
			mpShaderByteCode->Release();
			mpShaderByteCode = NULL;
		}
		if (mpPixelShader)
		{
			mpPixelShader->Release();
			mpPixelShader = NULL;
		}
	}

private:
	ID3D11PixelShader* mpPixelShader;
};

#endif