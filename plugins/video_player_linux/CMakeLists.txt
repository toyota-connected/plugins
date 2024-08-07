#
# Copyright 2023-2024 Toyota Connected North America
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

set(PROJECT_NAME "video_player_linux")

# This value is used when generating builds using this plugin, so it must
# not be changed
set(PLUGIN_NAME "plugin_${PROJECT_NAME}")

add_library(${PLUGIN_NAME} STATIC
        video_player_plugin_c_api.cc
        video_player_plugin.cc
        video_player.cc
        messages.g.cc
)
set_target_properties(${PLUGIN_NAME} PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_compile_features(${PLUGIN_NAME} PRIVATE cxx_std_17)

# System-level dependencies.
find_package(PkgConfig REQUIRED)
pkg_check_modules(GST IMPORTED_TARGET REQUIRED gstreamer-1.0>=1.4 gstreamer-video-1.0 libavformat libavutil)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(${PLUGIN_NAME} PRIVATE FLUTTER_PLUGIN_IMPL)
target_include_directories(${PLUGIN_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PLUGIN_NAME} PUBLIC platform_homescreen flutter PkgConfig::GST plugin_common_glib)
