/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm>
#include <cmath>
#include <functional>
#include <random>

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
#include <thread>
#include <future>

#include <filesystem>

#include <assert.h>

#ifdef OSMMD_CORE_EXPORT
#define OSMMD_CORE_API __declspec(dllexport)
#else
#define OSMMD_CORE_API __declspec(dllimport)
#endif

#define OSMMD_FUNC_API extern "C" OSMMD_CORE_API

#define TIMING_ON Driver::GetInstance().GetPerformance().TIMING

#undef min
#undef max

using Bytes = std::vector<unsigned char>;
