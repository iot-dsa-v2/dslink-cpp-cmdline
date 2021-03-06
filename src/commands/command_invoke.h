
#ifndef CMDLINE_DSLINK_COMMAND_INVOKE_H
#define CMDLINE_DSLINK_COMMAND_INVOKE_H

#include "core/command.h"

#include "message/response/invoke_response_message.h"

class CommandInvoke: public Command {
 private:
  ref_<IncomingInvokeStream> stream;
  ref_<const InvokeResponseMessage> message;
  std::string target_path;

 public:
  using Command::Command;

 protected:
  std::vector<int> _available_args_num_options() override;
  const char* _get_usage_info() override;
  COMMAND_RETURN_TYPE _execute() override;
  void _clear() override;
  void _print() override;
};

#endif //CMDLINE_DSLINK_COMMAND_INVOKE_H
