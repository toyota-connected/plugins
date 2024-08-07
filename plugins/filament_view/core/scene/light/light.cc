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

#include "light.h"

#include "core/utils/deserialize.h"
#include "plugins/common/common.h"

namespace plugin_filament_view {

Light::Light(float colorTemperature,
             float intensity,
             ::filament::math::float3 direction,
             bool castShadows) {
  type_ = ::filament::LightManager::Type::DIRECTIONAL;
  colorTemperature_ = colorTemperature;
  intensity_ = intensity;
  direction_ = std::make_unique<::filament::math::float3>(direction);
  castShadows_ = castShadows;
}

Light::Light(const flutter::EncodableMap& params) {
  SPDLOG_TRACE("++{}::{}", __FILE__, __FUNCTION__);
  for (auto& it : params) {
    auto key = std::get<std::string>(it.first);
    if (it.second.IsNull()) {
      SPDLOG_WARN("Light Param ITER is null key:{} file:{} function:{}", key,
                  __FILE__, __FUNCTION__);
      continue;
    }

    if (key == "type" && std::holds_alternative<std::string>(it.second)) {
      type_ = textToLightType(std::get<std::string>(it.second));
    } else if (key == "color" &&
               std::holds_alternative<std::string>(it.second)) {
      color_ = std::get<std::string>(it.second);
      SPDLOG_DEBUG("color: {}", color_.value());
    } else if (key == "colorTemperature" &&
               std::holds_alternative<double>(it.second)) {
      colorTemperature_ = std::get<double>(it.second);
    } else if (key == "intensity" &&
               std::holds_alternative<double>(it.second)) {
      intensity_ = std::get<double>(it.second);
    } else if (key == "position" &&
               std::holds_alternative<flutter::EncodableMap>(it.second)) {
      position_ = std::make_unique<::filament::math::float3>(
          Deserialize::Format3(std::get<flutter::EncodableMap>(it.second)));
    } else if (key == "direction" &&
               std::holds_alternative<flutter::EncodableMap>(it.second)) {
      direction_ = std::make_unique<::filament::math::float3>(
          Deserialize::Format3(std::get<flutter::EncodableMap>(it.second)));
    } else if (key == "castLight" && std::holds_alternative<bool>(it.second)) {
      castLight_ = std::get<bool>(it.second);
    } else if (key == "castShadows" &&
               std::holds_alternative<bool>(it.second)) {
      castShadows_ = std::get<bool>(it.second);
    } else if (key == "falloffRadius" &&
               std::holds_alternative<double>(it.second)) {
      falloffRadius_ = std::get<double>(it.second);
    } else if (key == "spotLightConeInner" &&
               std::holds_alternative<double>(it.second)) {
      spotLightConeInner_ = std::get<double>(it.second);
    } else if (key == "spotLightConeOuter" && !it.second.IsNull() &&
               std::holds_alternative<double>(it.second)) {
      spotLightConeOuter_ = std::get<double>(it.second);
    } else if (key == "sunAngularRadius" && !it.second.IsNull() &&
               std::holds_alternative<double>(it.second)) {
      sunAngularRadius_ = std::get<double>(it.second);
    } else if (key == "sunHaloSize" && !it.second.IsNull() &&
               std::holds_alternative<double>(it.second)) {
      sunHaloSize_ = std::get<double>(it.second);
    } else if (key == "sunHaloFalloff" && !it.second.IsNull() &&
               std::holds_alternative<double>(it.second)) {
      sunHaloFalloff_ = std::get<double>(it.second);
    } else if (!it.second.IsNull()) {
      spdlog::debug("[Light] Unhandled Parameter {}", key.c_str());
      plugin_common::Encodable::PrintFlutterEncodableValue(key.c_str(),
                                                           it.second);
    }
  }

  // Print("Setup Light");
  SPDLOG_TRACE("--{}::{}", __FILE__, __FUNCTION__);
}

void Light::Print(const char* tag) {
  spdlog::debug("++++++++");
  spdlog::debug("{} (Light)", tag);

  spdlog::debug("\ttype: {}", lightTypeToText(type_));
  if (color_.has_value()) {
    spdlog::debug("\tcolor: {}", color_.value());
  }
  if (colorTemperature_.has_value()) {
    spdlog::debug("\tcolorTemperature: {}", colorTemperature_.value());
  }
  if (intensity_.has_value()) {
    spdlog::debug("\tintensity: {}", intensity_.value());
  }
#if 1
  if (position_) {
    SPDLOG_DEBUG("\tposition {} {} {}", position_.get()->x, position_.get()->y,
                 position_.get()->z);
  }
  if (direction_) {
    SPDLOG_DEBUG("\tdirection_ {} {} {}", direction_.get()->x,
                 direction_.get()->y, direction_.get()->z);
  }
#endif
  if (castLight_.has_value()) {
    spdlog::debug("\tcastLight: {}", castLight_.value());
  }
  if (castShadows_.has_value()) {
    spdlog::debug("\tcastShadows: {}", castShadows_.value());
  }
  if (falloffRadius_.has_value()) {
    spdlog::debug("\tfalloffRadius: {}", falloffRadius_.value());
  }
  if (spotLightConeInner_.has_value()) {
    spdlog::debug("\tspotLightConeInner: {}", spotLightConeInner_.value());
  }
  if (spotLightConeOuter_.has_value()) {
    spdlog::debug("\tspotLightConeOuter: {}", spotLightConeOuter_.value());
  }
  if (sunAngularRadius_.has_value()) {
    spdlog::debug("\tsunAngularRadius: {}", sunAngularRadius_.value());
  }
  if (sunHaloSize_.has_value()) {
    spdlog::debug("\tsunHaloSize: {}", sunHaloSize_.value());
  }
  if (sunHaloFalloff_.has_value()) {
    spdlog::debug("\tsunHaloFalloff: {}", sunHaloFalloff_.value());
  }
  spdlog::debug("++++++++");
}

::filament::LightManager::Type Light::textToLightType(const std::string& type) {
  if (type == "SUN") {
    return ::filament::LightManager::Type::SUN;
  } else if (type == "DIRECTIONAL") {
    return ::filament::LightManager::Type::DIRECTIONAL;
  } else if (type == "POINT") {
    return ::filament::LightManager::Type::POINT;
  } else if (type == "FOCUSED_SPOT") {
    return ::filament::LightManager::Type::FOCUSED_SPOT;
  } else if (type == "SPOT") {
    return ::filament::LightManager::Type::SPOT;
  }
  return ::filament::LightManager::Type::DIRECTIONAL;
}

const char* Light::lightTypeToText(::filament::LightManager::Type type) {
  switch (type) {
    case ::filament::LightManager::Type::SUN:
      return "SUN";
    case ::filament::LightManager::Type::DIRECTIONAL:
      return "DIRECTIONAL";
    case ::filament::LightManager::Type::POINT:
      return "POINT";
    case ::filament::LightManager::Type::FOCUSED_SPOT:
      return "FOCUSED_SPOT";
    case ::filament::LightManager::Type::SPOT:
      return "SPOT";
    default:
      return "DIRECTIONAL";
  }
}

}  // namespace plugin_filament_view