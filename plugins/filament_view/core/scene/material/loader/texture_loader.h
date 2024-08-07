
#pragma once

#include "viewer/custom_model_viewer.h"

#include <future>

#include <filament/Texture.h>
#include <image/LinearImage.h>

#include <asio/io_context_strand.hpp>

#include "core/scene/material/texture/texture.h"

namespace plugin_filament_view {

class CustomModelViewer;

class Texture;

class TextureLoader {
 public:
  TextureLoader();
  ~TextureLoader() = default;

  static ::filament::Texture* loadTexture(Texture* texture);

  // Disallow copy and assign.
  TextureLoader(const TextureLoader&) = delete;
  TextureLoader& operator=(const TextureLoader&) = delete;

 private:
  static ::filament::Texture* createTextureFromImage(
      Texture::TextureType type,
      std::unique_ptr<image::LinearImage> image);

  static ::filament::Texture* loadTextureFromStream(std::istream* ins,
                                                    Texture::TextureType type,
                                                    const std::string& name);

  static ::filament::Texture* loadTextureFromUrl(const std::string& url,
                                                 Texture::TextureType type);
};
}  // namespace plugin_filament_view