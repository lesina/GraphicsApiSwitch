#pragma once

#include <windows.h>
#include <string>
#include <cassert>

#if defined(DEBUG) || defined(_DEBUG)
#define ASSERT_NOT_IMPLEMENTED do { assert(0 && "Not implemented"); } while(false)
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
