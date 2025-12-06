#pragma once
#include <filesystem>
#include <format>
#include <vector>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <chrono>
#include <Windows.h>
#include <thread>
#include <iomanip>
#include <wininet.h>
#include "imgui.h"
#include "core/globals.hpp"
#include "nlohmann/json.hpp"
#include "util/util.hpp"
#include "util/logger.hpp"
#include "widgets/font_awesome_5.h"
#include "security/xorstr.h"
#include "security/applicationchecker.hpp"
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "wininet.lib")

namespace fs = std::filesystem;
using namespace std::chrono_literals;

#define WINDOW_NAME "TGB's Loader"
#define VERSION "V3.0 Gui Overhaul"
#define TIME "12/6/2025"
#define USE_INTERENT 1//crappy wifi or messing with version/resources

namespace loader
{
	static bool active = true;
}