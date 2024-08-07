
#pragma once

#include <filament/IndirectLight.h>
#include <filament/MaterialInstance.h>
#include <filament/TransformManager.h>
#include <gltfio/AssetLoader.h>
#include <gltfio/FilamentAsset.h>
#include <gltfio/ResourceLoader.h>
#include <asio/io_context_strand.hpp>

#include "core/include/resource.h"
#include "core/model/model.h"
#include "viewer/custom_model_viewer.h"
#include "viewer/settings.h"

namespace plugin_filament_view {

class CustomModelViewer;

class Model;

class ModelLoader {
 public:
  ModelLoader(CustomModelViewer* modelViewer);

  /**
   * Frees all entities associated with the most recently-loaded model.
   */
  ~ModelLoader();

  void destroyModel();

  /**
   * Loads a monolithic binary glTF and populates the Filament scene.
   */
  void loadModelGlb(const std::vector<uint8_t>& buffer,
                    const ::filament::float3* centerPosition,
                    float scale,
                    bool transformToUnitCube = false);

  /**
   * Loads a JSON-style glTF file and populates the Filament scene.
   * The given callback is triggered for each requested resource.
   */
  void loadModelGltf(const std::vector<uint8_t>& buffer,
                     const ::filament::float3* centerPosition,
                     float scale,
                     std::function<const ::filament::backend::BufferDescriptor&(
                         std::string uri)>& callback,
                     bool transform = false);

  filament::gltfio::FilamentAsset* getAsset() const { return asset_; };

  std::optional<::filament::math::mat4f> getModelTransform();

  /**
   * Removes the transformation that was set up via transformToUnitCube.
   */
  void clearRootTransform();

  void transformToUnitCube(const ::filament::float3* centerPoint, float scale);

  void updateScene();

  std::future<Resource<std::string_view>> loadGlbFromAsset(
      const std::string& path,
      float scale,
      const ::filament::float3* centerPosition,
      bool isFallback = false);

  std::future<Resource<std::string_view>> loadGlbFromUrl(
      std::string url,
      float scale,
      const ::filament::float3* centerPosition,
      bool isFallback = false);

  std::future<Resource<std::string_view>> loadGltfFromAsset(
      const std::string& path,
      const std::string& pre_path,
      const std::string& post_path,
      float scale,
      const ::filament::float3* centerPosition,
      bool isFallback = false);

  std::future<Resource<std::string_view>> loadGltfFromUrl(
      const std::string& url,
      float scale,
      const ::filament::float3* centerPosition,
      bool isFallback = false);

  friend class CustomModelViewer;

 private:
  CustomModelViewer* modelViewer_;
  ::filament::Engine* engine_;
  const asio::io_context::strand& strand_;
  std::vector<filament::gltfio::FilamentInstance*> instances_;

  std::string assetPath_;
  utils::Entity sunlight_;
  ::filament::gltfio::AssetLoader* assetLoader_;
  ::filament::gltfio::MaterialProvider* materialProvider_;
  ::filament::gltfio::ResourceLoader* resourceLoader_;

  // Properties that can be changed from the application.
  filament::gltfio::FilamentAsset* asset_ = nullptr;
  filament::gltfio::FilamentInstance* instance_ = nullptr;
  filament::IndirectLight* indirectLight_ = nullptr;

  utils::Entity readyRenderables_[128];

  ::filament::viewer::Settings settings_;
  std::vector<float> morphWeights_;
  // TODO  ::filament::gltfio::NodeManager::SceneMask visibleScenes_;

  void fetchResources(
      ::filament::gltfio::FilamentAsset* asset,
      const std::function<uint8_t*(std::string asset)> callback);

  ::filament::math::mat4f inline fitIntoUnitCube(
      const ::filament::Aabb& bounds,
      ::filament::math::float3 offset);

  void updateRootTransform(bool autoScaleEnabled);

  void populateScene(::filament::gltfio::FilamentAsset* asset);

  bool isRemoteMode() const { return asset_ == nullptr; }

  void removeAsset();

  ::filament::mat4f getTransform();

  void setTransform(::filament::mat4f mat);

  std::vector<char> buffer_;
  void handleFile(
      const std::vector<uint8_t>& buffer,
      const std::string& fileSource,
      float scale,
      const ::filament::float3* centerPosition,
      bool isFallback,
      const std::shared_ptr<std::promise<Resource<std::string_view>>>& promise);
};
}  // namespace plugin_filament_view
