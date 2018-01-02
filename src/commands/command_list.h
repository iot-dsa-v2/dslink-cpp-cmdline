
#ifndef CMDLINE_DSLINK_COMMAND_LIST_H
#define CMDLINE_DSLINK_COMMAND_LIST_H

#include "core/command.h"

class CommandList: public Command {
 private:
  ref_<IncomingListCache> incoming_list_cache;
  IncomingListCache cache;
  std::vector<std::string> changes;
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

#endif //CMDLINE_DSLINK_COMMAND_LIST_H
