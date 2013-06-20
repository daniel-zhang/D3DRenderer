#include "RenderWindow.h"

int WINAPI wWinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPWSTR lpCmdLine, __in int nShowCmd )
{
	RenderWindow rw;

	if (! rw.create(L"D3D Renderer", WS_OVERLAPPEDWINDOW))
		return 0;

	rw.initRenderer();

	ShowWindow(rw.getWinHandle(), nShowCmd);

	MSG msg = {0};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			rw.render();
	}
	rw.releaseRenderer();

	return (int)msg.wParam;
}