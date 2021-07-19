#pragma once

#include <windows.h>
#include <wrl.h>
#include <string>
#include <cassert>
#include <queue>
#include <array>

// Just because...
#define BOX_LIMIT_COUNT 256

#if defined(DEBUG) || defined(_DEBUG)
#define ASSERT_NOT_IMPLEMENTED do { assert(0 && "Not implemented"); } while(false)
#else
#define ASSERT_NOT_IMPLEMENTED
#endif

class DxException
{
public:
	DxException() = default;
	DxException(
		HRESULT hr,
		const std::wstring& functionName,
		const std::wstring& filename,
		int lineNumber
	);

	std::wstring ToString()const;

	HRESULT ErrorCode = S_OK;
	std::wstring FunctionName;
	std::wstring Filename;
	int LineNumber = -1;
};

inline std::wstring AnsiToWString(const std::string& str)
{
	WCHAR buffer[512];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
	return std::wstring(buffer);
}

#ifndef ThrowIfFailed
#define ThrowIfFailed(x)                                              \
{                                                                     \
    HRESULT hr__ = (x);                                               \
    std::wstring wfn = AnsiToWString(__FILE__);                       \
    if(FAILED(hr__)) { throw DxException(hr__, L#x, wfn, __LINE__); } \
}
#endif

#ifndef ReleaseCom
#define ReleaseCom(x) { if(x){ x->Release(); x = 0; } }
#endif