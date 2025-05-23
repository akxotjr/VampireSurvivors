#pragma once

#include "Types.h"
#include "Defines.h"
#include "Enums.h"
#include "Values.h"
#include "Utils.h"

#include <windows.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <functional>
#include <cmath>
#include <ctime>
#include <random>
#include <memory>
#include <functional>
#include <array>
#include <ctype.h>
#include <assert.h>

// C++20
#include <format>
#include <filesystem>
namespace fs = std::filesystem;

#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

//#ifdef _DEBUG
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif

#pragma comment(lib, "msimg32.lib")

//#include <gdiplus.h>
//#pragma comment(lib, "gdiplus")
//
//using namespace Gdiplus;
using namespace std;