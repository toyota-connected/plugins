
#include "scene_controller.h"

#include <utility>

#include "logging/logging.h"

namespace plugin_filament_view {

SceneController::SceneController(
    PlatformView* platformView,
    FlutterDesktopEngineState* state,
    ::filament::Engine* engine,
    ::filament::gltfio::AssetLoader* assetLoader,
    ::filament::gltfio::ResourceLoader* resourceLoader,
    std::string flutterAssetsPath,
    std::unique_ptr<Model> model,
    std::unique_ptr<Scene> scene,
    std::unique_ptr<std::vector<std::unique_ptr<Shape>>> shapes,
    int32_t id)
    : id_(id),
      flutterAssetsPath_(std::move(flutterAssetsPath)),
      scene_(std::move(scene)),
      model_(std::move(model)),
      shapes_(std::move(shapes)) {
  modelViewer_ = std::make_unique<CustomModelViewer>(
      platformView, state, engine, assetLoader, resourceLoader);

  // TODO surfaceView.setOnTouchListener(modelViewer)
  //  surfaceView.setZOrderOnTop(true) // necessary

  glbLoader_ = std::make_unique<models::glb::GlbLoader>(
      nullptr, modelViewer_.get(), flutterAssetsPath_);
  gltfLoader_ = std::make_unique<models::gltf::GltfLoader>(
      nullptr, modelViewer_.get(), flutterAssetsPath_);

  lightManager_ = std::make_unique<LightManager>(modelViewer_.get());
  indirectLightManager_ = std::make_unique<IndirectLightManager>(
      this, modelViewer_.get(), flutterAssetsPath_);
  skyboxManager_ = std::make_unique<SkyboxManager>(this, modelViewer_.get(),
                                                   flutterAssetsPath_);
  animationManager_ = std::make_unique<AnimationManager>(modelViewer_.get());
  cameraManager_ = modelViewer_->getCameraManager();
  groundManager_ =
      std::make_unique<GroundManager>(modelViewer_.get(), flutterAssetsPath_);
  materialManager_ = std::make_unique<MaterialManager>(this, modelViewer_.get(),
                                                       flutterAssetsPath_);
  shapeManager_ = std::make_unique<ShapeManager>(modelViewer_.get(),
                                                 materialManager_.get());

  setUpGround();
  setUpCamera();
  setUpSkybox();
  setUpLight();
  setUpIndirectLight();
  setUpLoadingModel();
  setUpShapes();
}

void SceneController::setUpGround() {
  // TODO post on platform thread
  if (scene_.get() && scene_->getGround()) {
    groundManager_->createGround(scene_->getGround());
  }
}

void SceneController::setUpCamera() {
  if (!scene_.get() || !scene_->getCamera())
    return;

  cameraManager_->updateCamera(nullptr);
}

void SceneController::setUpSkybox() {
  // TODO post on platform thread
  if (!scene_.get())
    return;

  auto skybox = scene_->getSkybox();
  if (!skybox) {
    skyboxManager_->setDefaultSkybox();
    // TODO makeSurfaceViewTransparent();
  } else {
    const auto type = skybox->GetType();
    if (type.has_value()) {
      SPDLOG_DEBUG("skybox type: {}", type.value());
    }
  }

#if 0
  } else {
    when (skybox) {
      is KtxSkybox -> {
        if (!skybox.assetPath.isNullOrEmpty()) {
          skyboxManger.setSkyboxFromKTXAsset(skybox.assetPath)
        } else if (!skybox.url.isNullOrEmpty()) {
        skyboxManger.setSkyboxFromKTXUrl(skybox.url)
      }
    }
    is HdrSkybox -> {
      if (!skybox.assetPath.isNullOrEmpty()) {
        val shouldUpdateLight = skybox.assetPath == scene?.indirectLight?.assetPath
        skyboxManger.setSkyboxFromHdrAsset(
          skybox.assetPath,
          skybox.showSun ?: false,
          shouldUpdateLight,
          scene?.indirectLight?.intensity
        )
      } else if (!skybox.url.isNullOrEmpty()) {
        val shouldUpdateLight = skybox.url == scene?.indirectLight?.url
        skyboxManger.setSkyboxFromHdrUrl(
          skybox.url,
          skybox.showSun ?: false,
          shouldUpdateLight,
          scene?.indirectLight?.intensity
          )
      }
    }
    is ColoredSkybox -> {
      if (skybox.color != null) {
        skyboxManger.setSkyboxFromColor(skybox.color)
      }
    }

    }
  }
#endif
}

void SceneController::setUpLight() {
  // TODO post on platform thread
  if (scene_.get()) {
    auto light = scene_->getLight();
    if (light) {
      lightManager_->changeLight(light);
    } else {
      lightManager_->setDefaultLight();
    }
  } else {
    lightManager_->setDefaultLight();
  }
}

void SceneController::setUpIndirectLight() {
  // TODO post on platform thread
  if (scene_.get() && scene_->getIndirectLight()) {
    auto light = scene_->getIndirectLight();
    if (!light) {
      indirectLightManager_->setDefaultIndirectLight(light);
    } else {
      // TODO
    }
  }

#if 0
      when (light) {
        is KtxIndirectLight -> {
          if (!light.assetPath.isNullOrEmpty()) {
            indirectLightManger.setIndirectLightFromKtxAsset(
                light.assetPath, light.intensity
            )
          } else if (!light.url.isNullOrEmpty()) {
            indirectLightManger.setIndirectLightFromKtxUrl(light.url, light.intensity)
          }
        }
        is HdrIndirectLight -> {
          if (!light.assetPath.isNullOrEmpty()) {
            val shouldUpdateLight = light.assetPath != scene?.skybox?.assetPath

            if (shouldUpdateLight) {
              indirectLightManger.setIndirectLightFromHdrAsset(
                  light.assetPath, light.intensity
              )
            }

          } else if (!light.url.isNullOrEmpty()) {
            val shouldUpdateLight = light.url != scene?.skybox?.url
                                                                 if (shouldUpdateLight) {
              indirectLightManger.setIndirectLightFromHdrUrl(light.url, light.intensity)
            }
          }
        }
        is DefaultIndirectLight ->{
          indirectLightManger.setIndirectLight(light)
        }
        else -> {
          indirectLightManger.setDefaultIndirectLight()
        }
      }
    }
#endif
}
void SceneController::setUpLoadingModel() {
  // TODO post on platform thread
#if 0
  val result = loadModel(model)
  if (result != null && model?.fallback != null) {
    if (result is Resource.Error) {
      loadModel(model.fallback)
      setUpAnimation(model.fallback.animation)
    } else {
      setUpAnimation(model.animation)
    }
  } else {
      setUpAnimation(model?.animation)
  }
#endif
}

void SceneController::setUpShapes() {
  // TODO post on platform thread
  if (shapes_.get()) {
    shapeManager_->createShapes(*shapes_);
  }
}

}  // namespace plugin_filament_view