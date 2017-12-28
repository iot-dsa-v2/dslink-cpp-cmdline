#include "cmdline.h"

#include <boost/algorithm/string.hpp>

CmdLine::CmdLine(std::shared_ptr<App> app, ref_<DsLink> dslink) {
  this->app = app;
  this->strand.reset(app->new_strand());
  this->link = dslink;

  Command::current_path = "";
  Command::link = dslink;
}


void CmdLine::run() {
  strand->post([&](){
    while(this->get_input()){}
    if(link != nullptr) link->strand->post([this](){link->destroy();});
  });

  app->close();
  app->wait();
}


bool CmdLine::get_input() {
  char line[CMD_MAX_LENGTH];

  // Print current path and wait
  std::cout<<"> "<<Command::current_path<<" ";

  // 1. Input taking
  if (!fgets(line, CMD_MAX_LENGTH, stdin)) return false;
  std::string line_str(line);

  // If user press enter without anything
  if(line_str[0] == '\n') return true;

  // 2. Get Command
  auto cmd = command_factory.get_command(line_str);

  // 3. Execute Command
  cmd->execute();

  auto return_ = cmd->get_return_type();

  // 4. Command says we need wait he was executing
  if(return_ == COMMAND_RETURN_WAIT) {
    while (std::cin.get() != '\n') {}
  }

  // 5. Clear
  cmd->clear();

  return return_ != COMMAND_RETURN_TERMINATE;
}

