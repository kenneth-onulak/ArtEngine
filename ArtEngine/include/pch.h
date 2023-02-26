/*+*************************************************************************//*!
 \file:      pch.h

 \summary:   precompiled header

 \origin:    ArtEngine

 Copyright (c) 2023 Kenneth Onulak Jr.
 MIT License
**************************************************************************//*+*/
#ifndef ARTENGINE_PCH_H
#define ARTENGINE_PCH_H

// stl
#include <algorithm>
#include <array>
#include <atomic>
#include <cassert>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <deque>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <istream>
#include <iterator>
#include <list>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <numbers>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <stack>
#include <stdexcept>
#include <sstream>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>

// rendering dependencies
#include <gl/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// file / console IO
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

// ImGui
#include <imgui.h>
#include <imgui_internal.h>
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

using Handle = std::function<void()>;

// engine files
#include "view.h"
#include "event.h"

// utility
#include "utility/buffer.h"
#include "utility/model.h"
#include "utility/instance.h"
#include "utility/shader.h"
#include "utility/texture.h"
#include "utility/target.h"

// helpers
#include "helpers/camera.h"
#include "helpers/timer.h"
#include "helpers/color.h"
#include "helpers/object.h"
#include "helpers/parse.h"
#include "helpers/log.h"
#include "helpers/image.h"

#endif // ARTENGINE_PCH_H