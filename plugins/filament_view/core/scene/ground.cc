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

#include "ground.h"

#include "core/utils/deserialize.h"
#include "plugins/common/common.h"

namespace plugin_filament_view {

Ground::Ground(const std::string& flutter_assets_path,
               const flutter::EncodableMap& params)
    : flutterAssetsPath_(flutter_assets_path) {
  SPDLOG_TRACE("++{} {}", __FILE__, __FUNCTION__);
  bool done[5]{};
  for (auto& it : params) {
    auto key = std::get<std::string>(it.first);
    if (it.second.IsNull()) {
      SPDLOG_WARN("Ground Param ITER is null key:{} file:{} function:{}", key,
                  __FILE__, __FUNCTION__);
      continue;
    }

    if (!done[0] && key == "centerPosition" &&
        std::holds_alternative<flutter::EncodableMap>(it.second)) {
      done[0] = true;
      center_position_ = std::make_unique<::filament::math::float3>(
          Deserialize::Format3(std::get<flutter::EncodableMap>(it.second)));
    } else if (!done[1] && key == "normal" &&
               std::holds_alternative<flutter::EncodableMap>(it.second)) {
      done[1] = true;
      normal_ = std::make_unique<::filament::math::float3>(
          Deserialize::Format3(std::get<flutter::EncodableMap>(it.second)));
    } else if (!done[2] && key == "isBelowModel" &&
               std::holds_alternative<bool>(it.second)) {
      done[2] = true;
      isBelowModel_ = std::get<bool>(it.second);
    } else if (!done[3] && key == "size" &&
               std::holds_alternative<flutter::EncodableMap>(it.second)) {
      done[3] = true;
      size_ = std::make_unique<::filament::math::float3>(
          Deserialize::Format3(std::get<flutter::EncodableMap>(it.second)));
    } else if (!done[4] && key == "material" &&
               std::holds_alternative<flutter::EncodableMap>(it.second)) {
      done[4] = true;
      material_ = std::make_unique<Material>(
          flutterAssetsPath_, std::get<flutter::EncodableMap>(it.second));
      // material_->Print("Ground Creation");
    } else if (!it.second.IsNull()) {
      spdlog::debug("[Ground] Unhandled Parameter");
      plugin_common::Encodable::PrintFlutterEncodableValue(key.c_str(),
                                                           it.second);
    }
  }
  SPDLOG_TRACE("--{} {}", __FILE__, __FUNCTION__);
}

void Ground::Print(const char* tag) {
  spdlog::debug("++++++++");
  spdlog::debug("{} (Ground)", tag);
#if 0
  if (center_position_) {
    center_position_->Print("\tcenter_position");
  }
  if (normal_) {
    normal_->Print("\tnormal");
  }
#endif
  spdlog::debug("\tisBelowModel: {}", isBelowModel_);
#if 0
  if (size_) {
    size_->Print("\tsize");
  }
#endif
  if (material_) {
    material_->Print("\tmaterial");
  }
  spdlog::debug("++++++++");
}

}  // namespace plugin_filament_view