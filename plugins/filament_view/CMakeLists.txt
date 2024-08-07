#
# Copyright 2023 Toyota Connected North America
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

include_guard()

if (NOT EXISTS ${FILAMENT_INCLUDE_DIR})
    message(FATAL_ERROR "${FILAMENT_INCLUDE_DIR} does not exist")
endif ()
if (NOT EXISTS ${FILAMENT_LINK_LIBRARIES_DIR})
    message(FATAL_ERROR "${FILAMENT_LINK_LIBRARIES_DIR} does not exist")
endif ()

set(CMAKE_THREAD_PREFER_PTHREAD ON)
include(FindThreads)

add_library(filament INTERFACE)
target_include_directories(filament INTERFACE ${FILAMENT_INCLUDE_DIR} ${FILAMENT_INCLUDE_DIR}/filament)
target_link_directories(filament INTERFACE ${FILAMENT_LINK_LIBRARIES_DIR})
target_link_libraries(filament INTERFACE
        libbackend.a
        libbluevk.a
        libdracodec.a
        libfilamat.a
        libfilameshio.a
        libgltfio_core.a
        libimage.a
        libshaders.a
        libuberarchive.a
        libviewer.a
        libbasis_transcoder.a
        libcamutils.a
        libfilabridge.a
        libfilament.a
        libgeometry.a
        libibl.a
        libimageio.a
        libmeshoptimizer.a
        libsmol-v.a
        libuberzlib.a
        libvkshaders.a
        libcivetweb.a
        libtinyexr.a
        libfilaflat.a
        libfilament-iblprefilter.a
        libgltfio.a
        libibl-lite.a
        libktxreader.a
        libmikktspace.a
        libpng.a
        libstb.a
        libutils.a
        libzstd.a
        # libmatdbg.a # required for linking with debug libs

        z
        Threads::Threads
)

add_library(plugin_filament_view STATIC
        filament_view_plugin_c_api.cc
        filament_view_plugin.cc
        messages.g.cc

        filament_scene.cc
        core/scene/scene_controller.cc

        core/model/animation/animation.cc
        core/model/animation/animation_manager.cc
        core/model/loader/model_loader.cc
        core/model/model.cc
        core/scene/camera/camera.cc
        core/scene/camera/camera_manager.cc
        core/scene/camera/exposure.cc
        core/scene/camera/lens_projection.cc
        core/scene/camera/projection.cc
        core/scene/geometry/direction.cc
        core/scene/geometry/position.cc
        core/scene/geometry/size.cc
        core/scene/ground.cc
        core/scene/ground_manager.cc
        core/scene/indirect_light/indirect_light.cc
        core/scene/indirect_light/indirect_light_manager.cc
        core/utils/hdr_loader.cc
        core/scene/light/light.cc
        core/scene/light/light_manager.cc
        core/scene/material/loader/material_loader.cc
        core/scene/material/loader/texture_loader.cc
        core/scene/material/material_manager.cc
        core/scene/material/model/material.cc
        core/scene/material/model/material_parameter.cc
        core/scene/material/texture/texture.cc
        core/scene/material/texture/texture_sampler.cc
        core/scene/material/utils/material_instance.cc
        core/scene/skybox/skybox.cc
        core/scene/skybox/skybox_manager.cc
        core/scene/scene.cc
        core/shapes/shape.cc
        core/shapes/shape_manager.cc
        core/utils/deserialize.cc
        viewer/custom_model_viewer.cc
)

target_include_directories(plugin_filament_view PUBLIC
        .
        include
)

target_link_libraries(plugin_filament_view PUBLIC
        asio
        filament
        flutter
        platform_homescreen
        plugin_common
        plugin_common_curl
)

#
# Filament MVP Example
#
pkg_check_modules(SDL2 IMPORTED_TARGET sdl2)
if (SDL2_FOUND)
    add_executable(filament-mvp test/mvp.cc)
    target_link_libraries(filament-mvp PUBLIC
            PkgConfig::SDL2
            filament
            ${FILAMENT_LINK_LIBRARIES_DIR}/../../../../third_party/spirv-tools/source/opt/libSPIRV-Tools-opt.a
            ${FILAMENT_LINK_LIBRARIES_DIR}/../../../../third_party/spirv-cross/tnt/libspirv-cross-msl.a
    )
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(filament-mvp PRIVATE ${CONTEXT_COMPILE_OPTIONS})
        target_link_options(filament-mvp PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fuse-ld=lld -l:libc++.a -l:libc++abi.a -static-libgcc -lc -lm -v>)
    endif ()
    add_sanitizers(filament-mvp)

    if (IPO_SUPPORT_RESULT)
        set_property(TARGET filament-mvp PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif ()
endif ()
