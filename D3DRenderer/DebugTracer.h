#ifndef _DEBUG_TRACER_H
#define _DEBUG_TRACER_H

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>

class DebugTracer
{
public:
	static void dumpInfo(LPCWSTR info, const char * funcName, const char* file, int line)
	{
		const UINT msgLen = 500;
		WCHAR errorInfo[msgLen];
		ZeroMemory(errorInfo, msgLen);

		_snwprintf_s(errorInfo, msgLen, L">>%s\n\nLine>>%d\n\nFunction>>%S\n\nFile>>%S", info, line, funcName, file);

		MessageBox(mHwnd, errorInfo, L"Opps!", MB_OK);
	}

	static void setDumpWindow(HWND hwnd)
	{
		mHwnd = hwnd;
	}

	static HWND mHwnd;
};

//Helper macros for error tracking
#ifdef _DEBUG
#define _d_info(info) DebugTracer::dumpInfo(info, __FUNCDNAME__, __FILE__, __LINE__ )
#define _set_dump_point_(hwnd) DebugTracer::setDumpWindow(hwnd)
#else
#define _d_info(info)
#define _set_dump_point_(hwnd)
#endif

#endif