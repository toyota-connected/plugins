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

#include <cstdint>
#include <memory>
#include <optional>
#include <string>

#include "shell/platform/common/client_wrapper/include/flutter/encodable_value.h"

#include "models/model/model.h"
#include "models/scene/geometry/position.h"

namespace plugin_filament_view {

class Animation {
 public:
  Animation(void* parent,
            const std::string& flutter_assets_path,
            const flutter::EncodableMap& params);
  void Print(const char* tag);

  // Disallow copy and assign.
  Animation(const Animation&) = delete;
  Animation& operator=(const Animation&) = delete;

 private:
  std::optional<int32_t> index_;
  std::string name_;
  bool auto_play_;
  std::string asset_path_;
  std::optional<std::unique_ptr<Position>> center_position_;
  const std::string& flutterAssetsPath_;
};

}  // namespace plugin_filament_view