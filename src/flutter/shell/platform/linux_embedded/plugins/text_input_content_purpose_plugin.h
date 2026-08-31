#ifndef FLUTTER_SHELL_PLATFORM_LINUX_EMBEDDED_PLUGINS_CONTENT_PURPOSE_PLUGIN_H_
#define FLUTTER_SHELL_PLATFORM_LINUX_EMBEDDED_PLUGINS_CONTENT_PURPOSE_PLUGIN_H_

#include <memory>

#include "flutter/shell/platform/common/client_wrapper/include/flutter/basic_message_channel.h"
#include "flutter/shell/platform/common/client_wrapper/include/flutter/binary_messenger.h"
#include "flutter/shell/platform/common/client_wrapper/include/flutter/method_channel.h"
#include "flutter/shell/platform/linux_embedded/window_binding_handler.h"

namespace flutter {

class TextInputContentPurposePlugin {
 public:
  TextInputContentPurposePlugin(BinaryMessenger* messenger, WindowBindingHandler* delegate);
  ~TextInputContentPurposePlugin() = default;

 private:
  void HandleMethodCall(
      const flutter::MethodCall<EncodableValue>& method_call,
      std::unique_ptr<flutter::MethodResult<EncodableValue>> result);

  std::unique_ptr<flutter::MethodChannel<EncodableValue>> channel_;
  WindowBindingHandler* delegate_;
};

}  // namespace flutter

#endif  // FLUTTER_SHELL_PLATFORM_LINUX_EMBEDDED_PLUGINS_CONTENT_PURPOSE_PLUGIN_H_
