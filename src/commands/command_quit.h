
#ifndef CMDLINE_DSLINK_COMMAND_QUIT_H
#define CMDLINE_DSLINK_COMMAND_QUIT_H

#include "command.h"

class CommandQuit : public Command{
 public:
  using Command::Command;

 protected:
  void _print_usage_info() override;
  COMMAND_RETURN_TYPE _execute() override;
  void _clear() override;
  void _print() override;
};

#endif //CMDLINE_DSLINK_COMMAND_QUIT_H
