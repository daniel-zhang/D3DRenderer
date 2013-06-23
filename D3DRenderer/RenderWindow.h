#ifndef _RENDER_WINDOW_H
#define _RENDER_WINDOW_H

#include "winroot.h"
#include "RenderCore.h"
#include "DebugTracer.h"

class RenderWindow : public WinRoot<RenderWindow>
{
public:
	virtual LRESULT handleMsg(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual PCWSTR getClassName() const;
		
	void initGraphics()
	{
		//Mount debug tracer to this window
		_set_dump_point_(mHwnd);

		mpRenderEngine = new RenderCore(this->getWinHandle());

		if (mpRenderEngine == NULL)	
			_d_info(L"Failed to create render core.");

		if (mpRenderEngine->init() == false)
			_d_info(L"Failed to init render core.");

	}

	void exitGraphics()
	{
		if (mpRenderEngine) mpRenderEngine->clear();
	}

	void render()
	{
		mpRenderEngine->go();
	}

private:
	RenderCore* mpRenderEngine;
};

#endif



