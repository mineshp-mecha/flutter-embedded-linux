// Copyright 2023 Sony Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flutter/shell/platform/linux_embedded/plugins/keyboard_purpose_plugin.h"

#include "flutter/shell/platform/common/client_wrapper/include/flutter/standard_method_codec.h"

#if defined(DISPLAY_BACKEND_TYPE_X11)
#undef Success
#endif

namespace flutter {

namespace {
constexpr char kChannelName[] = "mechanix/keyboard_purpose";
constexpr char kSetPurposeMethod[] = "setPurpose";
constexpr char kPurposeKey[] = "purpose";
}  // namespace

KeyboardPurposePlugin::KeyboardPurposePlugin(BinaryMessenger* messenger,
                                             WindowBindingHandler* delegate)
    : channel_(std::make_unique<MethodChannel<EncodableValue>>(
          messenger,
          kChannelName,
          &StandardMethodCodec::GetInstance())),
      delegate_(delegate) {
  channel_->SetMethodCallHandler(
      [this](const MethodCall<EncodableValue>& call,
             std::unique_ptr<MethodResult<EncodableValue>> result) {
        HandleMethodCall(call, std::move(result));
      });
}

void KeyboardPurposePlugin::HandleMethodCall(
    const MethodCall<EncodableValue>& method_call,
    std::unique_ptr<MethodResult<EncodableValue>> result) {
  const std::string& method = method_call.method_name();
  if (method.compare(kSetPurposeMethod) != 0) {
    result->NotImplemented();
    return;
  }

  if (!method_call.arguments()) {
    result->Error("Argument error", "Missing purpose argument.");
    return;
  }

  const auto& arguments = *method_call.arguments();

  if (std::holds_alternative<std::string>(arguments)) {
    delegate_->SetKeyboardPurposeOverride(std::get<std::string>(arguments));
    result->Success();
    return;
  }

  if (std::holds_alternative<EncodableMap>(arguments)) {
    const auto& map = std::get<EncodableMap>(arguments);
    const auto purpose_it = map.find(EncodableValue(std::string(kPurposeKey)));
    if (purpose_it == map.end()) {
      result->Error("Argument error", "Missing purpose value.");
      return;
    }
    const auto& purpose = std::get<std::string>(purpose_it->second);
    delegate_->SetKeyboardPurposeOverride(purpose);
    result->Success();
    return;
  }

  result->Error("Argument error", "Unsupported purpose argument type.");
}

}  // namespace flutter
