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

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "wininet.lib")

#define WINDOW_NAME "TGB's Loader"

namespace loader
{
	static bool active = true;
}