//
// SystemUtil.h
//
// Clark Kromenaker
//
// Some cross-platform helper functions for querying the system.
//
#pragma once
#include <string>

#include "Platform.h"
#if defined(PLATFORM_MAC) or defined(PLATFORM_UNIX)
#include <unistd.h>
#include <limits.h>
#elif defined(PLATFORM_WINDOWS)
#include <Windows.h>
#include <lmcons.h> // for ULEN define
#endif

namespace SystemUtil
{
	// NOTE: Don't call this GetComputerName b/c Windows.h conflicts with that!
	inline std::string GetMachineName()
	{
#if defined(PLATFORM_MAC) or defined(PLATFORM_UNIX)
		char computerName[_POSIX_HOST_NAME_MAX];
		gethostname(computerName, _POSIX_HOST_NAME_MAX);
		return std::string(computerName);
#elif defined(PLATFORM_WINDOWS)
		const DWORD kBufferSize = MAX_COMPUTERNAME_LENGTH + 1;
		char computerName[kBufferSize];
		DWORD bufferSize = kBufferSize;
		if(!GetComputerName(computerName, &bufferSize))
		{
			std::cout << "Failed to get computer name!" << std::endl;
			return std::string("");
		}
		return std::string(computerName);
#endif
	}
	
	// NOTE: Don't call this GetUserName b/c Windows.h conflicts with that!
	inline std::string GetCurrentUserName()
	{
#if defined(PLATFORM_MAC) or defined(PLATFORM_UNIX)
		char userName[_POSIX_LOGIN_NAME_MAX];
		getlogin_r(userName, _POSIX_LOGIN_NAME_MAX);
		return std::string(userName);
#elif defined(PLATFORM_WINDOWS)
		const DWORD kBufferSize = UNLEN + 1;
		char userName[kBufferSize];
		DWORD bufferSize = kBufferSize;
		if(!GetUserName(userName, &bufferSize))
		{
			std::cout << "Failed to get user name!" << std::endl;
			return std::string("");
		}
		return std::string(userName);
#endif
	}
}
