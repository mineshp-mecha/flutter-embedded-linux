#include "flutter/shell/platform/linux_embedded/plugins/text_input_content_purpose_plugin.h"

#include "flutter/shell/platform/common/client_wrapper/include/flutter/standard_method_codec.h"

#if defined(DISPLAY_BACKEND_TYPE_X11)
#undef Success
#endif

namespace flutter {

namespace {
constexpr char kChannelName[] = "mechanix/text_input_content_purpose";
constexpr char kSetPurposeMethod[] = "setTextInputContentPurpose";
constexpr char kPurposeKey[] = "purpose";
}  // namespace

TextInputContentPurposePlugin::TextInputContentPurposePlugin(BinaryMessenger* messenger,
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

void TextInputContentPurposePlugin::HandleMethodCall(
    const MethodCall<EncodableValue>& method_call,
    std::unique_ptr<MethodResult<EncodableValue>> result) {
  if (method_call.method_name() != kSetPurposeMethod) {
    result->NotImplemented();
    return;
  }

  const auto* arguments = std::get_if<std::string>(method_call.arguments());
  if (!arguments) {
    result->Error("Argument error", "Missing or unsupported purpose argument type.");
    return;
  }

  delegate_->SetTextInputContentPurposeOverride(*arguments);
  result->Success();
}
}  // namespace flutter
