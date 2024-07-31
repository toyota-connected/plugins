// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// Autogenerated from Pigeon (v16.0.3), do not edit directly.
// See also: https://pub.dev/packages/pigeon

#undef _HAS_EXCEPTIONS

#include "messages.g.h"

#include <flutter/basic_message_channel.h>
#include <flutter/binary_messenger.h>
#include <flutter/encodable_value.h>
#include <flutter/standard_message_codec.h>

#include <optional>
#include <string>

namespace video_player_linux {
using flutter::BasicMessageChannel;
using flutter::CustomEncodableValue;
using flutter::EncodableList;
using flutter::EncodableMap;
using flutter::EncodableValue;

FlutterError CreateConnectionError(const std::string& channel_name) {
  return FlutterError(
      "channel-error",
      "Unable to establish connection on channel: '" + channel_name + "'.",
      EncodableValue(""));
}

/// The codec used by LinuxVideoPlayerApi.
const flutter::StandardMessageCodec& VideoPlayerApi::GetCodec() {
  return flutter::StandardMessageCodec::GetInstance(
      &flutter::StandardCodecSerializer::GetInstance());
}

// Sets up an instance of `LinuxVideoPlayerApi` to handle messages through the
// `binary_messenger`.
void VideoPlayerApi::SetUp(flutter::BinaryMessenger* binary_messenger,
                           VideoPlayerApi* api) {
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(
        binary_messenger,
        "dev.flutter.pigeon.video_player_linux.LinuxVideoPlayerApi."
        "initialize",
        &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler(
          [api](const EncodableValue& /* message */,
                const flutter::MessageReply<EncodableValue>& reply) {
            try {
              std::optional<FlutterError> output = api->Initialize();
              if (output.has_value()) {
                reply(WrapError(output.value()));
                return;
              }
              EncodableList wrapped;
              wrapped.push_back(EncodableValue());
              reply(EncodableValue(std::move(wrapped)));
            } catch (const std::exception& exception) {
              reply(WrapError(exception.what()));
            }
          });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(
        binary_messenger,
        "dev.flutter.pigeon.video_player_linux.LinuxVideoPlayerApi.create",
        &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler(
          [api](const EncodableValue& message,
                const flutter::MessageReply<EncodableValue>& reply) {
            try {
              const auto& args = std::get<EncodableList>(message);
              const auto& encodable_asset_arg = args.at(0);
              const auto* asset_arg =
                  std::get_if<std::string>(&encodable_asset_arg);
              const auto& encodable_uri_arg = args.at(1);
              const auto* uri_arg =
                  std::get_if<std::string>(&encodable_uri_arg);
              const auto& encodable_http_headers_arg = args.at(2);
              if (encodable_http_headers_arg.IsNull()) {
                reply(WrapError("http_headers_arg unexpectedly null."));
                return;
              }
              const auto& http_headers_arg =
                  std::get<EncodableMap>(encodable_http_headers_arg);
              ErrorOr<int64_t> output =
                  api->Create(asset_arg, uri_arg, http_headers_arg);
              if (output.has_error()) {
                reply(WrapError(output.error()));
                return;
              }
              EncodableList wrapped;
              wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
              reply(EncodableValue(std::move(wrapped)));
            } catch (const std::exception& exception) {
              reply(WrapError(exception.what()));
            }
          });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(
        binary_messenger,
        "dev.flutter.pigeon.video_player_linux.LinuxVideoPlayerApi.dispose",
        &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler(
          [api](const EncodableValue& message,
                const flutter::MessageReply<EncodableValue>& reply) {
            try {
              const auto& args = std::get<EncodableList>(message);
              const auto& encodable_texture_id_arg = args.at(0);
              if (encodable_texture_id_arg.IsNull()) {
                reply(WrapError("texture_id_arg unexpectedly null."));
                return;
              }
              const int64_t texture_id_arg =
                  encodable_texture_id_arg.LongValue();
              std::optional<FlutterError> output = api->Dispose(texture_id_arg);
              if (output.has_value()) {
                reply(WrapError(output.value()));
                return;
              }
              EncodableList wrapped;
              wrapped.push_back(EncodableValue());
              reply(EncodableValue(std::move(wrapped)));
            } catch (const std::exception& exception) {
              reply(WrapError(exception.what()));
            }
          });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(
        binary_messenger,
        "dev.flutter.pigeon.video_player_linux.LinuxVideoPlayerApi."
        "setLooping",
        &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler(
          [api](const EncodableValue& message,
                const flutter::MessageReply<EncodableValue>& reply) {
            try {
              const auto& args = std::get<EncodableList>(message);
              const auto& encodable_texture_id_arg = args.at(0);
              if (encodable_texture_id_arg.IsNull()) {
                reply(WrapError("texture_id_arg unexpectedly null."));
                return;
              }
              const int64_t texture_id_arg =
                  encodable_texture_id_arg.LongValue();
              const auto& encodable_is_looping_arg = args.at(1);
              if (encodable_is_looping_arg.IsNull()) {
                reply(WrapError("is_looping_arg unexpectedly null."));
                return;
              }
              const auto& is_looping_arg =
                  std::get<bool>(encodable_is_looping_arg);
              std::optional<FlutterError> output =
                  api->SetLooping(texture_id_arg, is_looping_arg);
              if (output.has_value()) {
                reply(WrapError(output.value()));
                return;
              }
              EncodableList wrapped;
              wrapped.push_back(EncodableValue());
              reply(EncodableValue(std::move(wrapped)));
            } catch (const std::exception& exception) {
              reply(WrapError(exception.what()));
            }
          });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(
        binary_messenger,
        "dev.flutter.pigeon.video_player_linux.LinuxVideoPlayerApi."
        "setVolume",
        &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler(
          [api](const EncodableValue& message,
                const flutter::MessageReply<EncodableValue>& reply) {
            try {
              const auto& args = std::get<EncodableList>(message);
              const auto& encodable_texture_id_arg = args.at(0);
              if (encodable_texture_id_arg.IsNull()) {
                reply(WrapError("texture_id_arg unexpectedly null."));
                return;
              }
              const int64_t texture_id_arg =
                  encodable_texture_id_arg.LongValue();
              const auto& encodable_volume_arg = args.at(1);
              if (encodable_volume_arg.IsNull()) {
                reply(WrapError("volume_arg unexpectedly null."));
                return;
              }
              const auto& volume_arg = std::get<double>(encodable_volume_arg);
              std::optional<FlutterError> output =
                  api->SetVolume(texture_id_arg, volume_arg);
              if (output.has_value()) {
                reply(WrapError(output.value()));
                return;
              }
              EncodableList wrapped;
              wrapped.push_back(EncodableValue());
              reply(EncodableValue(std::move(wrapped)));
            } catch (const std::exception& exception) {
              reply(WrapError(exception.what()));
            }
          });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(
        binary_messenger,
        "dev.flutter.pigeon.video_player_linux.LinuxVideoPlayerApi."
        "setPlaybackSpeed",
        &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler(
          [api](const EncodableValue& message,
                const flutter::MessageReply<EncodableValue>& reply) {
            try {
              const auto& args = std::get<EncodableList>(message);
              const auto& encodable_texture_id_arg = args.at(0);
              if (encodable_texture_id_arg.IsNull()) {
                reply(WrapError("texture_id_arg unexpectedly null."));
                return;
              }
              const int64_t texture_id_arg =
                  encodable_texture_id_arg.LongValue();
              const auto& encodable_speed_arg = args.at(1);
              if (encodable_speed_arg.IsNull()) {
                reply(WrapError("speed_arg unexpectedly null."));
                return;
              }
              const auto& speed_arg = std::get<double>(encodable_speed_arg);
              std::optional<FlutterError> output =
                  api->SetPlaybackSpeed(texture_id_arg, speed_arg);
              if (output.has_value()) {
                reply(WrapError(output.value()));
                return;
              }
              EncodableList wrapped;
              wrapped.push_back(EncodableValue());
              reply(EncodableValue(std::move(wrapped)));
            } catch (const std::exception& exception) {
              reply(WrapError(exception.what()));
            }
          });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(
        binary_messenger,
        "dev.flutter.pigeon.video_player_linux.LinuxVideoPlayerApi.play",
        &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler(
          [api](const EncodableValue& message,
                const flutter::MessageReply<EncodableValue>& reply) {
            try {
              const auto& args = std::get<EncodableList>(message);
              const auto& encodable_texture_id_arg = args.at(0);
              if (encodable_texture_id_arg.IsNull()) {
                reply(WrapError("texture_id_arg unexpectedly null."));
                return;
              }
              const int64_t texture_id_arg =
                  encodable_texture_id_arg.LongValue();
              std::optional<FlutterError> output = api->Play(texture_id_arg);
              if (output.has_value()) {
                reply(WrapError(output.value()));
                return;
              }
              EncodableList wrapped;
              wrapped.push_back(EncodableValue());
              reply(EncodableValue(std::move(wrapped)));
            } catch (const std::exception& exception) {
              reply(WrapError(exception.what()));
            }
          });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(
        binary_messenger,
        "dev.flutter.pigeon.video_player_linux.LinuxVideoPlayerApi."
        "getPosition",
        &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler(
          [api](const EncodableValue& message,
                const flutter::MessageReply<EncodableValue>& reply) {
            try {
              const auto& args = std::get<EncodableList>(message);
              const auto& encodable_texture_id_arg = args.at(0);
              if (encodable_texture_id_arg.IsNull()) {
                reply(WrapError("texture_id_arg unexpectedly null."));
                return;
              }
              const int64_t texture_id_arg =
                  encodable_texture_id_arg.LongValue();
              ErrorOr<int64_t> output = api->GetPosition(texture_id_arg);
              if (output.has_error()) {
                reply(WrapError(output.error()));
                return;
              }
              EncodableList wrapped;
              wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
              reply(EncodableValue(std::move(wrapped)));
            } catch (const std::exception& exception) {
              reply(WrapError(exception.what()));
            }
          });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(
        binary_messenger,
        "dev.flutter.pigeon.video_player_linux.LinuxVideoPlayerApi.seekTo",
        &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler(
          [api](const EncodableValue& message,
                const flutter::MessageReply<EncodableValue>& reply) {
            try {
              const auto& args = std::get<EncodableList>(message);
              const auto& encodable_texture_id_arg = args.at(0);
              if (encodable_texture_id_arg.IsNull()) {
                reply(WrapError("texture_id_arg unexpectedly null."));
                return;
              }
              const int64_t texture_id_arg =
                  encodable_texture_id_arg.LongValue();
              const auto& encodable_position_arg = args.at(1);
              if (encodable_position_arg.IsNull()) {
                reply(WrapError("position_arg unexpectedly null."));
                return;
              }
              const int64_t position_arg = encodable_position_arg.LongValue();
              std::optional<FlutterError> output =
                  api->SeekTo(texture_id_arg, position_arg);
              if (output.has_value()) {
                reply(WrapError(output.value()));
                return;
              }
              EncodableList wrapped;
              wrapped.push_back(EncodableValue());
              reply(EncodableValue(std::move(wrapped)));
            } catch (const std::exception& exception) {
              reply(WrapError(exception.what()));
            }
          });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(
        binary_messenger,
        "dev.flutter.pigeon.video_player_linux.LinuxVideoPlayerApi.pause",
        &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler(
          [api](const EncodableValue& message,
                const flutter::MessageReply<EncodableValue>& reply) {
            try {
              const auto& args = std::get<EncodableList>(message);
              const auto& encodable_texture_id_arg = args.at(0);
              if (encodable_texture_id_arg.IsNull()) {
                reply(WrapError("texture_id_arg unexpectedly null."));
                return;
              }
              const int64_t texture_id_arg =
                  encodable_texture_id_arg.LongValue();
              std::optional<FlutterError> output = api->Pause(texture_id_arg);
              if (output.has_value()) {
                reply(WrapError(output.value()));
                return;
              }
              EncodableList wrapped;
              wrapped.push_back(EncodableValue());
              reply(EncodableValue(std::move(wrapped)));
            } catch (const std::exception& exception) {
              reply(WrapError(exception.what()));
            }
          });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
}

EncodableValue VideoPlayerApi::WrapError(std::string_view error_message) {
  return EncodableValue(
      EncodableList{EncodableValue(std::string(error_message)),
                    EncodableValue("Error"), EncodableValue()});
}

EncodableValue VideoPlayerApi::WrapError(const FlutterError& error) {
  return EncodableValue(EncodableList{EncodableValue(error.code()),
                                      EncodableValue(error.message()),
                                      error.details()});
}

}  // namespace video_player_linux