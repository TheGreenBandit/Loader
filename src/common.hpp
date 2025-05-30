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
#include "../includes/ImGui/imgui.h"
#include "core/globals.hpp"
#include "../includes/json/json.hpp" //fuckit changeme 
#include "util/util.hpp"
#include "util/logger.hpp"
#include "widgets/font_awesome_5.h"

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "wininet.lib")

namespace fs = std::filesystem;
using namespace std::chrono_literals;

#define WINDOW_NAME "TGB's Loader"
#define VERSION "V2.52 CHAT FEATURE!!!"
#define TIME "5/29/2025"
#define USE_INTERENT 1//crappy wifi or messing with version/resources

namespace loader
{
	static bool active = true;
}