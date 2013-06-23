#include "RenderWindow.h"


LRESULT RenderWindow::handleMsg( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_CLOSE://User click close button
		//if (MessageBox(mHwnd, L"Quit?", L"Sample App", MB_OKCANCEL) == IDOK)
		DestroyWindow(mHwnd);//Post a WM_Destory
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);//Post a WM_QUIT, which makes GetMessage() to return 0.
		return 0;

	default:
		return DefWindowProc(mHwnd, uMsg, wParam, lParam);
	}
}

PCWSTR RenderWindow::getClassName() const
{
	return L"D3D11 Render Window";
}



