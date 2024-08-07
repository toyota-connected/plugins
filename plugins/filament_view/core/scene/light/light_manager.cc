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

#include "light_manager.h"
#include "core/include/color.h"

#include <filament/Color.h>
#include <filament/LightManager.h>

#include "asio/post.hpp"
#include "plugins/common/common.h"

namespace plugin_filament_view {

using ::filament::math::float3;
using ::filament::math::mat3f;
using ::filament::math::mat4f;

LightManager::LightManager() {
  SPDLOG_TRACE("++LightManager::LightManager");
  SPDLOG_TRACE("--LightManager::LightManager");
}

void LightManager::setDefaultLight() {
  SPDLOG_TRACE("++LightManager::setDefaultLight");
  auto light = std::make_unique<Light>();
  auto f = changeLight(light.get());
  f.wait();
  light.reset();
  SPDLOG_TRACE("--LightManager::setDefaultLight: {}", f.get().getMessage());
}

std::future<Resource<std::string_view>> LightManager::changeLight(
    Light* light) {
  SPDLOG_TRACE("++{}::{}", __FILE__, __FUNCTION__);

  CustomModelViewer* modelViewer = CustomModelViewer::Instance(__FUNCTION__);

  if (entityLight_.isNull()) {
    entityLight_ =
        modelViewer->getFilamentEngine()->getEntityManager().create();
  }

  const auto promise(
      std::make_shared<std::promise<Resource<std::string_view>>>());
  auto future(promise->get_future());

  if (!light) {
    promise->set_value(
        Resource<std::string_view>::Error("Light type must be provided"));
    SPDLOG_TRACE("--LightManager::changeLight");
    return future;
  }

  const asio::io_context::strand& strand_(modelViewer->getStrandContext());

  asio::post(strand_, [&, promise, light] {
    auto builder = ::filament::LightManager::Builder(light->type_);

    light->Print("Light Manager Instantiation");

    if (light->color_.has_value()) {
      auto colorValue = colorOf(light->color_.value());
      builder.color({colorValue[0], colorValue[1], colorValue[2]});
    } else if (light->colorTemperature_.has_value()) {
      auto cct = ::filament::Color::cct(light->colorTemperature_.value());
      auto red = cct.r;
      auto green = cct.g;
      auto blue = cct.b;
      builder.color({red, green, blue});
    }
    if (light->intensity_.has_value()) {
      builder.intensity(light->intensity_.value());
    }
    if (light->position_) {
      builder.position(*light->position_);
    }
    if (light->direction_) {
      // Note if Direction is 0,0,0 and you're on a spotlight
      // nothing will show.
      if (*light->direction_ == filament::math::float3(0, 0, 0) &&
          light->type_ == ::filament::LightManager::Type::SPOT) {
        spdlog::warn(
            "You've created a spot light without a direction, nothing will "
            "show. Undefined behavior.");
      }

      builder.direction(*light->direction_);
    }
    if (light->castLight_.has_value()) {
      builder.castLight(light->castLight_.value());
    }
    if (light->castShadows_.has_value()) {
      builder.castShadows(light->castShadows_.value());
    }
    if (light->falloffRadius_.has_value()) {
      builder.falloff(light->falloffRadius_.value());
    }
    if (light->spotLightConeInner_.has_value() &&
        light->spotLightConeOuter_.has_value()) {
      builder.spotLightCone(light->spotLightConeInner_.value(),
                            light->spotLightConeOuter_.value());
    }
    if (light->sunAngularRadius_.has_value()) {
      builder.sunAngularRadius(light->sunAngularRadius_.value());
    }
    if (light->sunHaloSize_.has_value()) {
      builder.sunHaloSize(light->sunHaloSize_.value());
    }
    if (light->sunHaloFalloff_.has_value()) {
      builder.sunHaloSize(light->sunHaloFalloff_.value());
    }

    CustomModelViewer* modelViewer =
        CustomModelViewer::Instance("changeLight::Lambda");
    builder.build(*modelViewer->getFilamentEngine(), entityLight_);
    auto scene = modelViewer->getFilamentScene();

    // this remove looks sus; seems like it should be the first thing
    // in the function, todo investigate.
    scene->removeEntities(&entityLight_, 1);
    scene->addEntity(entityLight_);
    promise->set_value(
        Resource<std::string_view>::Success("Light created Successfully"));
  });
  SPDLOG_TRACE("--{}::{}", __FILE__, __FUNCTION__);
  return future;
}

}  // namespace plugin_filament_view