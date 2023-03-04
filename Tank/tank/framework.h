#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 的一些常见且经常可放心忽略的隐藏警告消息
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC 支持功能区和控制条









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
#include <gdiplus.h>
#include<cassert>
#include<cmath>
#include<algorithm>
#include<deque>
#include<exception>
#include<fstream>
#include<functional>
#include<ios>
#include<iostream>
#include<istream>
#include<limits>
#include<list>
#include<locale>
#include<map>
#include<memory>
#include<numeric>
#include<ostream>
#include<queue>
#include<random>
#include<regex>
#include<set>
#include<stack>
#include<string>
#include<strstream>
#include<tuple>
#include<vector>
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;
#define PI 3.14159265357f

typedef struct PathNode {
	int x;
	int y;
}PathNode;
typedef std::vector<PathNode>VPath;
//删除内存的宏,删除内存并把指针赋值为空，以免后续代码误用已经删除的内存
#define SAFE_DEL_PTR(ptr)if((ptr)!=nullptr){delete ptr;ptr=nullptr;}
using namespace std;

