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

#include "scene.h"

#include "plugins/common/common.h"

namespace plugin_filament_view {

Scene::Scene(const std::string& flutter_assets_path,
             const flutter::EncodableValue& params)
    : flutterAssetsPath_(flutter_assets_path) {
  SPDLOG_TRACE("++{}::{}", __FILE__, __FUNCTION__);
  for (auto& it : std::get<flutter::EncodableMap>(params)) {
    auto key = std::get<std::string>(it.first);
    if (it.second.IsNull()) {
      SPDLOG_WARN("Scene Param ITER is null key:{} file:{} function:{}", key,
                  __FILE__, __FUNCTION__);
      continue;
    }

    if (key == "skybox" &&
        std::holds_alternative<flutter::EncodableMap>(it.second)) {
      skybox_ = plugin_filament_view::Skybox::Deserialize(
          std::get<flutter::EncodableMap>(it.second));
    } else if (key == "light" &&
               std::holds_alternative<flutter::EncodableMap>(it.second)) {
      light_ =
          std::make_unique<Light>(std::get<flutter::EncodableMap>(it.second));
    } else if (key == "indirectLight" &&
               std::holds_alternative<flutter::EncodableMap>(it.second)) {
      indirect_light_ = IndirectLight::Deserialize(
          std::get<flutter::EncodableMap>(it.second));
    } else if (key == "camera" &&
               std::holds_alternative<flutter::EncodableMap>(it.second)) {
      camera_ =
          std::make_unique<Camera>(std::get<flutter::EncodableMap>(it.second));
    } else if (key == "ground" &&
               std::holds_alternative<flutter::EncodableMap>(it.second)) {
      ground_ = std::make_unique<Ground>(
          flutterAssetsPath_, std::get<flutter::EncodableMap>(it.second));
    } else if (!it.second.IsNull()) {
      spdlog::debug("[Scene] Unhandled Parameter {}", key.c_str());
      plugin_common::Encodable::PrintFlutterEncodableValue(key.c_str(),
                                                           it.second);
    }
  }
  SPDLOG_TRACE("--{}::{}", __FILE__, __FUNCTION__);
}

Scene::~Scene() {
  SPDLOG_TRACE("Scene::~Scene()");
}

void Scene::Print(const char* tag) const {
  spdlog::debug("++++++++");
  spdlog::debug("{} (Scene)", tag);
#if 0
        if (skybox_.has_value()) {
          skybox_.value()->Print("\tskybox");
        }
#endif
  if (light_) {
    light_->Print("\tlight");
  }
  if (indirect_light_) {
    /// indirect_light_->Print("\tindirect_light");
  }
  if (camera_) {
    camera_->Print("\tcamera");
  }
  if (ground_) {
    ground_->Print("\tground");
  }
  spdlog::debug("++++++++");
}

}  // namespace plugin_filament_view
