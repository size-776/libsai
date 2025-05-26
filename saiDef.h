// http://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
#ifdef _WIN32
#	ifdef __cplusplus_winrt
#	define _LIBSAI_WINRT
#	endif
//#elif _WIN64
#elif defined(__APPLE__)
#	define _LIBSAI
#	define _LIBSAI_APPLE
#	include <TargetConditionals.h>
#	ifdef TARGET_IPHONE_SIMULATOR
#	define _LIBSAI_IOS
#	endif
#	ifdef TARGET_OS_IPHONE
#	define _LIBSAI_IOS
#	endif
#	ifdef TARGET_OS_MAC
#	define _LIBSAI_OSX
#	endif
#elif defined(_ANDROID)
#	ifndef _LIBSAI
#		define _LIBSAI
#	endif
#	ifndef _LIBSAI_ANDROID
#		define _LIBSAI_ANDROID
#	endif
#elif defined(__linux)
#	ifndef _LIBSAI
#	define _LIBSAI
#	endif
#	define _LIBSAI_UNIX
#elif defined(_AIX)
#	define _LIBSAI
#	define _LIBSAI_UNIX
#	define _LIBSAI_AIX
#elif defined(EMSCRIPTEN)
#	define _LIBSAI
#	define _LIBSAI_UNIX
#	define _LIBSAI_WASM
#elif defined(__unix)
#elif defined(__posix)
#endif

// Check Windows
#if _WIN32 || _WIN64
   #if _WIN64
     #define ENV64BIT
  #else
    #define ENV32BIT
  #endif
#endif

// Check GCC
#if __GNUC__
  #if __x86_64__ || __ppc64__
    #define ENV64BIT
  #else
    #define ENV32BIT
  #endif
#endif

#ifdef __APPLE__
  #define ENV64BIT
#endif
