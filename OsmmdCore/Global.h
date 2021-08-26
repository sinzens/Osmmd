/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm>
#include <cmath>
#include <functional>

#include <array>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <deque>
#include <stack>

#include <mutex>

#include <filesystem>

#ifdef OSMMD_CORE_EXPORT
#define OSMMD_CORE_API __declspec(dllexport)
#else
#define OSMMD_CORE_API __declspec(dllimport)
#endif

#define OSMMD_FUNC_API extern "C" OSMMD_CORE_API

#undef min
#undef max
