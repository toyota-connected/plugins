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

#include "filament_scene.h"

#include "shell/platform/common/client_wrapper/include/flutter/standard_message_codec.h"

#include "core/scene/scene_controller.h"
#include "plugins/common/common.h"

namespace plugin_filament_view {

FilamentScene::FilamentScene(PlatformView* platformView,
                             FlutterDesktopEngineState* state,
                             int32_t id,
                             const std::vector<uint8_t>& params,
                             const std::string& flutterAssetsPath) {
  SPDLOG_TRACE("++{} {}", __FILE__, __FUNCTION__);
  auto& codec = flutter::StandardMessageCodec::GetInstance();
  const auto decoded = codec.DecodeMessage(params.data(), params.size());
  const auto& creationParams =
      std::get_if<flutter::EncodableMap>(decoded.get());

  for (const auto& it : *creationParams) {
    auto key = std::get<std::string>(it.first);
    if (it.second.IsNull()) {
      SPDLOG_DEBUG("CreationParamName ITER is null {} {} {}", key.c_str(),
                   __FILE__, __FUNCTION__);
      continue;
    }

    if (key == "model") {
      SPDLOG_WARN("Loading Single Model - Deprecated Functionality {}", key);
      models_ = std::make_unique<std::vector<std::unique_ptr<Model>>>();
      models_->emplace_back(Model::Deserialize(flutterAssetsPath, it.second));
    } else if (key == "models" &&
               std::holds_alternative<flutter::EncodableList>(it.second)) {
      // load models here.
      SPDLOG_TRACE("Loading Multiple Models {}", key);

      models_ = std::make_unique<std::vector<std::unique_ptr<Model>>>();
      auto list = std::get<flutter::EncodableList>(it.second);

      for (const auto& iter : list) {
        if (iter.IsNull()) {
          SPDLOG_WARN("CreationParamName unable to cast {}", key.c_str());
          continue;
        }

        models_->emplace_back(Model::Deserialize(flutterAssetsPath, iter));
      }

    } else if (key == "scene") {
      scene_ = std::make_unique<Scene>(flutterAssetsPath, it.second);
    } else if (key == "shapes" &&
               std::holds_alternative<flutter::EncodableList>(it.second)) {
      shapes_ = std::make_unique<std::vector<std::unique_ptr<Shape>>>();

      auto list = std::get<flutter::EncodableList>(it.second);

      for (const auto& iter : list) {
        if (iter.IsNull()) {
          SPDLOG_DEBUG("CreationParamName unable to cast {}", key.c_str());
          continue;
        }

        auto shape = std::make_unique<Shape>(
            flutterAssetsPath, std::get<flutter::EncodableMap>(iter));
        shapes_->emplace_back(shape.release());
      }
    } else {
      spdlog::warn("[FilamentView] Unhandled Parameter {}", key.c_str());
      plugin_common::Encodable::PrintFlutterEncodableValue(key.c_str(),
                                                           it.second);
    }
  }
  sceneController_ = std::make_unique<SceneController>(
      platformView, state, flutterAssetsPath, models_.get(), scene_.get(),
      shapes_.get(), id);
  SPDLOG_TRACE("--{} {}", __FILE__, __FUNCTION__);
}

FilamentScene::~FilamentScene() {
  SPDLOG_TRACE("++FilamentScene::~FilamentScene");
  SPDLOG_ERROR("::~FilamentScene:: TODO");
  SPDLOG_TRACE("--FilamentScene::~FilamentScene");
};

}  // namespace plugin_filament_view
