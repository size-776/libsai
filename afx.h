#include "SmartDef.h"

#ifdef _DEBUG2
#define _EVLIB
#endif

#ifdef _SMARTLIB

#include "SmartLib.h"

#else // WINDOWS

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS
#define _HAS_AUTO_PTR_ETC 1
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _HAS_STD_BYTE  0

#define CRYPT_SIGN_MESSAGE_PARA_HAS_CMS_FIELDS

#ifdef _WINDOWS

#pragma once

//#define _HAS_AUTO_PTR_ETC 1 // 20230105 SIZE: per C++ 17 FTPClient.h
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

//#ifdef __AFX_H__
#define _SMARTLIB_AFX

#if defined(_DEBUG)
	#define _CRTDBG_MAP_ALLOC	// servono tutte e tre le righe in questo ordine
	//#include <stdlib.h>
	#include <crtdbg.h>	
#endif

#include "PixieLib.h"
#include <afxwin.h>
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxtempl.h>
#include <afxole.h>
#include <afxcmn.h>
#include <afxdtctl.h>
#include <afxinet.h>
#include <afxcview.h>
#include <afxinet.h>
#ifndef WIN64
#include <afxdao.h>
#endif
#include <afxdb.h>
#include <afxmt.h>
#include <afxsock.h>
#include <sddl.h>
#include <tchar.h>
#include "EasyLib.h"
#include <Psapi.h>

#ifdef _GDIPLUS
#include <gdiplus.h>
//using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")
#endif

#if defined(_DEBUG)
	#define new DEBUG_NEW
#endif

//#else // windows no MFC

//#define CString CEasyString
//#define CRect CEasyRect
//#define CPoint CEasyPoint

//#include "EasyString.h"
//#include "EasyRect.h"
//#include "EasyPoint.h"

//#endif // end afx

#endif

#endif // _SMARTLIB
