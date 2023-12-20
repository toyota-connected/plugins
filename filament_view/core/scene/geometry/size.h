/*
 * Copyright 2020-2023 Toyota Connected North America
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "shell/platform/common/client_wrapper/include/flutter/encodable_value.h"

#include <optional>

namespace plugin_filament_view {

class Size {
 public:
  Size(void* parent,
       const std::string& flutter_assets_path,
       const flutter::EncodableMap& params);
  Size(double x, double y, double z);
  void Print(const char* tag);

  // Disallow copy and assign.
  Size(const Size&) = delete;
  Size& operator=(const Size&) = delete;

 private:
  std::optional<double> x_;
  std::optional<double> y_;
  std::optional<double> z_;
};

}  // namespace plugin_filament_view