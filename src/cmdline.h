#ifndef CMDLINE_DSLINK_CMDLINE_H
#define CMDLINE_DSLINK_CMDLINE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/strand.hpp>

#include "dslink.h"
#include "util/app.h"

#include "commands/command_factory.h"

#define CMD_MAX_LENGTH 4096

using namespace dsa;


class CmdLine {
 private:
  std::shared_ptr<App> app;
  ref_<DsLink> link;
  std::string current_path;
  CommandFactory command_factory;

  std::unique_ptr<boost::asio::io_service::strand> strand;

  bool get_input();

 public:
  CmdLine(std::shared_ptr<App> app, ref_<DsLink> dslink);

  void run();
};

#endif //CMDLINE_DSLINK_CMDLINE_H