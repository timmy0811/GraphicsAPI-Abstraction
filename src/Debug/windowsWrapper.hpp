#pragma once

#ifdef CAST_PLATFORM_WINDOWS
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define STRICT_TYPED_ITEMIDS
#include <Windows.h>
#include <shlwapi.h
#elif CAST_PLATFORM_LINUX
#error "including widows wrapper on a linux build."
#endif
