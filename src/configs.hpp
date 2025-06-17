#pragma once

#include <filesystem>
#include <string>

#define APP_FPS 60
#define APP_WINDOW_WIDTH 1280
#define APP_WINDOW_HEIGHT 720

std::string getAssetsPath(const std::string& relativePath);
