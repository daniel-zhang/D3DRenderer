#ifndef TEXTURE_RESOURCE_H
#define TEXTURE_RESOURCE_H

#include <RenderResource.h>

class TextureResource : public RenderResource
{
public:
	TextureResource():mResourceType(TextureType){}

	~TextureResource();
	virtual bool load()
	{

	}
};

#endif