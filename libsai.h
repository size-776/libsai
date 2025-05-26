#pragma once

#include "saiDef.h"

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS

/*

_SMARTLIB
_SMARTLIB64
+SMARTLIB_RX RX62N oliv
+SMARTLIB_IOS
_SMARTLIB_APPLE
_SMARTLIB_OSX
+SMARTLIB_ANDROID
+SMARTLIB_UNIX
+SMARTLIB_UNIX+SMARTLIB_ARM
_SMARTLIB_WINRT
_SMARTLIB_FAKE

*/

#ifdef _SMARTLIB_WINRT /* WINPHONE SECTION */

#define HAVE_UINT32_T
//#undef UNICODE
//#undef _UNICODE
#define _SMARTLIB_WANTBMP

//#ifndef _SMARTLIB_FAKE
#include <windows.h>
//#endif
#include <tchar.h>
#include <io.h>

//typedef char TCHAR;

typedef int POSITION;

#define CRect CEasyRect
#define CPoint CEasyPoint
#define CSize CEasySize

//#define _T(x) L ## x
#define ASSERT(a) (a)

//typedef LPSTR BSTR;
#define CString CEasyStringT
#ifdef _UNICODE
#define CEasyStringT CEasyStringW
#else
#define CEasyStringT CEasyString
#endif
#define CStringW CEasyStringW
#define CStringT CEasyStringT
#define CStringList CEasyStringList
#define CTime CEasyTime

#include <stdio.h>
#include <time.h>

#include "EasyString.h"
#include "EasyStringW.h"
#include "EasyRect.h"
#include "EasySize.h"
#include "EasyPoint.h"
#include "EasyArray.h"
#include "EasyMap.h"
#ifndef _SMARTLIB_FAKE
#include "SmartGDI.h"
#endif
#include "SmartAFX.h"
#include "EasyTime.h"

typedef CEasyDoubleArray CDoubleArray;
typedef CEasyBoolArray CBoolArray;
typedef CEasyVoidPtrArray CVoidPtrArray;
#define CArray CEasyVTypeArray

int slMoveFile(LPCTSTR szSrc, LPCTSTR szDst);
int slCopyFile(LPCTSTR szSrc, LPCTSTR szDst, bool bFailIfExits);
int slDeleteFile(LPCTSTR szFile);
UINT slGetPrivateProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault, LPCTSTR szIniFile);
int slGetPrivateProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault, LPTSTR lpszValue, DWORD nValue, LPCTSTR szIniFile);
int slWritePrivateProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue, LPCTSTR szIniFile);
int slWritePrivateProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue, LPCTSTR szIniFile);
DWORD WINAPI GetTickCount(void);
int WINAPI MessageBox(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);

#define GetPrivateProfileInt slGetPrivateProfileInt
#define GetPrivateProfileString slGetPrivateProfileString
#define WritePrivateProfileInt slWritePrivateProfileInt
#define WritePrivateProfileString slWritePrivateProfileString
#define MoveFile slMoveFile
#define CopyFile slCopyFile
//#define DeleteFile slDeleteFile
#define AFX_MANAGE_STATE(a) a
#define AfxGetStaticModuleState() 0

#else

#ifdef _SMARTLIB_ARM
#define _SMARTLIB_UNIX
#endif

#ifdef _SMARTLIB_FAKE
#define _EXCEPT
#endif

#ifndef FILE_SHARE_READ
#define FILE_SHARE_READ 1
#endif

#if defined(_WIN64) || defined(__LP64__)
#define _SMARTLIB64
#endif

#if defined(_LIBSAI_WIN) || defined(_SMARTLIB_ANDROID) || defined(_SMARTLIB_IOS) || defined(_SMARTLIB_RX) || defined(_SMARTLIB_UNIX) || defined(_SMARTLIB_WINRT) // 20140910 SIZE: servono tutte per consentire compilazione WINDOWS/MFC

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <time.h>

#if !defined(_SMARTLIB_IOS)
#include <sys/stat.h>
#endif

//#if defined(_SMARTLIB_UNIX) && !defined(_SMARTLIB_FAKE)
#if (defined(_SMARTLIB_UNIX) || defined(_SMARTLIB_ANDROID) || defined(_SMARTLIB_IOS) || defined(_SMARTLIB_WINRT)) && !defined(_SMARTLIB_FAKE)
#if !defined(_SMARTLIB_WINRT)
#include <inttypes.h>
#include <locale.h>
#define __int64 int64_t
#define __int16 short
#endif
#define _fsopen(a,b,c) fopen(a,b)
#define _strrev strrev
#define _open open
#define _read read
#define _write write
#define _close close
#define HAVE_UINT32_T
#if !defined(_SMARTLIB_IOS) && !defined(_SMARTLIB_WASM)
#define __max max
#endif
#ifndef _SMARTLIB_WINRT
#define _atoi64(a) strtoull(a, NULL, 10)
char *strrev(char *str);
char *strupr(char *str);
#endif
const unsigned long long UINT64_ONE = 1ULL;
#endif

#if !defined(_SMARTLIB_ANDROID) && !defined(_SMARTLIB_IOS) && !defined(_SMARTLIB_UNIX) || defined(_SMARTLIB_FAKE)
#include <tchar.h>
#else
typedef char _TCHAR;
#define _itot _itoa
#define _ttoi atoi
#define _ttoi64 _atoi64
#define _stprintf sprintf
#define _tcscmp strcmp
#define _tcsncpy strncpy
#define _ttof atof
#define _tcsicmp stricmp
#define _tcscat strcat
#define _stscanf sscanf
#define _ftscanf fscanf
#define _tcstok strtok
#define _tcsnicmp strnicmp
#define _fgetts fgets
#define _tstat stat
#endif

#ifdef _ANDROID
#define _tstat	stat
#endif

//#ifdef _SMARTLIB_IOS
#ifdef _SMARTLIB
#define _ftprintf fprintf
#define _topen _open
#define _lseek lseek
#define _tremove remove
#define _vsctprintf _vscprintf
#define _vstprintf vsprintf
#endif

#define _SH_DENYRW      0x10    /* deny read/write mode */
#define _SH_DENYWR      0x20    /* deny write mode */
#define _SH_DENYRD      0x30    /* deny read mode */
#define _SH_DENYNO      0x40    /* deny none mode */
#define _SH_SECURE      0x80    /* secure mode */

#if !defined(_W64) && (defined(_SMARTLIB_ANDROID) || defined(_SMARTLIB_UNIX) || defined(_SMARTLIB_IOS))
#define _W64
#endif

#if defined(_SMARTLIB_ANDROID)
#define __stdcall

// _P spesso usato per CImageInfo
#ifdef _P
	#undef _P
#endif
// _S usata per CStrip2
#ifdef _S
	#undef _S
#endif

#ifdef _X
	#undef _X
#endif

#endif //  defined(_SMARTLIB_ANDROID)

#if defined(_SMARTLIB_IOS) && defined(__APPLE__)
#define __stdcall
#undef _ttoi64
#define _ttoi64 atoll
#endif

#ifdef _SMARTLIB_APPLE
int elCeil(double x);
#endif

//#define NULL 0
//#define strncpy_s strncpy

#define WINAPI __stdcall
#if defined(_SMARTLIB_UNIX) && !defined(_SMARTLIB_FAKE)
#define __stdcall
#endif
//#define FAR         _far
#define FAR
#define _FAR
#define NEAR
#define _NEAR
#define PASCAL      _pascal
#define CDECL       _cdecl
#define VOID        void
#define CALLBACK	__stdcall
#define EXTERN_C    extern "C"
#define STDAPI      EXTERN_C HRESULT STDAPICALLTYPE
#define STDMETHODCALLTYPE       __stdcall
#define STDMETHODIMP HRESULT STDMETHODCALLTYPE

#define CONST const

typedef char CHAR;
typedef CHAR* LPSTR;
typedef const CHAR* LPCSTR;

typedef wchar_t WCHAR;
typedef WCHAR* LPWSTR;
typedef const WCHAR* LPCWSTR;

#if !defined(_SMARTLIB_WINRT)
typedef CHAR TCHAR;
#endif
typedef TCHAR* LPTSTR;
//typedef const LPTSTR LPCTSTR;
typedef const TCHAR* LPCTSTR; // messo per iOS

typedef unsigned char BYTE;
typedef BYTE *LPBYTE;
typedef BYTE TBYTE;
typedef unsigned short WORD;
typedef WORD* LPWORD;
typedef unsigned int DWORD;
typedef short SHORT;
typedef SHORT *PSHORT;
typedef long LONG;
typedef LONG *PLONG;
typedef int *LPINT;
typedef void *LPVOID;
typedef LPVOID HANDLE;
typedef HANDLE HGLOBAL;
typedef HANDLE HWND;
typedef HANDLE HINSTANCE;
typedef HANDLE HMODULE;
typedef HANDLE HINTERNET;
typedef HANDLE HKEY;
typedef HANDLE HCONV;
typedef HANDLE HDDEDATA;
typedef HANDLE HSZ;
typedef HANDLE HTREEITEM;
typedef HANDLE HMENU;
typedef DWORD *LPDWORD;
typedef LPVOID LPOVERLAPPED;
typedef const LPVOID *LPCVOID;
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned int *PUINT;
#ifdef _WASM
typedef WORD __int16;
#endif
#ifdef _SMARTLIB_IOS
#ifndef __MACTYPES__
typedef signed char BOOL;
#endif
#define HAVE_UINT32_T
#else
typedef int BOOL;
#endif
typedef unsigned int UINT;
typedef _W64 unsigned long ULONG_PTR, *PULONG_PTR;
typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
typedef void IUnknown;
#if defined(_SMARTLIB64)
typedef __int64 LONG_PTR;
typedef __int64 UINT64, *PUINT64; // 20160216 SIZE: aggiunto per JPEG2000
#else
typedef long LONG_PTR;
typedef __int64 UINT64, *PUINT64; // 20160224 SIZE: per JPEG2000 UNIX32 (useless..)
#endif
#if defined(_SMARTLIB64)
#if defined(_SMARTLIB_UNIX) || defined(_SMARTLIB_IOS)
typedef unsigned long long int UINT_PTR;
#else
typedef unsigned __int64 UINT_PTR;
#endif
#else
typedef unsigned int UINT_PTR;
#endif
typedef LONG_PTR LRESULT;
typedef UINT_PTR WPARAM;
typedef LONG_PTR LPARAM;
typedef long HRESULT;
typedef wchar_t* BSTR;
typedef void* LPDISPATCH;
typedef int POSITION;
typedef void* MSG;

#ifndef HAVE_UINT32_T
typedef unsigned int uint32_t;
#endif

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((BYTE)((w) & 0xff))
#define HIBYTE(w)           ((BYTE)((w >> 8) & 0xff))

//#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define RGB(r,g,b)			((COLORREF)((((BYTE)(r))&0xFF) | ((((BYTE)(g))<<8) & 0xFF00) | ((((BYTE)(g))<<16) & 0xFF0000)))
//#define GetRValue(rgb)      (LOBYTE(rgb))
//#define GetGValue(rgb)      (LOBYTE(((WORD)(rgb)) >> 8))
//#define GetBValue(rgb)      (LOBYTE((rgb)>>16))
#define GetRValue(rgb)      ((BYTE)((rgb) & 0xFF))
#define GetGValue(rgb)      ((BYTE)(((rgb)>> 8) & 0xFF))
#define GetBValue(rgb)      ((BYTE)(((rgb)>>16) & 0xFF))

#define CString CEasyStringT
#define CStringW CEasyStringW
#define CStringT CEasyStringT
#define CStringList CEasyStringList

#if !defined(_SMARTLIB_WINRT)
#define CEasyStringT CEasyString
#else
#define CEasyStringT CEasyStringW
#endif

#define CRect CEasyRect
#define CPoint CEasyPoint
#define CSize CEasySize

#define FALSE   0
#define TRUE    1
//#define NULL    0

#define MAX_PATH    260
#ifndef INT_MAX
#define INT_MAX     2147483647
#endif
#ifndef UINT_MAX
#define UINT_MAX	0xffffffff
#endif

#ifndef MAXWORD
#define MAXWORD     0xFFFF
#endif

#ifndef MAXSHORT
#define MAXSHORT	0x7FFF
#endif

#ifndef SHRT_MAX
#define SHRT_MIN    (-32768)        // minimum (signed) short value
#define SHRT_MAX      32767         // maximum (signed) short value
#endif

#define INFINITE            0xFFFFFFFF

#define INTERNET_DEFAULT_HTTP_PORT 80
#define INTERNET_DEFAULT_HTTPS_PORT 443

//#ifdef _SMARTLIB_IOS // tolto per compilare segdata
//#define ASSERT(a)
//#else
#define ASSERT(a) (a)
//#endif
#define TRACE(a) (a)

//typedef LPBYTE LPSECURITY_ATTRIBUTES;

//#define GENERIC_READ 1
//#define GENERIC_WRITE 2

//#define OPEN_EXISTING 2
//#define CREATE_ALWAYS 3

#define FILE_BEGIN 0 // 20140729 SIZE: rimesso per UNIX libtiff
#define FILE_CURRENT 1
#define FILE_END 2

#define IDOK                1
#define IDCANCEL            2
#define IDABORT             3
#define IDRETRY             4
#define IDIGNORE            5
#define IDYES               6
#define IDNO                7

#define	S_OK				0

#define MB_OK                       0x00000000L
#define MB_OKCANCEL                 0x00000001L
#define MB_ABORTRETRYIGNORE         0x00000002L
#define MB_YESNOCANCEL              0x00000003L
#define MB_YESNO                    0x00000004L
#define MB_RETRYCANCEL              0x00000005L
#define MB_CANCELTRYCONTINUE        0x00000006L

#define MB_ICONHAND                 0x00000010L
#define MB_ICONQUESTION             0x00000020L
#define MB_ICONEXCLAMATION          0x00000030L
#define MB_ICONASTERISK             0x00000040L
#define MB_USERICON                 0x00000080L
#define MB_ICONWARNING              MB_ICONEXCLAMATION
#define MB_ICONERROR                MB_ICONHAND
#define MB_ICONINFORMATION          MB_ICONASTERISK
#define MB_ICONSTOP                 MB_ICONHAND
#define MB_TOPMOST					0x00040000L

//#define INVALID_HANDLE_VALUE 0xFFFFFFFF

//#define _vscprintf(f,a) vsprintf(NULL,f,a)
#define _vscprintf(f,a) vsnprintf(NULL, 0, f, a)
#define _strcmp strcmp
#define _strncmp strncmp
#define _stricmp strcasecmp
#define _strnicmp strncasecmp
#define stricmp strcasecmp
#define strnicmp strncasecmp
#ifndef _SMARTLIB_WINRT
#define _tfopen fopen
#define _tfsopen(a, b, c) fopen(a, b)
#define _tstof atof
#define _tcsupr _strupr
#define _tcsncmp strncmp
#define _tcsncat strncat
#define _tcslen strlen
#define _tcscpy strcpy
#endif
#define _itoa(n, buf, len) sprintf(buf, "%d", n)
#define _strupr strupr
#define CopyFile slCopyFile
#define MoveFile slMoveFile
#define DeleteFile slDeleteFile
#ifndef _SMARTLIB_IOS
#define interface class
#endif
#define GetSystemTime(st) CSmartHelper::GetTime(st, false)
#define GetLocalTime(st) CSmartHelper::GetTime(st, true)
#define Sleep slSleep

DWORD WINAPI GetLastError();
DWORD WINAPI GetCurrentProcessId();
int WINAPI MessageBox(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);

int slCopyFile(LPCTSTR szSrc, LPCTSTR szDst, bool bFailIfExits);
int slDeleteFile(LPCTSTR szFile);
int slMoveFile(LPCTSTR szSrc, LPCTSTR szDst);
int slSleep(DWORD dwTime);

#define AFX_MANAGE_STATE(a) a
#define AfxGetStaticModuleState() 0

/*#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })
	*/

#if !defined(min)
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

#ifdef _SMARTLIB_WINRT
#define _T(x)      L ## x
#else
#define _T(a) a
#endif

// da stdlib.h
#define _MAX_PATH 260

#define _SMARTLIB_WANTRPS // rect point size
#define _SMARTLIB_WANTBMP
#define _SMARTLIB_SMARTIMAGE

#ifdef _SMARTLIB_ANDROID
#define HAVE_UINT32_T
#endif

//#include "EasyString.h"
//#include "EasyStringW.h"
//#include "EasyRect.h"
//#include "EasySize.h"
//#include "EasyPoint.h"
//#include "SmartGDI.h"
//#include "SmartAFX.h"

UINT slGetPrivateProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault, LPCTSTR szIniFile, LPCTSTR szStream= NULL);
int slGetPrivateProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault, LPSTR lpszValue, DWORD nValue, LPCTSTR szIniFile, LPCTSTR szStream= NULL);
int slWritePrivateProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue, LPCTSTR szIniFile);
int slWritePrivateProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue, LPCTSTR szIniFile);
#define GetPrivateProfileInt slGetPrivateProfileInt
#define GetPrivateProfileString slGetPrivateProfileString
#define WritePrivateProfileInt slWritePrivateProfileInt
#define WritePrivateProfileString slWritePrivateProfileString

#ifdef _SMARTLIB_RX

#define _SMARTLIB_NOSMARTIMAGE
#define _SMARTPDF_LITE

#define _vscprintf(f,a) _MAX_PATH
#else

#include "saiArray.h"
//#include "EasyMap.h"

//#define CStrArray CEasyStrArray
typedef CsaiDoubleArray CDoubleArray;
typedef CsaiBoolArray CBoolArray;
typedef CsaiVoidPtrArray CVoidPtrArray;

#define CTime CEasyTime
//#include "EasyTime.h"

#endif

typedef long long INT64;
#ifndef _MSC_VER
#ifndef _SMARTLIB_UNIX
typedef INT64 __int64;
#endif
#define _1i64 1LL
#endif

#ifndef _WINDOWS

DWORD GetTickCount(void);
bool IsDigit(char c, bool Ext);

typedef struct _GUID {
    unsigned int  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
} GUID;

typedef GUID IID;
#define REFIID const IID &

#endif

// 20160217 SIZE: commentato
/*class CEasySigner
{
public:
};*/

#endif // mobile

#ifdef _WINDOWS

//#pragma once

//#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#if !defined(_WIN32_WINNT) && !defined(WINVER)
#if _MSC_VER >= 1600
#define _WIN32_WINNT	0x0501
#define WINVER			0x0501
#else
#define _WIN32_WINNT	0x0410
#define WINVER			0x0410
#endif
#define _WIN32_IE		0x0600
#endif

#ifdef _DEBUG2
#define _WIN32_WINNT	0x0502 //_WIN32_WINNT_WS03
#define WINVER			0x0502
//#define NTDDI_VERSION	NTDDI_WS03 // abilitare SHA 256 per test
#endif

//#define _SMARTLIB_IMAGE

#ifdef _SMARTLIB_WINCRT

#include <windows.h>
#include <sddl.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <tchar.h>
#include <share.h>
#include <Psapi.h>
#include <stdio.h>
#include <time.h>
//#include <minwindef.h>

#define CString CEasyStringT
#ifdef _UNICODE
#define CEasyStringT CEasyStringW
#else
#define CEasyStringT CEasyString
#endif
#define CStringW CEasyStringW
#define CRect CEasyRect
#define CPoint CEasyPoint
//#define POINT CEasyPoint
#define CSize CEasySize
typedef int POSITION;
typedef HANDLE HINTERNET;
typedef int INTERNET_PORT;

#define _W64
#define __in

#ifdef  _SMARTLIB64
typedef __int64             intptr_t;
#else
typedef _W64 int            intptr_t;
#endif

#if !defined(_SMARTLIB_WINCRT)
#if !defined(min)
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif
#endif // _SMARTLIB_WINCRT

#include "EasyString.h"
#include "EasyStringW.h"
#include "EasyRect.h"
#include "EasyPoint.h"
#include "EasySize.h"
#include "EasyArray.h"
#include "EasyMap.h"
#include "EasyRect.h"
#include "EasyPoint.h"

typedef CEasyDoubleArray CDoubleArray;
typedef CEasyBoolArray CBoolArray;
typedef CEasyVoidPtrArray CVoidPtrArray;

#define CTime CEasyTime
#include "EasyTime.h"

#include "SmartAFX.h"

#define ASSERT(a) a
#define TRACE(a) a

#ifdef __GNUC__
#define _tstof atof
#endif // __GNUC__

#else // MFC

#include <afxwin.h>
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxinet.h>
#ifndef WIN64
#include <afxdao.h>
#endif
#include <afxdb.h>
#include <afxmt.h>
#include <afxsock.h>

#if defined(_DEBUG)
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
	#define new DEBUG_NEW
#endif

#endif // end afx

#endif // windows

#if defined(_SMARTLIB_FAKE) || defined(_SMARTLIB_WINRT)

#undef _stricmp
#undef _strnicmp
#define strcasecmp _stricmp
#define strncasecmp _strnicmp

#undef HAVE_UINT32_T

#endif

#endif

//#include "EasyLib.h"

